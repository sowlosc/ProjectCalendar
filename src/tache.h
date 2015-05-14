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




    class succIterator
    {
        /* A continuer
         * */
        /*friend class PrecedenceManager;
        std::vector<const Precedence*>::iterator it;
        succIterator(std::vector<const Precedence*>::iterator i) : it(i) {}
    public:
        Precedence& operator*() { return *it; }
        succIterator operator++();
        bool operator!=(std::vector<const Precedence*>::iterator at) { return it != at.it; }*/
    };

    //succIterator getFirstSucc();
    //succIterator getLastSucc() { return succIterator(precedences.end()); }



};

#endif // TACHE_H
