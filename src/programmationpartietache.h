#ifndef PROGRAMMATIONPARTIETACHE_H
#define PROGRAMMATIONPARTIETACHE_H

#include "programmationtache.h"


class ProgrammationPartieTache : public ProgrammationTache
{
    Duree dureePartie;
public:
    ProgrammationPartieTache(const QDate& ddeb, const QTime& tdeb, const Duree& dp, const TacheUnitaire *t)
        : ProgrammationTache(ddeb,tdeb,t), dureePartie(dp) {}
    virtual ~ProgrammationPartieTache(){}

    const Duree& getDuree() const { return dureePartie; }
    const QString& getSujet() const { return this->getTache()->getTitre(); }
    virtual ProgrammationPartieTache* clone() const;
    virtual QString toString() const;

    bool isProgrammationPartieTache() const { return true; }

};

#endif // PROGRAMMATIONPARTIETACHE_H
