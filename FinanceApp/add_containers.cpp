#include "add_containers.h"
#include "ui_add_containers.h"
#include <qmovie.h>

add_containers::add_containers(MainWindow *mainwindow, Database& database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_containers), db(database), mainwindow(mainwindow)

{
    ui->setupUi(this);
    connect(ui->saveButton, &QPushButton::clicked, this, &add_containers::savebutton);
    connect(ui->cancelButton, &QPushButton::clicked, this, &add_containers::cancelbutton);
    QMovie *movie = new QMovie("C:/Users/wilso/CLionProjects/Personal Finance Tracker/All-In-One-Python-Projects/FinanceApp/FinanceMan.gif");

    ui->tgiflabel->setMovie(movie);
    movie->setScaledSize(QSize(371, 71));
    ui->tgiflabel->setAlignment(Qt::AlignCenter);
    ui->tgiflabel->setMovie(movie);
    movie->start();


}

add_containers::~add_containers()
{
    delete ui;
}

void add_containers::cancelbutton(){
    this->close();
}

void add_containers::savebutton(){
    //backend saving
    QString new_cat = ui->category_textedit->toPlainText();
    QString new_tag = ui->tag_textedit->toPlainText();
    QString amt_text = ui->amount_textedit->toPlainText();

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
    db.addContainer(new_cat,new_tag,amount);
    mainwindow->updateContainers();
    mainwindow->updateLabels();
    mainwindow->updatePieChart();


    this->close();

}
