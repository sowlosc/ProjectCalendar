#include "agenda.h"
#include "rdv.h"

Agenda* Agenda::instance = 0;

Agenda& Agenda::operator<<(Evenement& evt)
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == &evt)
            throw CalendarException("Cet évènement existe déjà");


    if(!isLibre(QDateTime(evt.getDate(),evt.getHoraire()),QDateTime(evt.getDate(),evt.getHoraire()).addSecs(evt.getDuree().getDureeEnMinutes()*60)))
        throw CalendarException("Un évènement est déjà programmé à ce moment");

    if(evt.isProgrammationTache())
        dynamic_cast<ProgrammationTache*>(&evt)->getTache()->setProgrammed(true);


    events.push_back(evt.clone());
    Observable::notifier();
    return *this;
}


Agenda& Agenda::operator>>(Evenement *evt)
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == evt){
            std::cout << "Agende :::: suppression evt "<<evt->getDate().toString().toStdString()<<" - "<<evt->getHoraire().toString().toStdString() <<"\n";

            if(evt->isProgrammationTache())
                dynamic_cast<ProgrammationTache*>(evt)->getTache()->setProgrammed(false);

            delete evt;
            events.erase(it);
            //Observable::notifier();
            return *this;
        }
    throw CalendarException("Erreur, Agenda, cet evenement n'existe pas");
}


Agenda::~Agenda()
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        delete *it;
}

std::vector<ProgrammationTache*> Agenda::getProgrammationTache(const Tache* t)
{
    std::vector<ProgrammationTache*> tab;
    for(iterator it = begin() ; it != end() ; ++it)
    {
        if((*it).isProgrammationTache())
        {
            ProgrammationTache* prog = dynamic_cast<ProgrammationTache*>(&(*it));
            if( prog->getTache() == t)
                tab.push_back(prog);

        }
    }
    return tab;
}

bool Agenda::isLibre(const QDateTime& debut, const QDateTime &fin)
{
    for(iterator it=begin(); it!= end(); ++it)
    {
        QDateTime deb2((*it).getDate(),(*it).getHoraire());
        QDateTime fin2((*it).getDate(),(*it).getHoraire().addSecs((*it).getDuree().getDureeEnMinutes()*60));

        if( !((debut<deb2 && fin<=deb2) || (debut>=fin2 && fin>fin2)))
            return false;
    }
    return true;
}


void Agenda::save(const QString &f)
{
     QFile newfile(f);
     if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
         throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("evenements");
     for(iterator it = begin() ; it!= end(); ++it)
     {
         (*it).toXml(stream);
     }
     stream.writeEndElement();
     stream.writeEndDocument();
     newfile.close();
}


void Agenda::load(const QString &f)
{
    QFile fin(f);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier tâches");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {

            if(xml.name() == "evenements")
                continue;
            else if(xml.name() == "evenement1j")
                this->operator <<(*Evenement1j::getFromXml(xml));
            else if(xml.name() == "evenementpj")
                this->operator <<(*EvenementPj::getFromXml(xml));
            else if(xml.name() == "rdv")
                this->operator <<(*Rdv::getFromXml(xml));
            else if(xml.name() == "programmationtache")
                this->operator <<(*ProgrammationTache::getFromXml(xml));
            else if(xml.name() == "programmationpartietache")
                this->operator <<(*ProgrammationPartieTache::getFromXml(xml));
           }
        //xml.readNext();
        }
    // Error handling.
    if(xml.hasError()) {
        throw CalendarException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";*/
}


