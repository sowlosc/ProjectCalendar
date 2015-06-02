#include "ajouttachedialog.h"
#include "ui_ajouttachedialog.h"

AjoutTacheDialog::AjoutTacheDialog(QWidget *parent , const QString& proj, const QString& tCompo) :
    QDialog(parent), nomProjet(proj), nomTacheComposite(tCompo),
    ui(new Ui::AjoutTacheDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->checkBox_composite,SIGNAL(stateChanged(int)),this,SLOT(activerDuree(int)));
}
/*
AjoutTacheDialog::AjoutTacheDialog(QWidget *parent,Projet *p) :
    QDialog(parent), projet(p),tCompo(0),
    ui(new Ui::AjoutTacheDialog)
{
    ui->setupUi(this);
    QObject:connect(ui->checkBox_composite,SIGNAL(stateChanged(int)),this,SLOT(activerDuree(int)));
}*/

AjoutTacheDialog::~AjoutTacheDialog()
{
    delete ui;
}


void AjoutTacheDialog::activerDuree(int b)
{
    bool x = (b?false:true);
    ui->label_duree->setVisible(x);
    ui->timeEdit_duree->setVisible(x);
}


void AjoutTacheDialog::accept()
{
    QString id = ui->lineEdit_id->text();
    QString titre = ui->lineEdit_titre->text();
    QString desc = ui->textEdit_desc->toPlainText();
    QDate dispo = ui->dateEdit_dispo->date();
    QDate ech = ui->dateEdit_ech->date();

    std::cout << "id = "<<id.toStdString()<<"\n";
    std::cout << "titre = "<<titre.toStdString()<<"\n";
    std::cout << "desc = "<<desc.toStdString()<<"\n";



   // if(id == "" || titre == "" || desc == "")
    //    throw CalendarException("Erreur, AjoutTacheDialog, une tache doit avoir des champs valides");
    /*
     * faire les verification
     * ou faire un try
     * */

    Tache* t;
    if(ui->checkBox_composite->isChecked())
    {
        t = new TacheComposite(id,titre,dispo,ech,desc);
    }else if(ui->checkBox_unitaire_non_preemptive->isChecked())
    {
        QTime time = ui->timeEdit_duree->time();
        Duree duree(time.hour(),time.minute());
        t = new TacheUnitaire(id,titre,dispo,ech,desc,duree,false);
    }else
    {
        QTime time = ui->timeEdit_duree->time();
        Duree duree(time.hour(),time.minute());
        t = new TacheUnitaire(id,titre,dispo,ech,desc,duree,true);
    }

    std::cout<<"=========== fin creation nouvelle tache ===========\n";
    std::cout<<t->toString().toStdString()<<"\n";
    if(!t)
        std::cout<<"\n !!!!!!!!!!!!!!!PROBLEM !!!!!!!!!!!!!!!!!";


    if(nomTacheComposite == "")
    {
        //on ajoute dans un projet

        ProjetManager& pm = ProjetManager::getInstance();
        Projet& proj = pm.getProjet(nomProjet);
        std::cout<<"=========== ajout dans un projet  "<< proj.getTitre().toStdString() << "===========\n";
        proj.ajouterTache(t);
    }else
    {
        //on ajoute dans une tache composite

        ProjetManager& pm = ProjetManager::getInstance();
        Projet& proj = pm.getProjet(nomProjet);
        TacheComposite* tc = dynamic_cast<TacheComposite*>(proj.getTache(nomTacheComposite));
        if(!tc)
            throw CalendarException("Erreur, AjoutTacheDialog, ajout dans une tache inexistante");
        std::cout<<"=========== ajout dans une tache dans "<< tc->toString().toStdString() <<"===========\n";

        tc->ajouterSousTache(t);

    }


    std::cout<<"---------------------------------------------------------- FIN AJOUT\n\n\n";
    this->done(1);

}
