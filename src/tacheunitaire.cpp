#include "tacheunitaire.h"
#include "agenda.h"
TacheUnitaire::~TacheUnitaire()
{
    //Agenda::getin
    std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(this);
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
