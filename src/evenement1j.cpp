#include "evenement1j.h"


Evenement1j* Evenement1j::clone() const
{
    return new Evenement1j(*this);
}

QString Evenement1j::toString() const
{
    std::stringstream ss;
    ss << "Evenement1j\n" << "date = " << getDate().toString().toStdString();
    ss << "\nhoraire = " << getHoraire().toString().toStdString();
    ss << "\nsujet = " << getSujet().toStdString() << "\nduree = " << duree << "\n";
    return ss.str().c_str();
}
