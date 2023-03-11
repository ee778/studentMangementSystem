#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString &userName, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_act_set_grade_triggered();

    void on_act_set_class_triggered();

    void on_act_stu_manage_triggered();

    void on_act_query_stu_triggered();

private:
    QLabel *currentTime;
    QLabel *user;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
