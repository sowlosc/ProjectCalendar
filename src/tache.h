#ifndef TACHE_H
#define TACHE_H

#include <QDate>
#include <set>
#include "exception.h"
#include "observateur.h"
#include <iostream>
#include "precedencemanager.h"
#include <QtXml>

/*! \class Tache
        \brief Classe abstraite representant une tache
*/
class Tache : public Observable
{
    QString identificateur;
    QString titre;
    QDate disponibilite;
    QDate echeance;
    QString description;

    /**
     * @brief Constructeur de recopie prive
     * @param t
     */
    Tache(const Tache& t);
    /**
     * @brief Operateur d'ffactation prive
     * @return
     */
    Tache& operator=(const Tache&);

public:
    /**
     * @brief constructeur
     * @param id identificateur
     * @param t titre
     * @param dispo date de disponbilite
     * @param ech date d'echeance
     * @param txt description
     */
    Tache(const QString& id,
          const QString& t,
          const QDate& dispo,
          const QDate& ech,
          const QString& txt) : identificateur(id), titre(t), disponibilite(dispo),echeance(ech),description(txt) {
        if(disponibilite>echeance)
            throw CalendarException("Disponibilité > Echéance");
    }
    virtual ~Tache();

    const QString& getId() const { return identificateur; }
    void setId(const QString& id) { identificateur = id; }
    const QString& getTitre() const { return titre; }
    void setTitre(const QString& t) { titre = t; }
    const QString& getDescription() const { return description; }
    void setDescription(const QString& d) { description = d; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }
    void setDateDisponibiliteEcheance(const QDate& dispo, const QDate& ech){
        if(dispo > ech) throw CalendarException("erreur, Tache, disponibilité > échéance");
        disponibilite = dispo;
        echeance = ech;
    }


    virtual bool isProgrammed() const = 0;
    virtual bool isComposite() const = 0;

    virtual QString toString() const = 0 ;
    virtual void toXml(QXmlStreamWriter&) const = 0;


    /*! \class const_succ_iterator
            \brief Classe permettant d'iterer sur les successeurs d'une tache
    */
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

    /**
     * @brief Retourne un iterateur const sur la premiere tache successeure
     * @return
     */
    const_succ_iterator beginSucc() const {
        PrecedenceManager::iterator iter = PrecedenceManager::getInstance().begin();
        PrecedenceManager::iterator end = PrecedenceManager::getInstance().end();

        while( iter != end && (*iter).getPredecesseur() != this)
            ++iter;
        return const_succ_iterator(iter,this);}

    /**
     * @brief Retourne un iterateur const apres la derniere tache successeure
     * @return
     */
    const_succ_iterator endSucc() const { return const_succ_iterator(PrecedenceManager::getInstance().end(),this); }


    /*! \class const_pred_iterator
            \brief Classe permettant d'iterer sur les predecesseurs d'une tache
    */
    class const_pred_iterator
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

    /**
     * @brief Retourne un iterateur const sur la premiere tache predecesseure
     * @return
     */
    const_pred_iterator beginPred() const {
        PrecedenceManager::iterator iter = PrecedenceManager::getInstance().begin();
        PrecedenceManager::iterator end = PrecedenceManager::getInstance().end();

        while( iter != end && (*iter).getSuccesseur() != this)
            ++iter;
        return const_pred_iterator(iter,this);}

    /**
     * @brief Retourne un iterateur const apres la derniere tache predecesseure
     * @return
     */
    const_pred_iterator endPred() const { return const_pred_iterator(PrecedenceManager::getInstance().end(),this); }


};

#endif TACHE_H
