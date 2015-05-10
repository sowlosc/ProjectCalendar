#include <QApplication>
#include "Calendar.h"
#include "projet.h"
#include <map>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


   ProjetManager& pm = ProjetManager::getInstance();




    pm.ajouterProjet("projet1","mon premier projet",QDate(1994,3,2),QDate(2002,1,4));


    pm.ajouterProjet("projet2","mon second projet",QDate(2012,4,7),QDate(2014,7,15));

    for(ProjetManager::iterator it = pm.begin() ; it != pm.end() ; ++it)
        it.getCurrent().afficher();

    pm.libererInstance();

     return a.exec();
}
