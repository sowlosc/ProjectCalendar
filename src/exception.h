#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QString>


class CalendarException{
public:
    CalendarException(const QString& message):info(message){}
    const QString& getInfo() const { return info; }
private:
    QString info;
};



#endif // EXCEPTION_H

