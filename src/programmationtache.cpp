#include "programmationtache.h"

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
    ss << "</table></body></html>";
    return ss.str().c_str();
}
