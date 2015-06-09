#include "projet.h"
#include <QtXml>
#include "tacheunitaire.h"
#include "projetmanager.h"

Projet::~Projet()
{
    for(iterator it=begin(); it != end(); ++it)
    {
        delete &(*it);
    }
}

Projet& Projet::ajouterTache(Tache *t)
{
    if(taches.find(t->getId()) != taches.end())
        throw CalendarException("Identifiant déjà existant");
    if(t->getDisponibilite()<disponibilite)
        throw CalendarException("Disponibilité inférieure à celle du projet");
    if(t->getEcheance()>echeance)
        throw CalendarException("Date d'échéance dupérieure à celle du projet");

    taches[t->getId()] = t;
    notifier();
    return *this;
}

void Projet::retirerTache(Tache *t)
{
    if(taches.find(t->getId()) != taches.end()){
        delete taches[t->getId()];
        taches.erase(t->getId());
        notifier();
    }
}
void Projet::retirerTache(const QString id)
{
    std::map<QString, Tache*>* parent = getTacheMap(id);
    if(parent)
    {
        delete parent->at(id);
        parent->erase(id);
        ProjetManager::getInstance().notifier();
    }
}



Tache* Projet::getTache(const QString &id)
{
   if(taches.find(id) != taches.end())
       return taches[id];
   else
   {
       for(Projet::iterator it = this->begin() ; it != this->end() ; ++it)
       {
           if((*it).isComposite())
           {
               Tache* result = dynamic_cast<TacheComposite&>(*it).getSousTache(id);
               if(result)
                       return result;
           }
       }
       return 0;
   }
}
bool Projet::contientTache(const Tache *t)
{
    if(taches.find(t->getId()) != taches.end() && taches[t->getId()] == t)
        return true;
    else
    {
        for(Projet::iterator it = this->begin() ; it != this->end() ; ++it)
        {
            if((*it).isComposite())
            {
                bool result = dynamic_cast<TacheComposite&>(*it).contientSousTache(t);
                if(result)
                        return result;
            }
        }
        return false;
    }
}


std::map<QString, Tache*>* Projet::getTacheMap(const QString &id)
{
    if(taches.find(id) != taches.end())
        return &taches;
    else
    {
        for(Projet::iterator it = begin() ; it != end() ; ++it)
        {
            if((*it).isComposite())
            {
                TacheComposite* tc = dynamic_cast<TacheComposite*>(&(*it));
                std::map<QString, Tache*>* result = tc->getTacheMap(id);
                if(result)
                    return result;
            }
        }
        return 0;
    }
}



// ---------------------------------- fonction d'affichage des projet en console -------------------
void Projet::affTache(Tache* t)
{
    if(t->isComposite())
    {
        std::cout << "tache composite : " << t->getDescription().toStdString() <<"\n";
        TacheComposite *tc = dynamic_cast<TacheComposite*>(t);
        for(TacheComposite::iterator it = tc->begin()  ;it != tc->end() ; ++it)
            affTache(&(*it));
    }else
        std::cout<<"tache : "<<t->getDescription().toStdString()<<"\n";
}


void Projet::describe()
{
    std::cout << "\n\n======= Description projet "<<getTitre().toStdString()<<" =======\n";
    for(Projet::iterator it = this->begin() ; it != this->end() ; ++it)
    {
        std::cout<<"----->\n";
        affTache(&(*it));
    }
    std::cout<<"\n\n";
}

//------------------------------------------------------------------------------------------


QString Projet::toString() const
{
    std::stringstream ss;

    ss << "<html><body><h2 align=\"center\">     " << getTitre().toStdString() << "</h2>";
    ss << "<table align=\"center\" cellpadding=\"4\" >";
    ss << "<tr><td>type</td><td>projet</td></tr>";
    ss << "<tr><td>date disponibilité </td><td> " << getDisponibilite().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>date échéance </td><td> " << getEcheance().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>description</b></td><td> " << getDescription().toStdString()<< "</td></tr>";
    ss << "</table></body></html>";

    return ss.str().c_str();
}

void Projet::toXml(QXmlStreamWriter& s) const
{
    s.writeStartElement("projet");
    s.writeTextElement("titre",getTitre());
    s.writeTextElement("disponibilite",getDisponibilite().toString(Qt::ISODate));
    s.writeTextElement("echeance",getEcheance().toString(Qt::ISODate));
    s.writeStartElement("taches");
    for(const_iterator it = begin() ; it != end() ; ++it)
        (*it).toXml(s);
    s.writeEndElement();
    s.writeEndElement();
}

void Projet::save(const QString &f)
{
    file=f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for(iterator it = begin() ; it!= end(); ++it)
    {
        (*it).toXml(stream);
    }
    stream.writeEndElement();
    newfile.close();

}

void Projet::load(const QString &f)
{
    std::cout << "======> \n debut des taches du projet\n";
    //qDebug()<<"debut load\n";
   //this->~TacheManager();
   file=f;
   QFile fin(file);
   // If we can't open it, let's show an error message.
   if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
       throw CalendarException("Erreur ouverture fichier tâches");
   }
   // QXmlStreamReader takes any QIODevice.
   QXmlStreamReader xml(&fin);
   //qDebug()<<"debut fichier\n";
   // We'll parse the XML until we reach end of it.
   while(!xml.atEnd() && !xml.hasError())
   {
       // Read next element.
       QXmlStreamReader::TokenType token = xml.readNext();
       // If token is just StartDocument, we'll go to next.
       if(token == QXmlStreamReader::StartDocument) continue;
       // If token is StartElement, we'll see if we can read it.
       if(token == QXmlStreamReader::StartElement)
       {
           // If it's named taches, we'll go to the next.
           if(xml.name() == "taches") continue;
           // If it's named tache, we'll dig the information from there.
           if(xml.name() == "tacheunitaire")
           {
               ajouterTache(TacheUnitaire::getFromXml(xml));
           }else if(xml.name() == "tachecomposite")
           {
               ajouterTache(TacheComposite::getFromXml(xml));
           }
       }

   }
   // Error handling.
   if(xml.hasError()) {
       throw CalendarException("Erreur lecteur fichier taches, parser xml");
   }
   // Removes any device() or data from the reader * and resets its internal state to the initial state.
   xml.clear();
   //qDebug()<<"fin load\n";

}
