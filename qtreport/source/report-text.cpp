/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   19/07/17
*/

#include "../include/report-text.h"

ReportText::ReportText(ReportCanvas *parent, QString text, QColor color, Qt::Alignment align) :
    ReportItem(parent), m_text(text), m_color(color), m_alignment(align), m_font(QFont())
{

}

void ReportText::paint(QPainter &painter)
{
    if(m_canvas->availableSpaceOnPage() < minimumHeight()){
        int skip = m_canvas->margin(ReportCanvas::BOTTOM) + m_canvas->space()
                   + m_canvas->margin(ReportCanvas::TOP);
        skip += m_canvas->printableHeight() - m_canvas->pageLastY();

        m_canvas->setLastY(m_canvas->lastY() + skip);
        m_canvas->setPageLastY(0);

        if(m_canvas->isPrinting())
            emit newPageRequest();
    }

    m_font = painter.font();
    QFontMetrics fm(m_font);

    int y = m_canvas->isPrinting() ? m_canvas->pageLastY() : m_canvas->lastY();

    QRect t = QRect(m_canvas->margin(ReportCanvas::LEFT), y,
                    m_canvas->printableWidth() , fm.height());

    painter.setPen(m_color);
    painter.drawText(t, m_alignment, m_text);

    m_canvas->increaseYs(height());
}

int ReportText::height()
{
    QFontMetrics f(m_font);

    return f.height() + 20;
}
