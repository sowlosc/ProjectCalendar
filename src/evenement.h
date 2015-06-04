#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QDate>
#include <QTime>
#include <sstream>

class Evenement
{
    QDate date;
    QTime horaire;


public:
    Evenement(const QDate& d, const QTime& t)
        : date(d), horaire(t) {}

    virtual ~Evenement(){}


    virtual Evenement* clone() const = 0;
    virtual QString toString() const = 0;

    const QDate& getDate() const { return date; }
    const QTime& getHoraire() const { return horaire; }
    void setDate(const QDate& d) { date = d; }
    void setHoraire(const QTime& t) { horaire = t; }

    virtual bool isProgrammationTache() const = 0;
    virtual bool isEvenementTrad() const = 0;
    virtual bool isEvenement1j() const = 0;

};

#endif // EVENEMENT_H
