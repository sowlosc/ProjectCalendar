#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H

#include "projet.h"
//#include "mainwindow.h"
#include "observateur.h"
#include <set>
#include <map>
#include <QString>
#include <QDate>
#include "exception.h"
#include "enregistrable.h"

class ProjetManager : public Observable, public Enregistrable
{

    std::map<QString,Projet*> projets;
    static ProjetManager* instance;

    ProjetManager() {};
    ProjetManager(const ProjetManager&);
    ~ProjetManager() {};
    ProjetManager& operator=(const ProjetManager&);

public:
    static ProjetManager& getInstance();
    static void libererInstance();
    Projet& ajouterProjet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech);

    Projet& getProjet(const QString& t);
    const Projet& getProjet(const QString &t) const;

    void supprimerProjet(const QString& t);

    void save(const QString& f);
    void load(const QString& f);






    /*lass iterator{
        friend class ProjetManager;
        std::map<QString, Projet*>::iterator it;
        iterator(const std::map<QString, Projet*>::iterator& iter) : it(iter) {}
    public:
        Projet& operator*() { return *(it->second); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(projets.begin()); }
    iterator end() { return iterator(projets.end()); }*/


    class iterator : public std::map<QString, Projet*>::iterator
    {
        iterator() : std::map<QString, Projet*>::iterator() {}
        public:
        Projet& operator*() { return *(*this)->second; }
        iterator(std::map<QString,Projet*>::iterator it) : std::map<QString,Projet*>::iterator(it) {}
    };

    iterator begin() { return iterator(projets.begin()); }
    iterator end() { return iterator(projets.end()); }


    /*class const_iterator{
        friend class ProjetManager;
        std::map<QString, Projet*>::const_iterator it;
        const_iterator(const std::map<QString, Projet*>::const_iterator& iter) : it(iter) {}
    public:
        const Projet& operator*() { return *(it->second); }
        const_iterator& operator++() { ++it; return *this; }
        bool operator!=(const const_iterator& at) const { return it != at.it; }
    };

    const_iterator begin() const  { return const_iterator(projets.begin()); }
    const_iterator end() const { return const_iterator(projets.end()); }*/


    class const_iterator : public std::map<QString, Projet*>::const_iterator
    {
        const_iterator() : std::map<QString, Projet*>::const_iterator() {}
        public:
        const_iterator(std::map<QString, Projet*>::const_iterator it):
          std::map<QString,Projet*>::const_iterator(it) {}
        const Projet& operator*() const { return *(*this)->second; }
    };

    const_iterator begin() const  { return const_iterator(projets.begin()); }
    const_iterator end() const { return const_iterator(projets.end()); }

};

#endif // PROJETMANAGER_H
