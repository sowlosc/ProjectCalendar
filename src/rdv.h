#ifndef RDV_H
#define RDV_H

#include "evenement1j.h"
#include <QtXml>

/*! \class Rdv
        \brief Classe representant un rendez-vous
*/
class Rdv : public Evenement1j
{
    QString lieu;
    /**
     * @brief Ensembles des noms des participants
     */
    std::vector<QString> personnes;
public:


    //! Constructeur a partir d'une date, d'une heure,d'une duree,d'un sujet et d'un lieu
    /*! \param ddeb date
        \param tdeb horaire
        \param dur duree
        \param l lieu
        */
    Rdv( const QDate& ddeb,
         const QTime& tdeb,
         const Duree& dur,
         const QString& suj,
         const QString& l)
            : Evenement1j(ddeb,tdeb,dur,suj), lieu(l) {}
    virtual ~Rdv(){}

    const QString& getLieu() const { return lieu; }
    void setLieu(const QString& l) { lieu = l; }
    const std::vector<QString>& getPersonnes() const { return personnes; }

    /**
     * @brief Ajoute un participant
     * @param nom
     */
    void ajouterPersonne(const QString& nom);
    /**
     * @brief Retire un participant
     * @param nom
     */
    void retirerPersonne(const QString& nom);

    virtual QString toString() const;
    virtual Rdv* clone() const;

    void toXml(QXmlStreamWriter &) const;
    static Rdv* getFromXml(QXmlStreamReader &xml);

    virtual bool isRdv() const { return true; }



    /*! \class personnes_iterator
            \brief Classe permettant d'iterer sur les personnes participants a un rendez-vous
    */
    class personnes_iterator{
        std::vector<QString>::iterator it;
        friend class Rdv;
        personnes_iterator(const std::vector<QString>::iterator iter) : it(iter) {}
    public:
        QString& operator*() { return *it; }
        personnes_iterator& operator++() { ++it; return *this; }
        bool operator!=(const personnes_iterator& at) { return it != at.it; }
    };

    /**
     * @brief Retourne un iterateur sur la premiere personne
     * @return
     */
    personnes_iterator begin_personnes() { return personnes_iterator(personnes.begin()); }
    /**
     * @brief Retourne un iterateur apres la derniere personne
     * @return
     */
    personnes_iterator end_personnes() { return personnes_iterator(personnes.end()); }


    /*! \class const_personnes_iterator
            \brief Classe permettant d'iterer sur les personnes participants a un rendez-vous
    */
    class const_personnes_iterator{
        std::vector<QString>::const_iterator it;
        friend class Rdv;
        const_personnes_iterator(const std::vector<QString>::const_iterator iter) : it(iter) {}
    public:
        const QString& operator*() { return *it; }
        const_personnes_iterator& operator++() { ++it; return *this; }
        bool operator!=(const const_personnes_iterator& at) { return it != at.it; }
    };

    /**
     * @brief Retourne un iterateur const sur la premier personne
     * @return
     */
    const_personnes_iterator begin_personnes() const { return const_personnes_iterator(personnes.begin()); }

    /**
     * @brief Retourne un iterateur const apres la derniere personne
     * @return
     */
    const_personnes_iterator end_personnes() const { return const_personnes_iterator(personnes.end()); }

};

#endif // RDV_H
