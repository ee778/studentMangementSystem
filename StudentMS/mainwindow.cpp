#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include "setclass.h"
#include "setgrade.h"
#include "managestudent.h"
#include "querystudent.h"
MainWindow::MainWindow(QString &userName, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(650, 450);
    this->setCentralWidget(ui->label);
    this->user = new QLabel("当前登录用户" + userName);

    this->currentTime = new QLabel("登录时间" + QTime::currentTime().toString());
    ui->statusbar->addWidget(user);

    ui->statusbar->addWidget(currentTime);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_act_set_grade_triggered()
{
    SetGrade *m_grade = new SetGrade(this);
    if (m_grade->exec()) {
        return;
    }
}


void MainWindow::on_act_set_class_triggered()
{
    // 使用模态对话框，使用后删除
    SetClass *m_class = new SetClass(this);
    if (m_class->exec()) {
        return;
    }
}


void MainWindow::on_act_stu_manage_triggered()
{
    // 使用模态对话框，使用后删除
    ManageStudent *ms = new ManageStudent(this);
    if (ms->exec()) {
        return;
    }
}


void MainWindow::on_act_query_stu_triggered()
{
    QueryStudent *qs = new QueryStudent(this);
    if (qs->exec()) {
        return;
    }
}

