/**
  @author MSc. Luis Guillermo Silva Rojas
  @author MSc. Rubén Alcolea Núñez
  @date   15/11/17
*/

#ifndef UTILS_H
#define UTILS_H

#include <QDateTime>
#include <QVariant>
#include <QMap>
#include <QColor>
#include <QString>

class utils
{
public:
    static int toDateStamp(QDate date);
    static int toDateStamp(QDateTime dateTime);
    static QDate toDate(int dateStamp);
    static QDateTime toDateTime(int dateStamp);

    static double formatNumber(double number, int precision = 4);
    static QString formatNumberToString(double number, int precision = 2);

//Database related
public:
    static int nextId(QString table);
    static bool isValidId(int productId);

    static QVariant settingsValue(QString name, QVariant initialValue = QVariant(0));
    static void addSettings(QString name, QString value);
};

#endif // UTILS_H
