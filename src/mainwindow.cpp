#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabels(QStringList() << "Projets");

    // Affichage des projets, des taches et des sous-taches
    for(ProjetManager::iterator it = pm.begin() ; it != pm.end() ; ++it)
    {
        TreeProjetItem *nouv = new TreeProjetItem(ui->treeWidget,&(*it));
        nouv->setText(0,(*it).getTitre());
        //nouv->setText(1,(*it).getDescription());

        for(Projet::iterator pit = (*it).begin() ; pit != (*it).end(); ++pit)
        {
            Tache& tc = *pit;
            TreeTacheItem *tache = new TreeTacheItem(nouv,&(*pit));
            tache->setText(0,tc.getTitre());
            //tache->setText(1,tc.getDescription());

            if(tc.isComposite())
            {
                TacheComposite& t = dynamic_cast<TacheComposite&>(tc);

                for(TacheComposite::iterator cit = t.begin() ; cit != t.end() ; ++cit)
                {
                    TreeTacheItem *sstache = new TreeTacheItem(tache,&(*cit));
                    sstache->setText(0,(*cit).getTitre());
                    //sstache->setText(0,(*cit).getDescription());
                }
            }
        }
    }
    QObject::connect(ui->treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(maj_descripteurs()));
    QObject::connect(ui->Bouton_ajouter_tache,SIGNAL(clicked()),this,SLOT(ajouterTache()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::maj_descripteurs()
{
    TreeItem *curr = dynamic_cast<TreeItem*>(ui->treeWidget->currentItem());
    std::stringstream ss;
    ss << curr->getDescriptionHtml().toStdString();
    ui->descripteur->setHtml(ss.str().c_str());
}

void MainWindow::ajouterTache()
{

    TreeItem* current = dynamic_cast<TreeItem*>(ui->treeWidget->currentItem());

    if(current && !current->isUnitaire())
    {   //projet ou tache composite qui ont une methode ajouter tache
        if(current->isProjetItem()){
            TreeProjetItem *curProjetItem = dynamic_cast<TreeProjetItem*>(current);
            AjoutTacheDialog *dial = new AjoutTacheDialog(this,curProjetItem->getProjet());
            dial->open();
        }else
        {
            TreeTacheItem *curTacheItem = dynamic_cast<TreeTacheItem*>(current);
            AjoutTacheDialog *dial = new AjoutTacheDialog(this,dynamic_cast<TacheComposite*>(curTacheItem->getTache()));
            dial->open();
        }

        maj_treeWidget();

    }
}






/*
 * idee a continuer
 *
 * Le tree donne le titre du projet + le titre de la tache ou on va ajouter
 * AjoutTacheDialog va recherche a partir du pm
 * et c'est le pm qui va l'ajouter
 *
 * pour obtenir les description c'etait ok avec les pointeur
 * mais ici pour creer non
 *
 * 1) recherche tache dans projet rech(id)
 *
*/











QString TreeTacheItem::getDescriptionHtml() const
{
    if(!tache)
        throw CalendarException("Erreur, TreeTacheItem, lie a aucune tache");
    return tache->toString();
}

QString TreeProjetItem::getDescriptionHtml() const
{
    if(!projet)
        throw CalendarException("Erreur, TreeProjetItem, lie a aucun projet");
    return projet->toString();
}

