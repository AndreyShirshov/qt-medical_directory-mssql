#include "login.h"

login::login(int argc, char *argv[] )
    : QApplication( argc, argv ) {

    popUp = new PopUp();

    QSettings settings("settings.ini", QSettings::IniFormat);
    const QString myServer = settings.value("SET_SERVER/IP").toString();
    const QString myPort= settings.value("SET_SERVER/Port").toString();
    const QString myDatabase = settings.value("SET_DATABASE/Name").toString();
    const QString myLogin = settings.value("SET_USER/Login").toString();
    const QString myPassword = settings.value("SET_USER/Password").toString();

    db = QSqlDatabase::addDatabase( "QODBC" ) ;
    db.setDatabaseName("DRIVER={SQL Server};SERVER="+myServer+","+myPort+";DATABASE="+myDatabase+";");
    db.setUserName(myLogin);
    db.setPassword(myPassword);

    if(!db.open()){
        popUp->setPopupText(tr("Соединение НЕ установлено").toUtf8());
        popUp->show();
        this->exit();
    }else{
        popUp->setPopupText(tr("Соединение установлено").toUtf8());
        popUp->show();
    }

}

login::~login() {
}
