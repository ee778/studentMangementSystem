#include "sqldata.h"

#include <QDebug>
#include <QSqlError>
SqlData::SqlData() {
//打开MySql数据库
    DB = QSqlDatabase::addDatabase("QMYSQL");
    DB.setHostName("127.0.0.1");
    DB.setPort(3306);
    DB.setDatabaseName("db_student");
    DB.setUserName("root");
    DB.setPassword("123456");
    bool ok = DB.open(); //打开数据库
    if (ok){
        qDebug() << "successes";
    }
    else {

        qDebug()<<"error open database because"<<DB.lastError().text();
        return;
    }
}
