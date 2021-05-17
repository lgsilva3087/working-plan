/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   11/11/17
*/

#include "../include/report-page-break.h"

ReportPageBreak::ReportPageBreak(ReportCanvas *parent) :
    ReportItem(parent)
{

}

void ReportPageBreak::paint(QPainter &painter)
{
    Q_UNUSED(painter);

    m_canvas->increaseYs(height());
}

int ReportPageBreak::height()
{
    return m_canvas->availableSpaceOnPage() + 5;
}
