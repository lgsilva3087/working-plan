/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#include "tasks-page.h"

#include "delegates/icon-delegate.h"
#include "delegates/date-delegate.h"
#include "delegates/time-delegate.h"
#include "delegates/spinbox-delegate.h"
#include "delegates/combobox-delegate.h"

#include <utils.h>

TasksPage::TasksPage(QString table, QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout;
    m_layout->setSpacing(0);
    m_layout->setMargin(0);

    m_table = table;

    m_date = QDate::currentDate();

    setLayout(m_layout);

    setupModelAndView();
}

void TasksPage::addTask()
{
    QSqlQuery query;
    query.prepare(QString("INSERT INTO %1 VALUES(:id, '', :startDate, :endDate, '08:00', "
                          "'12:00', 0, 1, 'black', 'FALSE', NULL)").arg(m_table));
    query.bindValue(":id", utils::nextId(m_table));
    query.bindValue(":startDate", utils::toDateStamp(m_date));
    query.bindValue(":endDate", utils::toDateStamp(m_date));
    query.exec();

    m_model->select();
}

void TasksPage::duplicateTask(QModelIndex index)
{
    QString title = index.model()->index(index.row(), 1).data().toString();
    int startDate = index.model()->index(index.row(), 2).data().toInt();
    int endDate =   index.model()->index(index.row(), 3).data().toInt();
    QString startTime =   index.model()->index(index.row(), 4).data().toString();
    QString endTime = index.model()->index(index.row(), 5).data().toString();
    int periodicity = 0;
    if(index.model()->index(index.row(), 6).data().toString() != "NO")
        periodicity = index.model()->index(index.row(), 6).data().toInt();
    int status = index.model()->index(index.row(), 7).data().toInt();
    QString color =   index.model()->index(index.row(), 8).data().toString();
    QString principal =   index.model()->index(index.row(), 9).data().toString();

    QSqlQuery query;
    query.prepare(QString("INSERT INTO %1 VALUES(:id, :title, :startDate, :endDate, :startTime,"
                  " :endTime, :periodicity, :status, :color, :principal, NULL)").arg(m_table));
    query.bindValue(":id", utils::nextId(m_table));
    query.bindValue(":title", title);
    query.bindValue(":startDate", startDate);
    query.bindValue(":endDate", endDate);
    query.bindValue(":startTime", startTime);
    query.bindValue(":endTime", endTime);
    query.bindValue(":periodicity", periodicity);
    query.bindValue(":status", status);
    query.bindValue(":color", color);
    query.bindValue(":principal", principal);
    query.exec();

    m_model->select();
}

void TasksPage::onDataChanged()
{
    emit dataChanged();
}

void TasksPage::updateTasks()
{
    m_model->select();
}

void TasksPage::setupModelAndView()
{
    m_model = new QSqlTableModel;
    m_model->setTable(m_table);

    m_view = new QTableView;
    m_view->setModel(m_model);

    m_view->resizeColumnsToContents();
    m_view->setColumnHidden(indexOfField("status"), true);
    m_view->setSortingEnabled(true);
    m_view->sortByColumn(indexOfField("startDate"), Qt::AscendingOrder);

    m_view->verticalHeader()->hide();

    m_model->setHeaderData(indexOfField("id"), Qt::Horizontal, tr(""));
    m_model->setHeaderData(indexOfField("name"), Qt::Horizontal, tr("Tarea"));
    m_model->setHeaderData(indexOfField("startDate"), Qt::Horizontal, tr("Fecha\nde inicio"));
    m_model->setHeaderData(indexOfField("endDate"), Qt::Horizontal, tr("Fecha\nde fin"));
    m_model->setHeaderData(indexOfField("startTime"), Qt::Horizontal, tr("Inicio"));
    m_model->setHeaderData(indexOfField("endTime"), Qt::Horizontal, tr("Fin"));
    m_model->setHeaderData(indexOfField("periodicity"), Qt::Horizontal, tr("Repetir"));
    m_model->setHeaderData(indexOfField("status"), Qt::Horizontal, tr("Estado"));
    m_model->setHeaderData(indexOfField("color"), Qt::Horizontal, tr("Color"));
    m_model->setHeaderData(indexOfField("principal"), Qt::Horizontal, tr("Principal"));
    m_model->setHeaderData(indexOfField("remove"), Qt::Horizontal, tr(""));

    m_view->setColumnWidth(indexOfField("id"), 30);
    m_view->setColumnWidth(indexOfField("startDate"), 85);
    m_view->setColumnWidth(indexOfField("endDate"), 85);
    m_view->setColumnWidth(indexOfField("remove"), 30);
    m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_view->horizontalHeader()->setSectionResizeMode(indexOfField("startDate"),
                                                     QHeaderView::Fixed);
    m_view->horizontalHeader()->setSectionResizeMode(indexOfField("endDate"),
                                                     QHeaderView::Fixed);
    m_view->horizontalHeader()->setSectionResizeMode(indexOfField("name"),
                                                     QHeaderView::Stretch);

    m_view->setShowGrid(true);
    m_view->setAlternatingRowColors(true);

    m_view->setItemDelegateForColumn(indexOfField("id"),
                                     new IconDelegate(QPixmap(":/resources/icons/add.png")));
    m_view->setItemDelegateForColumn(indexOfField("startDate"),
                                     new DateDelegate());
    m_view->setItemDelegateForColumn(indexOfField("endDate"),
                                     new DateDelegate());
    m_view->setItemDelegateForColumn(indexOfField("startTime"),
                                     new TimeDelegate());
    m_view->setItemDelegateForColumn(indexOfField("endTime"),
                                     new TimeDelegate());
    m_view->setItemDelegateForColumn(indexOfField("periodicity"),
                                     new SpinBoxDelegate());
    m_view->setItemDelegateForColumn(indexOfField("principal"),
                                     new ComboBoxDelegate());
    m_view->setItemDelegateForColumn(indexOfField("remove"),
                                     new IconDelegate(QPixmap(":/resources/icons/remove.png")));

    m_layout->addWidget(m_view);

    m_model->select();

    connect(m_model, &QSqlTableModel::dataChanged, this, &TasksPage::onDataChanged);
    connect(m_view, SIGNAL(clicked(QModelIndex)), this, SLOT(indexChangedSlot(QModelIndex)));
}

int TasksPage::indexOfField(QString fieldName)
{
    return m_model->record().indexOf(fieldName);
}

QDate TasksPage::date() const
{
    return m_date;
}

void TasksPage::setDate(const QDate &date)
{
    m_date = date;
}

void TasksPage::indexChangedSlot(QModelIndex index)
{
    if(index.column() == indexOfField("id")){
        duplicateTask(index);

        emit dataChanged();
    }
    else if (index.column() == m_model->columnCount() - 1)
    {
        int result = QMessageBox::information(nullptr, tr("Eliminar tarea"),
                                              tr("¿Desea eliminar la tarea seleccionada?"),
                                              QMessageBox::Ok | QMessageBox::Cancel,
                                              QMessageBox::Ok);
        if (result == QMessageBox::Ok)
        {
            remove(m_model->index(index.row(), 0).data().toInt());

            m_model->select();

            emit dataChanged();
        }
    }

}

void TasksPage::remove(int id)
{
    QSqlQuery query;

    query.prepare(QString("DELETE FROM %1 WHERE id = :id").arg(m_table));
    query.bindValue(":id", id);
    query.exec();
}

