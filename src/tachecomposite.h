#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include "tache.h"
#include <map>
#include <sstream>
class TacheComposite : public Tache
{
    std::map<QString, Tache*> sousTaches;

public:
    TacheComposite(const QString& id,
                   const QString& t,
                   const QDate& dispo,
                   const QDate& ech,
                   const QString& txt) : Tache(id,t,dispo,ech,txt) {}
    ~TacheComposite();

    virtual QString toString() const;
    virtual bool isComposite() const { return true; }

    void ajouterSousTache(Tache* t);


    void retirerSousTache(Tache* t);


    class iterator
    {
        friend class TacheComposite;
        std::map<QString, Tache*>::iterator it;
        iterator(std::map<QString, Tache*>::iterator iter) : it(iter) {}
    public:
        Tache& operator*() { return *(it->second); }
        iterator& operator++ (){ ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(sousTaches.begin()); }
    iterator end() { return iterator(sousTaches.end()); }
};

#endif // TACHECOMPOSITE_H
