#include "evenementpj.h"


EvenementPj* EvenementPj::clone() const
{
    return new EvenementPj(*this);
}

QString EvenementPj::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\" >" << getSujet().toStdString() << "</h2>";
    ss << "<table align=\"center\" cellpadding=\"8\" >";
    ss << "<tr><td>Date de début :</td><td> " << getDate().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Horaire de début :</td><td> " << getHoraire().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Date de fin :</td><td> " << getDateFin().toString().toStdString() << "</td></tr>";
    ss << "<tr><td>Horaire de fin :</td><td> " << getHoraireFin().toString().toStdString()<< "</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}


const Duree& EvenementPj::getDuree() const
{
    QDateTime fin(dateFin,horaireFin);
    QDateTime debut(Evenement::getDate(),Evenement::getHoraire());
    return debut.secsTo(fin) / 60;
}


void EvenementPj::toXml(QXmlStreamWriter &s) const
{
    s.writeStartElement("evenementpj");
    s.writeTextElement("date",Evenement::getDate().toString(Qt::ISODate));
    s.writeTextElement("horaire",Evenement::getHoraire().toString(Qt::ISODate));
    s.writeTextElement("datefin",dateFin.toString(Qt::ISODate));
    s.writeTextElement("horairefin",horaireFin.toString(Qt::ISODate));
    s.writeTextElement("sujet",EvenementTrad::getSujet());
    s.writeEndElement();
}

EvenementPj* EvenementPj::getFromXml(QXmlStreamReader& xml)
{
    QDate date;
    QTime horaire;
    QDate dateFin;
    QTime horaireFin;
    QString sujet;

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "evenementpj")){
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
            if(xml.name() == "datefin") {
                xml.readNext();
                dateFin = QDate::fromString(xml.text().toString(),Qt::ISODate);
            }
            if(xml.name() == "horairefin") {
                xml.readNext();
                horaireFin = QTime::fromString(xml.text().toString(),Qt::ISODate);
            }
            if(xml.name() == "sujet") {
                xml.readNext();
                sujet=xml.text().toString();
            }
        }
        xml.readNext();
    }
    EvenementPj *evt = new EvenementPj(date,horaire,dateFin,horaireFin,sujet);
    return evt;
}

