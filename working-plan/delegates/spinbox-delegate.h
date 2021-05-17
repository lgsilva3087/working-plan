#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QSpinBox>
#include <QPainter>

class SpinBoxDelegate : public QStyledItemDelegate
{
public:
    SpinBoxDelegate();
    virtual ~SpinBoxDelegate();

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

#endif // SPINBOXDELEGATE_H
