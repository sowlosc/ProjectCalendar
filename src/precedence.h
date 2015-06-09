#ifndef PRECEDENCE_H
#define PRECEDENCE_H

//#include "tache.h"
#include <QXmlStreamWriter>
//#include "projet.h"
class Projet;
class Tache;
class Precedence
{
    friend class PrecedenceManager;
    const Tache* pred;
    const Tache* succ;
    //QString nomProjet;
    const Projet* projet;
    Precedence(const Tache* t1, const Tache* t2,const Projet* proj)
        : pred(t1) , succ(t2), projet(proj) {}
    ~Precedence() {}
public:
    const Tache* getPredecesseur() const { return pred; }
    const Tache* getSuccesseur() const { return succ; }
    const Projet* getProjet() const { return projet; }
    //const QString& getProjet() const { return nomProjet; }

    void toXml(QXmlStreamWriter&) const;
};

#endif // PRECEDENCE_H
