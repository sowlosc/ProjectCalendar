#ifndef PROJECTCALENDAR_H
#define PROJECTCALENDAR_H

#include "agenda.h"
#include "projetmanager.h"
#include "precedencemanager.h"


class ProjectCalendar
{
    Agenda& ag;
    ProjetManager& pm;
    PrecedenceManager& predm;



public:
    ProjectCalendar();
    ~ProjectCalendar();

    void ajouterProjet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech);
};

#endif // PROJECTCALENDAR_H
