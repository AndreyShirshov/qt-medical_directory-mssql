#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlTableModel>
#include <QString>
#include <QSettings>

#include "popup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*********************************************************************/
class Model : public QSqlTableModel {

    Q_OBJECT

protected:
    //virtual QVariant    dataDisplay( const QModelIndex &I ) const ;
    //virtual QVariant    dataTextAlignment( const QModelIndex &I ) const ;
    //virtual QVariant    dataForeground( const QModelIndex &I ) const ; // Для отображения цвета текста
    //virtual QVariant    dataBackground( const QModelIndex &I ) const ; // Для отображения цвета фона
    //virtual QVariant    dataFont( const QModelIndex &I ) const ; // Для отображения зачёркнутого текста

public:
    Model( QObject *parent = nullptr ) ;
    virtual ~Model() ;

   // QVariant headerData( int section,
                         //Qt::Orientation orientation, int role ) const ; // Заголовки
} ;

/*********************************************************************/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    bool ok;
    Ui::MainWindow *ui;
    PopUp *popUp;       // Объявляем объект всплывающего сообщения
    QSqlDatabase db;
    Model* model;
};
#endif // MAINWINDOW_H
