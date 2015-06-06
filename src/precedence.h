#ifndef PRECEDENCE_H
#define PRECEDENCE_H

//#include "tache.h"
class Tache;
class Precedence
{
    friend class PrecedenceManager;
    const Tache* pred;
    const Tache* succ;
    Precedence(const Tache* t1, const Tache* t2)
        : pred(t1) , succ(t2) {}
    ~Precedence() {}
public:
    const Tache* getPredecesseur() const { return pred; }
    const Tache* getSuccesseur() const { return succ; }

};

#endif // PRECEDENCE_H
