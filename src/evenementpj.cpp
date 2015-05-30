#include "evenementpj.h"


EvenementPj* EvenementPj::clone() const
{
    return new EvenementPj(*this);
}

QString EvenementPj::toString() const
{
    std::stringstream ss;
    ss << "EvenemenetPj\ndate = " << getDate().toString().toStdString();
    ss << "\nhoraire = " << getHoraire().toString().toStdString();
    ss << "\ndateFin = " << dateFin.toString().toStdString();
    ss << "\nhoraireFin = " << horaireFin.toString().toStdString();
    ss  << "\nsujet = " << getSujet().toStdString() << "\n";
    return ss.str().c_str();
}
