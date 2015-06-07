#include "agenda.h"

Agenda* Agenda::instance = 0;

Agenda& Agenda::operator<<(Evenement& evt)
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == &evt)
            throw CalendarException("Erreur, Agenda, cet evenement existe deja");


    if(!isLibre(QDateTime(evt.getDate(),evt.getHoraire()),QDateTime(evt.getDate(),evt.getHoraire()).addSecs(evt.getDuree().getDureeEnMinutes()*60)))
        throw CalendarException("Erreur, Agenda, un evenement est deja programme a ce moment");

    if(evt.isProgrammationTache())
        dynamic_cast<ProgrammationTache*>(&evt)->getTache()->setProgrammed(true);


    events.push_back(evt.clone());
    Observable::notifier();
    return *this;
}


Agenda& Agenda::operator>>(Evenement *evt)
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == evt){
            std::cout << "Agende :::: suppression evt "<<evt->getDate().toString().toStdString()<<" - "<<evt->getHoraire().toString().toStdString() <<"\n";

            if(evt->isProgrammationTache())
                dynamic_cast<ProgrammationTache*>(evt)->getTache()->setProgrammed(false);

            delete evt;
            events.erase(it);
            Observable::notifier();
            return *this;
        }
    throw CalendarException("Erreur, Agenda, cet evenement n'existe pas");
}


Agenda::~Agenda()
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        delete *it;
}

std::vector<ProgrammationTache*> Agenda::getProgrammationTache(const Tache* t)
{
    std::vector<ProgrammationTache*> tab;
    for(iterator it = begin() ; it != end() ; ++it)
    {
        if((*it).isProgrammationTache())
        {
            ProgrammationTache* prog = dynamic_cast<ProgrammationTache*>(&(*it));
            if( prog->getTache() == t)
                tab.push_back(prog);

        }
    }
    return tab;
}

bool Agenda::isLibre(const QDateTime& debut, const QDateTime &fin)
{
    for(iterator it=begin(); it!= end(); ++it)
    {
        QDateTime deb2((*it).getDate(),(*it).getHoraire());
        QDateTime fin2((*it).getDate(),(*it).getHoraire().addSecs((*it).getDuree().getDureeEnMinutes()*60));

        if( !((debut<deb2 && fin<=deb2) || (debut>=fin2 && fin>fin2)))
            return false;
    }
    return true;
}
