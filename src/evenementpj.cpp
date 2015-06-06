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
