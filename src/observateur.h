#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H


class Observateur
{
public:
    virtual void mise_a_jour() = 0;
};

class Observable
{
    virtual void ajouterObservateur(Observateur*) = 0;
    virtual void supprimerObservateur(Observateur*)=0;
    virtual void notifier()=0;
};

#endif // OBSERVATEUR_H
