#include "agenda.h"

Agenda* Agenda::instance = 0;

Agenda& Agenda::operator<<(Evenement& evt)
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == &evt)
            throw CalendarException("Erreur, Agenda, cet evenement existe deja");
    events.push_back(evt.clone());
    return *this;
}


Agenda& Agenda::operator>>(Evenement &evt)
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        if( *it == &evt){
            delete &evt;
            events.erase(it);
            return *this;
        }
    throw CalendarException("Erreur, Agenda, cet evenement n'existe pas");
}


Agenda::~Agenda()
{
    for(std::vector<Evenement*>::iterator it = events.begin() ; it != events.end() ; ++it)
        delete *it;
}
