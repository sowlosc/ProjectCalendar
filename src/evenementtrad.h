#ifndef EVENEMENTTRAD_H
#define EVENEMENTTRAD_H

#include "evenement.h"


/*! \class EvenementTrad
        \brief Classe abstraite representant un evenement traditionnel
*/
class EvenementTrad : public Evenement
{
    QString sujet;
public:
    //! Constructeur a partir d'une date et d'un horaire et d'un sujet
    /*! \param ddeb date de debut
        \param tdeb horaire de debut
        \param dur duree
        */
    EvenementTrad(const QDate& ddeb, const QTime& tdeb, const QString& suj)
        :Evenement(ddeb,tdeb), sujet(suj) {}
    virtual ~EvenementTrad(){}

    virtual const QString& getSujet() const { return sujet; }
    virtual void setSujet(const QString& suj) { sujet = suj; }
    virtual bool isProgrammationTache() const { return false; }
    virtual bool isEvenementTrad() const { return true; }
    virtual bool isEvenement1j() const = 0;
    virtual bool isProgrammationPartieTache() const { return false; }
    virtual bool isRdv() const = 0;
};

#endif // EVENEMENTTRAD_H
