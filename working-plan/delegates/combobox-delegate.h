#ifndef COMBOBOX_DELEGATE_H
#define COMBOBOX_DELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QPainter>

class ComboBoxDelegate : public QStyledItemDelegate
{
public:
    ComboBoxDelegate();
    virtual ~ComboBoxDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex & index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
};

#endif // COMBOBOX_DELEGATE_H
