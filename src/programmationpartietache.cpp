#include "programmationpartietache.h"
#include "projetmanager.h"

ProgrammationPartieTache* ProgrammationPartieTache::clone() const
{
    return new ProgrammationPartieTache(*this);
}

QString ProgrammationPartieTache::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\" >" << ProgrammationTache::getTache()->getTitre().toStdString() << "</h2>";
    ss << "<table align=\"center\" cellpadding=\"8\" >";
    ss << "<tr><td>Date :</td><td> " << ProgrammationTache::getDate().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Durée :</td><td> " << dureePartie << "</td></tr>";
    ss << "<tr><td>Description :</td><td>" <<ProgrammationTache::getTache()->getDescription().toStdString()<<"</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}

void ProgrammationPartieTache::toXml(QXmlStreamWriter &s) const
{
    s.writeStartElement("programmationpartietache");
    s.writeTextElement("date",Evenement::getDate().toString(Qt::ISODate));
    s.writeTextElement("horaire",Evenement::getHoraire().toString(Qt::ISODate));
    s.writeTextElement("tache",ProgrammationTache::getTache()->getId());
    s.writeTextElement("projet",ProgrammationTache::getProjet()->getTitre());
    QString str;
    str.setNum(getDuree().getDureeEnMinutes());
    s.writeTextElement("duree",str);
    s.writeEndElement();
}

ProgrammationPartieTache* ProgrammationPartieTache::getFromXml(QXmlStreamReader& xml)
{
    QDate date;
    QTime horaire;
    QString idTache;
    QString nomProjet;
    Duree duree;

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "programmationpartietache")){
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
            if(xml.name() == "duree") {
                xml.readNext();
                duree.setDuree(xml.text().toString().toUInt());
            }
        }
        xml.readNext();
    }
    Projet& pr = ProjetManager::getInstance().getProjet(nomProjet);
    TacheUnitaire* tache = dynamic_cast<TacheUnitaire*>(pr.getTache(idTache));
    ProgrammationPartieTache *evt = new ProgrammationPartieTache(date,horaire,duree,tache, &pr);
    return evt;
}
