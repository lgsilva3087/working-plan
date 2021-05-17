/*
 *  Created on: Sept 15, 2012
 *      Author: guille
 */

#ifndef TIME_DELEGATE_H_
#define TIME_DELEGATE_H_

#include <QPainter>
#include <QStyledItemDelegate>
#include <QTimeEdit>

class TimeDelegate : public QStyledItemDelegate
{
public:
    TimeDelegate();
    virtual ~TimeDelegate();

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

#endif /* TIME_DELEGATE_H_ */
