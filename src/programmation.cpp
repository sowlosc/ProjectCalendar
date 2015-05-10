#include "programmation.h"


QTextStream& operator<<(QDataStream& f, const Programmation& p);


ProgrammationManager* ProgrammationManager::instance = 0;

void ProgrammationManager::addItem(Programmation* t){
    programmations.push_back(t);
}

Programmation* ProgrammationManager::trouverProgrammation(const Tache& t)const{
    for(std::vector<Programmation*>::const_iterator it = programmations.begin(); it != programmations.end(); ++it)
        if (&(*it)->getTache() == &t )
            return *it;
    return 0;
}

void ProgrammationManager::ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h){
    if (trouverProgrammation(t)) throw CalendarException("erreur, ProgrammationManager, Programmation deja existante");
    Programmation* newt=new Programmation(t,d,h);
    addItem(newt);
}


ProgrammationManager::~ProgrammationManager(){
    for(std::vector<Programmation*>::iterator it = programmations.begin(); it != programmations.end(); ++it)
        delete *it;
}


