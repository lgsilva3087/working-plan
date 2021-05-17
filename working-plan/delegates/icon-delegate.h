/*
 *
 *  Created on: Dec 5, 2013
 *      Author: Guille
 */

#ifndef ICONDELEGATE_H_
#define ICONDELEGATE_H_

#include <QPainter>
#include <QStyledItemDelegate>

class IconDelegate : public QStyledItemDelegate
{
public:
    IconDelegate(const QPixmap &pixmap);
    virtual ~IconDelegate();

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &) const;
    QWidget* createEditor(QWidget */*parent*/, const QStyleOptionViewItem &/*option*/,
                          const QModelIndex &/*index*/) const { return 0; }

private:
    QPixmap m_pixmap;
};

#endif /* ICONDELEGATE_H_ */
