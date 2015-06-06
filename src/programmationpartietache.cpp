#include "programmationpartietache.h"

ProgrammationPartieTache* ProgrammationPartieTache::clone() const
{
    return new ProgrammationPartieTache(*this);
}

QString ProgrammationPartieTache::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\" >" << getTache().getTitre().toStdString() << "</h2>";
    ss << "<table align=\"center\" cellpadding=\"8\" >";
    ss << "<tr><td>Date :</td><td> " << getDate().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Durée :</td><td> " << dureePartie << "</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}
