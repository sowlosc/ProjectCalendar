#include "projet.h"



Projet& Projet::ajouterTache(Tache *t)
{
    if(taches.find(t->getId()) != taches.end())
        throw CalendarException("erreur, Projet, id deja existant");
    taches[t->getId()] = t;
    return *this;
}

void Projet::retirerTache(Tache *t)
{
    if(taches.find(t->getId()) != taches.end()){
        delete taches[t->getId()];
        taches.erase(t->getId());
    }
}

Tache* Projet::getTache(const QString &id)
{
   if(taches.find(id) != taches.end())
       return taches[id];
   else
   {
       for(Projet::iterator it = this->begin() ; it != this->end() ; ++it)
       {
           if((*it).isComposite())
           {
               Tache* result = dynamic_cast<TacheComposite&>(*it).getSousTache(id);
               if(result)
                       return result;
           }
       }
       return 0;
   }
}



// ---------------------------------- fonction d'affichage des projet en console -------------------
void Projet::affTache(Tache* t)
{
    if(t){
    if(t->isComposite())
    {
        std::cout << "tache composite : " << t->getDescription().toStdString() <<"\n";
        TacheComposite *tc = dynamic_cast<TacheComposite*>(t);
        for(TacheComposite::iterator it = tc->begin()  ;it != tc->end() ; ++it)
            affTache(&(*it));
    }else
        std::cout<<"tache : "<<t->getDescription().toStdString()<<"\n";
}
}

void Projet::describe()
{
    std::cout << "\n\n======= Description projet "<<getTitre().toStdString()<<" =======\n";
    for(Projet::iterator it = this->begin() ; it != this->end() ; ++it)
    {
        std::cout<<"----->\n";
        affTache(&(*it));
    }
    std::cout<<"\n\n";
}

//------------------------------------------------------------------------------------------


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
