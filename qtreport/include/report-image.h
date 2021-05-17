/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#ifndef REPORTIMAGE_H
#define REPORTIMAGE_H

#include <QObject>
#include <QImage>

#include "report-item.h"

class QTREPORT_EXPORT ReportImage : public ReportItem
{
    Q_OBJECT

public:
    explicit ReportImage(ReportCanvas *parent, QString path, bool floating = false);

    void paint(QPainter &painter);

    virtual int height();

protected:
    QString m_path;
    QImage *m_image;

    bool m_floating;
};

#endif // REPORTIMAGE_H
