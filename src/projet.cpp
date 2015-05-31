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

QString Projet::toString() const
{
    std::stringstream ss;

    ss << "<html><body><h2 align=\"center\">     " << getTitre().toStdString() << "</h2>";
    ss << "<table align=\"center\" cellpadding=\"4\" >";
    ss << "<tr><td>type</td><td>projet</td></tr>";
    ss << "<tr><td>date disponibilité </td><td> " << getDisponibilite().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>date échéance </td><td> " << getEcheance().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>description</b></td><td> " << getDescription().toStdString()<< "</td></tr>";
    ss << "</table></body></html>";

    return ss.str().c_str();
}
