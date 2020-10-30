#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>
#include <QtSql>
#include <QSettings>
#include <QString>

#include "popup.h"

class login : public QApplication {
    Q_OBJECT

public:
    login( int argc, char *argv[] );
    virtual ~login();

private:
    PopUp *popUp;       // Объявляем объект всплывающего сообщения
    QSqlDatabase db;

};

#endif // LOGIN_H
