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
    MainWindow::getInstance().show();
    return a.exec();
}



