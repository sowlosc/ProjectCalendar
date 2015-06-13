#include "rdv.h"



void Rdv::ajouterPersonne(const QString &nom)
{
    for(std::vector<QString>::iterator it = personnes.begin() ; it != personnes.end() ; it++)
        if(*it == nom)
            throw CalendarException("Cette personne est déjà enregistrée");
    personnes.push_back(nom);
}


void Rdv::retirerPersonne(const QString &nom)
{
    std::vector<QString>::iterator it;
    for(it = personnes.begin() ; it != personnes.end() ; it++)
        if(*it == nom){
            personnes.erase(it);
            return ;
        }
    throw CalendarException("Erreur, Rdv, cette personne n'etait pas enregistree");
}


QString Rdv::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\" >" << getSujet().toStdString() << "</h2>";
    ss << "<table align=\"center\" cellpadding=\"8\" >";

    ss << "<tr><td>Date :</td><td> " << getDate().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Horaire :</td><td> " << getHoraire().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Durée :</td><td> " << getDuree() << "</td></tr>";
    ss << "<tr><td>Lieu :</td><td> " << getLieu().toStdString() << "</td></tr>";
    ss << "<tr><td>Participants :</td><td> "     << "</td></tr>";
    for(std::vector<QString>::const_iterator it = personnes.begin(); it != personnes.end(); ++it)
        ss << (*it).toStdString() << "<br>";
    ss << "</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}

Rdv* Rdv::clone() const
{
    return new Rdv(*this);
}


void Rdv::toXml(QXmlStreamWriter &s) const
{
    s.writeStartElement("rdv");
    s.writeTextElement("date",Evenement::getDate().toString(Qt::ISODate));
    s.writeTextElement("horaire",Evenement::getHoraire().toString(Qt::ISODate));
    QString str;
    str.setNum(getDuree().getDureeEnMinutes());
    s.writeTextElement("duree",str);
    s.writeTextElement("sujet",EvenementTrad::getSujet());
    s.writeTextElement("lieu",lieu);
    s.writeStartElement("personnes");
    for(const_personnes_iterator it = begin_personnes(); it!= end_personnes() ; ++it)
        s.writeTextElement("personne",(*it));
    s.writeEndElement();
    s.writeEndElement();
}

Rdv* Rdv::getFromXml(QXmlStreamReader& xml)
{
    QDate date;
    QTime horaire;
    Duree duree;
    QString sujet;
    QString lieu;

    //construction de l'objet a partir des donnees xml
    while(!(xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == "personnes")){
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "date") {
                xml.readNext();
                date = QDate::fromString(xml.text().toString(),Qt::ISODate);
            }
            if(xml.name() == "horaire") {
                xml.readNext();
                horaire = QTime::fromString(xml.text().toString(),Qt::ISODate);
            }
            if(xml.name() == "sujet") {
                xml.readNext();
                sujet=xml.text().toString();
            }
            if(xml.name() == "lieu") {
                xml.readNext();
                lieu=xml.text().toString();
            }
            if(xml.name() == "duree") {
                xml.readNext();
                duree.setDuree(xml.text().toString().toUInt());
            }
        }
        xml.readNext();
    }
    //creation du rdv
    Rdv *evt = new Rdv(date,horaire,duree,sujet,lieu);
    xml.readNext();
    // ajout des participants au Rdv
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "personnes")){
        QString personne;
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "personne") {
                xml.readNext();
                personne = xml.text().toString();
                evt->ajouterPersonne(personne);
            }
        }
        xml.readNext();
    }
    xml.readNext();

    return evt;
}
