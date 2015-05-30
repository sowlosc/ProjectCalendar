#ifndef RDV_H
#define RDV_H

#include "evenement1j.h"

class Rdv : public Evenement1j
{
    QString lieu;
    std::vector<QString> personnes;
public:


    Rdv( const QDate& ddeb,
         const QTime& tdeb,
         const Duree& dur,
         const QString& suj,
         const QString& l)
            : Evenement1j(ddeb,tdeb,dur,suj), lieu(l) {}
    ~Rdv(){}

    const QString& getLieu() const { return lieu; }
    void setLieu(const QString& l) { lieu = l; }
    const std::vector<QString>& getPersonnes() const { return personnes; }
    void addPersonne(const QString& nom);
    void removePersonne(const QString& nom);
};

#endif // RDV_H
