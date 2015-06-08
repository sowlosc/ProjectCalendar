#ifndef EVENEMENTPJ_H
#define EVENEMENTPJ_H

#include "evenementtrad.h"
#include <QDateTime>
#include <QtXml>

class EvenementPj : public EvenementTrad
{
    QDate dateFin;
    QTime horaireFin;

public:
    EvenementPj(const QDate& ddeb, const QTime& tdeb,const QDate& dfin, const QTime& tfin,const QString& suj)
        :EvenementTrad(ddeb,tdeb,suj),dateFin(dfin), horaireFin(tfin) {}
    virtual ~EvenementPj(){}

    const QTime& getHoraireFin() const { return horaireFin; }
    const QDate& getDateFin() const { return dateFin; }
    void setHoraireFin(const QTime& t) { horaireFin = t; }
    void setDateFin(const QDate& d) { dateFin = d; }

    const Duree& getDuree() const;

    virtual EvenementPj* clone() const;
    virtual QString toString() const;

    virtual bool isEvenement1j() const { return false; }
    virtual bool isEvenementPj() const { return true; }

    void toXml(QXmlStreamWriter &) const;
    static EvenementPj* getFromXml(QXmlStreamReader &);
};

#endif // EVENEMENTPJ_H
