#ifndef EVENEMENTTRAD_H
#define EVENEMENTTRAD_H

#include "evenement.h"

class EvenementTrad : public Evenement
{
    QString sujet;
public:
    EvenementTrad(const QDate& ddeb, const QTime& tdeb, const QString& suj)
        :Evenement(ddeb,tdeb), sujet(suj) {}
    ~EvenementTrad(){}
};

#endif // EVENEMENTTRAD_H
