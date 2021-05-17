/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#ifndef TASKS_PAGE_H
#define TASKS_PAGE_H

#include <QWidget>

#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDate>

class TasksPage : public QWidget
{
    Q_OBJECT
public:
    explicit TasksPage(QString table = "task", QWidget *parent = nullptr);

    QDate date() const;
    void setDate(const QDate &date);

public slots:
    void addTask();
    void duplicateTask(QModelIndex index);

    void onDataChanged();

    void updateTasks();

signals:
    void dataChanged();

protected slots:
    void indexChangedSlot(QModelIndex index);
    void remove(int id);

protected:
    void setupModelAndView();
    int indexOfField(QString fieldName);

protected:
    QVBoxLayout *m_layout;

    QString m_table;

    QSqlTableModel* m_model;
    QTableView *m_view;

    QDate m_date;
};

#endif // TASKS_PAGE_H
