#include "core-settings.h"

CoreSettings* CoreSettings::m_instance = nullptr;

CoreSettings* CoreSettings::instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new CoreSettings;
    }

    return m_instance;
}

QColor CoreSettings::colorFromString(QString c)
{
    if(m_colors.contains(c))
        return m_colors.value(c);

    return Qt::black;
}

CoreSettings::CoreSettings(QObject *parent) : QObject(parent)
{
    fillColors();
}

void CoreSettings::fillColors()
{
    m_colors.insert("black", Qt::black);
    m_colors.insert("red",   Qt::red);
    m_colors.insert("darkRed", QColor(177, 43, 26));
    m_colors.insert("blue",  Qt::blue);
    m_colors.insert("darkBlue",  Qt::darkBlue);
    m_colors.insert("green", Qt::green);
    m_colors.insert("darkGreen", Qt::darkGreen);
    m_colors.insert("magenta", Qt::magenta);
    m_colors.insert("darkMagenta", Qt::darkMagenta);
    m_colors.insert("cyan", Qt::cyan);
    m_colors.insert("darkCyan", Qt::darkCyan);
    m_colors.insert("yellow", Qt::yellow);
    m_colors.insert("darkYellow", Qt::darkYellow);
    m_colors.insert("gray", Qt::gray);
    m_colors.insert("darkGray", Qt::darkGray);
    m_colors.insert("orange", QColor(232, 105, 45));
    m_colors.insert("icpc", QColor(37, 133, 253));
}
