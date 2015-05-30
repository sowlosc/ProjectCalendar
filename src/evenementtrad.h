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

    virtual EvenementTrad* clone() const;
    virtual QString toString() const;
};

#endif // EVENEMENTTRAD_H
