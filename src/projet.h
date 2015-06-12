#ifndef PROJET_H
#define PROJET_H

#include <map>
#include <set>
#include <QString>
#include <sstream>
#include "duree.h"
#include "tache.h"
#include "tachecomposite.h"
#include "observateur.h"


class Projet : public Observable
{
    friend class ProjetManager;

    std::set<Observateur*> obs;
    QString file;
    QString titre;
    QString description;
    QDate disponibilite;
    QDate echeance;
    std::map<QString, Tache*> taches;

    Projet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech)
        :titre(t), description(desc), disponibilite(dispo), echeance(ech) {
        if(disponibilite>echeance)
            throw CalendarException("erreur, Projet, échéance < disponibilité");
    }
    ~Projet();
public:
    //peut-etre a enlever
    Tache& ajouterTache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& ech, bool preempt = false);
    Projet& ajouterTache(Tache* t);
    void retirerTache(Tache* t);
    void retirerTache(const QString id);

    Tache *getTache(const QString& id);
    bool contientTache(const Tache *t);

    std::map<QString, Tache *> *getTacheMap(const QString &id); //renvoie le map de tache parent



    void describe(); // A SUPPRIMER
    void affTache(Tache* t); // A SUPPRIMER


    const QString& getTitre() const { return titre; }
    const QString& getDescription() const { return description; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }

    void setTitre(const QString& t) { titre = t; }
    void setDescription(const QString& d) { description = d; }
    void setDisponibilite(const QDate& d) { disponibilite = d; }
    void setEcheance(const QDate& d) { echeance = d; }

    QString toString() const;

    void toXml(QXmlStreamWriter&) const;

    void ajouterObservateur(Observateur *o) { obs.insert(o); }
    void supprimerObservateur(Observateur *o) { obs.erase(o); }
    void notifier() {
        for(std::set<Observateur*>::iterator it = obs.begin() ; it != obs.end() ; ++it)
            (*it)->mise_a_jour();
    }


    void save(const QString &f);
    void load(const QString& f);










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
        bool operator!=(const const_iterator& at) const { return it != at.it; }
    };

    const_iterator begin() const { return const_iterator(taches.begin()); }
    const_iterator end() const { return const_iterator(taches.end()); }


    /*class programmation_iterator{
        friend class Agenda;
        std::vector<Evenement*>::iterator it;
        programmation_iterator(const std::vector<Evenement*>::iterator iter) : it(iter) {}
    public:
        Evenement& operator&() { return *it; }
        programmation_iterator& operator++() {
            while(it !=  !dynamic_cast<ProgrammationUnitaire*>(&(*it)) && dynamic_cast<ProgrammationUnitaire*>(&(*it))->tache != t)
                ++it;
            ++it ; return *this; }
        bool operator!=(const programmation_iterator& at) const { return it != at.it; }

    };*/


};





#endif // PROJET_H
