#ifndef PRECEDENCE_H
#define PRECEDENCE_H

//#include "tache.h"
#include <QXmlStreamWriter>
class Tache;
class Precedence
{
    friend class PrecedenceManager;
    const Tache* pred;
    const Tache* succ;
    QString nomProjet;
    Precedence(const Tache* t1, const Tache* t2,const QString& proj)
        : pred(t1) , succ(t2), nomProjet(proj) {}
    ~Precedence() {}
public:
    const Tache* getPredecesseur() const { return pred; }
    const Tache* getSuccesseur() const { return succ; }
    const QString& getProjet() const { return nomProjet; }

    void toXml(QXmlStreamWriter&) const;
};

#endif // PRECEDENCE_H
