#ifndef PROGRAMMATIONPARTIETACHE_H
#define PROGRAMMATIONPARTIETACHE_H

#include "programmationtache.h"
#include "duree.h"

class ProgrammationPartieTache : public ProgrammationTache
{
    Duree dureePartie;
public:
    ProgrammationPartieTache(const QDate& ddeb, const QTime& tdeb, const Duree& dp, const TacheUnitaire *t)
        : ProgrammationTache(ddeb,tdeb,t), dureePartie(dp) {}
    virtual ~ProgrammationPartieTache(){}

    virtual ProgrammationPartieTache* clone() const;
    virtual QString toString() const;
};

#endif // PROGRAMMATIONPARTIETACHE_H
