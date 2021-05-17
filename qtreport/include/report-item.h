/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   17/07/17
*/

#ifndef REPORTITEM_H
#define REPORTITEM_H

#include <QObject>
#include <QPainter>

#include "report-canvas.h"

class QTREPORT_EXPORT ReportItem : public QObject
{
    Q_OBJECT

public:
    explicit ReportItem(ReportCanvas *parent);

    virtual void paint(QPainter &painter) = 0;

    virtual int height() = 0;
    virtual int minimumHeight() {return height();}

signals:
    void newPageRequest();

protected:
    ReportCanvas *m_canvas;
};

#endif // REPORTITEM_H
