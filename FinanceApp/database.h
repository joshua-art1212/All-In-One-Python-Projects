#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlQuery>
#include <QString>
#include <QSqlDatabase>

class Database{
    public:
        ///QSqlQuery query;
        Database();
        void create_Transaction_Table();
        void create_Container_Table();
        void addTransaction(QString category, QString tag, double amount);
        void addContainer(QString category, QString tag, double amount);
        void deleteContainer();
        double getTotal();
        double totalSpending();
        double totalGiving();
        double totalSaving();
        QSqlDatabase getDatabase() const {
            return db;
        }
    private:
        QSqlDatabase db;

};





#endif // DATABASE_H
