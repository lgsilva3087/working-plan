/*
 * removeicondelegate.cpp
 *
 *  Created on: Dec 5, 2011
 *      Author: haazzz
 */

#include "icon-delegate.h"

IconDelegate::IconDelegate(const QPixmap &pixmap)
    : QStyledItemDelegate()
{
    m_pixmap = pixmap;
}

void IconDelegate::paint(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &) const
{
    if (option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, option.palette.highlight());

        painter->save();
        painter->setPen(option.palette.highlightedText().color());
    }

    painter->drawPixmap(option.rect.x() + 6, option.rect.y() + 6,
                        option.rect.width() - 12, option.rect.height() - 12,
                        m_pixmap);

    if (option.state & QStyle::State_Selected)
        painter->restore();

}

IconDelegate::~IconDelegate()
{
}
