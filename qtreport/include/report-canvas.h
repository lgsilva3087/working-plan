/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintEvent>

#include "print-manager.h"

class ReportItem;

class QTREPORT_EXPORT ReportCanvas : public QWidget
{
    Q_OBJECT

public:
    enum MARGINS {LEFT = 0, RIGHT, TOP, BOTTOM};

    explicit ReportCanvas(QWidget *parent = nullptr);

    ~ReportCanvas();

    void addReportItem(ReportItem *item);

    int pageWidth() const;
    void setPageWidth(int pageWidth);
    int numberOfPages() const;
    int space() const;
    inline int margin(MARGINS margin) const {return m_margins[margin];}

    int lastY() const;
    void setLastY(int lastY);

    int pageLastY() const;
    void setPageLastY(int pageLastY);

    void increaseYs(int value);

    int printableHeight() const;
    int printableWidth() const;
    int availableSpaceOnPage() const;

    int reportItemsHeight() const;

    virtual void footer(QPainter &painter, int page);

    bool isPrinting() const;

    QString footerText() const;
    void setFooterText(const QString &footerText);

public slots:
    void print();
    void printPDF();

    void clear();

    void newPrinterPage();

    void updateSize();

protected:
    void paintEvent(QPaintEvent *event);

private:
    int m_pageWidth;
    int m_pageHeight;

    int* m_margins;

    int m_currentPage;
    int m_numberOfPages;

    int m_space;

    int m_lastY;
    int m_pageLastY;

    QString m_footerText;

    QPainter *m_painter;

    QList<ReportItem*> m_reportItems;

    bool m_isPrinting = false;
};

#endif // CANVAS_H
