/**
  @author MSc. Luis Guillermo Silva Rojas
  @author MSc. Rubén Alcolea Núñez
  @date   15/11/17
*/

#include "utils.h"

#include <math.h>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <algorithm>

int utils::toDateStamp(QDate date)
{
    return ((date.year() * 100) + date.month()) * 100 + date.day();
}

int utils::toDateStamp(QDateTime dateTime)
{
    return toDateStamp(dateTime.date());
}

QDate utils::toDate(int dateStamp)
{
    int day = dateStamp % 100;
    dateStamp /= 100;

    int month = dateStamp % 100;
    dateStamp /= 100;

    int year = dateStamp;

    QDate date(year, month, day);
    return date;
}

QDateTime utils::toDateTime(int dateStamp)
{
    return QDateTime(toDate(dateStamp));
}

double utils::formatNumber(double number, int precision)
{
    double base = powl(10, precision);
    return floorl(number * base + 0.5) / base;
}

QString utils::formatNumberToString(double number, int precision)
{
    return QString::number(number, 'f', precision);
}

//---------------------------DATABASE-----------------------------
int utils::nextId(QString table)
{
    QSqlQuery query(QString("SELECT max(id) FROM %1").arg(table));

    return query.next() ? query.value(0).toInt() + 1 : 1;
}

bool utils::isValidId(int productId)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM product WHERE id = :id");
    query.bindValue(":id", productId);
    query.exec();

    return query.next();
}

QVariant utils::settingsValue(QString name, QVariant initialValue)
{
    QSqlQuery query;
    query.prepare("SELECT value FROM core_settings WHERE name = :name");
    query.bindValue(":name", name);
    query.exec();

    if (query.next())
        return query.value("value");

    return initialValue;
}

void utils::addSettings(QString name, QString value)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM core_settings WHERE name = :name");
    query.bindValue(":name", name);
    query.exec();

    int id = nextId("core_settings");

    if (query.next())
    {   // updating the element
        query.prepare("UPDATE core_settings SET value = :value WHERE name = :name");
        query.bindValue(":name", name);
        query.bindValue(":value", value);
        query.exec();
    }
    else
    {   // otherwise, we insert the element
        query.prepare("INSERT INTO core_settings VALUES(:id, :name, :value)");
        query.bindValue(":id", id);
        query.bindValue(":name", name);
        query.bindValue(":value", value);
        query.exec();
    }
}

