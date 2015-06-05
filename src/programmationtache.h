#ifndef PROGRAMMATIONTACHE_H
#define PROGRAMMATIONTACHE_H

#include "evenement.h"
#include "tacheunitaire.h"
//#include "duree.h"

class ProgrammationTache : public Evenement
{

    const TacheUnitaire* tache;
public:
    ProgrammationTache(const QDate& ddeb, const QTime& tdeb, const TacheUnitaire *t)
        :Evenement(ddeb,tdeb), tache(t) {}
    ~ProgrammationTache(){}

    const Tache& getTache() const { return *tache; }

    virtual const Duree& getDuree() const { return tache->getDuree(); }
    virtual const QString& getSujet() const { return tache->getTitre(); }

    virtual ProgrammationTache* clone() const;
    virtual QString toString() const;

    virtual bool isProgrammationTache() const { return true; }
    bool isEvenementTrad() const { return false; }
    bool isEvenement1j() const { return false; }
    bool isEvenementPj() const { return false; }

};

#endif // PROGRAMMATIONTACHE_H
