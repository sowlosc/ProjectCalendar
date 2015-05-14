#ifndef PRECEDENCE_H
#define PRECEDENCE_H

#include "tache.h"

class Precedence
{
    friend class PrecedenceManager;
    Tache* pred;
    Tache* succ;
    Precedence(Tache* t1, Tache* t2)
        : pred(t1) , succ(t2) {}
    ~Precedence() {}
public:
    const Tache& getPredecesseur() const { return *pred; }
    const Tache& getSuccesseur() const { return *succ; }

};

#endif // PRECEDENCE_H
