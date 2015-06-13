#include "tachecomposite.h"
#include "tacheunitaire.h"

TacheComposite::~TacheComposite()
{
    for(std::map<QString, Tache*>::iterator it = sousTaches.begin(); it != sousTaches.end() ; ++it)
        delete (it->second);
}



void TacheComposite::ajouterSousTache(Tache *t)
{
    if(sousTaches.find(t->getId()) != sousTaches.end())
        throw CalendarException("Erreur, TacheCompisite, cette sous tache existe deja");
    if(t->getDisponibilite()<Tache::getDisponibilite() || t->getEcheance()>Tache::getEcheance())
        throw CalendarException("Date de disponibilité et d'échéance incompatibles");
    sousTaches[t->getId()] = t;
    notifier();
}


void TacheComposite::retirerSousTache(Tache *t)
{
    if(sousTaches.find(t->getId()) != sousTaches.end()){
        delete sousTaches[t->getId()];
        sousTaches.erase(t->getId());
        //notifier();
    }
}


QString TacheComposite::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\">" << getTitre().toStdString() << " ("<< getId().toStdString() << ")</h2>";
    ss << "<table align=\"center\" cellpadding=\"4\" >";
    ss << "<tr><td>type</td><td>tache composite</td></tr>";
    ss << "<tr><td>date disponibilité </td><td> " << getDisponibilite().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>date échéance </td><td> " << getEcheance().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>description</b></td><td> " << getDescription().toStdString()<< "</td></tr>";
    ss << "<tr><td>taches précédentes </td><td>";
    for(const_pred_iterator it = beginPred(); it != endPred() ; ++it)
        ss << (*it)->getTitre().toStdString() << "<br>";
    ss << "</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}

void TacheComposite::toXml(QXmlStreamWriter &s) const
{

    s.writeStartElement("tachecomposite");
    s.writeTextElement("identificateur",Tache::getId());
    s.writeTextElement("titre",Tache::getTitre());
    s.writeTextElement("disponibilite",Tache::getDisponibilite().toString(Qt::ISODate));
    s.writeTextElement("echeance",Tache::getEcheance().toString(Qt::ISODate));
    s.writeTextElement("description",Tache::getDescription());
    s.writeStartElement("soustaches");
    for(const_iterator it = begin(); it != end() ; ++it)
        (*it).toXml(s);
    s.writeEndElement();
    s.writeEndElement();
}


TacheComposite* TacheComposite::getFromXml(QXmlStreamReader& xml)
{
    QString id;
    QString t;
    QDate dispo;
    QDate ech;
    QString desc;

    //construction de la tache composite a partir de l' xml
    while(!(xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "soustaches")){
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            // We've found identificteur.
            if(xml.name() == "identificateur") {
                xml.readNext(); id=xml.text().toString();
                //qDebug()<<"id="<<identificateur<<"\n";
            }
            // We've found titre.
            if(xml.name() == "titre") {
                xml.readNext(); t=xml.text().toString();
                //qDebug()<<"titre="<<titre<<"\n";
            }
            // We've found description.
            if(xml.name() == "description") {
                xml.readNext(); desc=xml.text().toString();
                //qDebug()<<"description="<<description<<"\n";
            }
            // We've found disponibilite
            if(xml.name() == "disponibilite") {
                xml.readNext();
                dispo=QDate::fromString(xml.text().toString(),Qt::ISODate);
                //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
            }
            // We've found echeance
            if(xml.name() == "echeance") {
                xml.readNext();
                ech=QDate::fromString(xml.text().toString(),Qt::ISODate);
                //qDebug()<<"echeance="<<echeance.toString()<<"\n";
            }
        }
        xml.readNext();
    }
    xml.readNext();
    TacheComposite *tache = new TacheComposite(id,t,dispo,ech,desc);
    // ajout des sous-taches
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "soustaches")){
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "tacheunitaire")
                tache->ajouterSousTache(TacheUnitaire::getFromXml(xml));
            else if(xml.name() == "tachecomposite")
                tache->ajouterSousTache(TacheComposite::getFromXml(xml));
        }
        xml.readNext();
    }
    xml.readNext();

    return tache;
}


Tache* TacheComposite::getSousTache(const QString &id)
{
    //si elle est dans les sous-taches
    if(sousTaches.find(id) != sousTaches.end())
        return sousTaches[id];
    else
    {   // sinon recherche dans les sous-taches au niveau inferieur
        for(std::map<QString, Tache*>::iterator it = sousTaches.begin() ; it != sousTaches.end() ; ++it)
        {
            if(it->second->isComposite())
            {
                Tache* t = dynamic_cast<TacheComposite*>(it->second)->getSousTache(id);
                if(t)
                    return t;
            }
        }
        return 0;
    }
}

bool TacheComposite::contientSousTache(const Tache *t)
{
    //si elle est dans les sous-taches
    if(sousTaches.find(t->getId()) != sousTaches.end() && sousTaches[t->getId()] == t)
        return true;
    else
    {    // sinon recherche dans les sous-taches au niveau inferieur
        for(std::map<QString, Tache*>::iterator it = sousTaches.begin() ; it != sousTaches.end() ; ++it)
        {
            if(it->second->isComposite())
            {
                bool result = dynamic_cast<TacheComposite*>(it->second)->contientSousTache(t);
                if(result)
                    return result;
            }
        }
        return false;
    }
}

bool TacheComposite::isProgrammed() const
{
    // programmee si toutes ses sous-taches ont ete programmees
    for(const_iterator it = begin() ; it!=end() ;++it)
    {
        if((*it).isProgrammed())
            return true;
    }
    return false;
}


std::map<QString, Tache *> *TacheComposite::getTacheMap(const QString &id)
{
    // si elle est dans les sosu-tache
    if(sousTaches.find(id) != sousTaches.end())
        return &sousTaches;
    else
    {   // sinon on cherche recursivemenet a l'interieur des sous-taches
        for(TacheComposite::iterator it = begin() ; it != end() ; ++it)
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

