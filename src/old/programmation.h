#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H
#include "projet.h"

class Programmation {
    const Tache* tache;
    QDate date;
    QTime horaire;
public:
    Programmation(const Tache& t, const QDate& d, const QTime& h):tache(&t), date(d), horaire(h){}
    const Tache& getTache() const { return *tache; }
    QDate getDate() const { return date; }
    QTime getHoraire() const { return horaire; }
};

class ProgrammationManager {
private:
    std::vector<Programmation*> programmations;
    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Tache& t) const;

    ProgrammationManager() {}
    ~ProgrammationManager();
    ProgrammationManager(const ProgrammationManager &um);
    ProgrammationManager& operator=(const ProgrammationManager& um);
    static ProgrammationManager *instance;
public:
    static ProgrammationManager& getInstance() { if(!instance) instance = new ProgrammationManager; return *instance; }
    static void libererInstance() { if(instance) delete instance; instance = 0; }
    void ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h);
};



#endif // PROGRAMMATION_H

