#include "evenement1j.h"


Evenement1j* Evenement1j::clone() const
{
    return new Evenement1j(*this);
}

QString Evenement1j::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\" >" << getSujet().toStdString() << "</h2>";
    ss << "<table align=\"center\" cellpadding=\"8\" >";
    ss << "<tr><td>Date :</td><td> " << getDate().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Horaire :</td><td> " << getHoraire().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Durée :</td><td> " << getDuree() << "</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}


void Evenement1j::toXml(QXmlStreamWriter &s) const
{
    s.writeStartElement("evenement1j");
    s.writeTextElement("date",Evenement::getDate().toString(Qt::ISODate));
    s.writeTextElement("horaire",Evenement::getHoraire().toString(Qt::ISODate));
    QString str;
    str.setNum(getDuree().getDureeEnMinutes());
    s.writeTextElement("duree",str);
    s.writeTextElement("sujet",EvenementTrad::getSujet());
    s.writeEndElement();
}


Evenement1j* Evenement1j::getFromXml(QXmlStreamReader& xml)
{
    QDate date;
    QTime horaire;
    Duree duree;
    QString sujet;
    //construction de l'objet en lisant le xml
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "evenement1j")){
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
            if(xml.name() == "duree") {
                xml.readNext();
                duree.setDuree(xml.text().toString().toUInt());
            }
        }
        xml.readNext();
    }
    Evenement1j *evt = new Evenement1j(date,horaire,duree,sujet);
    return evt;
}
