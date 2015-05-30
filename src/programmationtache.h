#ifndef PROGRAMMATIONTACHE_H
#define PROGRAMMATIONTACHE_H

#include "evenement.h"
#include "tacheunitaire.h"

class ProgrammationTache : public Evenement
{

    const TacheUnitaire* tache;
public:
    ProgrammationTache(const QDate& ddeb, const QTime& tdeb, const TacheUnitaire *t)
        :Evenement(ddeb,tdeb), tache(t) {}
    ~ProgrammationTache(){}

    const Tache& getTache() const { return *tache; }

    virtual ProgrammationTache* clone() const;
    virtual QString toString() const;
};

#endif // PROGRAMMATIONTACHE_H
