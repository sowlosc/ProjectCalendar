#include "projetmanager.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include "tacheunitaire.h"

ProjetManager* ProjetManager::instance = 0;

ProjetManager& ProjetManager::getInstance()
{
    if(!instance) instance = new ProjetManager;
    return *instance;
}

void ProjetManager::libererInstance()
{
    if(instance) delete instance;
    instance = 0;
}


Projet& ProjetManager::ajouterProjet(const QString &t, const QString &desc, const QDate &dispo, const QDate &ech)
{
    if(projets.find(t) != projets.end())
        throw CalendarException("erreur, ProjetManager, projet deja existant");
    projets[t] = new Projet(t,desc,dispo,ech);
    notifier();
    return *projets[t];
}

Projet& ProjetManager::getProjet(const QString &t)
{
    return *projets.at(t); //renvoie une exception si le projet n'existe pas
}

const Projet& ProjetManager::getProjet(const QString &t) const
{
    return *projets.at(t); //renvoie une exception si le projet n'existe pas
}


void ProjetManager::supprimerProjet(const QString &titre)
{
    if(projets.find(titre) == projets.end())
        throw CalendarException("Erreur, ProjetManager, impossible retirer un projet qui n'existe pas");
    else{
        delete projets[titre];
        projets.erase(titre);
        notifier();
    }
}

void  ProjetManager::save(const QString& f){
    QFile newfile(f);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("projets");
    for(iterator it = begin() ; it!= end(); ++it)
    {
        (*it).toXml(stream);
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


void ProjetManager::load(const QString &f)
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
           // If it's named taches, we'll go to the next.
           if(xml.name() == "projets") continue;
           // If it's named tache, we'll dig the information from there.
           if(xml.name() == "projet") {
               qDebug()<<"new tache\n";

               QString titre;
               QDate disponibilite;
               QDate echeance;
               QString description;
                qDebug() << "----------------------\n";
               while(!(xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "taches")) {
                   if(xml.tokenType() == QXmlStreamReader::StartElement) {

                       // We've found titre.
                       if(xml.name() == "titre") {
                           xml.readNext();
                           titre=xml.text().toString();
                           qDebug()<<"titre="<<titre<<"\n";
                       }
                       // We've found disponibilite
                       if(xml.name() == "disponibilite") {
                           xml.readNext();
                           disponibilite=QDate::fromString(xml.text().toString(),Qt::ISODate);
                           qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                       }
                       // We've found echeance
                       if(xml.name() == "echeance") {
                           xml.readNext();
                           echeance=QDate::fromString(xml.text().toString(),Qt::ISODate);
                           qDebug()<<"echeance="<<echeance.toString()<<"\n";
                       }
                       // We've found description
                       if(xml.name() == "description") {
                           xml.readNext();
                           description = xml.text().toString();
                           qDebug()<<"description="<<description<<"\n";
                       }

                   }
                   // ...and next...
                   xml.readNext();
               }
               //qDebug()<<"ajout tache "<<identificateur<<"\n";

                Projet& pr = ajouterProjet(titre,description,disponibilite,echeance);

                xml.readNext();

                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "taches")){
                    if(xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        std::cout << "on va lui rajouter "<<xml.name().toString().toStdString()<<"\n";
                        if(xml.name() == "tacheunitaire")
                            pr.ajouterTache(TacheUnitaire::getFromXml(xml));
                        else if(xml.name() == "tachecomposite")
                            pr.ajouterTache(TacheComposite::getFromXml(xml));
                    }
                    xml.readNext();
                }
                xml.readNext();

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

  //  for(iterator it = begin() ; it != end(); ++it)
    ///    (*it).load((*it).getTitre()+".xml");
}
