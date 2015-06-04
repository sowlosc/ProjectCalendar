#ifndef EVENEMENTTRAD_H
#define EVENEMENTTRAD_H

#include "evenement.h"

class EvenementTrad : public Evenement
{
    QString sujet;
public:
    EvenementTrad(const QDate& ddeb, const QTime& tdeb, const QString& suj)
        :Evenement(ddeb,tdeb), sujet(suj) {}
    virtual ~EvenementTrad(){}

    const QString getSujet() const { return sujet; }
    void setSujet(const QString& suj) { sujet = suj; }

    //virtual EvenementTrad* clone() const = 0;
    virtual QString toString() const;

    virtual bool isProgrammationTache() const { return false; }
    virtual bool isEvenementTrad() const { return true; }
    virtual bool isEvenement1j() const = 0;

};

#endif // EVENEMENTTRAD_H
