#include <QApplication>


#include <iostream>
#include "rdv.h"
#include "projetmanager.h"
#include "projet.h"
#include "agenda.h"
#include "evenementpj.h"
#include "tacheunitaire.h"
#include "programmationpartietache.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     Rdv r(QDate(),QTime(),Duree(1,1),"losc","lille");

     r.ajouterPersonne("Mavuba");
     r.ajouterPersonne("Renard");
     r.ajouterPersonne("Boufal");
     try{r.ajouterPersonne("Renard");}catch(CalendarException e){std::cerr<<e.getInfo().toStdString();}
     std::cout<<"Allez le losc\n\n";
     const std::vector<QString>& p = r.getPersonnes();
     for(std::vector<QString>::const_iterator it = p.begin(); it != p.end() ; ++it)
         std::cout<<(*it).toStdString()<<std::endl;

     std::cout<<"Remove de Boufal\n";
     r.retirerPersonne("Boufal");
     for(std::vector<QString>::const_iterator it = p.begin(); it != p.end() ; ++it)
         std::cout<<(*it).toStdString()<<std::endl;



     std::cout<<"Parcours avec l'iterator \n \n";
     for(Rdv::personnes_iterator it = r.begin_personnes(); it != r.end_personnes() ; ++it)
     {
         std::cout<<"Personne : "<<(*it).toStdString()<<std::endl;
     }

     ProjetManager& pm = ProjetManager::getInstance();
    pm.ajouterProjet("projet1","mon premier projet",QDate(2015,5,30),QDate(2015,6,14));
    pm.ajouterProjet("projet2","Mon deuxieme projet",QDate(2015,7,1),QDate(2015,8,30));

       std::cout<<":::::::::::::::::::::: Mes Projets :::::::::::::::::::::::: \n";
    for(ProjetManager::iterator it = pm.begin() ; it != pm.end() ; ++it)
        std::cout<<"titre : "<<(*it).getTitre().toStdString()<<"\ndesc : "<<(*it).getDescription().toStdString()<<"\n\n";

    std::cout<<"description du projet1 = "<<pm.getProjet("projet1").getDescription().toStdString()<<std::endl;

    try{ pm.retirerProjet("projdezet1"); } catch(CalendarException e) { std::cerr<<e.getInfo().toStdString()<<std::endl; }

    std::cout<<":::::::::::::::::::::: Mes Projets :::::::::::::::::::::::: \n";
    for(ProjetManager::iterator it = pm.begin() ; it != pm.end() ; ++it)
            std::cout<<"titre : "<<(*it).getTitre().toStdString()<<"\ndesc : "<<(*it).getDescription().toStdString()<<"\n\n";

    Projet& pj = pm.getProjet("projet1");

    pj.ajouterTache(new Tache("t1","tache 1",QDate(2015,6,1),QDate(2015,6,7),"descritption le la tache 1"));
    pj.ajouterTache(new Tache("t2","tache 2",QDate(2015,6,7),QDate(2015,6,12),"descritption le la tache 2"));

    for(Projet::iterator it = pj.begin() ; it != pj.end() ; ++it)
        std::cout<<(*it).getTitre().toStdString()<<std::endl;

    std::cout<<"--------------------------\n";
    Agenda& ag = Agenda::getInstance();


    EvenementTrad evt1(QDate(2015,6,30),QTime(20,50,0),"Finale CdF");
    Rdv evt2(QDate(2015,7,2),QTime(13,0,0),Duree(1,0),"Exemanen IC06","PG");
    evt2.ajouterPersonne("Brice Roy");
    EvenementPj evt3(QDate(2015,6,20),QTime(0,0,0),QDate(2015,7,1),QTime(0,0,0),"Examens finaux");

    ag << evt1 << evt2 << evt3;

    for(Agenda::iterator it = ag.begin() ; it != ag.end() ; ++it)
        std::cout<<(*it).toString().toStdString()<<std::endl;

    std::cout<<"Suppression evt2 : \n";

  //  ag >> ag.ge;

    for(Agenda::iterator it = ag.begin() ; it != ag.end() ; ++it)
        std::cout<<(*it).toString().toStdString()<<std::endl;

    Agenda::libererInstance();
    std::cout<<"---------------------------------\n";

    TacheUnitaire *t1 = new TacheUnitaire("t3","tache1",QDate(2015,6,1),QDate(2015,7,7),"Initialisation",Duree(1,0),false);
    TacheUnitaire *t2 = new TacheUnitaire("t4","tache1",QDate(2015,6,1),QDate(2015,7,7),"Developpement",Duree(3,0),true);

    pj.ajouterTache(t1);
    pj.ajouterTache(t2);

    for(Projet::iterator it = pj.begin() ; it != pj.end() ; ++it)
        std::cout<<(*it).getDescription().toStdString()<<std::endl;

    ProgrammationTache evt4(QDate(2015,6,2),QTime(12,0,0),t1);
    ProgrammationPartieTache evt5(QDate(2015,6,2),QTime(14,0,0),Duree(1,0),t2);





     return a.exec();
}

