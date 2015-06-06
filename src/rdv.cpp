#include "rdv.h"



void Rdv::ajouterPersonne(const QString &nom)
{
    for(std::vector<QString>::iterator it = personnes.begin() ; it != personnes.end() ; it++)
        if(*it == nom)
            throw CalendarException("Erreur, Rdv, cette personne est deja enregistree");
    personnes.push_back(nom);
}


void Rdv::retirerPersonne(const QString &nom)
{
    std::vector<QString>::iterator it;
    for(it = personnes.begin() ; it != personnes.end() ; it++)
        if(*it == nom){
            personnes.erase(it);
            return ;
        }
    throw CalendarException("Erreur, Rdv, cette personne n'etait pas enregistree");
}


QString Rdv::toString() const
{
    std::stringstream ss;
    ss << "<html><body><h2 align=\"center\" >" << getSujet().toStdString() << "</h2>";
    ss << "<table align=\"center\" cellpadding=\"8\" >";

    ss << "<tr><td>Date :</td><td> " << getDate().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Horaire :</td><td> " << getHoraire().toString().toStdString()<< "</td></tr>";
    ss << "<tr><td>Durée :</td><td> " << getDuree() << "</td></tr>";
    ss << "<tr><td>Lieu :</td><td> " << getLieu().toStdString() << "</td></tr>";
    ss << "<tr><td>Participants :</td><td> "     << "</td></tr>";
    for(std::vector<QString>::const_iterator it = personnes.begin(); it != personnes.end(); ++it)
        ss << (*it).toStdString() << "<br>";
    ss << "</td></tr>";
    ss << "</table></body></html>";
    return ss.str().c_str();
}

Rdv* Rdv::clone() const
{
    return new Rdv(*this);
}
