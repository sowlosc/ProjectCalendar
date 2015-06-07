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
    virtual ~TacheComposite();

    virtual QString toString() const;
    virtual bool isComposite() const { return true; }

    void ajouterSousTache(Tache* t);
    void retirerSousTache(Tache* t);


    Tache *getSousTache(const QString& id); // methode specifique aux taches composite return 0 si la tache n'existe pas    Tache *getSousTache(const QString& id); // methode specifique aux taches composite return 0 si la tache n'existe pas
    bool contientSousTache(const Tache* t);
    bool isProgrammed() const; //retourne si une sous tache est programmed

    std::map<QString, Tache*>* getTacheMap(const QString &id);


    class iterator
    {
        friend class TacheComposite;
        std::map<QString, Tache*>::iterator it;
        iterator(const std::map<QString, Tache*>::iterator& iter) : it(iter) {}
    public:
        Tache& operator*() { return *(it->second); }
        iterator& operator++ (){ ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(sousTaches.begin()); }
    iterator end() { return iterator(sousTaches.end()); }

    class const_iterator
    {
        friend class TacheComposite;
        std::map<QString, Tache*>::const_iterator it;
        const_iterator(const std::map<QString, Tache*>::const_iterator& iter) : it(iter) {}
    public:
        const Tache& operator*() { return *(it->second); }
        const_iterator& operator++ (){ ++it; return *this; }
        bool operator!=(const const_iterator& at) const { return it != at.it; }
    };

    const_iterator begin() const { return const_iterator(sousTaches.begin()); }
    const_iterator end() const { return const_iterator(sousTaches.end()); }
};

#endif // TACHECOMPOSITE_H
