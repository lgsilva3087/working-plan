#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSet>
#include <QSqlQuery>
#include <QVariant>

class Settings : public QObject
{
    Q_OBJECT

public:
    static Settings* instance();

    QSet<int> hollidays() const;
    void sethollidays(const QSet<int> &hollidays);

    bool isholliday(int date);

public slots:
    void updatehollidays();

protected:
    explicit Settings(QObject *parent = nullptr);

protected:
    static Settings* m_instance;

    QSet<int> m_hollidays;
};

#endif // SETTINGS_H
