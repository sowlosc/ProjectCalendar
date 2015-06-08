#include "tache.h"
//#include "precedencemanager.h"


Tache::~Tache()
{
    PrecedenceManager& prm =PrecedenceManager::getInstance();
    PrecedenceManager::iterator iter = prm.begin();
    PrecedenceManager::iterator end = prm.end();
    std::vector<const Precedence*> tab_a_suppr;
    while(iter != end){
        if((*iter).getPredecesseur() == this || (*iter).getSuccesseur() == this)
            tab_a_suppr.push_back(&(*iter));
        ++iter;
    }

    for(std::vector<const Precedence*>::iterator it = tab_a_suppr.begin() ; it != tab_a_suppr.end(); ++it)
        prm.retirerPrecedence(*((*it)->getPredecesseur()),*((*it)->getSuccesseur()));

}
