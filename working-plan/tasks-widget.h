/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#ifndef TASKSWIDGET_H
#define TASKSWIDGET_H

#include <QWidget>

#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QDate>

class TasksWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TasksWidget(QWidget *parent = nullptr);

    QDate date() const;
    void setDate(const QDate &date);

public slots:
    void addTask();

    void onDataChanged();

signals:
    void dataChanged();

protected slots:
    void indexChangedSlot(QModelIndex index);
    void remove(int id);

protected:
    void setupModelAndView();

protected:
    QVBoxLayout *m_layout;

    QSqlTableModel* m_model;
    QTableView *m_view;
    int indexOfField(QString fieldName);

    QDate m_date;
};

#endif // TASKSWIDGET_H
