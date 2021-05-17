/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#include "tasks-widget.h"

#include "delegates/icon-delegate.h"
#include "delegates/date-delegate.h"
#include "delegates/time-delegate.h"

#include <utils.h>

TasksWidget::TasksWidget(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout;
    m_layout->setSpacing(0);
    m_layout->setMargin(0);

    m_date = QDate::currentDate();

    setLayout(m_layout);

    setupModelAndView();
}

void TasksWidget::addTask()
{
    QSqlQuery query;
    query.prepare("INSERT INTO task VALUES(:id, '', :startDate, :endDate, '08:00', '12:00', "
                  "'NO', 1, 'red', 'FALSE', NULL)");
    query.bindValue(":id", utils::nextId("task"));
    query.bindValue(":startDate", utils::toDateStamp(m_date));
    query.bindValue(":endDate", utils::toDateStamp(m_date));
    query.exec();

    m_model->select();
}

void TasksWidget::onDataChanged()
{
    emit dataChanged();
}

void TasksWidget::setupModelAndView()
{
    m_model = new QSqlTableModel;
    m_model->setTable("task");

    m_view = new QTableView;
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->setModel(m_model);

    m_view->resizeColumnsToContents();
    m_view->setColumnHidden(indexOfField("id"), true);
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
    m_view->setColumnWidth(indexOfField("startDate"), 75);
    m_view->setColumnWidth(indexOfField("endDate"), 75);
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
                                     new IconDelegate(QPixmap(":/resources/icons/edit.png")));
    m_view->setItemDelegateForColumn(indexOfField("startDate"),
                                     new DateDelegate());
    m_view->setItemDelegateForColumn(indexOfField("endDate"),
                                     new DateDelegate());
    m_view->setItemDelegateForColumn(indexOfField("startTime"),
                                     new TimeDelegate());
    m_view->setItemDelegateForColumn(indexOfField("endTime"),
                                     new TimeDelegate());
    m_view->setItemDelegateForColumn(indexOfField("remove"),
                                     new IconDelegate(QPixmap(":/resources/icons/remove_small.png")));

    m_layout->addWidget(m_view);

    m_model->select();

    connect(m_model, &QSqlTableModel::dataChanged, this, &TasksWidget::onDataChanged);
    connect(m_view, SIGNAL(clicked(QModelIndex)), this, SLOT(indexChangedSlot(QModelIndex)));
}

int TasksWidget::indexOfField(QString fieldName)
{
    return m_model->record().indexOf(fieldName);
}

QDate TasksWidget::date() const
{
    return m_date;
}

void TasksWidget::setDate(const QDate &date)
{
    m_date = date;
}

void TasksWidget::indexChangedSlot(QModelIndex index)
{
    if (index.column() == m_model->columnCount() - 1)
    {
        int result = QMessageBox::information(0, tr("Eliminar tarea"),
                                              tr("¿Desea eliminar la tarea seleccionada?"),
                                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        if (result == QMessageBox::Ok)
        {
            remove(m_model->index(index.row(), 0).data().toInt());

            m_model->select();
        }
    }
}

void TasksWidget::remove(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM task WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

