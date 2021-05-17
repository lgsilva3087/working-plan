#ifndef HOLLIDAYS_WIDGET_H
#define HOLLIDAYS_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QTableView>
#include <QMessageBox>
#include <QHeaderView>
#include <QPushButton>

#include "utils.h"

class HollidaysWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HollidaysWidget(QWidget *parent = nullptr);

    void setupUi();

signals:
    void dataChanged();

protected slots:
    void indexChangedSlot(QModelIndex index);
    void remove(int id);
    void add();

private:
    int indexOfField(QString fieldName);

private:
    QVBoxLayout *m_layout;

    QPushButton *m_addPushButton;

    QSqlTableModel *m_model;
    QTableView *m_view;
};

#endif // HOLLIDAYS_WIDGET_H
