/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>
#include <QAction>
#include <QDockWidget>
#include <QMessageBox>
#include <QScrollBar>

#include <report-widget.h>
#include <print-manager.h>

#include "tasks-page.h"
#include "settings-widget.h"
#include "working-plan.h"

#include <QTableWidget>
#include <QFileDialog>
#include <QApplication>
#include <QTextStream>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupUi();
    void setupTasksDockWidget();
    void setupSettingsDockWidget();

    void testReportItems();

public slots:
    void addTask();
    void importTasks();
    void exportTasks();

    void printPDF();
    void printDialog();
    void printPreview();

    void addImage();
    void addText();

    void setPaperToLetter();
    void setPaperToA4();

    void forceUpdate();
    void onDateChanged(QDate date);

    void about();

protected:
    void timerEvent(QTimerEvent *event);

private:
    QToolBar *m_toolbar;

        QAction *m_addTaskAction;
        QAction *m_importTasksAction;
        QAction *m_exportTasksAction;

        QAction *m_printPDFAction;
        QAction *m_printDialogAction;
        QAction *m_printPreviewAction;
        QAction *m_clearPagesAction;
        QAction *m_addImageAction;
        QAction *m_addTextAction;

        QAction *m_letterAction;
        QAction *m_a4Action;

        QAction *m_updateAction;

        QAction *m_helpAction;

    ReportWidget *m_reportWidget;
    PrintManager *m_printManager;

    QDockWidget *m_tasksDockWidget;
    QTabWidget *m_tabWidget;
    TasksPage *m_centerTasksWidget;
    TasksPage *m_personalTasksWidget;

    QDockWidget *m_settingsDockWidget;
    SettingsWidget *m_settingsWidget;

    WorkingPlan *m_workingPlan;
};

#endif // MAINWINDOW_H
