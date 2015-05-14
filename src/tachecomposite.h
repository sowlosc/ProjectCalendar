#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include "tache.h"
#include <map>

class TacheComposite : public Tache
{
    std::map<QString, Tache*> sousTaches;

public:
    TacheComposite(const QString& id,
                   const QString& t,
                   const QDate& dispo,
                   const QDate& ech,
                   const QString& txt) : Tache(id,t,dispo,ech,txt) {}
    TacheComposite& operator<<(Tache* t);
    void retirerSousTache(Tache* t);
};

#endif // TACHECOMPOSITE_H
