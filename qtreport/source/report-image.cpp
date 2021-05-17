/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#include "../include/report-image.h"

ReportImage::ReportImage(ReportCanvas *parent, QString path, bool floating)
    : ReportItem(parent), m_path(path), m_floating(floating)
{
    m_image = new QImage(m_path);
}

void ReportImage::paint(QPainter &painter)
{
    painter.save();

    //painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    if(m_canvas->availableSpaceOnPage() < minimumHeight()){
        int skip = m_canvas->margin(ReportCanvas::BOTTOM) + m_canvas->space()
                   + m_canvas->margin(ReportCanvas::TOP);
        skip += m_canvas->printableHeight() - m_canvas->pageLastY();

        m_canvas->setLastY(m_canvas->lastY() + skip);
        m_canvas->setPageLastY(0);

        if(m_canvas->isPrinting())
            emit newPageRequest();
    }

    int deltha = m_image->width() / 2;

    if(!m_canvas->isPrinting())
        painter.drawImage(m_canvas->pageWidth() / 2 - deltha, m_canvas->lastY(), *m_image);
    else
        painter.drawImage(m_canvas->pageWidth() / 2 - deltha, m_canvas->pageLastY(), *m_image);

    painter.restore();

    m_canvas->increaseYs(height());
}

int ReportImage::height()
{
    return m_image->height() + 20;
}
