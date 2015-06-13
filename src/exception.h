#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QString>

/*! \class CalendarException
        \brief Classe permettant de gerer les exceptions
*/
class CalendarException{
public:
    /**
     * @brief constructeur
     * @param message
     */
    CalendarException(const QString& message):info(message){}
    /**
     * @brief Retourne l'info
     *
     */
    const QString& getInfo() const { return info; }
private:
    QString info;
};



#endif // EXCEPTION_H

