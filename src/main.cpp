#include <QApplication>


#include <iostream>
#include "rdv.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     Rdv r(QDate(),QTime(),Duree(1,1),"losc","lille");

     r.addPersonne("Mavuba");
     r.addPersonne("Renard");
     r.addPersonne("Boufal");
     try{r.addPersonne("Renard");}catch(CalendarException e){std::cerr<<e.getInfo().toStdString();}
     std::cout<<"Allez le losc\n\n";
     const std::vector<QString>& p = r.getPersonnes();
     for(std::vector<QString>::const_iterator it = p.begin(); it != p.end() ; ++it)
         std::cout<<(*it).toStdString()<<std::endl;

     std::cout<<"Remove de Boufal\n";
     r.removePersonne("Boufal");
     for(std::vector<QString>::const_iterator it = p.begin(); it != p.end() ; ++it)
         std::cout<<(*it).toStdString()<<std::endl;


     return a.exec();
}
