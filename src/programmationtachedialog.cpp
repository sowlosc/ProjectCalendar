#include "programmationtachedialog.h"
#include "ui_programmationtachedialog.h"

ProgrammationTacheDialog::ProgrammationTacheDialog(TacheUnitaire *t, const QString p, QWidget *parent) :
    QDialog(parent),tache(t),nomProjet(p),
    ui(new Ui::ProgrammationTacheDialog)
{


    ui->setupUi(this);
    QObject::connect(ui->checkBox_partie_tache,SIGNAL(stateChanged(int)),this,SLOT(activerDuree(int)));


    if(!t->isPreemptive())
        ui->checkBox_partie_tache->setVisible(0);



    ui->label_duree->setVisible(0);
    ui->timeEdit_duree->setVisible(0);
    ui->dateEdit_date->setDate(QDate::currentDate());
    ui->timeEdit_horaire->setTime(QTime::currentTime());
    ui->dateEdit_date->setMaximumDate(tache->getEcheance());
    ui->dateEdit_date->setMinimumDate(tache->getDisponibilite());

    QTime sum(0,0);
    std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(tache);
    for(std::vector<ProgrammationTache*>::iterator it = progs.begin() ; it != progs.end() ; ++it){
        if((*it)->isProgrammationPartieTache()){
            ui->checkBox_tache->setVisible(0);
            ui->checkBox_partie_tache->setChecked(true);
        }
        sum = sum.addSecs((*it)->getDuree().getDureeEnMinutes() * 60);
    }
    Duree duree_totale = tache->getDuree();
    QTime duree_t(duree_totale.getHeure(),duree_totale.getMinute());
    std::cout << "duree de la tahce = "<<duree_t.toString().toStdString()<<"\n";
    int nb_secs = sum.secsTo(duree_t);
    std::cout << "secs to e = "<<nb_secs<<"\n";

    QTime max_time(0,0);
    max_time = max_time.addSecs(nb_secs);
    std::cout << "MMMMAAAAXXXX TIME === " << max_time.toString().toStdString() << "\n";

    ui->timeEdit_duree->setMaximumTime(max_time);

}

ProgrammationTacheDialog::~ProgrammationTacheDialog()
{
    delete ui;
}


void ProgrammationTacheDialog::activerDuree(int x)
{
    ui->label_duree->setVisible(x);
    ui->timeEdit_duree->setVisible(x);
}


void ProgrammationTacheDialog::accept()
{
    QDate date = ui->dateEdit_date->date();
    QTime horaire = ui->timeEdit_horaire->time();
    int nbsecs = QDateTime(date,horaire).secsTo(QDateTime::currentDateTime());
    if(nbsecs > 30)
        throw CalendarException("erreur ProgrammationTacheDialog, impossible de programmer une tache dans le passe");

    bool ok = true;

    for(Tache::const_succ_iterator it = tache->beginSucc() ; it != tache->endSucc() ; ++it)
    {
        std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(*it);
        std::cout <<"VERIFICATION SUCC : "<<(*it)->getId().toStdString()<<"\n";
        for(std::vector<ProgrammationTache*>::const_iterator at = progs.begin() ; at != progs.end() ; ++at){
            std::cout << "-----------> "<<(*at)->getDate().toString().toStdString()<<"\n";
            if(QDateTime((*at)->getDate(),(*at)->getHoraire()) <= QDateTime(date,horaire))
                ok = false;
        }
    }

    for(Tache::const_pred_iterator it = tache->beginPred() ; it != tache->endPred() ; ++it)
    {
        std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(*it);
        std::cout <<"VERIFICATION PRED : "<<(*it)->getId().toStdString()<<"\n";

        for(std::vector<ProgrammationTache*>::iterator at = progs.begin() ; at != progs.end() ; ++at){
            std::cout << "-----------> "<<(*at)->getDate().toString().toStdString()<<"\n";
            if(QDateTime((*at)->getDate(),(*at)->getHoraire()) >= QDateTime(date,horaire))
                ok = false;
        }
    }

    if(ok){
        if(ui->checkBox_partie_tache->isChecked())
        {
            QTime duree = ui->timeEdit_duree->time();
            ProgrammationPartieTache prog(date,horaire,Duree(duree.hour(),duree.minute()),tache,nomProjet);
            Agenda::getInstance() << prog;
        }else
        {
            ProgrammationTache prog(date,horaire,tache,nomProjet);
            Agenda::getInstance() << prog;
        }
    }
    done(1);
}
