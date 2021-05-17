/*
 *  Created on: Sept 15, 2012
 *      Author: guille
 */

#include "date-delegate.h"
#include <utils.h>
#include <QDateEdit>

DateDelegate::DateDelegate()
    : QStyledItemDelegate()
{
}

void DateDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    int epoch = index.model()->index(index.row(), index.column()).data().toInt();
    QDateTime dateTime = utils::toDateTime(epoch);

    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());

        painter->save();
        painter->setPen(option.palette.highlightedText().color());
    }

    painter->drawText(QRect(option.rect.topLeft(), option.rect.bottomRight()),
                      Qt::AlignCenter, dateTime.date().toString("dd/MM/yyyy"));

    if (option.state & QStyle::State_Selected)
        painter->restore();
}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */,
                                    const QModelIndex & /*index*/) const
{
    QDateEdit *editor = new QDateEdit(parent);
    editor->setFrame(false);
    editor->setDisplayFormat("dd/MM/yyyy");
    editor->setCalendarPopup(true);

    return editor;
}

void DateDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QDate value = utils::toDate(index.model()->data(index, Qt::EditRole).toInt());

    QDateEdit *edit = static_cast<QDateEdit*>(editor);
    edit->setDate(value);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QDateEdit *edit = static_cast<QDateEdit*>(editor);
    int value = utils::toDateStamp(edit->date());

    model->setData(index, value, Qt::EditRole);
}

void DateDelegate::updateEditorGeometry(QWidget *editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

DateDelegate::~DateDelegate()
{
}
