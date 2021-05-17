/*
 *  Created on: Sept 15, 2012
 *      Author: guille
 */

#ifndef DATEDELEGATE_H_
#define DATEDELEGATE_H_

#include <QPainter>
#include <QStyledItemDelegate>
#include <QDateTime>

class DateDelegate : public QStyledItemDelegate
{
public:
    DateDelegate();
    virtual ~DateDelegate();

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

#endif /* DATEDELEGATE_H_ */
