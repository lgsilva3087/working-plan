/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#include "working-plan.h"

#include "working-plan-cell.h"
#include "core-settings.h"

WorkingPlan::WorkingPlan(ReportCanvas *canvas, QObject *parent)
    : QObject(parent), m_canvas(canvas)
{
    m_date = QDate::currentDate();

    m_settings = Settings::instance();

    fillMonths();
    fillDays();

    m_canvas->setFooterText("Software libre: https://codecomunidades.prod.uci.cu/lgsilva/working-plan");

    updateWorkingPlan();
}

void WorkingPlan::updateWorkingPlan()
{
    clean();

    addBoss();

    addLogo();

    addTitle();

    addMainTasks();

    addMe();

    addWorkingPlan();
}

void WorkingPlan::onDateChanged(QDate date)
{
    m_date = date;
}

void WorkingPlan::clean()
{
    m_canvas->clear();
}

void WorkingPlan::addBoss()
{
    m_canvas->addReportItem(new ReportText(m_canvas, "", Qt::black,
                                           Qt::AlignLeft));

    QString bossPosition = tr("APROBADO: ");
    bossPosition.append(utils::settingsValue("bossPosition").toString());
    m_canvas->addReportItem(new ReportText(m_canvas, bossPosition, Qt::black,
                            Qt::AlignLeft));

    QString bossName = tr("                      ");
    bossName.append(utils::settingsValue("bossName").toString());
    m_canvas->addReportItem(new ReportText(m_canvas, bossName, Qt::black,
                            Qt::AlignLeft));
}

void WorkingPlan::addLogo()
{
    m_canvas->addReportItem(new ReportImage(m_canvas, ":/resources/icons/uci.png"));

}

void WorkingPlan::addTitle()
{
    QString title = tr("PLAN DE TRABAJO INDIVIDUAL");

    int type = utils::settingsValue("type", 0).toInt();

    if(type > 0)
        title = "PLAN DE TRABAJO " + utils::settingsValue("center", "").toString();

    m_canvas->addReportItem(new ReportText(m_canvas, title, Qt::black));

    title = tr("MES: %1 %2").arg(spanishMonth(m_date.month()))
            .arg(m_date.year());

    m_canvas->addReportItem(new ReportText(m_canvas, title, Qt::black));
}

void WorkingPlan::addMainTasks()
{
    ReportTable *table = new ReportTable(m_canvas, 1);

    ReportCell *c = new ReportCell("ACTIVIDADES PRINCIPALES");
    c->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    table->addCell(c);

    c = new ReportCell(" ");
    c->setHeight(15);
    c->setBorder(ReportCell::BORDER_BOTTOM, 0);
    table->addCell(c);

    m_canvas->addReportItem(table);

    table = new ReportTable(m_canvas, 2);

    //Starting and ending dates of current month
    QDate start = m_date;
    start.setDate(start.year(), start.month(), 1);

    QDate end = start;
    end.setDate(start.year(), start.month(), start.daysInMonth());

    auto startStamp = utils::toDateStamp(start);
    auto endStamp   = utils::toDateStamp(end);

    QSqlQuery query;
    query.prepare("SELECT name, startDate FROM task WHERE (principal = 'TRUE' "
                  "AND startDate BETWEEN :startStamp AND :endStamp) OR (principal = 'TRUE' "
                  "AND periodicity > 0) "
                  "UNION "
                  "SELECT name, startDate FROM personal WHERE (principal = 'TRUE' "
                  "AND startDate BETWEEN :startStamp AND :endStamp) OR (principal = 'TRUE' "
                  "AND periodicity > 0) ORDER BY startDate");
    query.bindValue(":startStamp", startStamp);
    query.bindValue(":endStamp", endStamp);
    query.exec();

    int counter = query.size();

    int cellSize = 30;

    counter = 0;

    while(query.next()){
        counter++;

        ReportCell *cell = new ReportCell(QString::number(counter)
                                          .append("- ") + (query.value("name").toString()));

        cell->setBorder(ReportCell::BORDER_BOTTOM, 0);
        cell->setBorder(ReportCell::BORDER_TOP, 0);

        if(counter % 2 == 0)
            cell->setBorder(ReportCell::BORDER_LEFT, 0);
        else
            cell->setBorder(ReportCell::BORDER_RIGHT, 0);

        cell->setHeight(cellSize);
        table->addCell(cell);
    }

    if(counter % 2 != 0){
        ReportCell *cell = new ReportCell("");
        cell->setBorder(ReportCell::BORDER_LEFT, 0);
        cell->setBorder(ReportCell::BORDER_TOP, 0);
        cell->setHeight(cellSize);
        table->addCell(cell);
    }

    m_canvas->addReportItem(table);

    table = new ReportTable(m_canvas, 1);

    c = new ReportCell(" ");
    c->setBorder(ReportCell::BORDER_TOP, 0);
    c->setHeight(15);
    table->addCell(c);
    m_canvas->addReportItem(table);
}

void WorkingPlan::addMe()
{
    m_canvas->addReportItem(new ReportText(m_canvas, "", Qt::black,
                                           Qt::AlignLeft));

    QString myCharge = utils::settingsValue("myPosition").toString();
    m_canvas->addReportItem(new ReportText(m_canvas, myCharge, Qt::black,
                            Qt::AlignRight));

    QString me = utils::settingsValue("myName").toString();
    m_canvas->addReportItem(new ReportText(m_canvas, me, Qt::black,
                            Qt::AlignRight));

    m_canvas->addReportItem(new ReportPageBreak(m_canvas));
}

void WorkingPlan::addWorkingPlan()
{
    ReportTable *table = new ReportTable(m_canvas, 1, 100);
    ReportCell *ce = new ReportCell(QString("%1 %2").arg(spanishMonth(m_date.month()))
                                    .arg(m_date.year()), true);
    ce->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    table->addCell(ce);
    m_canvas->addReportItem(table);

    table = new ReportTable(m_canvas, 7, 100);

    QDate first = QDate(m_date.year(), m_date.month(), 1);
    QDate last = QDate(m_date.year(), m_date.month(), m_date.daysInMonth());
    auto firstDay = first.dayOfWeek();

    m_currentDate = first.addDays(-firstDay + 1);

    int total = int(m_currentDate.daysTo(last));
    int pixelSize = utils::settingsValue("tasksFontSize", 10).toInt();

    int weeks = total / 7;
    if(total % 7 > 0)
        weeks++;

    int cellHeight = ((m_canvas->printableHeight() - (weeks * 20)) / weeks) - weeks;

    addDays(table, m_currentDate);

    for(int i = 1; i <= total + 1; i++){

        QList<Task *> tasks;

        if(m_currentDate >= first && m_currentDate <= last)
            tasks = findTasks(m_currentDate);

        WorkingPlanCell *cell = new WorkingPlanCell("");
        cell->setTasks(tasks);
        cell->setBorder(ReportCell::BORDER_LEFT, 1);
        cell->setBorder(ReportCell::BORDER_RIGHT, 1);
        cell->setHeight(cellHeight);
        cell->setPixelSize(pixelSize);
        cell->setAlignment(Qt::AlignLeft);
        table->addCell(cell);

        m_currentDate = m_currentDate.addDays(1);

        if(i % 7 == 0)
            addDays(table, m_currentDate);
    }

    m_canvas->addReportItem(table);
}

void WorkingPlan::addDays(ReportTable *table, QDate currentDate)
{
    for (int i = 1; i <= 7; ++i) {
        ReportCell *cell = new ReportCell(QString("%1 %2")
                                          .arg(spanishDay(i))
                                          .arg(currentDate.day()), true);
        cell->setBorder(ReportCell::BORDER_LEFT, 1);
        cell->setBorder(ReportCell::BORDER_RIGHT, 1);
        cell->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        table->addCell(cell);
        currentDate = currentDate.addDays(1);
    }
}

QList<Task *> WorkingPlan::findTasks(QDate date)
{
    if(m_settings->isholliday(utils::toDateStamp(date)))
        return QList<Task *>();

    QSqlQuery query;
    query.exec("SELECT * FROM task UNION "
               "SELECT * FROM personal ORDER BY startTime,endTime");

    QList<Task *> tasks;

    while(query.next()){
        QDate startDate = utils::toDate(query.value("startDate").toInt());
        QDate endDate = utils::toDate(query.value("endDate").toInt());

        int periodicity = query.value("periodicity").toInt();

        QString text = "";

        if((date >= startDate && date <= endDate) || periodicity > 0){
            if(periodicity > 0)
            {
                QDate d = utils::toDate(query.value("startDate").toInt());

                int diff = int(std::abs(d.daysTo(date)));

                if(diff % query.value("periodicity").toInt() == 0){
                    text.append(query.value("startTime").toString()).append("-");
                    text.append(query.value("endTime").toString()).append(" ");
                    text.append(query.value("name").toString());

                    QColor c = CoreSettings::instance()->colorFromString(
                                query.value("color").toString());

                    tasks.append(new Task(text, c));
                }
            }
            else
            {
                text.append(query.value("startTime").toString()).append("-");
                text.append(query.value("endTime").toString()).append(" ");
                text.append(query.value("name").toString());

                QColor c = CoreSettings::instance()->colorFromString(
                            query.value("color").toString());

                tasks.append(new Task(text, c));
            }
        }
    }

    return tasks;
}

void WorkingPlan::fillMonths()
{
    m_months.insert(1, "Enero");
    m_months.insert(2, "Febrero");
    m_months.insert(3, "Marzo");
    m_months.insert(4, "Abril");
    m_months.insert(5, "Mayo");
    m_months.insert(6, "Junio");
    m_months.insert(7, "Julio");
    m_months.insert(8, "Agosto");
    m_months.insert(9, "Septiembre");
    m_months.insert(10, "Octubre");
    m_months.insert(11, "Noviembre");
    m_months.insert(12, "Diciembre");
}

QString WorkingPlan::spanishMonth(int monthNumber)
{
    return m_months.value(monthNumber);
}

void WorkingPlan::fillDays()
{
    m_days.insert(1, "Lunes");
    m_days.insert(2, "Martes");
    m_days.insert(3, "Miércoles");
    m_days.insert(4, "Jueves");
    m_days.insert(5, "Viernes");
    m_days.insert(6, "Sábado");
    m_days.insert(7, "Domingo");
}

QString WorkingPlan::spanishDay(int dayNumber)
{
    return m_days.value(dayNumber);
}
