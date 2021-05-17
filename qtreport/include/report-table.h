/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#ifndef TABLE_H
#define TABLE_H

#include "report-cell.h"
#include "report-item.h"

class QTREPORT_EXPORT ReportTable : public ReportItem
{
    Q_OBJECT
public:
    explicit ReportTable(ReportCanvas *parent, int columns, int percent = 100);

    void addCell(ReportCell *cell);
    void addHeader(ReportCell *header);

    void clear();

    void paint(QPainter &painter);
    void paintHeader(QPainter &painter);

    virtual int height();
    virtual int minimumHeight() {return 0;}

protected:
    int m_columns;
    int m_percent;

    int m_rows;

    int m_currentColumn = 0;
    int m_currentRow = 0;

    int m_tableWidth;
    int m_margin;
    int m_cellsWidth;

    QList<ReportCell*> m_headers;
    QList<ReportCell*> m_cells;
};

#endif // TABLE_H
