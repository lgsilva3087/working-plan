/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   16/08/17
*/

#ifndef REPORT_WIDGET_H
#define REPORT_WIDGET_H

#include "report-canvas.h"

#include <QWidget>
#include <QScrollArea>

class QTREPORT_EXPORT ReportWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReportWidget(QWidget *parent = nullptr);

    ReportCanvas *canvas() const;

    QScrollArea *scroller() const;
    void setScroller(QScrollArea *scroller);

protected:
    void setupUi();

protected:
    QVBoxLayout *m_layout;
    QScrollArea *m_scroller;

    ReportCanvas *m_canvas;
};

#endif // REPORT_WIDGET_H
