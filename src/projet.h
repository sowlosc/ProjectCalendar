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
    //peut-etre a enlever
    Tache& ajouterTache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& ech, bool preempt = false);
    Projet& ajouterTache(Tache* t);
    void retirerTache(Tache* t);
    Tache& getTache(const QString& id);
    const Tache& getTache(const QString& id) const;


    const QString& getTitre() const { return titre; }
    const QString& getDescription() const { return description; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }

    void setTitre(const QString& t) { titre = t; }
    void setDescription(const QString& d) { description = d; }
    void setDisponibilite(const QDate& d) { disponibilite = d; }
    void setEcheance(const QDate& d) { echeance = d; }



    class iterator
    {
        friend class Projet;
        std::map<QString, Tache*>::iterator it;
        iterator(const std::map<QString,Tache*>::iterator& i) : it(i) {}

    public:
        Tache& operator*() { return *(it->second); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(taches.begin()); }
    iterator end() { return iterator(taches.end()); }


    class const_iterator
    {
        friend class Projet;
        std::map<QString, Tache*>::const_iterator it;
        const_iterator(const std::map<QString,Tache*>::const_iterator& i) : it(i) {}

    public:
        const Tache& operator*() { return *(it->second); }
        const_iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    const_iterator begin() const { return const_iterator(taches.begin()); }
    const_iterator end() const { return const_iterator(taches.end()); }

};





#endif // PROJET_H
