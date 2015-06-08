#ifndef PROGRAMMATIONTACHE_H
#define PROGRAMMATIONTACHE_H

#include "evenement.h"
#include "tacheunitaire.h"
//#include "duree.h"
//class TacheUnitaire{ public: const Duree& getDuree();}; // const; const QString& getTitre() const; };
class ProgrammationTache : public Evenement
{

    TacheUnitaire* tache;
public:
    ProgrammationTache(const QDate& ddeb, const QTime& tdeb, TacheUnitaire *t)
        :Evenement(ddeb,tdeb), tache(t) {
        if(ddeb < tache->getDisponibilite() || ddeb > tache->getEcheance())
            throw CalendarException("erreur, ProgrammationTache, date non valide");
    }
    ~ProgrammationTache(){ }

    TacheUnitaire* getTache() const { return tache; }

    virtual const Duree& getDuree() const { return tache->getDuree(); }
    virtual const QString& getSujet() const { return tache->getTitre(); }

    virtual ProgrammationTache* clone() const;
    virtual QString toString() const;

    bool isProgrammationTache() const { return true; }
    virtual bool isProgrammationPartieTache() const { return false; }

    bool isEvenementTrad() const { return false; }
    bool isEvenement1j() const { return false; }
    bool isEvenementPj() const { return false; }

};

#endif // PROGRAMMATIONTACHE_H
