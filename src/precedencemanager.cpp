#include "precedencemanager.h"

PrecedenceManager* PrecedenceManager::instance = 0;

PrecedenceManager& PrecedenceManager::getInstance()
{
    if(!instance) instance = new PrecedenceManager;
    return *instance;
}

void PrecedenceManager::libereInstace()
{
    if(instance) delete instance;
    instance = 0;
}

std::vector<Precedence*>::iterator PrecedenceManager::findPrecedence(const Tache& t1, const Tache &t2)
{
    for(std::vector<Precedence*>::iterator it = precedences.begin() ; it != precedences.end() ; ++it)
        if((*it)->pred == &t1 && (*it)->succ == &t2)
            return it;
    return precedences.end();
}


void PrecedenceManager::ajouterPrecedence(Tache &t1, Tache &t2)
{
    /* il faut verifier que la precedence n'existe pas deja
     * et qu'elle ne provoque pas d'incoherence
     * */
    Precedence *p = new Precedence(&t1,&t2);
    precedences.push_back(p);
}

void PrecedenceManager::retirerPrecedence(const Tache &t1, const Tache &t2)
{
    /* il faut verif qu'elle existe
     * */
    std::vector<Precedence*>::iterator position = findPrecedence(t1,t2);
    if(position != precedences.end())
        delete (*position);
    precedences.erase(position);
}



