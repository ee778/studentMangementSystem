#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

#define MAXERRORNUM 3

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QString &userName, QWidget *parent = nullptr);
    ~Login();
private:
    bool m_moving = false; // 表示窗口是否在鼠标操作下移动
    QPoint mj_lastPost;
    QString m_user = "user";
    QString m_password = "123456";
    int m_tryCount = 0; // 试错次数
    void readSettings(); // 读取设置， 数据库
    void writeSettings(); // 写入设置， 数据库
    QString encrypt(const QString &str); // 字符串加密
protected:
    // 用于鼠标拖动窗口的鼠标事件
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
