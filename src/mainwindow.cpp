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




    ui->calendarWidget->setSelectedDate(QDate::currentDate());










    QObject::connect(ui->treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(maj_descripteurs()));
    QObject::connect(ui->Bouton_ajouter_tache,SIGNAL(clicked()),this,SLOT(ajouterTache()));
    QObject::connect(ui->Bouton_supprimer_tache,SIGNAL(clicked()),this,SLOT(supprimerTache()));
    QObject::connect(ui->Bouton_supprimer_projet,SIGNAL(clicked()),this,SLOT(supprimerProjet()));
    QObject::connect(ui->Bouton_ajouter_projet,SIGNAL(clicked()),this,SLOT(ajouterProjet()));






    scenes[0] = new JourGraphicScene("Lundi",QDate(1994,3,20),0,0,100,480,960,ui->graphicsView_lundi);
    scenes[1] = new JourGraphicScene("Mardi",QDate(1994,3,21),0,0,100,480,960,ui->graphicsView_mardi);
    scenes[2] = new JourGraphicScene("Mercredi",QDate(1994,3,22),0,0,100,480,960,ui->graphicsView_mercredi);
    scenes[3] = new JourGraphicScene("Jeudi",QDate(1994,3,23),0,0,100,480,960,ui->graphicsView_jeudi);
    scenes[4] = new JourGraphicScene("Vendredi",QDate(1994,3,24),0,0,100,480,960,ui->graphicsView_vendredi);
    scenes[5] = new JourGraphicScene("Samedi",QDate(1994,3,25),0,0,100,480,960,ui->graphicsView_samedi);
    scenes[6] = new JourGraphicScene("Dimanche",QDate(1994,3,26),0,0,100,480,960,ui->graphicsView_dimanche);

    for(int i=0;i<7;i++)
        Agenda::getInstance().ajouterObservateur(scenes[i]);
    //QGraphicsRectItem *rect1 = scene->ajouterEvenement("tache1",QTime(12,0),Duree(2,30));

    //QGraphicsRectItem *rect2 = scene->ajouterEvenement("tache2",QTime(16,15),Duree(0,30));

    //QGraphicsRectItem *rect3 = scene->ajouterEvenement("tache3",QTime(20,20),Duree(0,15));






  //  QObject::connect(rect1,SIGNAL(clicked()),this,SLOT(test()));
    //QObject::connect(rect2,SIGNAL(clicked()),this,SLOT(test()));
   // QObject::connect(rect3,SIGNAL(clicked()),this,SLOT(test()));
    //scene->addRect(0,0,50,50,QPen(Qt::red));


    ui->graphicsView_lundi->setScene(scenes[0]);
    ui->graphicsView_mardi->setScene(scenes[1]);
    ui->graphicsView_mercredi->setScene(scenes[2]);
    ui->graphicsView_jeudi->setScene(scenes[3]);
    ui->graphicsView_vendredi->setScene(scenes[4]);
    ui->graphicsView_samedi->setScene(scenes[5]);
    ui->graphicsView_dimanche->setScene(scenes[6]);

   /* QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QBrush redBrush(Qt::red);
    QPen pen(Qt::black);
*/
   /*QGraphicsRectItem *rect = scene->addRect(0,0,100,100,pen,redBrush);
    rect->setFlag(QGraphicsItem::ItemIsFocusable);

    QGraphicsTextItem *txt = scene->addText("losc");*/


    QObject::connect(ui->graphicsView_lundi->scene(),SIGNAL(selectionChanged()),this,SLOT(detaillerEvenement_lundi()));
    QObject::connect(ui->graphicsView_mardi->scene(),SIGNAL(selectionChanged()),this,SLOT(detaillerEvenement_mardi()));
    QObject::connect(ui->graphicsView_mercredi->scene(),SIGNAL(selectionChanged()),this,SLOT(detaillerEvenement_mercredi()));
    QObject::connect(ui->graphicsView_jeudi->scene(),SIGNAL(selectionChanged()),this,SLOT(detaillerEvenement_jeudi()));
    QObject::connect(ui->graphicsView_vendredi->scene(),SIGNAL(selectionChanged()),this,SLOT(detaillerEvenement_vendredi()));
    QObject::connect(ui->graphicsView_samedi->scene(),SIGNAL(selectionChanged()),this,SLOT(detaillerEvenement_samedi()));
    QObject::connect(ui->graphicsView_dimanche->scene(),SIGNAL(selectionChanged()),this,SLOT(detaillerEvenement_dimanche()));

    QObject::connect(ui->calendarWidget,SIGNAL(selectionChanged()),this,SLOT(maj_dates()));


    for(int i=0;i<7;i++)
        scenes[i]->mise_a_jour();
    maj_treeWidget();
    maj_dates();
}

void MainWindow::detaillerEvenement_lundi()
 {
    bool mise_a_jour_necessaire = false;
    QList<QGraphicsItem*> itemsList = ui->graphicsView_lundi->scene()->selectedItems();
    QList<QGraphicsItem*>::iterator iter = itemsList.begin();
    QList<QGraphicsItem*>::iterator end = itemsList.end();

    while(iter!=end)
    {
        mise_a_jour_necessaire = true;
        Evenement* evt = dynamic_cast<EvenementGraphicItem*>(*iter)->getEvenement();
        EvenementInfoDialog *dial = new EvenementInfoDialog(evt);
        dial->exec();
        delete dial;
        iter++;
    }
    if(mise_a_jour_necessaire){
        dynamic_cast<JourGraphicScene*>(ui->graphicsView_lundi->scene())->mise_a_jour();
    }
 }
void MainWindow::detaillerEvenement_mardi()
{
   bool mise_a_jour_necessaire = false;
   QList<QGraphicsItem*> itemsList = ui->graphicsView_mardi->scene()->selectedItems();
   QList<QGraphicsItem*>::iterator iter = itemsList.begin();
   QList<QGraphicsItem*>::iterator end = itemsList.end();

   while(iter!=end)
   {
       mise_a_jour_necessaire = true;
       Evenement* evt = dynamic_cast<EvenementGraphicItem*>(*iter)->getEvenement();
       EvenementInfoDialog *dial = new EvenementInfoDialog(evt);
       dial->exec();
       delete dial;
       iter++;
   }
   if(mise_a_jour_necessaire){
       dynamic_cast<JourGraphicScene*>(ui->graphicsView_mardi->scene())->mise_a_jour();
   }
}
void MainWindow::detaillerEvenement_mercredi()
{
   bool mise_a_jour_necessaire = false;
   QList<QGraphicsItem*> itemsList = ui->graphicsView_mercredi->scene()->selectedItems();
   QList<QGraphicsItem*>::iterator iter = itemsList.begin();
   QList<QGraphicsItem*>::iterator end = itemsList.end();

   while(iter!=end)
   {
       mise_a_jour_necessaire = true;
       Evenement* evt = dynamic_cast<EvenementGraphicItem*>(*iter)->getEvenement();
       EvenementInfoDialog *dial = new EvenementInfoDialog(evt);
       dial->exec();
       delete dial;
       iter++;
   }
   if(mise_a_jour_necessaire){
       dynamic_cast<JourGraphicScene*>(ui->graphicsView_mercredi->scene())->mise_a_jour();
   }
}
void MainWindow::detaillerEvenement_jeudi()
{
   bool mise_a_jour_necessaire = false;
   QList<QGraphicsItem*> itemsList = ui->graphicsView_jeudi->scene()->selectedItems();
   QList<QGraphicsItem*>::iterator iter = itemsList.begin();
   QList<QGraphicsItem*>::iterator end = itemsList.end();

   while(iter!=end)
   {
       mise_a_jour_necessaire = true;
       Evenement* evt = dynamic_cast<EvenementGraphicItem*>(*iter)->getEvenement();
       EvenementInfoDialog *dial = new EvenementInfoDialog(evt);
       dial->exec();
       delete dial;
       iter++;
   }
   if(mise_a_jour_necessaire){
       dynamic_cast<JourGraphicScene*>(ui->graphicsView_jeudi->scene())->mise_a_jour();
   }
}
void MainWindow::detaillerEvenement_vendredi()
{
   bool mise_a_jour_necessaire = false;
   QList<QGraphicsItem*> itemsList = ui->graphicsView_vendredi->scene()->selectedItems();
   QList<QGraphicsItem*>::iterator iter = itemsList.begin();
   QList<QGraphicsItem*>::iterator end = itemsList.end();

   while(iter!=end)
   {
       mise_a_jour_necessaire = true;
       Evenement* evt = dynamic_cast<EvenementGraphicItem*>(*iter)->getEvenement();
       EvenementInfoDialog *dial = new EvenementInfoDialog(evt);
       dial->exec();
       delete dial;
       iter++;
   }
   if(mise_a_jour_necessaire){
       dynamic_cast<JourGraphicScene*>(ui->graphicsView_vendredi->scene())->mise_a_jour();
   }
}
void MainWindow::detaillerEvenement_samedi()
{
   bool mise_a_jour_necessaire = false;
   QList<QGraphicsItem*> itemsList = ui->graphicsView_samedi->scene()->selectedItems();
   QList<QGraphicsItem*>::iterator iter = itemsList.begin();
   QList<QGraphicsItem*>::iterator end = itemsList.end();

   while(iter!=end)
   {
       mise_a_jour_necessaire = true;
       Evenement* evt = dynamic_cast<EvenementGraphicItem*>(*iter)->getEvenement();
       EvenementInfoDialog *dial = new EvenementInfoDialog(evt);
       dial->exec();
       delete dial;
       iter++;
   }
   if(mise_a_jour_necessaire){
       dynamic_cast<JourGraphicScene*>(ui->graphicsView_samedi->scene())->mise_a_jour();
   }
}
void MainWindow::detaillerEvenement_dimanche()
{
   bool mise_a_jour_necessaire = false;
   QList<QGraphicsItem*> itemsList = ui->graphicsView_dimanche->scene()->selectedItems();
   QList<QGraphicsItem*>::iterator iter = itemsList.begin();
   QList<QGraphicsItem*>::iterator end = itemsList.end();

   while(iter!=end)
   {
       mise_a_jour_necessaire = true;
       Evenement* evt = dynamic_cast<EvenementGraphicItem*>(*iter)->getEvenement();
       EvenementInfoDialog *dial = new EvenementInfoDialog(evt);
       dial->exec();
       delete dial;
       iter++;
   }
   if(mise_a_jour_necessaire){
       dynamic_cast<JourGraphicScene*>(ui->graphicsView_dimanche->scene())->mise_a_jour();
   }
}




void MainWindow::maj_dates()
{
    QDate selected = ui->calendarWidget->selectedDate();
    int num_j = selected.dayOfWeek()-1;

    scenes[num_j]->setDate(selected);

    for(int i=1 ; i<=num_j ; i++)
        scenes[num_j-i]->setDate(selected.addDays(-i));

    for(int i=1 ; i + num_j < 7; i++)
        scenes[num_j+i]->setDate(selected.addDays(i));

    ui->date_lundi->setText(scenes[0]->getDate().toString("dd/MM/yyyy"));
    ui->date_mardi->setText(scenes[1]->getDate().toString("dd/MM/yyyy"));
    ui->date_mercredi->setText(scenes[2]->getDate().toString("dd/MM/yyyy"));
    ui->date_jeudi->setText(scenes[3]->getDate().toString("dd/MM/yyyy"));
    ui->date_vendredi->setText(scenes[4]->getDate().toString("dd/MM/yyyy"));
    ui->date_samedi->setText(scenes[5]->getDate().toString("dd/MM/yyyy"));
    ui->date_dimanche->setText(scenes[6]->getDate().toString("dd/MM/yyyy"));

    for(int i=0;i<7;i++)
        scenes[i]->mise_a_jour();

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
    /*for(int i=0;i<7;i++)
        scenes[i]->mise_a_jour();*/
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

