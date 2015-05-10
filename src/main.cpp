#include <QApplication>
#include "Calendar.h"
#include "projet.h"
#include <map>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


   ProjetManager& pm = ProjetManager::getInstance();




    pm.ajouterProjet("projet1","mon premier projet",QDate(1994,3,2),QDate(2002,1,4)).ajouterTache("t1","ma premiere tache",Duree(4,44),QDate(4,2,1),QDate(4,3,3),false);

    pm.getProjet("projet1").ajouterTache("t2","ma deuxieme tache",Duree(3,3),QDate(4,4,4),QDate(5,5,5),true);
    pm.getProjet("projet1").ajouterTache("t3","ma troisieme tache",Duree(3,3),QDate(4,4,5),QDate(5,5,5),true);
    pm.getProjet("projet1").ajouterTache("t4","ma quatrieme tache",Duree(3,3),QDate(4,4,7),QDate(5,5,5),true);

    pm.ajouterProjet("projet2","mon second projet",QDate(2012,4,7),QDate(2014,7,15));

    pm.ajouterProjet("Projet3","mon troisieme projet",QDate(4,4,2032),QDate(5,5,2045));

    for(ProjetManager::iterator it = pm.begin() ; it != pm.end() ; ++it){
        it.getCurrent().afficher();
        for(Projet::iterator pt = it.getCurrent().begin(); pt != it.getCurrent().end(); ++pt)
            pt.getCurrent().afficher();
    }

    pm.libererInstance();



     return a.exec();
}
