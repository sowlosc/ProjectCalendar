#include "projet.h"



Projet& Projet::ajouterTache(Tache *t)
{
    if(taches[t->getId()])
        throw CalendarException("erreur, Projet, id deja existant");
    taches[t->getId()] = t;
    return *this;
}

void Projet::retirerTache(Tache *t)
{
    if(taches[t->getId()]){
        delete taches[t->getId()];
        taches.erase(t->getId());
    }
}

Tache& Projet::getTache(const QString &id)
{
   return *taches.at(id); //renvoie une exception si la tache n'existe pas
}

const Tache& Projet::getTache(const QString &id) const
{
   return *taches.at(id); //renvoie une exception si la tache n'existe pas
}
