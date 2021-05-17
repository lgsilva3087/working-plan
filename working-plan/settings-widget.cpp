/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#include "settings-widget.h"

#include "utils.h"

#include "hollidays-widget.h"

SettingsWidget::SettingsWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void SettingsWidget::setupUi()
{
    m_layout = new QVBoxLayout;
    m_layout->setMargin(3);
    m_layout->setSpacing(3);

    setLayout(m_layout);

    m_formLayout = new QFormLayout;
    m_formLayout->setMargin(0);
    m_formLayout->setSpacing(3);
    m_layout->addLayout(m_formLayout);

    m_dateEdit = new QDateEdit(QDate::currentDate());
    m_dateEdit->setCalendarPopup(true);
    m_dateEdit->setDisplayFormat("dd/MM/yyyy");
    connect(m_dateEdit, &QDateEdit::dateChanged, this, &SettingsWidget::dateChanged);
    m_formLayout->addRow(tr("Fecha:"), m_dateEdit);

    m_typeComboBox = new QComboBox;
    m_typeComboBox->addItem("Personal");
    m_typeComboBox->addItem("Institucional");
    m_typeComboBox->setCurrentIndex(utils::settingsValue("type", 0).toInt());
    m_formLayout->addRow(tr("Tipo"), m_typeComboBox);
    connect(m_typeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(writeSettings()));

    m_centerLineEdit = new QLineEdit;
    m_centerLineEdit->setText(utils::settingsValue("center", "").toString());
    m_formLayout->addRow(tr("Centro:"), m_centerLineEdit);

    m_bossPositionLineEdit = new QLineEdit;
    m_bossPositionLineEdit->setText(utils::settingsValue("bossPosition", "").toString());
    m_formLayout->addRow(tr("Aprobado:"), m_bossPositionLineEdit);

    m_bossLineEdit = new QLineEdit;
    m_bossLineEdit->setText(utils::settingsValue("bossName", "").toString());
    m_formLayout->addRow(tr("Nombre:"), m_bossLineEdit);

    m_myPositionLineEdit = new QLineEdit;
    m_myPositionLineEdit->setText(utils::settingsValue("myPosition", "").toString());
    m_formLayout->addRow(tr("Mi cargo:"), m_myPositionLineEdit);

    m_meLineEdit = new QLineEdit;
    m_meLineEdit->setText(utils::settingsValue("myName", "").toString());
    m_formLayout->addRow(tr("Mi nombre:"), m_meLineEdit);

    m_fontSize = new QSpinBox;
    m_fontSize->setRange(6, 14);
    m_fontSize->setValue(utils::settingsValue("tasksFontSize", 10).toInt());
    m_formLayout->addRow(tr("Fuente:"), m_fontSize);

    QHBoxLayout *hb = new QHBoxLayout;
    m_layout->addLayout(hb);
    m_updatePushButton = new QPushButton(tr("Actualizar"));
    connect(m_updatePushButton, &QPushButton::clicked, this, &SettingsWidget::writeSettings);
    hb->addStretch();
    hb->addWidget(m_updatePushButton);

    HollidaysWidget *m_hollidays = new HollidaysWidget;
    connect(m_hollidays, &HollidaysWidget::dataChanged, this, &SettingsWidget::dataChanged);
    m_layout->addWidget(m_hollidays);
}

void SettingsWidget::writeSettings()
{
    utils::addSettings("type", QString::number(m_typeComboBox->currentIndex()));
    utils::addSettings("center", m_centerLineEdit->text());
    utils::addSettings("bossPosition", m_bossPositionLineEdit->text());
    utils::addSettings("bossName", m_bossLineEdit->text());
    utils::addSettings("myPosition", m_myPositionLineEdit->text());
    utils::addSettings("myName", m_meLineEdit->text());
    utils::addSettings("tasksFontSize", QString::number(m_fontSize->value()));

    emit dataChanged();
}
