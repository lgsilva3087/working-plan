/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#ifndef WORKINGPLAN_H
#define WORKINGPLAN_H

#include <QObject>
#include <QDate>

#include <report-canvas.h>
#include <report-text.h>
#include <report-table.h>
#include <report-image.h>
#include <report-page-break.h>

#include "utils.h"
#include "database-manager.h"
#include "settings.h"
#include "task.h"

class WorkingPlan : public QObject
{
    Q_OBJECT
public:
    explicit WorkingPlan(ReportCanvas *canvas, QObject *parent = nullptr);

public slots:
    void updateWorkingPlan();

    void onDateChanged(QDate date);

protected:
    void clean();

    void addBoss();

    void addLogo();

    void addTitle();

    void addMainTasks();

    void addMe();

    void addWorkingPlan();

    void addDays(ReportTable *table, QDate currentDate);

    QList<Task *> findTasks(QDate date);

    void fillMonths();
    QString spanishMonth(int monthNumber);

    void fillDays();
    QString spanishDay(int dayNumber);

private:
    ReportCanvas *m_canvas;

    QDate m_date;
    QDate m_currentDate;

    QMap<int, QString> m_months;
    QMap<int, QString> m_days;

    Settings *m_settings;
};

#endif // WORKINGPLAN_H
