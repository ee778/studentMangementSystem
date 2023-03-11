#include "mainwindow.h"
#include "sqldata.h"
#include <QApplication>
#include <QDebug>
#include "login.h"

#define TEST 0
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString userName;

    SqlData *sql = new SqlData();
    Login *l = new Login(userName);  // 所有QObject必须由operator new创建，或者必须在父级之前被销毁。
    if (TEST == 0) {
        if (l->exec() == QDialog::Accepted) {
            qDebug() << userName;
            MainWindow *w = new MainWindow(userName);
            w->show();
            return a.exec();
        }
        else {
            return 0;
        }
    }



//    MainWindow w;
//    w.show();

//    SetClass *m_class = new SetClass();
//    m_class->show();
    return a.exec();
}
