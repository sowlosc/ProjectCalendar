#include "evenementtrad.h"

/*EvenementTrad* EvenementTrad::clone() const
{
    return new EvenementTrad(*this);
}*/

QString EvenementTrad::toString() const
{
    std::stringstream ss;
    ss << "EvenementTrad\ndate = " << getDate().toString().toStdString();
    ss << "\nhoraire = " << getHoraire().toString().toStdString() << "\nsujet = " << sujet.toStdString() << "\n";
    return ss.str().c_str();
}

