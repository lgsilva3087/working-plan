#include "delegates/combobox-delegate.h"

ComboBoxDelegate::ComboBoxDelegate()
{

}

void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    QString value = index.model()->index(index.row(), index.column()).data().toString();

    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());

        painter->save();
        painter->setPen(option.palette.highlightedText().color());
    }

    QPoint bottomRight = option.rect.bottomRight() - QPoint(10, 0);

    painter->drawText(QRect(option.rect.topLeft(), bottomRight),
                      Qt::AlignVCenter | Qt::AlignLeft, value);

    if (option.state & QStyle::State_Selected)
        painter->restore();
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */,
                                    const QModelIndex & /*index*/) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem("TRUE");
    editor->addItem("FALSE");
    editor->setFrame(false);

    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    QComboBox *edit = static_cast<QComboBox*>(editor);
    edit->setCurrentIndex(edit->findText(value));
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QComboBox *edit = static_cast<QComboBox*>(editor);

    model->setData(index, edit->currentText(), Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

ComboBoxDelegate::~ComboBoxDelegate()
{
}
