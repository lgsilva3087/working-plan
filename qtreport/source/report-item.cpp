/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   17/07/17
*/

#include "../include/report-item.h"

ReportItem::ReportItem(ReportCanvas *parent)
    : QObject(parent)
{
    m_canvas = parent;
}
