#include "evenement.h"



QString Evenement::toString() const
{
    std::stringstream ss;
    ss << "Evenement\ndate = " << date.toString().toStdString() << "\nhoraire = " << horaire.toString().toStdString() << "\n";
    return ss.str().c_str();
}

