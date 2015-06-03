#ifndef AGENDA_H
#define AGENDA_H

#include "evenement.h"
#include <vector>
#include "exception.h"
#include <iostream>

class Agenda
{
    std::vector<Evenement*> events;
    static Agenda* instance;
    Agenda() {}
    ~Agenda();
    Agenda(const Agenda&);
    Agenda& operator=(const Agenda&);

public:
    static Agenda& getInstance() { if(!instance) instance = new Agenda; return *instance; }
    static void libererInstance() { if(instance) delete instance; instance = 0; }
    Agenda& operator<<(Evenement& evt);
    Agenda& operator>>(Evenement* evt);


    class iterator{
        friend class Agenda;
        std::vector<Evenement*>::iterator it;
        iterator(const std::vector<Evenement*>::iterator& iter) : it(iter) {}
    public:
        Evenement& operator*() { return *(*it); }
        iterator& operator++() { ++it; return *this; }
        bool operator!=(const iterator& at) const { return it != at.it; }
    };

    iterator begin() { return iterator(events.begin()); }
    iterator end() { return iterator(events.end()); }

};

#endif // AGENDA_H
