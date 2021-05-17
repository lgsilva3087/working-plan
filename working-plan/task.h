#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QColor>


class Task
{
public:
    Task(QString text, QColor color = Qt::black, QColor background = Qt::transparent);

    QString text() const;
    void setText(const QString &text);

    QColor color() const;
    void setColor(const QColor &color);

    QColor background() const;
    void setBackground(const QColor &background);

protected:
    QString m_text;
    QColor m_color;
    QColor m_background;
};

#endif // TASK_H
