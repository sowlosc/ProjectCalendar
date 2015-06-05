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
    virtual ~Evenement1j(){}

    const Duree& getDuree() const { return duree; }
    void setDuree(const Duree& dur) { duree = dur; }

    virtual Evenement1j* clone() const;
    virtual QString toString() const;

    virtual bool isEvenement1j() const { return true; }
    virtual bool isEvenementPj() const { return false; }

};

#endif // EVENEMENT1J_H
