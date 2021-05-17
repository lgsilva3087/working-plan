/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#include "../include/report-cell.h"

ReportCell::ReportCell(QString text, bool bold, QObject *parent)
    : QObject(parent), m_text(text), m_bold(bold), m_height(20), m_rect(QRect())
{
    m_background = QColor(255, 255, 255);

    m_borders = new int[4];

    m_borders[BORDER_LEFT]   = 1;
    m_borders[BORDER_RIGHT]  = 1;
    m_borders[BORDER_TOP]    = 1;
    m_borders[BORDER_BOTTOM] = 1;

    m_textOptions.setAlignment(Qt::AlignVCenter);

    m_pixelSize = 11;
}

void ReportCell::setText(QString text)
{
    if(m_text != text){
        m_text = text;

        emit textChanged(m_text);
    }
}

void ReportCell::setRect(QRect rect)
{
    m_rect = rect;

    emit rectChanged(m_rect);
}

void ReportCell::setBold(bool bold)
{
    if(m_bold != bold){
        m_bold = bold;
    }
}

void ReportCell::setBackground(QColor background)
{
    m_background = background;
}

void ReportCell::setBorder(ReportCell::BORDER border, int value)
{
    m_borders[border] = value;
}

void ReportCell::paint(QPainter &painter)
{
    painter.fillRect(m_rect, m_background);

    if(m_borders[BORDER_TOP]){
        painter.setPen(QPen(QBrush(Qt::black), m_borders[BORDER_TOP]));
        painter.drawLine(m_rect.topLeft(), m_rect.topRight());
    }

    if(m_borders[BORDER_BOTTOM]){
        painter.setPen(QPen(QBrush(Qt::black), m_borders[BORDER_BOTTOM]));
        painter.drawLine(m_rect.bottomLeft() + QPoint(0, 2), m_rect.bottomRight() + QPoint(0, 2));
    }

    if(m_borders[BORDER_LEFT]){
        painter.setPen(QPen(QBrush(Qt::black), m_borders[BORDER_LEFT]));
        painter.drawLine(m_rect.topLeft(), m_rect.bottomLeft());
    }

    if(m_borders[BORDER_RIGHT]){
        painter.setPen(QPen(QBrush(Qt::black), m_borders[BORDER_RIGHT]));
        painter.drawLine(m_rect.topRight(), m_rect.bottomRight());
    }

    painter.save();

    QFont f = painter.font();
    f.setPixelSize(m_pixelSize);

    if(m_bold)
        f.setBold(true);

    painter.setFont(f);

    painter.setPen(Qt::black);
    //Shifting text to right
    painter.drawText(QRect(QPoint(m_rect.x() + 4, m_rect.y() + 4),
                           QPoint(m_rect.right() - 4, m_rect.bottom() - 4)),
                     m_text, m_textOptions);

    painter.restore();
}

int ReportCell::height() const
{
    return m_height;
}

void ReportCell::setHeight(int height)
{
    m_height = height;
}

void ReportCell::setAlignment(Qt::Alignment alignment)
{
    m_textOptions.setAlignment(alignment);
}

int ReportCell::pixelSize() const
{
    return m_pixelSize;
}

void ReportCell::setPixelSize(int pixelSize)
{
    m_pixelSize = pixelSize;
}
