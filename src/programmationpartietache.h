#ifndef PROGRAMMATIONPARTIETACHE_H
#define PROGRAMMATIONPARTIETACHE_H

#include "programmationtache.h"


class ProgrammationPartieTache : public ProgrammationTache
{
    Duree dureePartie;
public:
    ProgrammationPartieTache(const QDate& ddeb, const QTime& tdeb, const Duree& dp, TacheUnitaire *t,Projet* p)
        : ProgrammationTache(ddeb,tdeb,t,p), dureePartie(dp) {}
    virtual ~ProgrammationPartieTache(){}

    const Duree& getDuree() const { return dureePartie; }
    const QString& getSujet() const { return this->getTache()->getTitre(); }
    virtual ProgrammationPartieTache* clone() const;
    virtual QString toString() const;
    void toXml(QXmlStreamWriter &s) const;
    static ProgrammationPartieTache* getFromXml(QXmlStreamReader& xml);




    bool isProgrammationPartieTache() const { return true; }


};




#endif // PROGRAMMATIONPARTIETACHE_H
