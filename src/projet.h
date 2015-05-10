#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QDebug>
#include <vector>
#include <map>
#include "Calendar.h"
#include <iostream>



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
        : titre(t), description(desc), disponibilite(dispo), echeance(ech) {}
    ~Projet() {}; // Il faudra supprimer toutes les taches du projet

    void afficher() const{ //temporaire
        std::cout<<"losc"<<std::endl;
        qDebug()<<"------------- Projet ----------- \n ";
        qDebug()<<"titre : "<<titre;
        //std::cout<<"duree : "<<duree<<std::endl;
        qDebug()<<"desc : "<<description;
        qDebug()<<"dispo : "<<disponibilite;
        qDebug()<<"echeacne : "<<echeance;
    }
};






/*! \class ProjetManager
        \brief Classe permettant de gerer des projets
        Cet unique objet (singleton) permet de creer de nouveau projets ou d'en supprimer
*/
class ProjetManager
{
    std::map<QString, Projet*> projets;
    ProjetManager() {}
    ~ProjetManager();
    ProjetManager(const ProjetManager&);
    ProjetManager& operator=(const ProjetManager&);

    struct Handler{
        ProjetManager* instance;
        Handler() : instance(0) {}
        ~Handler() { if(instance) delete instance; }
    };
    static Handler handler;

public:
    static ProjetManager& getInstance();
    static void libererInstance();
    Projet& ajouterProjet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech);

    class iterator
    {
        friend class ProjetManager;
        std::map<QString, Projet*>::iterator it;
        iterator(const std::map<QString, Projet*>::iterator& i) : it(i) {}
    public:
        iterator() {}
        Projet& getCurrent() {
            return *(it->second);
        }

        iterator& operator++() {
            ++it;
            return *this;
        }
        bool operator!=(const iterator& at) const {
            return it != at.it;
        }
    };
    iterator begin() { return iterator(projets.begin()); }
    iterator end() { return iterator(projets.end()); }


};










#endif // PROJET_H
