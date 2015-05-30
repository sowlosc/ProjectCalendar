#include "programmationpartietache.h"

ProgrammationPartieTache* ProgrammationPartieTache::clone() const
{
    return new ProgrammationPartieTache(*this);
}

QString ProgrammationPartieTache::toString() const
{
    std::stringstream ss;
    ss << "ProgrammationPartieTache\ndate = " << getDate().toString().toStdString();
    ss << "\nhoraire = " << getHoraire().toString().toStdString();
    ss << "\ntache = " << getTache().getTitre().toStdString() << "\nduree = " << dureePartie << "\n";
    return ss.str().c_str();
}
