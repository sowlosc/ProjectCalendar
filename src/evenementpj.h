#ifndef EVENEMENTPJ_H
#define EVENEMENTPJ_H

#include "evenementtrad.h"

class EvenementPj : public EvenementTrad
{
    QDate dateFin;
    QTime horaireFin;

public:
    EvenementPj(const QDate& ddeb, const QTime& tdeb,const QDate& dfin, const QTime& tfin,const QString& suj)
        :EvenementTrad(ddeb,tdeb,suj),dateFin(dfin), horaireFin(tfin) {}
    ~EvenementPj(){}
};

#endif // EVENEMENTPJ_H
