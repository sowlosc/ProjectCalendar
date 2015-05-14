#ifndef PROJET_H
#define PROJET_H

#include <map>
#include <QString>
#include "duree.h"
#include "tache.h"


class Projet
{
    friend class ProjetManager;
    QString titre;
    QString description;
    //Duree duree;
    QDate disponibilite;
    QDate echeance;
    std::map<QString, Tache*> taches;

    Projet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech)
        :titre(t), description(desc), disponibilite(dispo), echeance(ech) {}
    ~Projet() {}
public:
    Tache& ajouterTache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& ech, bool preempt = false);
    Tache& getTache(const QString& id);
    const Tache& getTache(const QString& id) const;


    class iterator
    {
        friend class Projet;
        std::map<QString, Tache*>::iterator it;
        iterator(const std::map<QString,Tache*>::iterator& i) : it(i) {}

    public:
        iterator() {}
        Tache& operator*() { return *(it->second); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(taches.begin()); }
    iterator end() { return iterator(taches.end()); }

};





#endif // PROJET_H
