#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpieseries.h>

class Database;
class transactionwindow;
class add_containers;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void updateContainers();
    void updateLabels();
    void updatePieChart();
    //void updateIncome();

private:
    Ui::MainWindow *ui;
    Database *db;
    transactionwindow *transaction;
    add_containers *addcontainer;
    int rows;
    QPieSeries *series;
    QChart *chart;
private slots:
    void transactionbutton();
    void containerbutton();
    void deletebutton();


    //void updateCategories();

};
#endif // MAINWINDOW_H
