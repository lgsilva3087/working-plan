#include "settings.h"

Settings* Settings::m_instance = nullptr;

Settings::Settings(QObject *parent) : QObject(parent)
{
    updatehollidays();
}

QSet<int> Settings::hollidays() const
{
    return m_hollidays;
}

void Settings::sethollidays(const QSet<int> &hollidays)
{
    m_hollidays = hollidays;
}

bool Settings::isholliday(int date)
{
    if(m_hollidays.contains(date))
        return true;

    return false;
}

void Settings::updatehollidays()
{
    m_hollidays.clear();

    QSqlQuery query("SELECT * FROM holliday");

    while(query.next()){
        m_hollidays.insert(query.value("dateStamp").toInt());
    }
}

Settings* Settings::instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new Settings;
    }

    return m_instance;
}
