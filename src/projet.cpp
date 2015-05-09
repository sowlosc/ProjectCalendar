#include "projet.h"





ProjetManager& ProjetManager::getInstance()
{
    if(!instance) instance = new ProjectManager();
    return *instance;
}


void ProjetManager::libererInstance()
{
    if(instance) delete instance;
    instance = 0;
}


