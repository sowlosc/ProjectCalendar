#ifndef PROGRAMMATIONTACHE_H
#define PROGRAMMATIONTACHE_H

#include "evenement.h"
#include "tacheunitaire.h"
//#include "duree.h"
//class TacheUnitaire{ public: const Duree& getDuree();}; // const; const QString& getTitre() const; };
class ProgrammationTache : public Evenement
{

    TacheUnitaire* tache;
    QString nomProjet;
public:
    ProgrammationTache(const QDate& ddeb, const QTime& tdeb, TacheUnitaire *t,const QString& nomProj)
        :Evenement(ddeb,tdeb), tache(t), nomProjet(nomProj) {
        if(ddeb < tache->getDisponibilite() || ddeb > tache->getEcheance())
            throw CalendarException("erreur, ProgrammationTache, date non valide");
    }
    ~ProgrammationTache(){ }

    TacheUnitaire* getTache() const { return tache; }
    const QString& getProjet() const { return nomProjet; }

    virtual const Duree& getDuree() const { return tache->getDuree(); }
    virtual const QString& getSujet() const { return tache->getTitre(); }

    virtual ProgrammationTache* clone() const;
    virtual QString toString() const;
    virtual void toXml(QXmlStreamWriter&) const;
    static ProgrammationTache* getFromXml(QXmlStreamReader& xml);


    bool isProgrammationTache() const { return true; }
    virtual bool isProgrammationPartieTache() const { return false; }

    bool isEvenementTrad() const { return false; }
    bool isEvenement1j() const { return false; }
    bool isEvenementPj() const { return false; }

};

#endif // PROGRAMMATIONTACHE_H
