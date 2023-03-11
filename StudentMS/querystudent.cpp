#include "querystudent.h"
#include "ui_querystudent.h"
#include <QSqlError>
#include <QMessageBox>
QueryStudent::QueryStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryStudent)
{
    ui->setupUi(this);
    // 打开数据表
    qryModel = new QSqlQueryModel;
    qryModel->setQuery("SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo ORDER BY stuID");
    if (qryModel->lastError().isValid()) {
            QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                     +qryModel->lastError().text(), QMessageBox::Ok);
            return;
    }
    qryModel->setHeaderData(0, Qt::Horizontal, "学生编号");
    qryModel->setHeaderData(1, Qt::Horizontal, "姓名");
    qryModel->setHeaderData(2, Qt::Horizontal, "年级");
    qryModel->setHeaderData(3, Qt::Horizontal, "班级");
    qryModel->setHeaderData(4, Qt::Horizontal, "年龄");
    qryModel->setHeaderData(5, Qt::Horizontal, "性别");
    qryModel->setHeaderData(6, Qt::Horizontal, "住址");
    qryModel->setHeaderData(7, Qt::Horizontal, "联系电话");

    ui->tableView->setModel(qryModel);
}

QueryStudent::~QueryStudent()
{
    delete ui;
}

void QueryStudent::on_pushButton_select_clicked()
{
    QString queryMethod = ui->comboBox->currentText();
    QString key = ui->lineEdit_key->text();
    QString queryInfo;
    if (queryMethod == "学生编号") {
        queryInfo = "SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo WHERE stuID = " + key + " ORDER BY stuID ";
        qryModel->setQuery(queryInfo);
        if (qryModel->lastError().isValid()) {
           QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                    +qryModel->lastError().text(), QMessageBox::Ok);
           return;
        }
    }
    else {
        queryInfo = "SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo WHERE stuName = '" + key + "' ORDER BY stuID ";
        qryModel->setQuery(queryInfo);
        if (qryModel->lastError().isValid()) {
            QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                                 +qryModel->lastError().text(), QMessageBox::Ok);
            return;
        }
    }
}

// 当文本框发生清空时,就重新查询所有结果.
void QueryStudent::on_lineEdit_key_textEdited(const QString &arg1)
{
    if (arg1.isEmpty()) {
        qryModel->setQuery("SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo ORDER BY stuID");
        if (qryModel->lastError().isValid()) {
                QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                         +qryModel->lastError().text(), QMessageBox::Ok);
                return;
        }
    }
}

