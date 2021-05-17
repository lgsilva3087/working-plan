/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#include "mainwindow.h"

#include <report-image.h>
#include <report-text.h>
#include <report-table.h>

#include "database-manager.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Plan de Trabajo");
    setWindowIcon(QIcon(":/resources/icons/icon.png"));

    DatabaseManager::instance();

    Settings::instance();

    m_printManager = PrintManager::instance();

    setupUi();

    m_workingPlan = new WorkingPlan(m_reportWidget->canvas());

    connect(m_centerTasksWidget, &TasksPage::dataChanged,
            this, &MainWindow::forceUpdate);
    connect(m_personalTasksWidget, &TasksPage::dataChanged,
            this, &MainWindow::forceUpdate);
    connect(m_settingsWidget, &SettingsWidget::dateChanged,
            this, &MainWindow::onDateChanged);

    startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete m_reportWidget;
}

void MainWindow::setupUi()
{
    m_reportWidget = new ReportWidget;
    setCentralWidget(m_reportWidget);

    m_toolbar = addToolBar("Barra de herramientas");

    m_addTaskAction = new QAction("Adicionar tarea", nullptr);
    m_addTaskAction->setIcon(QIcon(":/resources/icons/add.png"));
    m_addTaskAction->setToolTip("Adicionar tarea:\n"""
                                "Adiciona una tarea a la tabla,\n"
                                "usando los valores por defecto.");
    connect(m_addTaskAction, &QAction::triggered, this, &MainWindow::addTask);
    m_toolbar->addAction(m_addTaskAction);

    m_importTasksAction = new QAction("Importar tareas", nullptr);
    m_importTasksAction->setIcon(QIcon(":/resources/icons/import.png"));
    m_importTasksAction->setToolTip("Importar tareas:\n"""
                                    "Importa tareas hacia la pestaña seleccionada\n"
                                    "desde un archivo en formato JSON.");
    connect(m_importTasksAction, &QAction::triggered, this, &MainWindow::importTasks);
    m_toolbar->addAction(m_importTasksAction);

    m_exportTasksAction = new QAction("Exportar tareas", nullptr);
    m_exportTasksAction->setIcon(QIcon(":/resources/icons/export.png"));
    m_exportTasksAction->setToolTip("Exportar tareas:\n"""
                                    "Exporta las tareas de la pestaña seleccionada\n"
                                    "hacia un archivo en formato JSON.");
    connect(m_exportTasksAction, &QAction::triggered, this, &MainWindow::exportTasks);
    m_toolbar->addAction(m_exportTasksAction);

    m_toolbar->addSeparator();

    m_printPDFAction = new QAction("Print", nullptr);
    m_printPDFAction->setIcon(QIcon(":/resources/icons/pdf.png"));
    m_printPDFAction->setToolTip("Exportar como PDF:\n"
                                 "Exporta el Plan de Trabajo del mes\n"
                                 "correspondiente a la fecha seleccionada.");
    connect(m_printPDFAction, &QAction::triggered, this, &MainWindow::printPDF);
    m_toolbar->addAction(m_printPDFAction);

    m_printDialogAction = new QAction("Print Dialog", nullptr);
    m_printDialogAction->setIcon(QIcon(":/resources/icons/print.svg"));
    m_printDialogAction->setToolTip("Diálogo de impresión:\n"
                                    "Muestra el cuadro de diálogo de impresión.");
    connect(m_printDialogAction, &QAction::triggered, this, &MainWindow::printDialog);
    m_toolbar->addAction(m_printDialogAction);

    m_printPreviewAction = new QAction("Print Preview", nullptr);
    m_printPreviewAction->setIcon(QIcon(":/resources/icons/printPreview.svg"));
    m_printPreviewAction->setToolTip("Vista previa de impresión:\n"
                                     "Muestra una vista previa de impresión,\n"
                                     "teniendo en cuenta el papel seleccionado.");
    connect(m_printPreviewAction, &QAction::triggered, this, &MainWindow::printPreview);
    m_toolbar->addAction(m_printPreviewAction);

    m_toolbar->addSeparator();

    m_letterAction = new QAction("Letter", nullptr);
    m_letterAction->setIcon(QIcon(":/resources/icons/letter.png"));
    m_letterAction->setToolTip("Tamaño Carta");
    connect(m_letterAction, &QAction::triggered, this, &MainWindow::setPaperToLetter);
    m_toolbar->addAction(m_letterAction);

    m_a4Action = new QAction("A4", nullptr);
    m_a4Action->setIcon(QIcon(":/resources/icons/a4.png"));
    m_a4Action->setToolTip("Tamaño A4");
    connect(m_a4Action, &QAction::triggered, this, &MainWindow::setPaperToA4);
    m_toolbar->addAction(m_a4Action);

    m_toolbar->addSeparator();

    m_updateAction = new QAction("Actualizar", nullptr);
    m_updateAction->setIcon(QIcon(":/resources/icons/refresh.png"));
    connect(m_updateAction, &QAction::triggered, this, &MainWindow::forceUpdate);
    m_toolbar->addAction(m_updateAction);

    m_toolbar->addSeparator();

    m_helpAction = new QAction("Acerca de...", nullptr);
    m_helpAction->setIcon(QIcon(":/resources/icons/help.png"));
    connect(m_helpAction, &QAction::triggered, this, &MainWindow::about);
    m_toolbar->addAction(m_helpAction);

    setupTasksDockWidget();
    setupSettingsDockWidget();
}

void MainWindow::setupTasksDockWidget()
{
    m_tasksDockWidget = new QDockWidget(tr("Tareas"));
    m_tasksDockWidget->setMinimumWidth(400);

    addDockWidget(Qt::TopDockWidgetArea, m_tasksDockWidget);

    m_tabWidget = new QTabWidget(this);

    m_centerTasksWidget = new TasksPage;
    m_personalTasksWidget = new TasksPage("personal");

    m_tabWidget->addTab(m_centerTasksWidget, "Centro");
    m_tabWidget->addTab(m_personalTasksWidget, "Personal");

    m_tasksDockWidget->setWidget(m_tabWidget);
}

void MainWindow::setupSettingsDockWidget()
{
    m_settingsDockWidget = new QDockWidget(tr("Configuración"));
    m_settingsDockWidget->setMinimumWidth(250);

    addDockWidget(Qt::LeftDockWidgetArea, m_settingsDockWidget);

    m_settingsWidget = new SettingsWidget;
    connect(m_settingsWidget, &SettingsWidget::dataChanged, this, &MainWindow::forceUpdate);
    m_settingsDockWidget->setWidget(m_settingsWidget);
}

void MainWindow::testReportItems()
{
    ReportCanvas *canvas = m_reportWidget->canvas();

    canvas->addReportItem(new ReportImage(canvas, ":/resources/logo.png"));

    canvas->addReportItem(new ReportText(canvas, "PRUEBA DE TEXTO DE ALINITA"));

    ReportTable *table = new ReportTable(canvas, 5, 60);

    for(int i = 0; i < 5; i++){
        table->addHeader(new ReportCell(QString("Probando %1").arg(i)));
    }

    for(int i = 5; i < 260; i++){
        table->addCell(new ReportCell(QString("Probando %1").arg(i)));
    }

    for(int i = 0; i < 5; i++){
        table->addCell(new ReportCell(QString("Probando %1").arg(i), true));
    }

    canvas->addReportItem(table);

    canvas->addReportItem(new ReportText(canvas, "FÓRMULA DE BRISILLA DE PRUEBA (ASDAS HDKJAH SDKJ)"));

    canvas->addReportItem(new ReportText(canvas, "Probando otro texto"));
}

void MainWindow::addTask()
{
    if(m_tabWidget->currentIndex() == 0)
        m_centerTasksWidget->addTask();
    else
        m_personalTasksWidget->addTask();
}

void MainWindow::importTasks()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Exportar tareas"),
                                 utils::settingsValue("jsonLocation",
                                                      QApplication::applicationDirPath()).toString(),
                                 tr("JSON file (*.json)"));

    if(fileName.isEmpty())
        return;

    QFile data(fileName);

    if (data.open(QFile::ReadOnly)) {
        QByteArray d = data.readAll();

        QJsonParseError *e = new QJsonParseError;
        QJsonDocument doc = QJsonDocument::fromJson(d, e);
        qDebug(qPrintable(e->errorString()));

        if(doc.isNull()){
            qDebug("NULL document");
        }

        QJsonArray arr = doc.array();

        for(int i = 0; i < arr.size(); i++){
            QJsonObject object = arr.at(i).toObject();

            /*query.exec("CREATE TABLE task (id int primary key, name varchar(30), startDate int, endDate int,"
                       "startTime varchar(10), endTime varchar(10), periodicity int, status int,"
                       "color varchar(10), principal boolean, remove varchar(1))");*/

            QSqlQuery query;
            query.prepare("INSERT INTO task VALUES(:id, :name, :startDate, :endDate, "
                          ":startTime, :endTime, :periodicity, :status, :color, "
                          ":principal, NULL)");
            query.bindValue(":id", utils::nextId("task"));
            query.bindValue(":name", object.value("name").toString());
            query.bindValue(":startDate", object.value("startDate").toString());
            query.bindValue(":endDate", object.value("endDate").toString());
            query.bindValue(":startTime", object.value("startTime").toString());
            query.bindValue(":endTime", object.value("endTime").toString());
            query.bindValue(":periodicity", object.value("periodicity").toString());
            query.bindValue(":status", object.value("status").toString());
            query.bindValue(":color", object.value("color").toString());
            query.bindValue(":principal", object.value("principal").toString());
            query.exec();
        }
    }

    m_centerTasksWidget->updateTasks();
    m_workingPlan->updateWorkingPlan();
}

void MainWindow::exportTasks()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exportar tareas"),
                                 utils::settingsValue("jsonLocation",
                                                      QApplication::applicationDirPath()).toString(),
                                 tr("JSON file (*.json)"));

    if(fileName.isEmpty())
        return;

    QFile data(fileName);

    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);

        QJsonDocument doc;
        QJsonArray array;

        QSqlQuery query;

        query.exec("SELECT * FROM task");

        while(query.next()){
            QJsonObject object;

            object.insert("id", query.value("id").toString());
            object.insert("name", query.value("name").toString());
            object.insert("startDate", query.value("startDate").toString());
            object.insert("endDate", query.value("endDate").toString());
            object.insert("startTime", query.value("startTime").toString());
            object.insert("endTime", query.value("endTime").toString());
            object.insert("periodicity", query.value("periodicity").toString());
            object.insert("status", query.value("status").toString());
            object.insert("color", query.value("color").toString());
            object.insert("principal", query.value("principal").toString());

            array.append(object);
        }

        doc.setArray(array);

        out << doc.toJson();

        utils::addSettings("jsonLocation", fileName);
    }
}

void MainWindow::printPDF()
{
    m_reportWidget->canvas()->printPDF();
}

void MainWindow::printDialog()
{
    m_printManager->printDialog()->exec();
}

void MainWindow::printPreview()
{
    QPrintPreviewDialog *preview = m_printManager->printerPreviewDialog();
    connect(preview, &QPrintPreviewDialog::paintRequested, m_reportWidget->canvas(),
            &ReportCanvas::print);

    preview->exec();
}

void MainWindow::addImage()
{
    ReportImage *image = new ReportImage(m_reportWidget->canvas(), ":/resources/logo.png", false);
    m_reportWidget->canvas()->addReportItem(image);
}

void MainWindow::addText()
{
    ReportText *text = new ReportText(m_reportWidget->canvas(), "PRUEBA DE TEXTO");
    m_reportWidget->canvas()->addReportItem(text);
}

void MainWindow::setPaperToLetter()
{
    PrintManager::instance()->printer()->setPaperSize(QPagedPaintDevice::Letter);
    m_reportWidget->canvas()->updateSize();

    forceUpdate();
}

void MainWindow::setPaperToA4()
{
    PrintManager::instance()->printer()->setPaperSize(QPagedPaintDevice::A4);
    m_reportWidget->canvas()->updateSize();

    forceUpdate();
}

void MainWindow::forceUpdate()
{
    QScrollArea *s = m_reportWidget->scroller();
    int value = s->verticalScrollBar()->value();

    Settings::instance()->updatehollidays();
    m_workingPlan->updateWorkingPlan();
    m_reportWidget->canvas()->updateSize();
    m_reportWidget->update();

    s->verticalScrollBar()->setValue(value);
}

void MainWindow::onDateChanged(QDate date)
{
    m_workingPlan->onDateChanged(date);
    m_centerTasksWidget->setDate(date);

    forceUpdate();
}

void MainWindow::about()
{
    QMessageBox::about(this, "Acerca de Plan de Trabajo",
                       "Basado en la Instrucción 1 del año 2009.\n\n"
                       "Creado para facilitar la elaboración del Plan de Trabajo\n"
                       "en el Centro de Entornos Interactivos 3D, Vertex.\n\n"
                       "Código fuente disponible en:\n"
                       "https://codecomunidades.prod.uci.cu/lgsilva/working-plan\n\n"
                       "Desarrollado con Qt 5.9.2.");
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());

    forceUpdate();
}
