#ifndef PROGRAMMATIONPARTIETACHE_H
#define PROGRAMMATIONPARTIETACHE_H

#include "programmationtache.h"

/*! \class ProgrammationPartieTache
        \brief Classe representant la programmation d'une partie d'une tache
*/
class ProgrammationPartieTache : public ProgrammationTache
{
    Duree dureePartie;
public:


    //! Constructeur a partir d'une date, d'une heure, d'une duree, d'une tache et d'une projet
    /*! \param ddeb date
        \param tdeb horaire
        \param dp duree de la partie
        \param t pointeur sur la tache programmee
        \param p pointeur sur le projet
        */
    ProgrammationPartieTache(const QDate& ddeb, const QTime& tdeb, const Duree& dp, TacheUnitaire *t,Projet* p)
        : ProgrammationTache(ddeb,tdeb,t,p), dureePartie(dp) {}
    virtual ~ProgrammationPartieTache(){}

    virtual const Duree& getDuree() const { return dureePartie; }
    virtual const QString& getSujet() const { return this->getTache()->getTitre(); }
    virtual ProgrammationPartieTache* clone() const;
    virtual QString toString() const;
    virtual void toXml(QXmlStreamWriter &s) const;
    static ProgrammationPartieTache* getFromXml(QXmlStreamReader& xml);
    bool isProgrammationPartieTache() const { return true; }
};




#endif // PROGRAMMATIONPARTIETACHE_H
