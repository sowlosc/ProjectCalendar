#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <vector>

/*! \class ProjetManager
        \brief Classe permettant de gerer des projets
        Cet unique objet (singleton) permet de creer de nouveau projets ou d'en supprimer
*/
class ProjetManager
{
    std::vector<Projet*> projets;
    ProjetManager();
    ~ProjetManager();
    ProjetManager(const ProjetManager&);
    ProjetManager& operator=(const ProjetManager&);
    static ProjetManager* instance;

public:
    static ProjetManager& getInstance();
    static void libererInstance();



};








/*! \class Projet
        \brief Classe permettant de manipuler des projets
        Les projets de cette classe contiendront des taches
*/
class Projet
{
    QString titre;
    QString description;
    Duree duree;            //sera recalcule quand on ajoute des taches
    QDate disponibilite;
    QDate echeance;
    Tache** taches;


public:
    //! Constructeur à partir d'un titre, d'une description, d'une date de disponibilite et d'une date d'echeance
    /*! \param t titre
        \param desc description du projet
        \param dispo date à laquelle le projet pourra debuter
        \param ech date à laquelle le projet devra etre termine
        */
    Projet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech)
        : titre(t), description(desc), disonibilite(dispo), echeance(ech) {}
    ~Projet(); // Il faudra supprimer toutes les taches du projet
};

#endif // PROJET_H
