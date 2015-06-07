#include <QApplication>


#include <iostream>
#include "rdv.h"
#include "projetmanager.h"
#include "projet.h"
#include "agenda.h"
#include "evenementpj.h"
#include "tacheunitaire.h"
#include "programmationpartietache.h"
#include "tachecomposite.h"

#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow& w = MainWindow::getInstance();
    ProjetManager& pm = ProjetManager::getInstance();
    PrecedenceManager& prm = PrecedenceManager::getInstance();

    pm.ajouterObservateur(&w);
    prm.ajouterObservateur(&w);
    for(ProjetManager::iterator it = ProjetManager::getInstance().begin(); it != ProjetManager::getInstance().end() ; ++it)
        (*it).ajouterObservateur(&w);


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


    pm.ajouterProjet("projet1","mon premier projet",QDate(2015,5,30),QDate(2015,6,14));
    pm.ajouterProjet("projet2","Mon deuxieme projet",QDate(2015,7,1),QDate(2015,8,30));

    pm.getProjet("projet1").ajouterObservateur(&w);
    pm.getProjet("projet2").ajouterObservateur(&w);


       std::cout<<":::::::::::::::::::::: Mes Projets :::::::::::::::::::::::: \n";
    for(ProjetManager::iterator it = pm.begin() ; it != pm.end() ; ++it)
        std::cout<<"titre : "<<(*it).getTitre().toStdString()<<"\ndesc : "<<(*it).getDescription().toStdString()<<"\n\n";

    std::cout<<"description du projet1 = "<<pm.getProjet("projet1").getDescription().toStdString()<<std::endl;

    try{ pm.supprimerProjet("projdezet1"); } catch(CalendarException e) { std::cerr<<e.getInfo().toStdString()<<std::endl; }

    std::cout<<":::::::::::::::::::::: Mes Projets :::::::::::::::::::::::: \n";
    for(ProjetManager::iterator it = pm.begin() ; it != pm.end() ; ++it)
            std::cout<<"titre : "<<(*it).getTitre().toStdString()<<"\ndesc : "<<(*it).getDescription().toStdString()<<"\n\n";

    Projet& pj = pm.getProjet("projet1");

    pj.ajouterTache(new TacheUnitaire("t1","tache 1",QDate(2015,6,1),QDate(2015,6,7),"descritption le la tache 1",Duree(1,1)));
    pj.ajouterTache(new TacheUnitaire("t2","tache 2",QDate(2015,6,7),QDate(2015,6,12),"descritption le la tache 2",Duree(2,20)));

    for(Projet::iterator it = pj.begin() ; it != pj.end() ; ++it)
        std::cout<<(*it).getTitre().toStdString()<<std::endl;

    std::cout<<"--------------------------\n";
    Agenda& ag = Agenda::getInstance();


    Evenement1j evt1(QDate(1994,3,20),QTime(19,50,0),Duree(3,0),"Finale CdF");
    Rdv evt2(QDate(1994,3,20),QTime(13,0,0),Duree(3,0),"Exemanen IC06","PG");
    Rdv evt99(QDate(1994,3,21),QTime(6,0,0),Duree(1,0),"Evenement test","PG");

    evt2.ajouterPersonne("Brice Roy");
    EvenementPj evt3(QDate(2015,6,20),QTime(0,0,0),QDate(2015,7,1),QTime(0,0,0),"Examens finaux");

    ag << evt1 << evt2 << evt3 << evt99;

    for(Agenda::iterator it = ag.begin() ; it != ag.end() ; ++it)
        std::cout<<(*it).toString().toStdString()<<std::endl;

    std::cout<<"Suppression evt2 : \n";

  //  ag >> ag.ge;

    for(Agenda::iterator it = ag.begin() ; it != ag.end() ; ++it)
        std::cout<<(*it).toString().toStdString()<<std::endl;

    std::cout<<"---------------------------------\n";

    TacheUnitaire *t1 = new TacheUnitaire("t1","tache1",QDate(2015,6,1),QDate(2015,7,7),"Initialisation",Duree(1,0),false);
    TacheUnitaire *t2 = new TacheUnitaire("t2","tache2",QDate(2015,6,1),QDate(2015,7,7),"Developpement",Duree(3,0),true);
    TacheComposite *t3 = new TacheComposite("t3","taches3",QDate(2015,6,1),QDate(2015,7,7),"Tahce complexe");

    TacheUnitaire *t4 = new TacheUnitaire("t3.1","sousTache1",QDate(2015,8,1),QDate(2015,9,7),"Initialisation",Duree(1,40),false);
    TacheUnitaire *t5 = new TacheUnitaire("t3.2","sousTache2",QDate(2015,8,1),QDate(2015,9,7),"Developpement",Duree(2,35),true);

    TacheComposite *t6 = new TacheComposite("t3.3","sousTache3",QDate(2015,6,1),QDate(2015,7,7),"sous Tahce complexe");

    TacheUnitaire *t7 = new TacheUnitaire("t3.3.1","sssousTache1",QDate(2015,8,1),QDate(2015,9,7),"sssoust1",Duree(1,40),false);
    TacheUnitaire *t8 = new TacheUnitaire("t3.3.2","sssousTache2",QDate(2015,8,1),QDate(2015,9,7),"sssout2",Duree(2,35),true);

    t1->ajouterObservateur(&w);
    t2->ajouterObservateur(&w);
    t3->ajouterObservateur(&w);
    t4->ajouterObservateur(&w);
    t5->ajouterObservateur(&w);
    t6->ajouterObservateur(&w);
    t7->ajouterObservateur(&w);
    t8->ajouterObservateur(&w);


    pm.getProjet("projet2").ajouterTache(t1);
    pm.getProjet("projet2").ajouterTache(t2);
    pm.getProjet("projet2").ajouterTache(t3);

    t3->ajouterSousTache(t4);
    t3->ajouterSousTache(t5);
    t3->ajouterSousTache(t6);

    t6->ajouterSousTache(t7);
    t6->ajouterSousTache(t8);

    TacheComposite *c1 = new TacheComposite("c1","c1",QDate(2015,6,1),QDate(2015,7,7),"Tahce complexe1");
    TacheComposite *c2 = new TacheComposite("c2","c2",QDate(2015,6,1),QDate(2015,7,7),"Tahce complexe2");
    TacheComposite *c3 = new TacheComposite("c3","c3",QDate(2015,6,1),QDate(2015,7,7),"Tahce complexe3");

    c2->ajouterObservateur(&w);
    c1->ajouterObservateur(&w);
    c3->ajouterObservateur(&w);

    pm.getProjet("projet2").ajouterTache(c1);
    c1->ajouterSousTache(c2);
    c2->ajouterSousTache(c3);





    for(Projet::iterator it = pj.begin() ; it != pj.end() ; ++it)
        std::cout<<(*it).getDescription().toStdString()<<std::endl;

    ProgrammationTache evt4(QDate(1994,3,22),QTime(12,0,0),t2);
    ProgrammationPartieTache evt5(QDate(1994,3,22),QTime(18,30,0),Duree(1,30),t5);
    EvenementPj evtP(QDate(1994,3,24),QTime(10,0),QDate(1994,3,26),QTime(17,30),"Projet LO21");



    ag << evt5 << evt4 << evtP;





    std::cout<<"____________________________________\n";
    prm.ajouterPrecedence(*t1,*t2);
    prm.ajouterPrecedence(*t1,*t3);


    prm.ajouterPrecedence(*t3,*t4);
    prm.ajouterPrecedence(*t1,*t4);
    prm.ajouterPrecedence(*t5,*t6);
    prm.ajouterPrecedence(*t1,*t7);


    for(Tache::const_succ_iterator it = t1->beginSucc(); it != t1->endSucc(); ++it)
        std::cout << "Tache succ  -> " << (*it)->getTitre().toStdString() << "\n";


    for(Tache::const_pred_iterator it = t3->beginPred() ; it!= t3->endPred() ; ++it)
        std::cout << "Tache pred -> " << (*it)->getTitre().toStdString() << "\n";


    w.show();


    //std::cout << "resulte getSousTache = " << pm.getProjet("projet2").getTache("t3.2")->getDescription().toStdString() << "\n";


     return a.exec();
}

