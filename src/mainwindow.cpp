#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <typeinfo>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ag(Agenda::getInstance()),
    pm(ProjetManager::getInstance()), predm(PrecedenceManager::getInstance())
{
    ui->setupUi(this);
    maj_treeWidget();

}

void MainWindow::maj_treeWidget()
{
    ui->treeWidget->setColumnCount(2);
    ui->treeWidget->setHeaderLabels(QStringList() << "Tache" << "Description");

    // Affichage des projets, des taches et des sous-taches
    for(ProjetManager::iterator it = pm.begin() ; it != pm.end() ; ++it)
    {
        QTreeWidgetItem *nouv = new QTreeWidgetItem(ui->treeWidget);
        nouv->setText(0,(*it).getTitre());
        nouv->setText(1,(*it).getDescription());

        for(Projet::iterator pit = (*it).begin() ; pit != (*it).end(); ++pit)
        {
            Tache& tc = *pit;
            QTreeWidgetItem *tache = new QTreeWidgetItem(nouv);
            tache->setText(0,tc.getTitre());
            tache->setText(1,tc.getDescription());

            if(tc.isComposite())
            {
                TacheComposite& t = dynamic_cast<TacheComposite&>(tc);

                for(TacheComposite::iterator cit = t.begin() ; cit != t.end() ; ++cit)
                {
                    QTreeWidgetItem *sstache = new QTreeWidgetItem(tache);
                    sstache->setText(0,(*cit).getTitre());
                    sstache->setText(0,(*cit).getDescription());
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
