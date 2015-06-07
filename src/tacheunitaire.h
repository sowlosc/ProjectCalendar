#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include "duree.h"
#include "tache.h"
#include <sstream>
//#include "agenda.h"

class TacheUnitaire : public Tache
{
    Duree duree;
    bool preemptive;
    bool estProgramme;

public:
    TacheUnitaire(const QString& id,
                  const QString& t,
                  const QDate& dispo,
                  const QDate& ech,
                  const QString& txt,
                  const Duree& d,
                  bool preempt = false) : Tache(id,t,dispo,ech,txt), duree(d), preemptive(preempt),estProgramme(false) {}
    const Duree& getDuree() const { return duree; }
    bool isPreemptive() const { return preemptive; }
    void setDuree(const Duree& d) { duree = d; }
    void setPreemptive(bool b) { preemptive = b; }

    virtual QString toString() const;
    virtual bool isComposite() const { return false; }

    bool isProgrammed() const { return estProgramme;}
    void setProgrammed(bool b) { estProgramme = b; }

    /*class prog_iterator
    {
        friend class TacheUnitaire;
        Agenda::iterator it;
        prog_iterator(const Agenda::iterator& iter) : it(iter) {}
    public:
        Evenement& operator*() { return *it; }
        prog_iterator& operator++() {
            ++it;
            Agenda::iterator iter_end = Agenda::getInstance().end();
            while(it != iter_end && (*it).isProgrammationTache()
    };
*/
};

#endif // TACHEUNITAIRE_H
