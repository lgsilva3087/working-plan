/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/08/17
*/

#include "../include/print-manager.h"

PrintManager *PrintManager::m_instance = nullptr;

PrintManager *PrintManager::instance()
{
    if(m_instance == nullptr){
        m_instance = new PrintManager;
    }

    return m_instance;
}

PrintManager::PrintManager(QObject *parent) : QObject(parent)
{
    setupPrinter();

    setupPrintDialog();

    setupPrintPreviewDialog();
}

void PrintManager::setupPrinter()
{
    m_printer = new QPrinter;
    m_printer->setFullPage(true);
    m_printer->setPaperSize(QPagedPaintDevice::Letter);
}

void PrintManager::setupPrintDialog()
{
    m_printDialog = new QPrintDialog;
}

void PrintManager::setupPrintPreviewDialog()
{
    m_printPreviewDialog = new QPrintPreviewDialog(m_printer);
}
