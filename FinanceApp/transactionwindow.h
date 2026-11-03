#ifndef TRANSACTIONWINDOW_H
#define TRANSACTIONWINDOW_H

#include <QDialog>
#include "database.h"
#include "mainwindow.h"

namespace Ui {
class transactionwindow;
}

class transactionwindow : public QDialog
{
    Q_OBJECT

public:
    explicit transactionwindow(MainWindow *mainwindow, Database& database, QWidget *parent = nullptr);
    ~transactionwindow();

private:
    Ui::transactionwindow *ui;
    Database& db;
    MainWindow *mainwindow;
private slots:
    void cancelbutton();
    void savebutton();

};

#endif // TRANSACTIONWINDOW_H
