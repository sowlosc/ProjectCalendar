#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H

#include "projet.h"
#include "observateur.h"
#include "exception.h"
#include "enregistrable.h"

/*! \class ProjetManager
        \brief Classe permettant de gerer les projets (singleton)
*/
class ProjetManager : public Observable, public Enregistrable
{
    /**
     * @brief Ensemble des projets
     */
    std::map<QString,Projet*> projets;
    static ProjetManager* instance;

    /**
     * @brief Constructeur prive
     */
    ProjetManager() {}
    /**
     * @brief Constructeur de recopie prive
     */
    ProjetManager(const ProjetManager&);
    ~ProjetManager() {}
    /**
     * @brief Operateur d'affectation prive
     *
     */
    ProjetManager& operator=(const ProjetManager&);

public:
    /*! Methode statique permettant de recupere ou creer l'unique instance
    */
    static ProjetManager& getInstance();
    /*! Methode statique permettant de liberer l'unique instance
    */
    static void libererInstance();

    /**
     * @brief Ajoute un projet
     * @param t titre
     * @param desc description
     * @param dispo date de disponibilite
     * @param ech date d'echeance
     *
     */
    Projet& ajouterProjet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech);

    /**
     * @brief Supprime un projet
     * @param t titre
     */
    void supprimerProjet(const QString& t);


    Projet& getProjet(const QString& t);
    const Projet& getProjet(const QString &t) const;

    void save(const QString& f);
    void load(const QString& f);





    /*! \class iterator
            \brief Classe permettant d'iterer sur les projets
    */
    class iterator : public std::map<QString, Projet*>::iterator
    {
        public:
        Projet& operator*() { return *std::map<QString,Projet*>::iterator::operator *().second; }
        iterator(std::map<QString,Projet*>::iterator it) : std::map<QString,Projet*>::iterator(it) {}
    };

    /**
     * @brief Retourne un iterateur sur le premier projet
     * @return
     */
    iterator begin() { return iterator(projets.begin()); }
    /**
     * @brief Retourne un iterateur apres le dernier projet
     * @return
     */
    iterator end() { return iterator(projets.end()); }



    /*! \class const_iterator
            \brief Classe permettant d'iterer sur les projets
    */
    class const_iterator : public std::map<QString, Projet*>::const_iterator
    {
        public:
        const_iterator(std::map<QString, Projet*>::const_iterator it):
          std::map<QString,Projet*>::const_iterator(it) {}
        const Projet& operator*() const { return *std::map<QString,Projet*>::const_iterator::operator *().second; }
    };

    /**
     * @brief Retourne un iterateur const sur le premier projet
     * @return
     */
    const_iterator begin() const  { return const_iterator(projets.begin()); }
    /**
     * @brief Retourne un iterateur const apres le dernier projet
     * @return
     */
    const_iterator end() const { return const_iterator(projets.end()); }

};

#endif // PROJETMANAGER_H
