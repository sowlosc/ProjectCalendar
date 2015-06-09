#ifndef ENREGISTRABLE_H
#define ENREGISTRABLE_H
#include <QString>

class Enregistrable
{
public:
    Enregistrable(){}
    ~Enregistrable(){}

    virtual void save(const QString& f) = 0;
    virtual void load(const QString& f) = 0;
};

#endif // ENREGISTRABLE_H
