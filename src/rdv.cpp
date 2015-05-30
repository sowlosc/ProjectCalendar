#include "rdv.h"



void Rdv::addPersonne(const QString &nom)
{
    for(std::vector<QString>::iterator it = personnes.begin() ; it != personnes.end() ; it++)
        if(*it == nom)
            throw CalendarException("Erreur, Rdv, cette personne est deja enregistree");
    personnes.push_back(nom);
}


void Rdv::removePersonne(const QString &nom)
{
    std::vector<QString>::iterator it;
    for(it = personnes.begin() ; it != personnes.end() ; it++)
        if(*it == nom){
            personnes.erase(it);
            return ;
        }
    throw CalendarException("Erreur, Rdv, cette personne n'etait pas enregistree");
}
