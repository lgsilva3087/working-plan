/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#include "../include/report-canvas.h"
#include "../include/report-item.h"

#include <QSizePolicy>
#include <QDesktopServices>
#include <QApplication>

ReportCanvas::ReportCanvas(QWidget *parent)
    : QWidget(parent)
{
    QPrinter *printer = PrintManager::instance()->printer();
    m_pageWidth = printer->pageRect().width();
    m_pageHeight = printer->pageRect().height();

    m_margins = new int[4];

    m_margins[LEFT] = 40;
    m_margins[RIGHT] = 40;
    m_margins[TOP] = 40;
    m_margins[BOTTOM] = 40;

    m_currentPage = 1;
    m_numberOfPages = 1;

    m_space = 4;

    m_lastY = m_space + m_margins[TOP];
    m_pageLastY = 0;

    m_painter = new QPainter;

    setFixedSize(m_pageWidth, (m_pageHeight + m_space) * m_numberOfPages + m_space);

    connect(PrintManager::instance()->printerPreviewDialog(), &QPrintPreviewDialog::paintRequested,
            this, &ReportCanvas::print);
}

void ReportCanvas::addReportItem(ReportItem *item)
{
    m_reportItems.append(item);

    connect(item, &ReportItem::newPageRequest, this, &ReportCanvas::newPrinterPage);

    m_numberOfPages = reportItemsHeight() / printableHeight() + 1;

    setFixedSize(m_pageWidth, (m_pageHeight + m_space) * m_numberOfPages + m_space);

    update();
}

void ReportCanvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);             //QWidget's paint event

    QPainter painter;
    painter.begin(this);

    //Page frame
    for(int i = 0; i < m_numberOfPages; i++){
        QRect r(0, (i * (m_pageHeight + m_space)) + m_space, m_pageWidth, m_pageHeight);
        painter.fillRect(r, Qt::white);

        painter.setPen(Qt::lightGray);
        painter.drawRect(QRect(r.topLeft() + QPoint(m_margins[LEFT], m_margins[TOP]),
                         r.bottomRight() - QPoint(m_margins[RIGHT], m_margins[BOTTOM])));
    }

    m_lastY = m_space + m_margins[TOP];
    m_pageLastY = 0;

    for(ReportItem *item : m_reportItems){
        item->paint(painter);
    }

    painter.setPen(Qt::black);
    for(int i = 0; i < m_numberOfPages; i++)
        footer(painter, i + 1);

    painter.end();
}

QString ReportCanvas::footerText() const
{
    return m_footerText;
}

void ReportCanvas::setFooterText(const QString &footerText)
{
    m_footerText = footerText;
}

void ReportCanvas::printPDF()
{
    m_currentPage = 1;

    QPrinter *printer = PrintManager::instance()->printer();
    printer->setOutputFormat(QPrinter::PdfFormat);

    QString file = QApplication::applicationDirPath() + "/Plan_de_trabajo.pdf";

    printer->setOutputFileName(file);

    int s = m_reportItems.size();

    m_isPrinting = true;

    m_painter->begin(printer);

    //Margin's frame
    /*m_painter->drawRect(m_margins[LEFT], m_margins[TOP],
                        m_pageWidth - (m_margins[LEFT] + m_margins[RIGHT]),
                        m_pageHeight - (m_margins[TOP] + m_margins[BOTTOM]));*/

    footer(*m_painter, m_currentPage);

    m_lastY = m_space + m_margins[TOP];
    m_pageLastY = m_margins[TOP];

    for(int i = 0; i < s; i++) {
        ReportItem *item = m_reportItems.at(i);

        item->paint(*m_painter);
    }

    m_painter->end();

    m_isPrinting = false;

    QDesktopServices::openUrl(QUrl(file));
}

void ReportCanvas::print()
{
    m_currentPage = 1;

    QPrinter *printer = PrintManager::instance()->printer();

    int s = m_reportItems.size();

    m_isPrinting = true;

    m_painter->begin(printer);

    //Margin's frame
    /*m_painter->drawRect(m_margins[LEFT], m_margins[TOP],
                        m_pageWidth - (m_margins[LEFT] + m_margins[RIGHT]),
                        m_pageHeight - (m_margins[TOP] + m_margins[BOTTOM]));*/

    footer(*m_painter, m_currentPage);

    m_lastY = m_space + m_margins[TOP];
    m_pageLastY = m_margins[TOP];

    for(int i = 0; i < s; i++) {
        ReportItem *item = m_reportItems.at(i);

        item->paint(*m_painter);
    }

    m_painter->end();

    m_isPrinting = false;
}

void ReportCanvas::clear()
{
    while(!m_reportItems.empty()){
        delete m_reportItems.takeFirst();
    }

    m_numberOfPages = 1;

    setFixedSize(m_pageWidth, (m_pageHeight + m_space) * m_numberOfPages + m_space);

    update();
}

void ReportCanvas::newPrinterPage()
{
    QPrinter *printer = PrintManager::instance()->printer();
    printer->newPage();

    m_currentPage++;
    m_pageLastY = m_margins[TOP];

    if(m_isPrinting){
        /*m_painter->setPen(QPen(Qt::lightGray, 0.5));
        m_painter->drawRect(m_margins[LEFT], m_margins[TOP],
                            m_pageWidth - (m_margins[LEFT] + m_margins[RIGHT]),
                            m_pageHeight - (m_margins[TOP] + m_margins[BOTTOM]));

        m_painter->setPen(QPen(Qt::black, 1.0));*/
        footer(*m_painter, m_currentPage);
    }
}

void ReportCanvas::updateSize()
{
    QPrinter *printer = PrintManager::instance()->printer();
    m_pageWidth = printer->pageRect().width();
    m_pageHeight = printer->pageRect().height();

    m_numberOfPages = reportItemsHeight() / printableHeight() + 1;

    setFixedSize(m_pageWidth, (m_pageHeight + m_space) * m_numberOfPages + m_space);

    update();
}

void ReportCanvas::footer(QPainter &painter, int page)
{
    QFont font = painter.font();
    QFontMetrics fm(font);

    int y = 0;
    int deltha = (m_margins[BOTTOM] - fm.height()) / 2;

    if(!m_isPrinting){
        y =  page * (m_space + m_pageHeight) - (m_margins[BOTTOM]) + deltha;
    } else {
        y = (m_pageHeight - m_margins[BOTTOM]) + deltha;
    }

    QRect t = QRect(0, y, pageWidth(), fm.height());

    if(m_footerText.isEmpty()){
        m_footerText = QString("Page %1/%2 - Last Y: %3, Page Last Y: %4")
                .arg(page).arg(m_numberOfPages).arg(m_lastY).arg(m_pageLastY);
    }

    painter.drawText(t, Qt::AlignCenter, m_footerText);
}

bool ReportCanvas::isPrinting() const
{
    return m_isPrinting;
}

void ReportCanvas::setPageLastY(int pageLastY)
{
    m_pageLastY = pageLastY;
}

void ReportCanvas::increaseYs(int value)
{
    m_lastY     += value;
    m_pageLastY += value;
}

int ReportCanvas::printableHeight() const
{
    return m_pageHeight - (m_margins[TOP] + m_margins[BOTTOM]);
}

int ReportCanvas::printableWidth() const
{
    return m_pageWidth - (m_margins[LEFT] + m_margins[RIGHT]);
}

int ReportCanvas::availableSpaceOnPage() const
{
    if(!m_isPrinting)
        return printableHeight() - m_pageLastY;

    return printableHeight() - m_pageLastY + m_margins[TOP];
}

int ReportCanvas::reportItemsHeight() const
{
    int total = 0;

    for(ReportItem *item : m_reportItems){
        total += item->height();
    }

    return total;
}

int ReportCanvas::lastY() const
{
    return m_lastY;
}

void ReportCanvas::setLastY(int lastY)
{
    m_lastY = lastY;
}

int ReportCanvas::pageLastY() const
{
    return m_pageLastY;
}

int ReportCanvas::space() const
{
    return m_space;
}

int ReportCanvas::numberOfPages() const
{
    return m_numberOfPages;
}

int ReportCanvas::pageWidth() const
{
    return m_pageWidth;
}

void ReportCanvas::setPageWidth(int pageWidth)
{
    m_pageWidth = pageWidth;
}

ReportCanvas::~ReportCanvas()
{
    clear();
}
