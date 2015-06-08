#include "programmationtache.h"
#include "projetmanager.h"
ProgrammationTache* ProgrammationTache::clone() const
{
    return new ProgrammationTache(*this);
}

QString ProgrammationTache::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\" >" << tache->getTitre().toStdString() << "</h2>";
    ss << "<table align=\"center\" cellpadding=\"8\" >";
    ss << "<tr><td>Date :</td><td> " << getDate().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Durée :</td><td> " << tache->getDuree() << "</td></tr>";
    ss << "<tr><td>Description :</td><td>" <<tache->getDescription().toStdString()<<"</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}

void ProgrammationTache::toXml(QXmlStreamWriter &s) const
{
    s.writeStartElement("programmationtache");

    s.writeTextElement("date",Evenement::getDate().toString(Qt::ISODate));
    s.writeTextElement("horaire",Evenement::getHoraire().toString(Qt::ISODate));
    s.writeTextElement("tache",tache->getId());
    s.writeTextElement("projet",nomProjet);
    s.writeEndElement();
}


ProgrammationTache* ProgrammationTache::getFromXml(QXmlStreamReader& xml)
{
    QDate date;
    QTime horaire;
    QString idTache;
    QString nomProjet;

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "programmationtache")){
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
            if(xml.name() == "tache") {
                xml.readNext();
                idTache=xml.text().toString();
            }
            if(xml.name() == "projet") {
                xml.readNext();
                nomProjet = xml.text().toString();
            }
        }
        xml.readNext();
    }
    Projet& pr = ProjetManager::getInstance().getProjet(nomProjet);
    TacheUnitaire* tache = dynamic_cast<TacheUnitaire*>(pr.getTache(idTache));
    ProgrammationTache *evt = new ProgrammationTache(date,horaire,tache,nomProjet);
    return evt;
}
