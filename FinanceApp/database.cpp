#include "database.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

Database::Database() {
    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("finance.db");

    if (!db.open()) {
        qDebug() << "Database failed:" << db.lastError().text();
        return;
    }

    qDebug() << "Database connected!";

    create_Container_Table();
    create_Transaction_Table();
}


void Database::addTransaction(QString category, QString tag, double amount){
    QSqlQuery query(db);

    query.prepare(
        "INSERT INTO transactions (category, tag, amount) "
        "VALUES (:category, :tag, :amount)"
        );

    query.bindValue(":category", category);
    query.bindValue(":tag", tag);
    query.bindValue(":amount", amount);


    if (!query.exec()) {
        qDebug() << "Failed to add transaction:" << query.lastError().text();
        return;
    }


    QSqlQuery updatequery(db);

    updatequery.prepare(
        "UPDATE containers "
        "SET amount = amount - :amount "
        "WHERE category = :category AND tag = :tag"
        );

    updatequery.bindValue(":amount", amount);
    updatequery.bindValue(":category", category);
    updatequery.bindValue(":tag", tag);

    if (!updatequery.exec()) {
        qDebug() << "Failed to update balance:"
                 << updatequery.lastError().text();
    }

}


double Database::getTotal(){
    QSqlQuery query(db);
    query.exec(
        "SELECT SUM(amount) "
        "FROM containers"
        );
    double total = 0;
    if (query.next()) {
        total = query.value(0).toDouble();

    }
    return total;

}

double Database::totalSpending(){
    QSqlQuery query(db);

    query.prepare(
        "SELECT SUM(amount) FROM containers "
        "WHERE category = :category"
        );

    query.bindValue(":category", "Spending");

    double total = 0;

    if (query.exec() && query.next()) {
        total = query.value(0).toDouble();
    }

    return total;

}
double Database::totalGiving(){
    QSqlQuery query(db);

    query.prepare(
        "SELECT SUM(amount) FROM containers "
        "WHERE category = :category"
        );

    query.bindValue(":category", "Giving");

    double total = 0;

    if (query.exec() && query.next()) {
        total = query.value(0).toDouble();
    }

    return total;
}
double Database::totalSaving(){
    QSqlQuery query(db);

    query.prepare(
        "SELECT SUM(amount) FROM containers "
        "WHERE category = :category"
        );

    query.bindValue(":category", "Saving");

    double total = 0;

    if (query.exec() && query.next()) {
        total = query.value(0).toDouble();
    }

    return total;

}


void Database::create_Transaction_Table(){
     QSqlQuery query(db);
    query.exec(
        "CREATE TABLE transactions ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "category TEXT,"
           "tag TEXT,"
           "amount REAL"
           ")"
        );
}


void Database::create_Container_Table(){
    QSqlQuery query(db);
    query.exec(
        "CREATE TABLE containers("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "category TEXT,"
        "tag TEXT,"
        "amount REAL"
        ")"
        );
}

void Database::addContainer(QString category, QString tag, double amount){

    QSqlQuery query(db);

    query.prepare(
        "INSERT INTO containers (category, tag, amount) "
        "VALUES (:category, :tag, :amount)"
        );

    query.bindValue(":category", category);
    query.bindValue(":tag", tag);
    query.bindValue(":amount", amount);

    if (!query.exec()) {
        qDebug() << "Failed to add container:"
                 << query.lastError().text();
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
        qDebug() << query.boundValues();
    }
}

void Database::deleteContainer(){
    QSqlQuery query(db);

    if (!query.exec("DELETE FROM containers")) {
        qDebug() << "Failed to clear containers:"
                 << query.lastError().text();
    }
}