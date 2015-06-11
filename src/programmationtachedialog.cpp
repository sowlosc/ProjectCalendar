#include "programmationtachedialog.h"
#include "ui_programmationtachedialog.h"
#include <QMessageBox>

ProgrammationTacheDialog::ProgrammationTacheDialog(TacheUnitaire *t, Projet* p, QWidget *parent) :
    QDialog(parent),tache(t),projet(p),
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

    //on cherche la date et l'horaire maximal pour les prédécesseurs de la tache
    for(Tache::const_pred_iterator it = tache->beginPred() ; it != tache->endPred() ; ++it)
    {
        if(!(*it)->isComposite())
        {
            QDateTime date_max_temp;
             std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(*it);
             if(progs.size()==0)
             {
                 QMessageBox::warning(this,"Avertissement xx","Vous devez d'abord programmer les tâches antérieures à celle-ci");
                 ui->buttonBox->setEnabled(false);
             }else if(progs.size()==1 && !progs.begin().operator *()->isProgrammationPartieTache())
             {
                 std::vector<ProgrammationTache*>::iterator at = progs.begin();

                 QDate mind = (*at)->getDate();
                 Duree d = (*at)->getDuree();
                 int nb_secs = d.getDureeEnMinutes() * 60;
                 QTime h = (*at)->getHoraire();

                 date_max_temp = QDateTime(mind,h);
                 date_max_temp = date_max_temp.addSecs(nb_secs);

                 ui->dateEdit_date->setMinimumDate(date_max_temp.date());
                 ui->dateEdit_date->setDate(date_max_temp.date());
                 ui->timeEdit_horaire->setTime(date_max_temp.time());


             }else
             {
                 //verification si la tache precedente a ete complement programmee
                 QDateTime max;

                 bool tache_non_complete = false;
                 QTime sum(0,0);
                 std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(*it);
                 for(std::vector<ProgrammationTache*>::iterator at = progs.begin() ; at != progs.end() ; ++at)
                 {
                     sum = sum.addSecs((*at)->getDuree().getDureeEnMinutes() * 60);
                    if(QDateTime((*at)->getDate(),(*at)->getHoraire())>max)
                        max = QDateTime((*at)->getDate(),(*at)->getHoraire());

                 }
                 Duree duree_totale = dynamic_cast<const TacheUnitaire*>(*it)->getDuree();
                 QTime duree_t(duree_totale.getHeure(),duree_totale.getMinute());
                 std::cout << "duree_t = "<<duree_t.toString().toStdString()<<"\n";
                 std::cout <<"sum = "<<sum.toString().toStdString()<<"\n";
                 if(duree_t>sum)
                     tache_non_complete = true;
                 if(tache_non_complete){
                     QMessageBox::warning(this,"Avertissement","Vous devez d'abord programmer les tâches antérieures à celle-ci");
                     ui->buttonBox->setEnabled(false);
                }else
                 {
                     date_max_temp = max;
                 }
             }
             if(date_max_temp>date_max)
                 date_max = date_max_temp;
        }
    }

     std::cout << "<<<<<<<<<<<<<<<<<<<< date_max = "<<date_max.toString().toStdString()<<"\n";


// fverif si > date_max
    ui->timeEdit_horaire->setMinimumTime(QTime(6,0));
    ui->timeEdit_horaire->setMaximumTime(QTime(22,0));

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
    QDateTime horaire_prog_deb(date,horaire);
    QDateTime horaire_prog_fin = horaire_prog_deb.addSecs(tache->getDuree().getDureeEnMinutes()*60);
    int nbsecs = QDateTime(date,horaire).secsTo(QDateTime::currentDateTime());
    if(nbsecs > 30)
        throw CalendarException("erreur ProgrammationTacheDialog, impossible de programmer une tache dans le passe");

    bool ok = true;
    // verification que les predecesseurs
    for(Tache::const_succ_iterator it = tache->beginSucc() ; it != tache->endSucc() ; ++it)
    {
        std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(*it);
        std::cout <<"VERIFICATION SUCC : "<<(*it)->getId().toStdString()<<"\n";
        for(std::vector<ProgrammationTache*>::const_iterator at = progs.begin() ; at != progs.end() ; ++at){
            std::cout << "-----------> "<<(*at)->getDate().toString().toStdString()<<"\n";
            if(QDateTime((*at)->getDate(),(*at)->getHoraire()) <= horaire_prog_fin)
                ok = false;
        }
    }

    for(Tache::const_pred_iterator it = tache->beginPred() ; it != tache->endPred() ; ++it)
    {
        std::vector<ProgrammationTache*> progs = Agenda::getInstance().getProgrammationTache(*it);
        std::cout <<"VERIFICATION PRED : "<<(*it)->getId().toStdString()<<"\n";

        for(std::vector<ProgrammationTache*>::iterator at = progs.begin() ; at != progs.end() ; ++at){
            std::cout << "-----------> "<<(*at)->getDate().toString().toStdString()<<"\n";
            if(QDateTime((*at)->getDate(),(*at)->getHoraire()).addSecs((*at)->getDuree().getDureeEnMinutes()) > horaire_prog_deb)
                ok = false;
        }
    }

    if(ok){
        bool noProblem = true;
        if(ui->checkBox_partie_tache->isChecked())
        {
            QTime duree = ui->timeEdit_duree->time();
            ProgrammationPartieTache prog(date,horaire,Duree(duree.hour(),duree.minute()),tache,projet);
            try
            {
                Agenda::getInstance() << prog;
            }catch(CalendarException e)
            {
                QMessageBox::warning(this,"Avertissement",e.getInfo());
                noProblem = false;
            }
        }else
        {
            ProgrammationTache prog(date,horaire,tache,projet);
            try
            {
                Agenda::getInstance() << prog;
            }catch(CalendarException e)
            {
                QMessageBox::warning(this,"Avertissement",e.getInfo());
                noProblem=false;
            }
        }
        if(noProblem)
            done(1);
    }else
        QMessageBox::warning(this,"Avertissement","Contrainte de précédence non respectée");

}
