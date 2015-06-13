#ifndef PRECEDENCE_H
#define PRECEDENCE_H

#include <QXmlStreamWriter>

class Projet;
class Tache;


/*! \class Precedence
        \brief Classe representant des contraintes de precedence
*/
class Precedence
{
    friend class PrecedenceManager;
    /**
     * @brief Tache qui precede
     */
    const Tache* pred;
    /**
     * @brief Tache qui suit
     */
    const Tache* succ;
    /**
     * @brief Projet au quel appartiennent les deux taches
     */
    const Projet* projet;

    //! Constructeur de 2 pointeurs sur les taches et d'un pointeur sur le projet de ces taches
    /*! \param t1 tache precedente
        \param t2 tache successeure
        \param proj projet des taches
        */
    Precedence(const Tache* t1, const Tache* t2,const Projet* proj)
        : pred(t1) , succ(t2), projet(proj) {}
    ~Precedence() {}
public:
    const Tache* getPredecesseur() const { return pred; }
    const Tache* getSuccesseur() const { return succ; }
    const Projet* getProjet() const { return projet; }
    void toXml(QXmlStreamWriter&) const;
};

#endif // PRECEDENCE_H
