/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#ifndef REPORT_CELL_H
#define REPORT_CELL_H

#include <QObject>
#include <QPainter>

#include "report.h"

class QTREPORT_EXPORT ReportCell : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText MEMBER m_text NOTIFY textChanged)
    Q_PROPERTY(QRect rect READ rect WRITE setRect MEMBER m_rect NOTIFY rectChanged)
    Q_PROPERTY(bool bold READ isBold WRITE setBold MEMBER m_bold)
    Q_PROPERTY(QColor background READ background WRITE setBackground MEMBER m_background)

public:
    explicit ReportCell(QString text, bool bold = false, QObject *parent = nullptr);

    enum BORDER{BORDER_LEFT = 0, BORDER_RIGHT, BORDER_TOP, BORDER_BOTTOM};

    inline QString text() const {return m_text;}
    void setText(QString text);

    inline QRect rect() const {return m_rect;}
    void setRect(QRect rect);

    inline bool isBold() const {return m_bold;}
    void setBold(bool bold);

    inline QColor background() const {return m_background;}
    void setBackground(QColor background);

    inline void setBold();

    void setBorder(BORDER border, int value);

    virtual void paint(QPainter &painter);

    int height() const;
    void setHeight(int height);

    void setAlignment(Qt::Alignment alignment);

    int pixelSize() const;
    void setPixelSize(int pixelSize);

signals:
    void textChanged(QString text);
    void rectChanged(QRect rect);

protected:
    QString m_text;
    bool m_bold;
    int m_pixelSize;
    int m_height;
    QRect m_rect;
    QColor m_background;

    int *m_borders;

    QTextOption m_textOptions;
};

#endif // REPORT_CELL_H
