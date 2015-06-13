#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QDate>
#include <QTime>
#include <sstream>
#include "duree.h"
#include <QtXml>

/*! \class Evenement
        \brief Classe abstraite representant un evenement
*/
class Evenement
{
    QDate date;
    QTime horaire;


public:
    //! Constructeur a partir d'une date et d'une heure
    /*! \param d date
        \param t horaire
        */
    Evenement(const QDate& d, const QTime& t)
        : date(d), horaire(t) {}

    virtual ~Evenement(){}

    /**
     * @brief Clone un evenement
     *
     */
    virtual Evenement* clone() const = 0;
    /**
     * @brief Retourne une description de l'objet en chaine de caracteres
     *
     */
    virtual QString toString() const = 0;


    const QDate& getDate() const { return date; }
    const QTime& getHoraire() const { return horaire; }
    void setDate(const QDate& d) { date = d; }
    void setHoraire(const QTime& t) { horaire = t; }
    virtual const Duree& getDuree() const = 0;
    virtual const QString& getSujet() const = 0;


    virtual bool isProgrammationTache() const = 0;
    virtual bool isEvenementTrad() const = 0;
    virtual bool isEvenement1j() const = 0;
    virtual bool isEvenementPj() const = 0;
    virtual bool isProgrammationPartieTache() const = 0;
    virtual bool isRdv() const = 0;

    /**
     * @brief Ecrit le contenu du fichier dans le stream xml passe en parametre
     */
    virtual void toXml(QXmlStreamWriter&) const = 0;

};

#endif // EVENEMENT_H
