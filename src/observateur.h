#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

#include <set>

class Observateur
{
public:
    virtual void mise_a_jour() = 0;
};

class Observable
{
    std::set<Observateur*> obs;

  public:
    void ajouterObservateur(Observateur *o) { obs.insert(o); }
    void supprimerObservateur(Observateur *o) { obs.erase(o); }
    void notifier() {
        for(std::set<Observateur*>::iterator it = obs.begin() ; it != obs.end() ; ++it)
            (*it)->mise_a_jour();
    }
};

#endif // OBSERVATEUR_H
