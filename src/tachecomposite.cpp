#include "tachecomposite.h"



TacheComposite& TacheComposite::operator<<(Tache* t)
{
    /* id est gere par le logiciel
     * 1->1.1 1.2 1.3 ...
     * id = num tacheMere + . + nbSousTacheDeLaTacheMere+1
     * */
    if(sousTaches[t->getId()])
        throw CalendarException("erreur, TacheComposite, sous tache deja existante");
    sousTaches[t->getId()] = t;
    return *this;
}



void TacheComposite::retirerSousTache(Tache *t)
{
    if(sousTaches[t->getId()]){
        delete sousTaches[t->getId()];
        sousTaches.erase(t->getId());
    }
}
