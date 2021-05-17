#include "delegates/spinbox-delegate.h"

SpinBoxDelegate::SpinBoxDelegate()
{

}

void SpinBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    int value = index.model()->index(index.row(), index.column()).data().toInt();

    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());

        painter->save();
        painter->setPen(option.palette.highlightedText().color());
    }

    QPoint bottomRight = option.rect.bottomRight() - QPoint(10, 0);

    painter->drawText(QRect(option.rect.topLeft(), bottomRight),
                      Qt::AlignVCenter | Qt::AlignRight, QString::number(value).append(" días"));

    if (option.state & QStyle::State_Selected)
        painter->restore();
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */,
                                    const QModelIndex & /*index*/) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setRange(0, 365);
    editor->setFrame(false);

    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();

    QSpinBox *edit = static_cast<QSpinBox*>(editor);
    edit->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QSpinBox *edit = static_cast<QSpinBox*>(editor);

    model->setData(index, edit->value(), Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

SpinBoxDelegate::~SpinBoxDelegate()
{
}
