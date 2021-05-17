#ifndef WORKINGPLANCELL_H
#define WORKINGPLANCELL_H

#include <report-cell.h>
#include <QPainter>

#include "task.h"

class WorkingPlanCell : public ReportCell
{
public:
    WorkingPlanCell(QString text, bool bold = false, QObject *parent = nullptr);

    virtual void paint(QPainter &painter);

    QList<Task *> tasks() const;
    void setTasks(const QList<Task *> &tasks);

protected:
    QList<Task *> m_tasks;
};

#endif // WORKINGPLANCELL_H
