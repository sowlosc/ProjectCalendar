#include "projet.h"

ProjetManager::Handler ProjetManager::handler = Handler();

ProjetManager::~ProjetManager()
{
    for(std::map<QString, Projet*>::iterator it = projets.begin() ; it != projets.end(); ++it)
        delete it->second;
}




Projet& ProjetManager::ajouterProjet(const QString &t, const QString &desc, const QDate &dispo, const QDate &ech)
{
    if(projets[t])
        throw CalendarException("erreur, ProjetManager, projet existe deja");
    projets[t] = new Projet(t,desc,dispo,ech);
    return *projets[t];
}



ProjetManager& ProjetManager::getInstance()
{
    if(!handler.instance) handler.instance = new ProjetManager;
    return *(handler.instance);
}


void ProjetManager::libererInstance()
{
    if(handler.instance) delete handler.instance;
    handler.instance = 0;
}


