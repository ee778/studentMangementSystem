#ifndef SETGRADE_H
#define SETGRADE_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
namespace Ui {
class SetGrade;
}

class SetGrade : public QDialog
{
    Q_OBJECT
private:
    QSqlQueryModel *qryModel;
    QSqlQuery *query;
    QItemSelectionModel *theSelection;
    void openTable();
    void updataRecord();
public:
    explicit SetGrade(QWidget *parent = nullptr);
    ~SetGrade();
private slots:
    void on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_pushButton_insert_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::SetGrade *ui;
};

#endif // SETGRADE_H
