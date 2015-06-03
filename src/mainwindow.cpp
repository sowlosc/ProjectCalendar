#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow* MainWindow::instance = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ag(Agenda::getInstance()),
    pm(ProjetManager::getInstance()), predm(PrecedenceManager::getInstance())
{
    ui->setupUi(this);
    maj_treeWidget();
    QObject::connect(ui->treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(maj_descripteurs()));
    QObject::connect(ui->Bouton_ajouter_tache,SIGNAL(clicked()),this,SLOT(ajouterTache()));
    QObject::connect(ui->Bouton_supprimer_tache,SIGNAL(clicked()),this,SLOT(supprimerTache()));
    QObject::connect(ui->Bouton_supprimer_projet,SIGNAL(clicked()),this,SLOT(supprimerProjet()));
    QObject::connect(ui->Bouton_ajouter_projet,SIGNAL(clicked()),this,SLOT(ajouterProjet()));



    scene = new JourGraphicScene("lundi",QDate(1994,3,20),0,0,100,480,960,ui->graphicsView);


    QGraphicsRectItem *rect1 = scene->ajouterEvenement("tache1",QTime(12,0),Duree(2,30));

    QGraphicsRectItem *rect2 = scene->ajouterEvenement("tache2",QTime(16,15),Duree(0,30));

    QGraphicsRectItem *rect3 = scene->ajouterEvenement("tache3",QTime(20,20),Duree(0,15));


  //  QObject::connect(rect1,SIGNAL(clicked()),this,SLOT(test()));
    //QObject::connect(rect2,SIGNAL(clicked()),this,SLOT(test()));
   // QObject::connect(rect3,SIGNAL(clicked()),this,SLOT(test()));
    //scene->addRect(0,0,50,50,QPen(Qt::red));
    ui->graphicsView->setScene(scene);

   /* QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QBrush redBrush(Qt::red);
    QPen pen(Qt::black);
*/
   /*QGraphicsRectItem *rect = scene->addRect(0,0,100,100,pen,redBrush);
    rect->setFlag(QGraphicsItem::ItemIsFocusable);

    QGraphicsTextItem *txt = scene->addText("losc");*/


    QObject::connect(ui->graphicsView->scene(),SIGNAL(selectionChanged()),this,SLOT(test()));

    scene->mise_a_jour();
    maj_treeWidget();
}

void MainWindow::test()
 { std::cout << "______________ LOSC ___________\n";
    for(QList<QGraphicsItem *>::iterator it = ui->graphicsView->scene()->selectedItems().begin() ; it != ui->graphicsView->scene()->selectedItems().end() ; ++it)
       {}//std::cout << "- " <<  dynamic_cast<TacheGraphicItem*>(*it)->getEvenement().getDate().toString().toStdString() << "\n";//mise a jour du descripteur
 }

void MainWindow::construct_recurs_tree(Tache* t, QTreeWidgetItem *root)
{
    TreeTacheItem *nouv = new TreeTacheItem(root,t);
    nouv->setText(0,t->getTitre());
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


void MainWindow::mise_a_jour()
{
    maj_treeWidget();
    scene->mise_a_jour();
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
    }
}

void MainWindow::supprimerTache()
{
    TreeItem* current = dynamic_cast<TreeItem*>(ui->treeWidget->currentItem());
    TreeProjetItem* projet = dynamic_cast<TreeProjetItem*>(current->getParentProject());

    if(current && !current->isProjetItem())
    {
        TreeTacheItem* ta = dynamic_cast<TreeTacheItem*>(current);
        projet->getProjet()->retirerTache(ta->getTache()->getId());
    }
}

void MainWindow::supprimerProjet()
{
    TreeItem* current = dynamic_cast<TreeItem*>(ui->treeWidget->currentItem());
    if(current && current->isProjetItem())
    {
        TreeProjetItem* p = dynamic_cast<TreeProjetItem*>(current);
        ProjetManager& pm = ProjetManager::getInstance();
        pm.supprimerProjet(p->getProjet()->getTitre());
    }
}

void MainWindow::ajouterProjet()
{
    AjoutProjetDialog *dial = new AjoutProjetDialog;
    dial->exec();
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
 *
 *
 * --> adaptateur entre projet et tache composite
 * --> observateur , les precedence observent le projetmanager, les projets et les taches
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

