#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ag(Agenda::getInstance()),
    pm(ProjetManager::getInstance()), predm(PrecedenceManager::getInstance())
{
    ui->setupUi(this);
    maj_treeWidget();
    QObject::connect(ui->treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(maj_descripteurs()));
    QObject::connect(ui->Bouton_ajouter_tache,SIGNAL(clicked()),this,SLOT(ajouterTache()));

}


void MainWindow::construct_recurs_tree(Tache* t, QTreeWidgetItem *root)
{
    TreeTacheItem *nouv = new TreeTacheItem(root,t);
    nouv->setText(0,t->getDescription());
    if(t->isComposite())
    {
        TacheComposite* tc = dynamic_cast<TacheComposite*>(t);

        for(TacheComposite::iterator cit = tc->begin() ; cit != tc->end() ; ++cit)
        {
            construct_recurs_tree(&(*cit),nouv);
        }
    }
}

void MainWindow::maj_treeWidget()
{
    ui->treeWidget->clear(); //detruit et libere memoire

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabels(QStringList() << "Projets");

    // Affichage des projets, des taches et des sous-taches
    for(ProjetManager::iterator it = pm.begin() ; it != pm.end() ; ++it)
    {
        TreeProjetItem *nouv = new TreeProjetItem(ui->treeWidget,&(*it));
        nouv->setText(0,(*it).getTitre());

        for(Projet::iterator pit = (*it).begin() ; pit != (*it).end(); ++pit)
        {
            construct_recurs_tree(&(*pit),nouv);
        }
    }
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
    TreeProjetItem* projet = dynamic_cast<TreeProjetItem*>(current->getParentProject());

    if(current && !current->isUnitaire())
    {   //projet ou tache composite qui ont une methode ajouter tache

        int retour = 0;
        if(current->isProjetItem())
        {
            AjoutTacheDialog *dial = new AjoutTacheDialog(this,projet->getProjet()->getTitre(),"");
            retour = dial->exec();
        }else
        {
            TreeTacheItem *curTacheItem = dynamic_cast<TreeTacheItem*>(current);
            AjoutTacheDialog *dial = new AjoutTacheDialog(this,projet->getProjet()->getTitre(),curTacheItem->getTache()->getId());
            retour = dial->exec();
        }

        Projet& p  = ProjetManager::getInstance().getProjet("projet2");
        if(retour == QDialog::Accepted)
        {std::cout<<"\nRGREGBRTBRTB-------- exception levee -------\n";
            try{maj_treeWidget();}catch(...){std::cout<<"\nRGREGBRTBRTB-------- exception levee -------\n";}
         }
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







TreeItem* TreeItem::getParentProject()
{
    QTreeWidgetItem *cur = this, *pred = this->parent();
    while(pred)
    {
        cur = pred;
        pred = pred->parent();
    }
    return dynamic_cast<TreeItem*>(cur);
}



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

