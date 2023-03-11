#include "login.h"
#include "ui_login.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>
Login::Login(QString &userName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    userName = this->m_user;
    ui->setupUi(this);
    this->setFixedSize(550, 450);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    this->setAttribute(Qt::WA_DeleteOnClose);// 设置为关闭时删除
    this->setWindowFlags(Qt::SplashScreen); // 设置为Splash 窗口
    readSettings();
    qDebug() << encrypt("123456");
}

Login::~Login()
{
    delete ui;
}

void Login::readSettings()
{

}

void Login::writeSettings()
{

}

QString Login::encrypt(const QString &str)
{
    // 字符串MD5 加密
    QByteArray btArray;
    btArray.append(str);
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(btArray); // 添加数据
    QByteArray resultArray = hash.result();  // 返回最终的散列值
    QString md5 = resultArray.toHex();
    return md5;
}

void Login::mousePressEvent(QMouseEvent *event)
{

}

void Login::mouseMoveEvent(QMouseEvent *event)
{

}

void Login::mouseReleaseEvent(QMouseEvent *event)
{

}

void Login::on_pushButton_login_clicked()
{
    //登陆按钮
    QString user = ui->lineEdit_username->text().trimmed(); // trimmed() 返回一个删除了头和尾空白的字符
    QString pswd = ui->lineEdit_password->text().trimmed();
    QString encrptPSWD = encrypt(pswd);  // 对输入的密码进行加密

    // 这里使用数据库查找是否有对应的用户名，如果有对应的用户名那么其密码是否相同，如果相同
    // 那么执行写入设置函数  对话框accept，关闭对话框
    // 否则记录输入错误的次数，一旦错误次数超过3， 那么就要关闭对话框
    // 尝试使用QSqlQuery
    QSqlQuery query;

    query.prepare("SELECT * FROM tb_user where userName = ? ");
    query.bindValue(0, user);
    query.exec();
    query.first();
    if (!query.isValid() || encrptPSWD != query.value("userPassword").toString()) { // 没有查询成功
        qDebug() << query.value("userName").toString();
        m_tryCount++;
        if (m_tryCount > MAXERRORNUM) {
            QMessageBox::critical(this, "错误", "输入次数太多了，强行退出");
            this->reject();//退出
        }
        else {
            QMessageBox::warning(this, "错误提示", "用户名或者密码输入错误");
        }
    }
    else if(encrptPSWD == query.value("userPassword").toString()){
        writeSettings();
        this->accept();  //对话框accept，关闭对话框
    }
}

