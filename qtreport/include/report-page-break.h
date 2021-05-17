/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   11/11/17
*/

#ifndef REPORT_PAGE_BREAK_H
#define REPORT_PAGE_BREAK_H

#include "report-item.h"
#include "report-canvas.h"

class QTREPORT_EXPORT ReportPageBreak : public ReportItem
{
    Q_OBJECT

public:
    explicit ReportPageBreak(ReportCanvas *parent);

    //! Reimplemented from ReportItem
    virtual void paint(QPainter &painter);

    //! Reimplemented from ReportItem
    virtual int height();
};

#endif // REPORT_PAGE_BREAK_H
