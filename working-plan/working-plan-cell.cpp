#include "working-plan-cell.h"

WorkingPlanCell::WorkingPlanCell(QString text, bool bold, QObject *parent)
    : ReportCell (text, bold, parent)
{

}

void WorkingPlanCell::paint(QPainter &painter)
{
    painter.fillRect(m_rect, m_background);

    if(m_borders[BORDER_TOP]){
        painter.setPen(QPen(QBrush(Qt::black), m_borders[BORDER_TOP]));
        painter.drawLine(m_rect.topLeft(), m_rect.topRight());
    }

    if(m_borders[BORDER_BOTTOM]){
        painter.setPen(QPen(QBrush(Qt::black), m_borders[BORDER_BOTTOM]));
        painter.drawLine(m_rect.bottomLeft() + QPoint(0, 2), m_rect.bottomRight() + QPoint(0, 2));
    }

    if(m_borders[BORDER_LEFT]){
        painter.setPen(QPen(QBrush(Qt::black), m_borders[BORDER_LEFT]));
        painter.drawLine(m_rect.topLeft(), m_rect.bottomLeft());
    }

    if(m_borders[BORDER_RIGHT]){
        painter.setPen(QPen(QBrush(Qt::black), m_borders[BORDER_RIGHT]));
        painter.drawLine(m_rect.topRight(), m_rect.bottomRight());
    }

    painter.save();

    QFont f = painter.font();
    f.setPixelSize(m_pixelSize);

    if(m_bold)
        f.setBold(true);

    painter.setFont(f);

    if(m_tasks.isEmpty()){
        painter.restore();
        return;
    }

    QRect adjustedRect = QRect(QPoint(m_rect.x() + 2, m_rect.y() + 2),
                               QPoint(m_rect.right() - 2, m_rect.bottom() - 2));

    QFontMetrics metrics = painter.fontMetrics();

    for(Task *t : m_tasks){
        QRect r = metrics.boundingRect(adjustedRect, Qt::AlignLeft | Qt::TextWordWrap,
                                       t->text());

        //painter.drawRect(r);

        painter.setPen(QPen(t->color()));

        painter.drawText(r, t->text(), m_textOptions);

        adjustedRect.setY(adjustedRect.y() + r.height() + 2);
    }

    painter.restore();
}

QList<Task *> WorkingPlanCell::tasks() const
{
    return m_tasks;
}

void WorkingPlanCell::setTasks(const QList<Task *> &tasks)
{
    m_tasks = tasks;
}
