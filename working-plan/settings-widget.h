/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>

#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <QSpinBox>

class SettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = nullptr);

    void setupUi();

public slots:
    void writeSettings();

signals:
    void dataChanged();
    void dateChanged(QDate date);

protected:
    QVBoxLayout *m_layout;

    QFormLayout *m_formLayout;

    QDateEdit *m_dateEdit;
    QComboBox *m_typeComboBox;
    QLineEdit *m_centerLineEdit;
    QLineEdit *m_bossPositionLineEdit;
    QLineEdit *m_bossLineEdit;
    QLineEdit *m_myPositionLineEdit;
    QLineEdit *m_meLineEdit;
    QSpinBox *m_fontSize;

    QPushButton *m_updatePushButton;
};

#endif // SETTINGSWIDGET_H
