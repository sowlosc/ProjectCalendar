#ifndef EVENEMENTPJ_H
#define EVENEMENTPJ_H

#include "evenementtrad.h"
#include <QDateTime>
#include <QtXml>

/*! \class EvenementPj
        \brief Classe representant un evenement qui dure plusieurs jours
*/
class EvenementPj : public EvenementTrad
{
    QDate dateFin;
    QTime horaireFin;

public:
    //! Constructeur a partir d'une date et d'un horaire de debut,d'une date et d'un horaire de fin et d'un sujet
    /*! \param ddeb date de debut
        \param tdeb horaire de debut
        \param dfin date de fin
        \param tfin horaire de fin
        \param suj sujet
        */
    EvenementPj(const QDate& ddeb, const QTime& tdeb,const QDate& dfin, const QTime& tfin,const QString& suj)
        :EvenementTrad(ddeb,tdeb,suj),dateFin(dfin), horaireFin(tfin) {
        if(ddeb>= dfin)
            throw CalendarException("La date de début doit être inférieure à la date de fin");
    }
    virtual ~EvenementPj(){}

    const QTime& getHoraireFin() const { return horaireFin; }
    const QDate& getDateFin() const { return dateFin; }
    void setHoraireFin(const QTime& t) { horaireFin = t; }
    void setDateFin(const QDate& d) { dateFin = d; }
    const Duree& getDuree() const;

    /**
     * @brief Clone un evenement sur plusieurs jours
     * @return
     */
    virtual EvenementPj* clone() const;
    virtual QString toString() const;

    virtual bool isEvenement1j() const { return false; }
    virtual bool isEvenementPj() const { return true; }
    virtual bool isRdv() const { return false; }
    virtual void toXml(QXmlStreamWriter &) const;

    /**
     * @brief construit un evenement sur 1 jour a partir du stream xml
     * @param xml
     * @return pointeur sur l'objet cree
     */
    static EvenementPj* getFromXml(QXmlStreamReader &);
};

#endif // EVENEMENTPJ_H
