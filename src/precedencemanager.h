#ifndef PRECEDENCEMANAGER_H
#define PRECEDENCEMANAGER_H

#include <vector>
#include "precedence.h"
#include "exception.h"
#include "observateur.h"
#include "enregistrable.h"


/*! \class PrecedenceManager
        \brief Classe permettant de gerer les contraintes de precedence (singleton)
*/
class PrecedenceManager : public Observable, public Enregistrable
{
    /**
     * @brief Ensemble des contraintes de precedences
     */
    std::vector<Precedence*> precedences;
    static PrecedenceManager* instance;
    /**
     * @brief Constructeur prive
     */
    PrecedenceManager() {}
    /**
     * @brief Constructeur de recopie prive
     */
    PrecedenceManager(const PrecedenceManager&);
    /**
     * @brief Operateur d'affectation prive
     *
     */
    PrecedenceManager& operator=(const PrecedenceManager&);
    ~PrecedenceManager() {}
public:
    /*! Methode statique permettant de recupere ou creer l'unique instance
    */
    static PrecedenceManager& getInstance();
    /*! Methode statique permettant de liberer l'unique instance
    */
    static void libereInstace();

    /**
     * @brief Recherche une precedence
     * @param t1 tache qui precede
     * @param t2 tache qui succede
     * @return Iterateur sur la precedence trouvee ou sur end
     */
    std::vector<Precedence*>::iterator findPrecedence(const Tache& t1, const Tache& t2);
    /**
     * @brief Ajoute une precedence
     * @param t1 tache qui precede
     * @param t2 tache qui succede
     * @param proj projet au quel appartiennent les deux taches
     */
    void ajouterPrecedence(const Tache &t1, const Tache &t2, const Projet *proj);

    /**
     * @brief Retire une precedence
     * @param t1 tache qui precede
     * @param t2 tache qui succede
     */
    void retirerPrecedence(const Tache &t1, const Tache &t2);

    virtual void save(const QString& f);
    virtual void load(const QString& f);


    /*! \class iterator
            \brief Classe permettant d'iterer sur les contraintes de precedence
    */
    class iterator
    {
        friend class PrecedenceManager;
        std::vector<Precedence*>::iterator it;
        iterator(std::vector<Precedence*>::iterator i) : it(i) {}
    public:
        const Precedence& operator*() { return *(*it); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    /**
     * @brief Retourne un iterateur sur la premiere precedence
     *
     */
    iterator begin() { return iterator(precedences.begin()); }

    /**
     * @brief Retourne un iterateur apres la derniere precedence
     *
     */
    iterator end() { return iterator(precedences.end()); }

};

#endif // PRECEDENCEMANAGER_H
