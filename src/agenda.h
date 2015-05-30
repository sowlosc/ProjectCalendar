#ifndef AGENDA_H
#define AGENDA_H
#include "evenement.h"
#include <vector>

class Agenda
{
    std::vector<Evenement*> events;
    static Agenda* instance;
    Agenda(){}
    ~Agenda(){}
    Agenda(const Agenda&);
    Agenda& operator=(const Agenda&);

public:
    static Agenda& getInstance() { if(!instance) instance = new Agenda; return *instance; }
    static void libererInstance() { if(instance) delete instance; instance = 0; }
    Agenda& operator<<(Evenement&);

};

#endif // AGENDA_H
