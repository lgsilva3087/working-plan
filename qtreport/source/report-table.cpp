/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#include "../include/report-table.h"

ReportTable::ReportTable(ReportCanvas *parent, int columns, int percent)
    : ReportItem(parent)
{
    m_columns = columns;
    m_percent = percent;
}

void ReportTable::addCell(ReportCell *cell)
{
    m_cells.append(cell);

    int s = m_cells.size();

    m_rows = s / m_columns;
}

void ReportTable::addHeader(ReportCell *header)
{
    m_headers.append(header);
}

void ReportTable::paint(QPainter &painter)
{
    m_tableWidth = m_canvas->printableWidth() * (float(m_percent)/100.0);
    m_margin = (m_canvas->pageWidth() - m_tableWidth) / 2;

    m_cellsWidth = m_tableWidth / m_columns;

    paintHeader(painter);

    int size = m_cells.size();

    //qDebug("Size: %d", size);

    painter.save();

    for(int i = 0; i < size; i++)
    {
        ReportCell *cell = m_cells.at(i);

        if(m_canvas->availableSpaceOnPage() < cell->height()){
            int skip = m_canvas->margin(ReportCanvas::BOTTOM) + m_canvas->space()
                         + m_canvas->margin(ReportCanvas::TOP);
            skip += m_canvas->printableHeight() - m_canvas->pageLastY();

            m_canvas->setLastY(m_canvas->lastY() + skip);
            m_canvas->setPageLastY(0);

            if(m_canvas->isPrinting())
                emit newPageRequest();

            paintHeader(painter);
        }

        m_currentRow = i / m_columns;
        m_currentColumn = i % m_columns;

        painter.setPen(Qt::blue);

        int y = m_canvas->isPrinting() ? m_canvas->pageLastY() : m_canvas->lastY();

        QRect r(m_margin + (m_currentColumn * m_cellsWidth), y, m_cellsWidth, cell->height());

        cell->setRect(r);
        cell->paint(painter);

        if(i % m_columns == m_columns - 1 || i >= size - 1){
            m_canvas->increaseYs(cell->height());
        }

        //if(i >= size - 1)
        //    m_canvas->increaseYs(cell->height());
    }

    painter.restore();
}

void ReportTable::paintHeader(QPainter &painter)
{
    Q_UNUSED(painter);

    /*painter.save();

    painter.setPen(Qt::black);

    if(m_canvas->availableSpaceOnPage() < 20){
        int skip = m_canvas->margin(ReportCanvas::BOTTOM) + m_canvas->space()
                     + m_canvas->margin(ReportCanvas::TOP);
        skip += m_canvas->printableHeight() - m_canvas->pageLastY();

        m_canvas->setLastY(m_canvas->lastY() + skip);
        m_canvas->setPageLastY(0);

        if(m_canvas->isPrinting())
            emit newPageRequest();

        for(int i = 0; i < m_headers.size(); i++){
            ReportCell *cell = m_headers.at(i);
            cell->setBold(true);
            cell->setBackground(QColor(128, 200, 128));

            int y = m_canvas->isPrinting() ? m_canvas->pageLastY() : m_canvas->lastY();

            QRect r(m_margin + (i * m_cellsWidth), y, m_cellsWidth, 20);

            cell->setRect(r);
            cell->paint(painter);
        }
    }

    painter.restore();

    m_canvas->increaseYs(20);*/
}

int ReportTable::height()
{
    if(m_cells.isEmpty())
        return 0;

    int h = 0;

    for(int i = 0; i < m_cells.size() - 1; i += m_columns)
    {
        h += m_cells.at(i)->height();
    }

    return h;
}

void ReportTable::clear()
{
    m_headers.clear();
    m_cells.clear();
}
