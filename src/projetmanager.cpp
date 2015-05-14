#include "projetmanager.h"


ProjetManager* ProjetManager::instance = 0;

ProjetManager& ProjetManager::getInstance()
{
    if(!instance) instance = new ProjetManager;
    return *instance;
}

void ProjetManager::libererInstance()
{
    if(instance) delete instance;
    instance = 0;
}


Projet& ProjetManager::ajouterProjet(const QString &t, const QString &desc, const QDate &dispo, const QDate &ech)
{
    if(projets[t])
        throw CalendarException("erreur, ProjetManager, projet deja existant");
    projets[t] = new Projet(t,desc,dispo,ech);
    return *projets[t];
}

Projet& ProjetManager::getProjet(const QString &t)
{
    return *projets.at(t); //renvoie une exception si le projet n'existe pas
}

const Projet& ProjetManager::getProjet(const QString &t) const
{
    return *projets.at(t); //renvoie une exception si le projet n'existe pas
}
