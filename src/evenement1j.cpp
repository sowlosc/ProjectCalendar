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
