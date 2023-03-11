#include "setgrade.h"
#include "ui_setgrade.h"
#include <QMessageBox>
#include <QSqlRecord>
void SetGrade::openTable()
{
    qryModel = new QSqlQueryModel(this);
    theSelection = new QItemSelectionModel(qryModel);
    qryModel->setQuery("SELECT gradeID, gradeName FROM tb_grade order by gradeID");

    if (qryModel->lastError().isValid()) { // 如果出现报错
        QMessageBox::information(this, "错误", "数据表查询错误，错误信息\n"
                                 + qryModel->lastError().text(),QMessageBox::Ok);
        return;
    }
    qryModel->setHeaderData(0, Qt::Horizontal, "年级编号");
    qryModel->setHeaderData(1, Qt::Horizontal, "年级名称");


    ui->tableView->setModel(qryModel);
    ui->tableView->setSelectionModel(theSelection);

    query = new QSqlQuery();


    connect(this->theSelection, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this,SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));

}

void SetGrade::updataRecord()
{
    qryModel->setQuery("SELECT gradeID, gradeName FROM tb_grade order by gradeID");
    if (qryModel->lastError().isValid()) { // 如果出现报错
        QMessageBox::information(this, "错误", "数据表查询错误，错误信息\n"
                                 + qryModel->lastError().text(),QMessageBox::Ok);
        return;
    }
}

SetGrade::SetGrade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetGrade)
{
    ui->setupUi(this);
    openTable();

}

SetGrade::~SetGrade()
{
    delete ui;
}

void SetGrade::on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    // 当选择的下标改变时，我们也需要改变line框中的数据
    Q_UNUSED(previous);
    if (!current.isValid()) {
        return;
    }
    int curRecNo = theSelection->currentIndex().row(); //获取当前行号
    QSqlRecord curRec = qryModel->record(curRecNo);
    int gradeID = curRec.value("gradeID").toInt();
    QString gradeName = curRec.value("gradeName").toString();
    ui->lineEdit_gradeID->setText(QString::number(gradeID));
    ui->lineEdit_gradeName->setText(gradeName);
}

void SetGrade::on_pushButton_insert_clicked()
{
    if (ui->lineEdit_gradeID->text().isEmpty()
            or ui->lineEdit_gradeName->text().isEmpty()) {
        // 如果为空，返回错误
        QMessageBox::information(this, "错误", "输入信息有空值\n",QMessageBox::Ok);
        return;
    }
    int gradeID = ui->lineEdit_gradeID->text().toInt();
    QString gradeName = ui->lineEdit_gradeName->text();

    query->clear();
    // 根据classID修改gradeID 和 className, 需要注意，如果没有对应的gradeID，应该会报错。
    query->prepare("INSERT INTO tb_grade VALUES(?, ?)");

    query->bindValue(0, gradeID);
    query->bindValue(1, gradeName);
    if (!query->exec()) {
        QMessageBox::information(this, "错误", "数据插入错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    this->updataRecord();
}


void SetGrade::on_pushButton_update_clicked()
{
    if (ui->lineEdit_gradeID->text().isEmpty()
            or ui->lineEdit_gradeName->text().isEmpty()) {
        // 如果为空，返回错误
        QMessageBox::information(this, "错误", "输入信息有空值\n",QMessageBox::Ok);
        return;
    }
    int gradeID = ui->lineEdit_gradeID->text().toInt();
    QString gradeName = ui->lineEdit_gradeName->text();

    query->clear();
    // 根据classID修改gradeID 和 className, 需要注意，如果没有对应的gradeID，应该会报错。
    query->prepare("UPDATE tb_grade SET gradeName = ? WHERE gradeID = ?");

    query->bindValue(0, gradeName);
    query->bindValue(1, gradeID);

    if (!query->exec()) {
        QMessageBox::information(this, "错误", "数据更改错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    this->updataRecord();
}


void SetGrade::on_pushButton_delete_clicked()
{
    if (ui->lineEdit_gradeID->text().isEmpty()
            or ui->lineEdit_gradeName->text().isEmpty()) {
        // 如果为空，返回错误
        QMessageBox::information(this, "错误", "输入信息有空值\n",QMessageBox::Ok);
        return;
    }
    int gradeID = ui->lineEdit_gradeID->text().toInt();
    QString gradeName = ui->lineEdit_gradeName->text();

    query->clear();
    // 根据classID修改gradeID 和 className, 需要注意，如果没有对应的gradeID，应该会报错。
    query->prepare("DELETE FROM tb_grade WHERE gradeID = ?");

    query->bindValue(0, gradeID);

    if (!query->exec()) {
        QMessageBox::information(this, "错误", "数据删除错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    this->updataRecord();
}

