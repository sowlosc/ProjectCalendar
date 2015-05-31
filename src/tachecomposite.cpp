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


QString TacheComposite::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\">" << getTitre().toStdString() << " ("<< getId().toStdString() << ")</h2>";
    ss << "<table align=\"center\" cellpadding=\"4\" >";
    ss << "<tr><td>type</td><td>tache composite</td></tr>";
    ss << "<tr><td>date disponibilité </td><td> " << getDisponibilite().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>date échéance </td><td> " << getEcheance().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>description</b></td><td> " << getDescription().toStdString()<< "</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}

