#include "transactionwindow.h"
#include "ui_transactionwindow.h"
#include <QMovie>

transactionwindow::transactionwindow(MainWindow *mainwindow, Database& database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::transactionwindow), db(database)
    , mainwindow(mainwindow)
{
    ui->setupUi(this);
    connect(ui->saveButton, &QPushButton::clicked, this, &transactionwindow::savebutton);
    connect(ui->cancelButton, &QPushButton::clicked, this, &transactionwindow::cancelbutton);
    //Gif Label
    QMovie *movie = new QMovie("C:/Users/wilso/CLionProjects/Personal Finance Tracker/All-In-One-Python-Projects/FinanceApp/transactiontitle.gif");

    ui->tgiflabel->setMovie(movie);
    movie->setScaledSize(QSize(371, 71));
    ui->tgiflabel->setAlignment(Qt::AlignCenter);
    ui->tgiflabel->setMovie(movie);
    movie->start();


}

void transactionwindow::cancelbutton(){
    this->close();
}
void transactionwindow::savebutton(){
    //backend saving
    QString new_cat = ui->category_textEdit->toPlainText();
    QString new_tag = ui->tag_textEdit->toPlainText();
    QString amt_text = ui->amount_textEdit->toPlainText();

    bool valid;
    double amount = amt_text.toDouble(&valid);

    // Validation
    if (new_cat.isEmpty()) {
        qDebug() << "Error: Group name is required.";
        return;
    }

    if (!valid || amount <= 0) {
        qDebug() << "Error: Enter a valid amount greater than 0.";
        return;
    }

    if (new_tag != "Spending" &&
        new_tag != "Giving" &&
        new_tag != "Saving") {

        qDebug() << "Error: Enter a valid tag";
        return;
    }

    //Database Updating
    db.addTransaction(new_cat,new_tag,amount);
    mainwindow->updateContainers();
    mainwindow->updateLabels();
    mainwindow->updatePieChart();


    this->close();
}

transactionwindow::~transactionwindow()
{
    delete ui;
}
