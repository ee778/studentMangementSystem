#ifndef SQLDATA_H
#define SQLDATA_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
class SqlData:public QObject {
    Q_OBJECT
 private:
    QSqlDatabase DB;
 public:
    SqlData();
};
#endif // SQLDATA_H
