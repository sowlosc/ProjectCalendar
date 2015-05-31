#include "tachecomposite.h"

TacheComposite::~TacheComposite()
{
    for(std::map<QString, Tache*>::iterator it = sousTaches.begin(); it != sousTaches.end() ; ++it)
        delete (it->second);
}

/*
TacheComposite& TacheComposite::operator<<(Tache* t)
{
    /* id est gere par le logiciel
     * 1->1.1 1.2 1.3 ...
     * id = num tacheMere + . + nbSousTacheDeLaTacheMere+1
     *
    if(sousTaches[t->getId()])
        throw CalendarException("erreur, TacheComposite, sous tache deja existante");
    sousTaches[t->getId()] = t;
    return *this;
}*/

void TacheComposite::ajouterSousTache(Tache *t)
{
    if(sousTaches[t->getId()])
        throw CalendarException("Erreur, TacheCompisite, cette sous tache existe deja");
    else
        sousTaches[t->getId()] = t;
}


void TacheComposite::retirerSousTache(Tache *t)
{
    if(sousTaches[t->getId()]){
        delete sousTaches[t->getId()];
        sousTaches.erase(t->getId());
    }
}
