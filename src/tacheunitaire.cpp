#include "tacheunitaire.h"


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
    ss << "</table></body></html>";
    return ss.str().c_str();
}
