#include "precedencemanager.h"
#include <iostream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include "projetmanager.h"

PrecedenceManager* PrecedenceManager::instance = 0;

PrecedenceManager& PrecedenceManager::getInstance()
{
    if(!instance) instance = new PrecedenceManager;
    return *instance;
}

void PrecedenceManager::libereInstace()
{
    if(instance) delete instance;
    instance = 0;
}

std::vector<Precedence*>::iterator PrecedenceManager::findPrecedence(const Tache& t1, const Tache &t2)
{
    for(std::vector<Precedence*>::iterator it = precedences.begin() ; it != precedences.end() ; ++it)
        if((*it)->pred == &t1 && (*it)->succ == &t2)
            return it;
    return precedences.end();
}


void PrecedenceManager::ajouterPrecedence(const Tache &t1, const Tache &t2,const QString& nomProj)
{
    /* il faut verifier que la precedence n'existe pas deja
     * et qu'elle ne provoque pas d'incoherence
     * */

    if(findPrecedence(t1,t2) != precedences.end())
            throw CalendarException("Erreur, PercedenceManager, cette precedence existe deja");

    Precedence *p = new Precedence(&t1,&t2,nomProj);
    precedences.push_back(p);
    notifier();
}

void PrecedenceManager::retirerPrecedence(const Tache &t1, const Tache &t2)
{
    /* il faut verif qu'elle existe
     * */

    std::vector<Precedence*>::iterator position = findPrecedence(t1,t2);
    if(position != precedences.end())
    {
        std::cout << "------------------------suppresion precedence : \n";
        delete (*position);
        precedences.erase(position);
    }else
    {
        std::cout <<"-------------- mauvaise precedence a suppr\n";
        throw CalendarException("Erreur, PrecedenceManager, la precedence a retirer n'existe pas");
    }
}

void  PrecedenceManager::save(const QString& f){
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("precedences");
    for(iterator it = begin() ; it!= end(); ++it)
    {
        (*it).toXml(stream);
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}



void PrecedenceManager::load(const QString &f)
{

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
   while(!xml.atEnd() && !xml.hasError()) {
       // Read next element.
       QXmlStreamReader::TokenType token = xml.readNext();
       // If token is just StartDocument, we'll go to next.
       if(token == QXmlStreamReader::StartDocument) continue;
       // If token is StartElement, we'll see if we can read it.
       if(token == QXmlStreamReader::StartElement) {
           // If it's named taches, we'll go to the next.
           if(xml.name() == "precedences") continue;
           // If it's named tache, we'll dig the information from there.
           if(xml.name() == "precedence") {
               qDebug()<<"new tache\n";

               QString nomProjet;
               QString idPred;
               QString idSucc;
              qDebug() << "----------------------\n";
               while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "precedence")) {
                   if(xml.tokenType() == QXmlStreamReader::StartElement) {

                       // We've found titre.
                       if(xml.name() == "projet") {
                           xml.readNext();
                           nomProjet=xml.text().toString();
                       }
                       // We've found disponibilite
                       if(xml.name() == "pred") {
                           xml.readNext();
                           idPred=xml.text().toString();
                       }
                       // We've found echeance
                       if(xml.name() == "succ") {
                           xml.readNext();
                           idSucc=xml.text().toString();
                       }

                   }
                   // ...and next...
                   xml.readNext();
               }
               //qDebug()<<"ajout tache "<<identificateur<<"\n";

std::cout << "----------nom projet = "<<nomProjet.toStdString()<<"\n";
               Projet& p = ProjetManager::getInstance().getProjet(nomProjet);
               Tache* pred = p.getTache(idPred);
               Tache* succ = p.getTache(idSucc);
               PrecedenceManager::getInstance().ajouterPrecedence(*pred,*succ,p.getTitre());

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
}





