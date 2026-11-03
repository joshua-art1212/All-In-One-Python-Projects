#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transactionwindow.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QMovie>
#include <QDebug>
#include <QPixmap>
#include <qsqlerror.h>
#include "database.h"
#include "add_containers.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , db(new Database())
{
    ui->setupUi(this);
    connect(ui->transactionButton, &QPushButton::clicked, this, &MainWindow::transactionbutton);
    connect(ui->container_pushButton, &QPushButton::clicked, this, &MainWindow::containerbutton);
    connect(ui->delete_container_push,&QPushButton::clicked, this, &MainWindow::deletebutton);
    transaction = new transactionwindow(this,*db);
    addcontainer = new add_containers(this,*db);

    //Display:
        // Title
        QPixmap balanceImage("C:/Users/wilso/CLionProjects/Personal Finance Tracker/All-In-One-Python-Projects/FinanceApp/title.png");
        ui->giftitle->setPixmap(balanceImage);


        //Gif Label
        QMovie *movie = new QMovie("C:/Users/wilso/CLionProjects/Personal Finance Tracker/All-In-One-Python-Projects/FinanceApp/f005.gif");

        ui->giflabel->setMovie(movie);
        movie->setScaledSize(QSize(50, 50));
        ui->giflabel->setAlignment(Qt::AlignCenter);
        ui->giflabel->setMovie(movie);
        movie->start();


        //Initialize Category Table
        this->rows = 1;
        ui->categories_tableWidget->setRowCount(rows);
        ui->categories_tableWidget->setColumnCount(3);
        ui->categories_tableWidget->setHorizontalHeaderLabels({"Category","Tag", "Amount"});

        ui->categories_tableWidget->setItem(0,0, new QTableWidgetItem("Eden's Mission Trip"));
        ui->categories_tableWidget->setItem(0,1, new QTableWidgetItem("Giving"));
        ui->categories_tableWidget->setItem(0,2, new QTableWidgetItem("$40"));
        ui->categories_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


        //Income Pie Chart
        series = new QPieSeries();

        series->append("Spending", 40);
        series->append("Giving", 20);
        series->append("Saving", 15);

        chart = new QChart();

        chart->addSeries(series);
        chart->setTitle("Money Allocation");


        ui->income_tableView->setChart(chart);
}






//Functions
void MainWindow::transactionbutton(){
    transaction->show();
}

void MainWindow::containerbutton(){
    addcontainer->show();
}

void MainWindow::updateContainers(){

    QSqlQuery query(db->getDatabase());

    query.prepare("SELECT category, tag, amount FROM containers");

    if (!query.exec()) {
        qDebug() << "Failed to retrieve categories:"
                 << query.lastError().text();
        return;
    }

    rows = 0;
    this->ui->categories_tableWidget->setRowCount(rows);

    while (query.next()){
        this->ui->categories_tableWidget->insertRow(rows);

        QString category = query.value("category").toString();
        QString tag = query.value("tag").toString();
        double amount = query.value("amount").toDouble();

        ui->categories_tableWidget->setItem(
            rows, 0, new QTableWidgetItem(category)
            );

        ui->categories_tableWidget->setItem(
            rows, 1, new QTableWidgetItem(tag)
            );

        ui->categories_tableWidget->setItem(
            rows, 2, new QTableWidgetItem(
                QString("$%1").arg(amount, 0, 'f', 2)
                )
            );

        rows++;
    }


}

void MainWindow::updateLabels(){
    double balance = 2000 - db->getTotal();
    this->ui->balance_value_label->setText("$" + QString::number(balance, 'f', 2));
    this->ui->giflabel->hide();
    this->ui->label_5->hide();

};
void MainWindow::updatePieChart(){
    this->series->clear();

    this->series->append("Spending", db->totalSpending());
    this->series->append("Giving", db->totalGiving());
   this->series->append("Saving", db->totalSaving());

};


void MainWindow::deletebutton(){
    db->deleteContainer();
    this->updateLabels();
    this->updateContainers();
    this->updatePieChart();
    this->ui->giflabel->show();
    this->ui->label_5->show();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete db;
}

