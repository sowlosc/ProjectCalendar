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

class ProjetManager : public Observable
{
    std::set<Observateur*> obs;
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

    void ajouterObservateur(Observateur *o) { obs.insert(o); }
    void supprimerObservateur(Observateur *o) { obs.erase(o); }
    void notifier() {
        for(std::set<Observateur*>::iterator it = obs.begin() ; it != obs.end() ; ++it)
            (*it)->mise_a_jour();
    }





    class iterator{
        friend class ProjetManager;
        std::map<QString, Projet*>::iterator it;
        iterator(const std::map<QString, Projet*>::iterator& iter) : it(iter) {}
    public:
        Projet& operator*() { return *(it->second); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(projets.begin()); }
    iterator end() { return iterator(projets.end()); }

    class const_iterator{
        friend class ProjetManager;
        std::map<QString, Projet*>::const_iterator it;
        const_iterator(const std::map<QString, Projet*>::const_iterator& iter) : it(iter) {}
    public:
        const Projet& operator*() { return *(it->second); }
        const_iterator& operator++() { ++it; return *this; }
        bool operator!=(const const_iterator& at) const { return it != at.it; }
    };

    const_iterator begin() const  { return const_iterator(projets.begin()); }
    const_iterator end() const { return const_iterator(projets.end()); }


};

#endif // PROJETMANAGER_H
