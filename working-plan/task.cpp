#include "task.h"

Task::Task(QString text, QColor color, QColor background)
{
    m_text = text;
    m_color = color;
    m_background = background;
}

QString Task::text() const
{
    return m_text;
}

void Task::setText(const QString &text)
{
    m_text = text;
}

QColor Task::color() const
{
    return m_color;
}

void Task::setColor(const QColor &color)
{
    m_color = color;
}

QColor Task::background() const
{
    return m_background;
}

void Task::setBackground(const QColor &background)
{
    m_background = background;
}
