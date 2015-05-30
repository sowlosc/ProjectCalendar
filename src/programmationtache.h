#ifndef PROGRAMMATIONTACHE_H
#define PROGRAMMATIONTACHE_H

#include "evenement.h"

class ProgrammationTache : public Evenement
{
public:
    ProgrammationTache(const QDate& ddeb, const QTime& tdeb)
        :Evenement(ddeb,tdeb) {}
    ~ProgrammationTache(){}
};

#endif // PROGRAMMATIONTACHE_H
