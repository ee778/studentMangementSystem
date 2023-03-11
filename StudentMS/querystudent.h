#ifndef QUERYSTUDENT_H
#define QUERYSTUDENT_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QSqlQuery>

namespace Ui {
class QueryStudent;
}

class QueryStudent : public QDialog
{
    Q_OBJECT

public:
    explicit QueryStudent(QWidget *parent = nullptr);
    ~QueryStudent();
private slots:
    void on_pushButton_select_clicked();

    void on_lineEdit_key_textEdited(const QString &arg1);

private:
    QSqlQueryModel *qryModel;
private:
    Ui::QueryStudent *ui;
};

#endif // QUERYSTUDENT_H
