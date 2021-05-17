/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   16/08/17
*/

#include "../include/report-widget.h"

ReportWidget::ReportWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void ReportWidget::setupUi()
{
    m_layout = new QVBoxLayout;
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    setLayout(m_layout);

    m_scroller = new QScrollArea;
    m_scroller->setAlignment(Qt::AlignCenter);
    m_scroller->setBackgroundRole(QPalette::Dark);

    m_canvas = new ReportCanvas;
    m_scroller->setWidget(m_canvas);

    m_layout->addWidget(m_scroller);
}

QScrollArea *ReportWidget::scroller() const
{
    return m_scroller;
}

void ReportWidget::setScroller(QScrollArea *scroller)
{
    m_scroller = scroller;
}

ReportCanvas *ReportWidget::canvas() const
{
    return m_canvas;
}
