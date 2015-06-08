#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QDebug>
#include <vector>
#include <QDate>
#include <map>
#include "duree.h"





class Tache {
    QString identificateur;
    QString titre;
    Duree duree;
    QDate disponibilite;
    QDate echeance;
    bool preemptive;
    Tache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool preempt=false):
            identificateur(id),titre(t),duree(dur),disponibilite(dispo),echeance(deadline),preemptive(preempt){}
    Tache(const Tache& t);
    Tache& operator=(const Tache&);
    friend class Projet;
    friend class TacheManager; //a supprimer
public:
    QString getId() const { return identificateur; }
    void setId(const QString& str);
    QString getTitre() const { return titre; }
    void setTitre(const QString& str) { titre=str; }
    Duree getDuree() const { return duree; }
    void setDuree(const Duree& d) { duree=d; }
    QDate getDateDisponibilite() const {  return disponibilite; }
    QDate getDateEcheance() const {  return echeance; }
    void setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e) {
        if (e<disp) throw CalendarException("erreur Tache : date echeance < date disponibilite");
        disponibilite=disp; echeance=e;
    }
    bool isPreemptive() const { return preemptive; }
    void setPreemptive() { preemptive=true; }
    void setNonPreemptive() { preemptive=false; }

    void afficher() const{
        qDebug() << "//// tache ////////";
        qDebug() << identificateur;
        qDebug() << titre;
    }
};

QTextStream& operator<<(QTextStream& f, const Tache& t);










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
    std::map<QString, Tache*> taches;

    //! Constructeur à partir d'un titre, d'une description, d'une date de disponibilite et d'une date d'echeance
    /*! \param t titre
        \param desc description du projet
        \param dispo date à laquelle le projet pourra debuter
        \param ech date à laquelle le projet devra etre termine
        */
    Projet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech)
        : titre(t), description(desc), disponibilite(dispo), echeance(ech) {
        if(disponibilite>echeance)
            throw CalendarException("erreur, Projet, date disponibilite > date echeance");
    }
    ~Projet();
    friend class ProjetManager;
public:
    void afficher() const{ //temporaire
        qDebug()<<"------------- Projet ----------- \n ";
        qDebug()<<"titre : "<<titre;
        //std::cout<<"duree : "<<duree<<std::endl;
        qDebug()<<"desc : "<<description;
        qDebug()<<"dispo : "<<disponibilite;
        qDebug()<<"echeacne : "<<echeance;
    }
    Tache& ajouterTache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& ech, bool preempt=false);
    Tache& getTache(const QString& id);
    const Tache& getTache(const QString &id) const;

    class iterator
    {
        friend class Projet;
        std::map<QString, Tache*>::iterator it;
        iterator(const std::map<QString, Tache*>::iterator &i) : it(i) {}
    public:
        iterator() {}
        Tache& getCurrent() { return *(it->second); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(taches.begin()); }
    iterator end() { return iterator(taches.end()); }
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
    static ProjetManager* instance;

public:
    static ProjetManager& getInstance();
    static void libererInstance();
    Projet& ajouterProjet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech);
    Projet& getProjet(const QString& t);
    const Projet& getProjet(const QString &t) const;

    class iterator
    {
        friend class ProjetManager;
        std::map<QString, Projet*>::iterator it;
        iterator(const std::map<QString, Projet*>::iterator& i) : it(i) {}
    public:
        iterator() {}
        Projet& getCurrent() { return *(it->second); }

        iterator& operator++() { ++it; return *this;}
        bool operator!=(const iterator& at) const {
            return it != at.it;
        }
    };
    iterator begin() { return iterator(projets.begin()); }
    iterator end() { return iterator(projets.end()); }


};










#endif // PROJET_H
