#ifndef TACHE_H
#define TACHE_H

#include <QDate>
#include <set>
#include "exception.h"
#include "observateur.h"
#include <iostream>
#include "precedencemanager.h"
class Tache : public Observable
{
    std::set<Observateur*> obs;


    QString identificateur;
    QString titre;
    QDate disponibilite;
    QDate echeance;
    QString description;

    Tache(const Tache& t);
    Tache& operator=(const Tache&);

public:
    Tache(const QString& id,
          const QString& t,
          const QDate& dispo,
          const QDate& ech,
          const QString& txt) : identificateur(id), titre(t), disponibilite(dispo),echeance(ech),description(txt) {}
    virtual ~Tache() {}

    const QString& getId() const { return identificateur; }
    void setId(const QString& id) { identificateur = id; }
    const QString& getTitre() const { return titre; }
    void setTitre(const QString& t) { titre = t; }
    const QString& getDescription() const { return description; }
    void setDescription(const QString& d) { description = d; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }
    void setDateDisponibiliteEcheance(const QDate& dispo, const QDate& ech){
        if(dispo > ech) throw CalendarException("erreur, Tache, disponibilite > echeance");
        disponibilite = dispo;
        echeance = ech;
    }



    virtual QString toString() const = 0 ;
    virtual bool isComposite() const = 0;

    void ajouterObservateur(Observateur *o) { obs.insert(o); }
    void supprimerObservateur(Observateur *o) { obs.erase(o); }
    void notifier() {
        for(std::set<Observateur*>::iterator it = obs.begin() ; it != obs.end() ; ++it)
            (*it)->mise_a_jour();
    }


    class const_succ_iterator
    {
        friend class Tache;
        PrecedenceManager::iterator it;
        const Tache* tachePred;
        const_succ_iterator(const PrecedenceManager::iterator& iter,const Tache* t) : it(iter),tachePred(t) {}
    public:
        const Tache* operator*() { return (*it).getSuccesseur(); }
        const_succ_iterator& operator++() {
            PrecedenceManager::iterator end = PrecedenceManager::getInstance().end();
            ++it;
            while(it!= end && (*it).getPredecesseur() != tachePred)
                ++it;
            return *this;
        }
        bool operator!=(const const_succ_iterator& at) const { return it != at.it; }
    };

    const_succ_iterator beginSucc() const {
        PrecedenceManager::iterator iter = PrecedenceManager::getInstance().begin();
        PrecedenceManager::iterator end = PrecedenceManager::getInstance().end();

        while( iter != end && (*iter).getPredecesseur() != this)
            ++iter;
        return const_succ_iterator(iter,this);}

    const_succ_iterator endSucc() const { return const_succ_iterator(PrecedenceManager::getInstance().end(),this); }

    class const_pred_iterator //const
    {
        friend class Tache;
        PrecedenceManager::iterator it;
        const Tache* tachePred;
        const_pred_iterator(const PrecedenceManager::iterator& iter,const Tache* t) : it(iter),tachePred(t) {}
    public:
        const Tache* operator*() { return (*it).getPredecesseur(); }
        const_pred_iterator& operator++() {
            PrecedenceManager::iterator end = PrecedenceManager::getInstance().end();
            ++it;
            while(it!= end && (*it).getSuccesseur() != tachePred)
                ++it;
            return *this;
        }
        bool operator!=(const const_pred_iterator& at) const { return it != at.it; }
    };

    const_pred_iterator beginPred() const {
        PrecedenceManager::iterator iter = PrecedenceManager::getInstance().begin();
        PrecedenceManager::iterator end = PrecedenceManager::getInstance().end();

        while( iter != end && (*iter).getSuccesseur() != this)
            ++iter;
        return const_pred_iterator(iter,this);}

    const_pred_iterator endPred() const { return const_pred_iterator(PrecedenceManager::getInstance().end(),this); }






};

#endif TACHE_H
