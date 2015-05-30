#ifndef PROGRAMMATIONPARTIETACHE_H
#define PROGRAMMATIONPARTIETACHE_H

#include "programmationtache.h"
#include "duree.h"
#include "tacheunitaire.h"

class ProgrammationPartieTache : public ProgrammationTache
{
    Duree dureePartie;
    TacheUnitaire* tache;
public:
    ProgrammationPartieTache(const QDate& ddeb, const QTime& tdeb, const Duree& dp)
        : ProgrammationTache(ddeb,tdeb), dureePartie(dp) {}
    ~ProgrammationPartieTache(){}
};

#endif // PROGRAMMATIONPARTIETACHE_H
