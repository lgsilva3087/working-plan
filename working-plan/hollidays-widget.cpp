#include "hollidays-widget.h"

#include "delegates/date-delegate.h"
#include "delegates/icon-delegate.h"

#include "settings.h"

HollidaysWidget::HollidaysWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void HollidaysWidget::setupUi()
{
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    setLayout(m_layout);

    QHBoxLayout *m_push = new QHBoxLayout;
    m_push->setMargin(3);
    m_push->setSpacing(3);

    m_layout->addLayout(m_push);

    m_addPushButton = new QPushButton(tr("Adicionar día"));
    m_push->addWidget(m_addPushButton);
    connect(m_addPushButton, &QPushButton::clicked, this, &HollidaysWidget::add);
    m_push->addStretch();


    m_model = new QSqlTableModel;
    m_model->setTable("holliday");

    m_model->setHeaderData(indexOfField("id"), Qt::Horizontal, tr(""));
    m_model->setHeaderData(indexOfField("name"), Qt::Horizontal, tr("Tarea"));

    m_view = new QTableView;
    m_layout->addWidget(m_view);
    m_view->setModel(m_model);
    m_view->setSortingEnabled(true);
    m_view->sortByColumn(indexOfField("dateStamp"), Qt::AscendingOrder);
    m_view->setColumnHidden(indexOfField("id"), true);

    m_view->verticalHeader()->hide();

    m_model->setHeaderData(indexOfField("dateStamp"), Qt::Horizontal, tr("Vacaciones"));
    m_model->setHeaderData(indexOfField("remove"), Qt::Horizontal, tr(""));

    m_view->setColumnWidth(indexOfField("remove"), 30);
    m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    m_view->horizontalHeader()->setSectionResizeMode(indexOfField("dateStamp"),
                                                     QHeaderView::Stretch);

    m_view->setShowGrid(true);
    m_view->setAlternatingRowColors(true);

    m_view->setItemDelegateForColumn(indexOfField("dateStamp"),
                                     new DateDelegate());
    m_view->setItemDelegateForColumn(indexOfField("remove"),
                                     new IconDelegate(QPixmap(":/resources/icons/remove.png")));

    m_model->select();

    connect(m_model, &QSqlTableModel::dataChanged, this, &HollidaysWidget::dataChanged);
    connect(m_view, SIGNAL(clicked(QModelIndex)), this, SLOT(indexChangedSlot(QModelIndex)));
}

int HollidaysWidget::indexOfField(QString fieldName)
{
    return m_model->record().indexOf(fieldName);
}

void HollidaysWidget::indexChangedSlot(QModelIndex index)
{
    if (index.column() == m_model->columnCount() - 1)
    {
        int result = QMessageBox::information(0, tr("Eliminar tarea"),
                                              tr("¿Desea eliminar el día seleccionado?"),
                                              QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        if (result == QMessageBox::Ok)
        {
            remove(m_model->index(index.row(), 0).data().toInt());

            m_model->select();

            emit dataChanged();

            //Settings::instance()->updatehollidays();
        }
    }
}

void HollidaysWidget::remove(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM holliday WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

void HollidaysWidget::add()
{
    QSqlQuery query;
    query.prepare("INSERT INTO holliday VALUES(:id, :dateStamp, NULL)");
    query.bindValue(":id", utils::nextId("holliday"));
    query.bindValue(":dateStamp", utils::toDateStamp(QDate::currentDate()));
    query.exec();

    m_model->select();

    emit dataChanged();
}
