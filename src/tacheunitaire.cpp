#include "tacheunitaire.h"
#include "agenda.h"
TacheUnitaire::~TacheUnitaire()
{
    std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(this);
    //suppression de toutes ses programmations
    for(std::vector<ProgrammationTache*>::iterator it = progs.begin() ; it != progs.end() ; ++it)
        Agenda::getInstance() >> *it;
}

QString TacheUnitaire::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\" >" << getTitre().toStdString() << " ("<< getId().toStdString() << ")</h2>";
    ss << "<table align=\"center\" cellpadding=\"4\" >";
    ss << "<tr><td>type</td><td>tache unitaire</td></tr>";
    ss << "<tr><td>duree</b></td><td> " << getDuree() << "</td></tr>";
    ss << "<tr><td>date disponibilité </td><td> " << getDisponibilite().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>date échéance </td><td> " << getEcheance().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>description</b></td><td> " << getDescription().toStdString()<< "</td></tr>";
    ss << "<tr><td>preemptive</b></td><td> " << (isPreemptive() ? "true":"false") << "</td></tr>";
    ss << "<tr><td>taches précédentes </td><td>";
    for(const_pred_iterator it = beginPred(); it != endPred() ; ++it)
        ss << (*it)->getTitre().toStdString() << "<br>";
    ss << "</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}


void TacheUnitaire::toXml(QXmlStreamWriter& s) const
{
    s.writeStartElement("tacheunitaire");
    s.writeAttribute("preemptive", (isPreemptive())?"true":"false");
    s.writeTextElement("identificateur",Tache::getId());
    s.writeTextElement("titre",Tache::getTitre());
    s.writeTextElement("disponibilite",Tache::getDisponibilite().toString(Qt::ISODate));
    s.writeTextElement("echeance",Tache::getEcheance().toString(Qt::ISODate));
    s.writeTextElement("description",Tache::getDescription());
    QString str;
    str.setNum(getDuree().getDureeEnMinutes());
    s.writeTextElement("duree",str);
    s.writeEndElement();
}

TacheUnitaire*  TacheUnitaire::getFromXml(QXmlStreamReader& xml)
{
    QString id;
    QString t;
    QDate dispo;
    QDate ech;
    Duree dur;
    QString desc;
    bool pre;

    QXmlStreamAttributes attributes = xml.attributes();
    /* Let's check that Task has attribute. */
    if(attributes.hasAttribute("preemptive")) {
        QString val =attributes.value("preemptive").toString();
        pre=(val == "true" ? true : false);
    }

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tacheunitaire")){
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
            // We've found duree
            if(xml.name() == "duree") {
                xml.readNext();
                dur.setDuree(xml.text().toString().toUInt());
                //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
            }
        }
        xml.readNext();
    }
    TacheUnitaire *tache = new TacheUnitaire(id,t,dispo,ech,desc,dur,pre);
    return tache;
}
