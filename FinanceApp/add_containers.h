#ifndef ADD_CONTAINERS_H
#define ADD_CONTAINERS_H

#include <QDialog>
#include "database.h"
#include "mainwindow.h"

namespace Ui {
class add_containers;
}

class add_containers : public QDialog
{
    Q_OBJECT

public:
    explicit add_containers(MainWindow *mainwindow, Database& database, QWidget *parent = nullptr);
    ~add_containers();

private:
    Ui::add_containers *ui;
    void cancelbutton();
    void savebutton();
    Database& db;
    MainWindow *mainwindow;
};

#endif // ADD_CONTAINERS_H
