#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H

#include "projet.h"


class ProjetManager
{
    std::map<QString,Projet*> projets;
    static ProjetManager* instance;

    ProjetManager() {};
    ProjetManager(const ProjetManager&);
    ~ProjetManager() {};
    ProjetManager& operator=(const ProjetManager&);

public:
    static ProjetManager& getInstance();
    static void libererInstance();
    Projet& ajouterProjet(const QString& t, const QString& desc, const QDate& dispo, const QDate& ech);
    Projet& getProjet(const QString& t);
    const Projet& getProjet(const QString &t) const;

};

#endif // PROJETMANAGER_H
