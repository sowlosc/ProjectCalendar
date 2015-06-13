#ifndef PROJET_H
#define PROJET_H

#include <map>
#include <set>
#include <QString>
#include <sstream>
#include "duree.h"
#include "tache.h"
#include "tachecomposite.h"
#include "observateur.h"


/*! \class Projet
        \brief Classe representant projet
*/
class Projet : public Observable
{
    friend class ProjetManager;

    QString titre;
    QString description;
    QDate disponibilite;
    QDate echeance;
    /**
     * @brief Ensemble des taches du projet
     */
    std::map<QString, Tache*> taches;



    //! Constructeur prive a partir d'un titre, d'une description, d'une date de disponibilite et d'une date d'echeance
    /*! \param t titre
        \param desc description
        \param dispo disponibilite
        \param ech echeance
        */
    Projet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech)
        :titre(t), description(desc), disponibilite(dispo), echeance(ech) {
        if(disponibilite>echeance)
            throw CalendarException("erreur, Projet, échéance < disponibilité");
    }
    ~Projet();

public:
    /**
     * @brief Atjoue une tache au projet
     * @param t tache
     */
    void ajouterTache(Tache* t);
    /**
     * @brief Retire une tache du projet
     * @param id identificateur de la tache
     */
    void retirerTache(const QString& id);



    Tache *getTache(const QString& id);
    /**
     * @brief Verifie si le projet contient une certaine tache
     * @param t tache a rechercher
     * @return 0 ou 1
     */
    bool contientTache(const Tache *t);

    /**
     * @brief Retourne un pointeur sur le map de la tache parente de celle passe en parametre
     * @param id identificateur de la tache
     *
     */
    std::map<QString, Tache *> *getTacheMap(const QString &id);

    const QString& getTitre() const { return titre; }
    const QString& getDescription() const { return description; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }

    void setTitre(const QString& t) { titre = t; }
    void setDescription(const QString& d) { description = d; }
    void setDisponibilite(const QDate& d) { disponibilite = d; }
    void setEcheance(const QDate& d) { echeance = d; }

    QString toString() const;

    void toXml(QXmlStreamWriter&) const;

    void save(const QString &f);
    void load(const QString& f);


    /*! \class iterator
            \brief Classe permettant d'iterer sur les taches du projet
    */
    class iterator
    {
        friend class Projet;
        std::map<QString, Tache*>::iterator it;
        iterator(const std::map<QString,Tache*>::iterator& i) : it(i) {}

    public:
        Tache& operator*() { return *(it->second); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    /**
     * @brief Retourne un iterateur sur la premiere tache
     *
     */
    iterator begin() { return iterator(taches.begin()); }

    /**
     * @brief Retourne un iterateur apres la derniere tache
     *
     */
    iterator end() { return iterator(taches.end()); }

    /*! \class const_iterator
            \brief Classe permettant d'iterer sur les taches du projet
    */
    class const_iterator
    {
        friend class Projet;
        std::map<QString, Tache*>::const_iterator it;
        const_iterator(const std::map<QString,Tache*>::const_iterator& i) : it(i) {}

    public:
        const Tache& operator*() { return *(it->second); }
        const_iterator& operator++() { ++it; return *this; }
        bool operator!=(const const_iterator& at) const { return it != at.it; }
    };
    /**
     * @brief Retourne un iterateur const sur la premier tache
     *
     */
    const_iterator begin() const { return const_iterator(taches.begin()); }
    /**
     * @brief Retourne un iterateur const apres la derniere tache
     *
     */
    const_iterator end() const { return const_iterator(taches.end()); }

};





#endif // PROJET_H
