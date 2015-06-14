#ifndef EVENEMENT1J_H
#define EVENEMENT1J_H

#include "evenementtrad.h"

/*! \class Evenement1j
        \brief Classe representant un evenement sur un jour
*/
class Evenement1j : public EvenementTrad
{
    Duree duree;
public:
    //! Constructeur a partir d'une date, d'un horaire,d'une duree et d'un sujet
    /*! \param ddeb date de debut
        \param tdeb horaire de debut
        \param dur duree
        \param suj sujet
        */
    Evenement1j(const QDate& ddeb, const QTime& tdeb,const Duree& dur, const QString& suj)
        : EvenementTrad(ddeb,tdeb,suj), duree(dur) {}
    virtual ~Evenement1j(){}

    const Duree& getDuree() const { return duree; }
    void setDuree(const Duree& dur) { duree = dur; }

    /**
     * @brief Clone un evenement sur 1 jour
     *
     */
    virtual Evenement1j* clone() const;
    virtual QString toString() const;


    virtual bool isEvenement1j() const { return true; }
    virtual bool isEvenementPj() const { return false; }
    virtual bool isRdv() const { return false; }


    virtual void toXml(QXmlStreamWriter&s) const;
    /**
     * @brief construit un evenement sur 1 jour a partir du stream xml
     * @param xml
     * @return pointeur dur l'objet cree
     */
    static Evenement1j* getFromXml(QXmlStreamReader& xml);


};

#endif // EVENEMENT1J_H
