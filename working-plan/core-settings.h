#ifndef CORESETTINGS_H
#define CORESETTINGS_H

#include <QObject>
#include <QColor>
#include <QMap>

class CoreSettings : public QObject
{
    Q_OBJECT

public:
    static CoreSettings* instance();

    QColor colorFromString(QString c);

protected:
    explicit CoreSettings(QObject *parent = nullptr);

    void fillColors();

protected:
    static CoreSettings* m_instance;

protected:
    QMap<QString, QColor> m_colors;
};

#endif // CORESETTINGS_H
