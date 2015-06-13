#ifndef PROGRAMMATIONTACHE_H
#define PROGRAMMATIONTACHE_H

#include "evenement.h"
#include "tacheunitaire.h"

/*! \class ProgrammationTache
        \brief Classe representant la programmation complete d'une tache
*/
class ProgrammationTache : public Evenement
{

    TacheUnitaire* tache;
    Projet* projet;

public:

    //! Constructeur a partir d'une date, d'une heure, d'une tache et d'une projet
    /*! \param ddeb date
        \param tdeb horaire
        \param t pointeur sur la tache programmee
        \param p pointeur sur le projet
        */
    ProgrammationTache(const QDate& ddeb, const QTime& tdeb, TacheUnitaire *t,Projet* p)
        :Evenement(ddeb,tdeb), tache(t), projet(p) {
        if(ddeb < tache->getDisponibilite() || ddeb > tache->getEcheance())
            throw CalendarException("erreur, ProgrammationTache, date non valide");
    }
    virtual ~ProgrammationTache(){ }

    TacheUnitaire* getTache() const { return tache; }
    const Projet* getProjet() const { return projet; }

    virtual const Duree& getDuree() const { return tache->getDuree(); }
    virtual const QString& getSujet() const { return tache->getTitre(); }

    virtual ProgrammationTache* clone() const;
    virtual QString toString() const;
    virtual void toXml(QXmlStreamWriter&) const;
    /**
     * @brief construit une programmation d'une tache a partir du stream xml
     * @param xml
     * @return pointeur sur l'objet cree
     */
    static ProgrammationTache* getFromXml(QXmlStreamReader& xml);

    virtual bool isProgrammationTache() const { return true; }
    virtual bool isProgrammationPartieTache() const { return false; }
    virtual bool isEvenementTrad() const { return false; }
    virtual bool isEvenement1j() const { return false; }
    virtual bool isEvenementPj() const { return false; }
    virtual bool isRdv() const { return false; }


};

#endif // PROGRAMMATIONTACHE_H
