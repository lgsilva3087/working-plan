/*
 *  Created on: Sept 15, 2012
 *      Author: guille
 */

#include "time-delegate.h"
#include <utils.h>

TimeDelegate::TimeDelegate()
    : QStyledItemDelegate()
{
}

void TimeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    QString value = index.model()->index(index.row(), index.column()).data().toString();
    //QTime dateTime = utils::toDateTime(epoch);

    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());

        painter->save();
        painter->setPen(option.palette.highlightedText().color());
    }

    painter->drawText(QRect(option.rect.topLeft(), option.rect.bottomRight()),
                      Qt::AlignCenter, value);

    if (option.state & QStyle::State_Selected)
        painter->restore();
}

QWidget *TimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */,
                                    const QModelIndex & /*index*/) const
{
    QTimeEdit *editor = new QTimeEdit(parent);
    editor->setFrame(false);
    editor->setDisplayFormat("hh:mm");
    //editor->setCalendarPopup(true);

    return editor;
}

void TimeDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    QTimeEdit *edit = static_cast<QTimeEdit*>(editor);
    edit->setTime(QTime::fromString(value, "hh:mm"));
}

void TimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QTimeEdit *edit = static_cast<QTimeEdit*>(editor);
    QString value = edit->time().toString("hh:mm");

    model->setData(index, value, Qt::EditRole);
}

void TimeDelegate::updateEditorGeometry(QWidget *editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

TimeDelegate::~TimeDelegate()
{
}
