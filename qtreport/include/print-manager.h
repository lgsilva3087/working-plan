/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QObject>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

#include "report.h"

class QTREPORT_EXPORT PrintManager : public QObject
{
    Q_OBJECT

public:
    static PrintManager *instance();

    inline QPrinter* printer() {return m_printer;}
    inline QPrintDialog* printDialog() {return m_printDialog;}
    inline QPrintPreviewDialog* printerPreviewDialog() {return m_printPreviewDialog;}

protected:
    static PrintManager *m_instance;
    explicit PrintManager(QObject *parent = nullptr);

    void setupPrinter();
    void setupPrintDialog();
    void setupPrintPreviewDialog();


protected:
    QPrinter *m_printer;

    QPrintDialog *m_printDialog;
    QPrintPreviewDialog *m_printPreviewDialog;
};

#endif // PRINTMANAGER_H
