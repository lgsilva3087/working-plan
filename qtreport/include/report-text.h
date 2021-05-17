/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   19/07/17
*/

#ifndef REPORTTEXT_H
#define REPORTTEXT_H

#include "report-item.h"
#include "report-canvas.h"

class QTREPORT_EXPORT ReportText : public ReportItem
{
    Q_OBJECT

public:
    explicit ReportText(ReportCanvas *parent, QString text, QColor color = Qt::black,
                        Qt::Alignment align = Qt::AlignCenter);

    //! Reimplemented from ReportItem
    virtual void paint(QPainter &painter);

    //! Reimplemented from ReportItem
    virtual int height();

    inline QString text() const {return m_text;}

protected:
    QString m_text;

    QColor m_color;

    Qt::Alignment m_alignment;
    QFont m_font;
};

#endif // REPORTTEXT_H
