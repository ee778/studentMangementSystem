#ifndef MANAGESTUDENT_H
#define MANAGESTUDENT_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QSqlQuery>

namespace Ui {
class ManageStudent;
}

class ManageStudent : public QDialog
{
    Q_OBJECT

public:
    explicit ManageStudent(QWidget *parent = nullptr);
    ~ManageStudent();
private:
    QSqlQueryModel *qryModel;
    QSqlQuery *query;
    QItemSelectionModel *theSelection;
    void openTable();
    void on_updateRecord();
private slots:
    void on_currentRowChanged(const QModelIndex &current,const QModelIndex &previous);
    void on_comboBox_grade_currentTextChanged(const QString &arg1);

    void on_comboBox_class_currentTextChanged(const QString &arg1);

    void on_pushButton_refresh_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::ManageStudent *ui;
};

#endif // MANAGESTUDENT_H
