#ifndef TACHE_H
#define TACHE_H

#include <QDate>
#include "exception.h"


class Tache
{
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


   /* class succIterator
    {
        /* A continuer
         *


        friend class PrecedenceManager;
        std::vector<Precedence*>::iterator it;
        succIterator(std::vector<Precedence*>::iterator iter) : it(iter) {}
    public:
        Tache& operator*() { return (*it)->getSuccesseur(); }
        succIterator operator++();
        bool operator!=(std::vector<Precedence*>::iterator at) { return it != at.it; }
    };

    succIterator getFirstSucc() {
        PrecedenceManager& pm = PrecedenceManager::getInstance();
        std::vector<Precedence*>::iterator it = precedence.begin();
        while(*it->getSuccesseur().getId() != this->identificateur)
            it++;
        return succIterator(it);
    }
    succIterator getLastSucc() { return succIterator(precedences.end()); }

*/

};

#endif TACHE_H
