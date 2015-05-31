#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include "duree.h"
#include "tache.h"
#include "agenda.h"

class TacheUnitaire : public Tache
{
    Duree duree;
    bool preemptive;
public:
    TacheUnitaire(const QString& id,
                  const QString& t,
                  const QDate& dispo,
                  const QDate& ech,
                  const QString& txt,
                  const Duree& d,
                  bool preempt = false) : Tache(id,t,dispo,ech,txt), duree(d), preemptive(preempt) {}
    virtual QString toString() const { return "TacheUnitaire"; }
    virtual bool isComposite() const { return false; }

};

#endif // TACHEUNITAIRE_H
