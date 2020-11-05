#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    this->setWindowIcon(QIcon(":/doc.ico"));
    ui->pushButton->setStyleSheet("QPushButton {\
        background-color: #52A0EC;\
        border-style: outset;\
        border-width: 1px;\
        border-radius: 10px;\
        border-color: beige;\
        font: bold 14px;\
        padding: 6px;}\
        QPushButton:pressed {\
            background-color: #FF9D0F;\
            border-style: inset\
    }");
    ui->searchContentLine->setStyleSheet("QLineEdit {\
         border: 1px solid #8A85EE;\
         border-radius: 5px;\
         padding: 0 8px;\
         selection-background-color: #352BDD;\
    }");
this->setStyleSheet(
            "#MainWindow { "
            " border-image: url(:/1.jpg) 0 0 0 0 stretch stretch;"
            "}");
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

/*-------------------------------------------------------------------*/

//QVariant Model::dataTextAlignment( const QModelIndex &I ) const {
//    int Result = Qt::AlignVCenter ; // По вертикали выравниваем по базовой линии AlignBaseline или по центру AlignVCenter
//    Result |= I.column() == 1 ?  Qt::AlignLeft : Qt::AlignHCenter ; // 1 колонку выравниваем влево, остальные по центру
//    return Result ;
//}

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

        ui->tableView->setStyleSheet("QTableView {selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 0.5,\
            y2: 0.5,stop: 0 #1C7CD8, stop: 1 #7BB4EC);\
                                     selection-color: black;\
                                     background-color: rgba(255, 255, 255, 200);\
                                     border: 2px solid #7BB4EC;\
                                     border-top-color: #094C8C;\
                                     border-radius: 4px;\
                                     gridline-color: #777;\
                                     color:#333;\
                                     font-size:12px;\
                                     font-color: #000000;\
                                 }\
                                 QHeaderView {\
                                     background-color: #fff;\
                                     font-size:16px;\
                                 }\
                                 QHeaderView::section:horizontal {\
                                     color: black;\
                                     font: bold 14px;\
                                     font-family: Times New Roman;\
                                     border-style: solid;\
                                     background-color: qlineargradient( x1: 0, y1: 0, x2: 0, y2: 1,\
                                     stop: 0 #7BB4EC, stop: 1 #1C7CD8);\
                                 }\
                                 QScrollBar:vertical {\
                                     background: #e4e4e4;\
                                     border-top-right-radius: 4px;\
                                     border-bottom-right-radius: 4px;\
                                     width: 16px;\
                                     margin: 0px;\
                                 }\
                                 QScrollBar::handle:vertical {\
                                    background-color: qlineargradient( x1: 0, y1: 0, x2: 1, y2: 0,\
                                                                    stop: 0 #4287ff, stop: 1 #1C7CD8);\
                                     border-radius: 4px;\
                                     min-height: 20px;\
                                     margin: 0px 2px 0px 2px;\
                                 }\
                                 QScrollBar::add-line:vertical {\
                                     background: none;\
                                     height: 0px;\
                                     subcontrol-position: right;\
                                     subcontrol-origin: margin;\
                                 }\
                                 QScrollBar::sub-line:vertical {\
                                     background: none;\
                                     height: 0px;\
                                     subcontrol-position: left;\
                                     subcontrol-origin: margin;\
                                 }");
        ui->tableView->show();
    }

}
