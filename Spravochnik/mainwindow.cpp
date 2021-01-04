#include "mainwindow.h"
#include "ui_mainwindow.h"

/*********************************************************************/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    popUp = new PopUp();
    ui->searchContentLine->setFocus();
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
    ok = db.open();
    if(!ok){
        popUp->setPopupText(tr("Соединение НЕ установлено").toUtf8());
        popUp->show();
    }else{
        popUp->setPopupText(tr("Соединение установлено").toUtf8());
        popUp->show();
    }

    connect(ui->searchContentLine, SIGNAL (returnPressed()), ui->pushButton, SIGNAL(clicked() ) );
    this->setWindowTitle(tr("Справочник"));
    this->setWindowIcon(QIcon(":/source/images/icons/doc.ico"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*********************************************************************/

Model ::Model( QObject *parent )
    :  QSqlTableModel( parent ){

}

Model ::~Model() {
    }

/*********************************************************************/

void MainWindow::on_pushButton_clicked(){
    if(!ok){
        popUp->setPopupText(tr("Соединение НЕ установлено").toUtf8());
        popUp->show();
    }else{
        popUp->setPopupText(tr("Получаем данные").toUtf8());
        popUp->show();
        //model = new QSqlTableModel();
        model = new Model(this);
        model->setTable("Usluga");
        QString str = ui->searchContentLine->text();
        model->setFilter(QString("NameUslugi LIKE '%")+str+QString("%'"));
        //model->setFilter(QString("NameUslugi LIKE '%")+str+QString("%'")+(QString("OR OpisanieUslugi LIKE '%"))+str+QString("%'"));
        model->setHeaderData(1, Qt::Horizontal,"  Код  ");
        model->setHeaderData(2, Qt::Horizontal,"Имя услуги");
        model->setHeaderData(3, Qt::Horizontal,"Описание услуги");
        model->select();

        ui->tableView->setModel(model);     // Устанавливаем модель на TableView
        ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
        ui->tableView->setColumnHidden( 4, true );    // Скрываем колонку

        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);    //Запрет на редактирование
        //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);    // Разрешаем выделение строк
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);    // Разрешаем выделение единичных записей.
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);    // Устанавливаем режим выделения лишь одно строки в таблице

        ui->tableView->resizeRowsToContents();   // Устанавливаем высоту строк по содержимому
        //ui->tableView->resizeColumnsToContents();    // Устанавливаем ширину колонок по содержимому

        ui->tableView->horizontalHeader()->setDefaultSectionSize(45);    // Значения для QHeaderView::Fixed
        ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
        ui->tableView->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
        //ui->tableView->horizontalHeader()->setStretchLastSection(true);
        //ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    // Убирать горизонтальный скрол

        ui->tableView->verticalHeader()->setVisible(false);    // Скрываем вертикальные заголовки
        //ui->tableView->verticalHeader()->setDefaultSectionSize(100);
        //ui->tableView->verticalHeader()->setMinimumSectionSize(35);
        //ui->tableView->verticalHeader()->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        ui->tableView->show();
    }

}
