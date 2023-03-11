#include "managestudent.h"
#include "ui_managestudent.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
ManageStudent::ManageStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageStudent)
{
    ui->setupUi(this);
    // 需要在这里确定年级列表,当选择了年级列表后,需要更新班级列表
    query = new QSqlQuery();
    if (!query->exec("SELECT gradeName FROM tb_grade order by gradeID")) {
        QMessageBox::information(this, "错误", "数据查询错误,错误信息\n"
                                 + query->lastError().text());
        return;
    }
    query->first();
    while (query->isValid()) {
        QString gradeName = query->value("gradeName").toString();
        ui->comboBox_grade->addItem(gradeName);
        if (!query->next()) {
            break;
        }
    }
    query->clear();
    openTable();
}

ManageStudent::~ManageStudent()
{
    delete ui;
}

void ManageStudent::openTable()
{
    // 打开数据库
    qryModel = new QSqlQueryModel(this);
    theSelection = new QItemSelectionModel(qryModel);
    qryModel->setQuery("SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo ORDER BY stuID");
    // 如果出现报错:
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
    ui->tableView->setSelectionModel(theSelection);

    connect(this->theSelection, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this, SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));
}

// 更新显示数据
void ManageStudent::on_updateRecord()
{
    //如果gradeitem 为 all ,则全部加载
    // 如果 gradeitem 不为all , classitem 为all ,则限制gradeitem
    // 如果gradeitem 不为all, classitem 不为all, 则限制gradeitem\classitem
    QString currentGrade = ui->comboBox_grade->currentText();
    QString currentClass = ui->comboBox_class->currentText();
    QString queryInfo;  // 查询语句
    if (currentGrade == "全部") {
        queryInfo = "SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo ORDER BY stuID";
        // 如果出现报错:
        qryModel->setQuery(queryInfo);
        if (qryModel->lastError().isValid()) {
            QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                     +qryModel->lastError().text(), QMessageBox::Ok);
            return;
        }
    }
    else if (currentClass == "全部") {
        queryInfo = "SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo WHERE gradeName = '" + currentGrade + "' ORDER BY stuID";
        qryModel->setQuery(queryInfo);
        // 如果出现报错:
        if (qryModel->lastError().isValid()) {
            QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                     +qryModel->lastError().text(), QMessageBox::Ok);
            return;
        }
    }
    else {
        queryInfo = "SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo WHERE gradeName = '" + currentGrade + "' and className = '" + currentClass + "' ORDER BY stuID";
        qryModel->setQuery(queryInfo);
        // 如果出现报错:
        if (qryModel->lastError().isValid()) {
            QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                     +qryModel->lastError().text(), QMessageBox::Ok);
            return;
        }
    }

}

// 当当前的选择项发生改变时,各个lineEdit的值也会随着发生改变.
void ManageStudent::on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    if (!current.isValid()) {
        return;
    }
    int curRecNo = theSelection->currentIndex().row();
    QSqlRecord curRec = qryModel->record(curRecNo);
    int stuID = curRec.value("stuID").toInt();
    QString stuName = curRec.value("stuName").toString();
    //QString gradeName = curRec.value("gradeName").toString();
   // QString className = curRec.value("className").toString();

    int age = curRec.value("age").toInt();
    QString sex = curRec.value("sex").toString();
    QString address = curRec.value("address").toString();
    QString phone = curRec.value("phone").toString();

    ui->lineEdit_phone->setText(phone);
    ui->lineEdit_adress->setText(address);
    ui->lineEdit_age->setText(QString::number(age));
    ui->lineEdit_stuID->setText(QString::number(stuID));
    ui->lineEdit_stuName->setText(stuName);
    ui->comboBox_sex->setCurrentText(sex);


}

void ManageStudent::on_comboBox_grade_currentTextChanged(const QString &arg1)
{
    // 当前的的item发生改变时,对应的claseitem也会出现改变
    // 具体的改变规则如下:
    // 1. 当gradeitem 发生更改时, 那么classitem的cureentitem更改为all
    // 2. 当gradeitem 为 all 时,classitem 只能剩下 all
    // 3. 当gradeitem 为 all 以外的值时,classitem 的所有item要与gradeitem的值向对应.


    // 重置gradeitem
    if (arg1 == "全部") {
        ui->comboBox_class->clear();
        ui->comboBox_class->addItem("全部");
        ui->comboBox_class->setCurrentText("全部");
    }
    else {
        ui->comboBox_class->clear();
        ui->comboBox_class->addItem("全部");
        query->prepare("select className from v_classinfo where gradeName = ? order by classID");
        query->bindValue(0, arg1);

        if (!query->exec()) {
            QMessageBox::information(this, "错误", "数据查询错误,错误信息\n"
                                     + query->lastError().text());
            return;
        }
        query->first();
        while(query->isValid()) {
           QString className = query->value("className").toString();
           ui->comboBox_class->addItem(className);
           if (!query->next()) {
               break;
           }
        }
        query->clear();
        ui->comboBox_class->setCurrentText("全部");
    }


    if (arg1 == "全部") {
        qryModel->setQuery("SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo ORDER BY stuID");
        // 如果出现报错:
        if (qryModel->lastError().isValid()) {
            QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                     +qryModel->lastError().text(), QMessageBox::Ok);
            return;
        }
    }
    else{
        QString queryName = "SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo WHERE gradeName = '" + arg1 + "' ORDER BY stuID";
        qDebug() << queryName;
        qryModel->setQuery(queryName);
        // 如果出现报错:
        if (qryModel->lastError().isValid()) {
            QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                     +qryModel->lastError().text(), QMessageBox::Ok);
            return;
        }
    }


}


void ManageStudent::on_comboBox_class_currentTextChanged(const QString &arg1)
{
    // 当前text changed  时,那么需要判断grade text是否为all
    QString gradeName = ui->comboBox_grade->currentText();
    QString queryinfo;
    if (gradeName == "全部") {
        return;
    }
    if (arg1.isEmpty()) {
        return;
    }
    if (arg1 == "全部") {
        queryinfo = "SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo WHERE gradeName = '" + gradeName + "' ORDER BY stuID";
        qryModel->setQuery(queryinfo);

        // 如果出现报错:
        if (qryModel->lastError().isValid()) {
            QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                     +qryModel->lastError().text(), QMessageBox::Ok);
            return;
        }
    }
    else{
        queryinfo = "SELECT stuID, stuName, gradeName, className, age, sex, address, phone FROM v_studentinfo WHERE gradeName = '" + gradeName + "' and className = '" + arg1 + "' ORDER BY stuID";
        qDebug() << queryinfo;
        qryModel->setQuery(queryinfo);
        // 如果出现报错:
        if (qryModel->lastError().isValid()) {
            QMessageBox::information(this, "错误", "数据表查询错误,错误信息\n"
                                     +qryModel->lastError().text(), QMessageBox::Ok);
            return;
        }
    }
}


void ManageStudent::on_pushButton_refresh_clicked()
{
    this->on_updateRecord();
}


void ManageStudent::on_pushButton_insert_clicked()
{
    // insert
    // 需要读取全部的信息,另外需要 class和gradename 不为all
    QString gradeName = ui->comboBox_grade->currentText();
    QString className = ui->comboBox_class->currentText();

    if (gradeName == "全部" or className == "全部") {
        QMessageBox::information(this, "错误", "请选择正确的年级和班级\n", QMessageBox::Ok);
        return;
    }
    int stuID = ui->lineEdit_stuID->text().toInt();
    QString stuName = ui->lineEdit_stuName->text();
    int age = ui->lineEdit_age->text().toInt();
    QString sex = ui->comboBox_sex->currentText();
    QString phone = ui->lineEdit_phone->text();
    QString address = ui->lineEdit_adress->text();

    //查询当前的gradeid
    query->clear();
    query->prepare("SELECT gradeID FROM tb_grade WHERE gradeName = ?");
    qDebug() << gradeName;
    query->bindValue(0, gradeName);
    query->exec();
    query->first();
    if (!query->isValid()) {
        QMessageBox::information(this, "错误", "数据查询错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    int gradeID = query->value("gradeID").toInt();

    // 查询classID
    query->clear();
    query->prepare("SELECT classID FROM tb_class WHERE className = ?");
    //qDebug() << className;
    query->bindValue(0, className);
    query->exec();
    query->first();
    if (!query->isValid()) {
        QMessageBox::information(this, "错误", "数据查询错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    int classID = query->value("classID").toInt();

    query->prepare("INSERT INTO tb_student VALUES(?,?,?,?,?,?,?,?)");
    query->bindValue(0,  stuID);
    query->bindValue(1,  stuName);
    query->bindValue(2,  classID);
    query->bindValue(3,  gradeID);
    query->bindValue(4,  age);
    query->bindValue(5,  sex);
    query->bindValue(6,  phone);
    query->bindValue(7,  address);

    if (!query->exec()) {
        QMessageBox::information(this, "错误", "数据添加错误，错误信息\n"
                                         + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    this->on_updateRecord();
}


void ManageStudent::on_pushButton_update_clicked()
{
    // update
    // 需要读取全部的信息,另外需要 class和gradename 不为all
    QString gradeName = ui->comboBox_grade->currentText();
    QString className = ui->comboBox_class->currentText();

    if (gradeName == "全部" or className == "全部") {
        QMessageBox::information(this, "错误", "请选择正确的年级和班级\n", QMessageBox::Ok);
        return;
    }
    int stuID = ui->lineEdit_stuID->text().toInt();
    QString stuName = ui->lineEdit_stuName->text();
    int age = ui->lineEdit_age->text().toInt();
    QString sex = ui->comboBox_sex->currentText();
    QString phone = ui->lineEdit_phone->text();
    QString address = ui->lineEdit_adress->text();

    //查询当前的gradeid
    query->clear();
    query->prepare("SELECT gradeID FROM tb_grade WHERE gradeName = ?");
    qDebug() << gradeName;
    query->bindValue(0, gradeName);
    query->exec();
    query->first();
    if (!query->isValid()) {
        QMessageBox::information(this, "错误", "数据查询错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    int gradeID = query->value("gradeID").toInt();

    // 查询classID
    query->clear();
    query->prepare("SELECT classID FROM tb_class WHERE className = ?");
    //qDebug() << className;
    query->bindValue(0, className);
    query->exec();
    query->first();
    if (!query->isValid()) {
        QMessageBox::information(this, "错误", "数据查询错误，错误信息\n"
                                 + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    int classID = query->value("classID").toInt();

    query->clear();
    query->prepare("UPDATE tb_student SET stuName = ?, classID = ?, gradeID = ?, age = ?, sex = ?, phone = ?, address = ? WHERE stuID = ?");

    query->bindValue(0,  stuName);
    query->bindValue(1,  classID);
    query->bindValue(2,  gradeID);
    query->bindValue(3,  age);
    query->bindValue(4,  sex);
    query->bindValue(5,  phone);
    query->bindValue(6,  address);
    query->bindValue(7,  stuID);

    if (!query->exec()) {
        QMessageBox::information(this, "错误", "数据修改错误，错误信息\n"
                                         + query->lastError().text(),QMessageBox::Ok);
        return;
    }
    this->on_updateRecord();
}


void ManageStudent::on_pushButton_delete_clicked()
{
    if (ui->lineEdit_stuID->text().isEmpty()) {
        QMessageBox::warning(this,
                "警告", "当前的学号为空", QMessageBox::Ok);
        return;
    }
    int stuID = ui->lineEdit_stuID->text().toInt();
    QMessageBox::StandardButton reply = QMessageBox::warning(this,
        "警告", "你确定要删除当前选择的学生信息吗", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        query->prepare("DELETE FROM tb_student WHERE stuID = ?");
        query->bindValue(0, stuID);
        if (!query->exec()) {
            QMessageBox::information(this, "错误", "数据删除错误，错误信息\n"
                                             + query->lastError().text(),QMessageBox::Ok);
            return;
        }
    }
    this->on_updateRecord();
}

