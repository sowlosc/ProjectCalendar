#ifndef EVENEMENT1J_H
#define EVENEMENT1J_H

#include "evenementtrad.h"
#include "duree.h"

class Evenement1j : public EvenementTrad
{
    Duree duree;
public:
    Evenement1j(const QDate& ddeb, const QTime& tdeb,const Duree& dur, const QString& suj)
        : EvenementTrad(ddeb,tdeb,suj), duree(dur) {}
    ~Evenement1j(){}
};

#endif // EVENEMENT1J_H
