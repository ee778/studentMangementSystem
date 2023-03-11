#ifndef SETCLASS_H
#define SETCLASS_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QSqlQuery>
namespace Ui {
class SetClass;
}

class SetClass : public QDialog
{
    Q_OBJECT
private:
    QSqlQueryModel *qryModel; //数据库模型
    QSqlQuery *query;
    // 不需要选择模型？  可以有选择模型，实现点击数据库的行后，直接在年级编号和年级名称中显示
    QItemSelectionModel *theSelection;  // 选择模型
    void openTable(); // 打开数据表
    void updateRecord(int recNo); // 更新记录
    void deleteData();
    void InsertData();
    void modifyData();
public:
    explicit SetClass(QWidget *parent = nullptr);
    ~SetClass();
private slots:
    void on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_pushButton_append_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_update_clicked();

private:
    Ui::SetClass *ui;
};

#endif // SETCLASS_H
