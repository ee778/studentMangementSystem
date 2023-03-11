#pragma execution_character_set("utf-8")
#include "setclass.h"
#include "ui_setclass.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDebug>
void SetClass::openTable()
{
    // 打开数据表
    qryModel = new QSqlQueryModel(this);
    theSelection = new QItemSelectionModel(qryModel);
    qryModel->setQuery("SELECT classID, gradeName, className FROM v_classinfo order by gradeID, classID");
    if (qryModel->lastError().isValid()) { // 如果出现报错
        QMessageBox::information(this, "错误", "数据表查询错误，错误信息\n"
                                 + qryModel->lastError().text(),QMessageBox::Ok);
        return;
    }
    qryModel->setHeaderData(0, Qt::Horizontal, "班级编号");
    qryModel->setHeaderData(1, Qt::Horizontal, "所属年级");
    qryModel->setHeaderData(2, Qt::Horizontal, "班级名称");

    ui->tableView->setModel(qryModel);
    ui->tableView->setSelectionModel(theSelection);



    connect(this->theSelection, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this,SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));

}

void SetClass::updateRecord(int recNo)
{
    Q_UNUSED(recNo);
    qryModel->setQuery("SELECT classID, gradeName, className FROM v_classinfo order by gradeID, classID");
    if (qryModel->lastError().isValid()) { // 如果出现报错
        QMessageBox::information(this, "错误", "数据表查询错误，错误信息\n"
                                 + qryModel->lastError().text(),QMessageBox::Ok);
        return;
    }
}

void SetClass::deleteData()
{
    if (ui->lineEdit_classID->text().isEmpty()
            or ui->lineEdit_className->text().isEmpty()) {
        // 如果为空，返回错误
        QMessageBox::information(this, "错误", "输入信息有空值\n",QMessageBox::Ok);
        return;
    }
    int classID = ui->lineEdit_classID->text().toInt();
    QString className = ui->lineEdit_className->text();
//    //QString grade
//    query->clear();
//    query->prepare("SELECT gradeID FROM tb_grade WHERE gradeName = ?");
//    qDebug() << ui->comboBox_grade->currentText();
//    query->bindValue(0, ui->comboBox_grade->currentText());
//    query->exec();
//    query->first();
//    if (!query->isValid()) {
//        QMessageBox::information(this, "错误", "数据查询错误，错误信息\n"
//                                 + query->lastError().text(),QMessageBox::Ok);
//        return;
//    }
//    int gradeID = query->value("gradeID").toInt();
    query->clear();

    query->prepare("Delete FROM tb_class WHERE classID = ?");

    query->bindValue(0, classID);

    if (!query->exec()) {
        QMessageBox::information(this, "错误", "数据删除错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    this->updateRecord(0);
}

void SetClass::InsertData()
{
    if (ui->lineEdit_classID->text().isEmpty()
            or ui->lineEdit_className->text().isEmpty()) {
        // 如果为空，返回错误
        QMessageBox::information(this, "错误", "输入信息有空值\n",QMessageBox::Ok);
        return;
    }
    int classID = ui->lineEdit_classID->text().toInt();
    QString className = ui->lineEdit_className->text();
    //QString grade
    query->clear();
    query->prepare("SELECT gradeID FROM tb_grade WHERE gradeName = ?");
    qDebug() << ui->comboBox_grade->currentText();
    query->bindValue(0, ui->comboBox_grade->currentText());
    query->exec();
    query->first();
    if (!query->isValid()) {
        QMessageBox::information(this, "错误", "数据查询错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    int gradeID = query->value("gradeID").toInt();

    query->clear();

    query->prepare("INSERT INTO tb_class VALUES(?, ?, ?)");

    query->bindValue(0, classID);
    query->bindValue(1, gradeID);
    query->bindValue(2, className);

    if (!query->exec()) {
        QMessageBox::information(this, "错误", "数据添加错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }

    this->updateRecord(0);
}

void SetClass::modifyData()
{
    if (ui->lineEdit_classID->text().isEmpty()
            or ui->lineEdit_className->text().isEmpty()) {
        // 如果为空，返回错误
        QMessageBox::information(this, "错误", "输入信息有空值\n",QMessageBox::Ok);
        return;
    }
    int classID = ui->lineEdit_classID->text().toInt();
    QString className = ui->lineEdit_className->text();
    //QString grade
    query->clear();
    query->prepare("SELECT gradeID FROM tb_grade WHERE gradeName = ?");
    qDebug() << ui->comboBox_grade->currentText();
    query->bindValue(0, ui->comboBox_grade->currentText());
    query->exec();
    query->first();
    if (!query->isValid()) {
        QMessageBox::information(this, "错误", "数据查询错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    int gradeID = query->value("gradeID").toInt();

    query->clear();
    // 根据classID修改gradeID 和 className, 需要注意，如果没有对应的gradeID，应该会报错。
    query->prepare("UPDATE tb_class SET gradeID = ?, className = ? WHERE classID = ?");


    query->bindValue(0, gradeID);
    query->bindValue(1, className);
    query->bindValue(2, classID);

    if (!query->exec()) {
        QMessageBox::information(this, "错误", "数据添加错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    this->updateRecord(0);
}

SetClass::SetClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetClass)
{
    ui->setupUi(this);
    query = new QSqlQuery();
    // 将全部年级插入到combox中
//    QSqlQuery query;  // 设置一个查询类
    query->exec("select gradeName from tb_grade order by gradeID");
    query->first();
    while(query->isValid()) {
        QString gradeName = query->value("gradeName").toString();
        ui->comboBox_grade->addItem(gradeName);
        if (!query->next()) {
            break;
        }
    }
    query->clear();
    openTable();
}

SetClass::~SetClass()
{
    delete ui;
}

void SetClass::on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    // 当选择的下标改变时，我们也需要改变line框中的数据
    Q_UNUSED(previous);
    if (!current.isValid()) {
        return;
    }
    int curRecNo = theSelection->currentIndex().row(); //获取当前行号
    QSqlRecord curRec = qryModel->record(curRecNo);
    int classID = curRec.value("classID").toInt();
    QString className = curRec.value("className").toString();
    QString gradeName = curRec.value("gradeName").toString();
    ui->lineEdit_classID->setText(QString::number(classID));
    ui->lineEdit_className->setText(className);
    ui->comboBox_grade->setCurrentText(gradeName);

}

void SetClass::on_pushButton_append_clicked()
{
    this->InsertData();
}


void SetClass::on_pushButton_delete_clicked()
{
    this->deleteData();
}


//
void SetClass::on_pushButton_update_clicked()
{
    this->modifyData();
}

