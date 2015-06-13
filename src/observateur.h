#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

#include <set>

/*! \class Observateur
        \brief Classe d'objets observateurs
*/
class Observateur
{
public:
    virtual void mise_a_jour() = 0;
};

/*! \class Observable
        \brief Classe d'objets Observable
*/
class Observable
{
protected:
    /**
     * @brief Ensemble des observateurs
     */
    std::set<Observateur*> obs;

  public:
    /**
     * @brief Ajoute un observateur
     * @param o observateur
     */
    void ajouterObservateur(Observateur *o) { obs.insert(o); }
    /**
     * @brief Supprime un observateur
     * @param o observateur
     */
    void supprimerObservateur(Observateur *o) { obs.erase(o); }
    /**
     * @brief Notifie tous les observateurs
     */
    void notifier() {
        for(std::set<Observateur*>::iterator it = obs.begin() ; it != obs.end() ; ++it)
            (*it)->mise_a_jour();
    }
};

#endif // OBSERVATEUR_H
