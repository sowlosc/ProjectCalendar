#include "projet.h"


QTextStream& operator<<(QTextStream& fout, const Tache& t){
    fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    fout<<t.getDuree()<<"\n";
    fout<<t.getDateDisponibilite().toString()<<"\n";
    fout<<t.getDateEcheance().toString()<<"\n";
    return fout;
}

/*
void Tache::setId(const QString& str){
  if (TacheManager::getInstance().isTacheExistante((str))) throw CalendarException("erreur TacheManager : tache id deja existante");
  identificateur=str;
}
*/














Projet::~Projet()
{
    qDebug() << "Destructeur Projet : desctruction des taches";
    for(std::map<QString, Tache*>::iterator it = taches.begin(); it != taches.end(); ++it)
        delete it->second;
}


Tache& Projet::ajouterTache(const QString &id, const QString &t, const Duree &dur, const QDate &dispo, const QDate &ech, bool preempt)
{
    if(taches[id]) throw CalendarException("erreur, Projet, tache deja existante");
    taches[id] = new Tache(id,t,dur,dispo,ech,preempt);;
    return *taches[id];
}

Tache& Projet::getTache(const QString &id)
{
    if(!taches[id]) throw CalendarException("erreur, Projet, tache inexistante");
    return *taches[id];
}

const Tache& Projet::getTache(const QString &id) const
{
    if(!taches.at(id)) throw CalendarException("erreur, Projet, tache inexistante");
    return *taches.at(id);
}











ProjetManager* ProjetManager::instance = 0;

ProjetManager::~ProjetManager()
{
    qDebug() << "Appel desctructeur ProjetManager\n";
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

Projet& ProjetManager::getProjet(const QString &t)
{
    if(!projets[t]) throw CalendarException("erreur, ProjetManager, projet inexistant");
    return *projets[t];
}

const Projet& ProjetManager::getProjet(const QString &t) const
{
    if(!projets.at(t)) throw CalendarException("erreur, ProjetManager, projet inexistant");
    return *projets.at(t);
}


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


