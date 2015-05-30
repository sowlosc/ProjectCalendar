#include "programmationtache.h"

ProgrammationTache* ProgrammationTache::clone() const
{
    return new ProgrammationTache(*this);
}

QString ProgrammationTache::toString() const
{
    std::stringstream ss;
    ss << "ProgrammationTache\ndate = " << getDate().toString().toStdString();
    ss <<"\nhoraire = " << getHoraire().toString().toStdString();
    ss << "\ntache = " << tache->getTitre().toStdString() << "\n";
    return ss.str().c_str();
}
