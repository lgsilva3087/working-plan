/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   16/08/17
*/

#ifndef REPORT_H
#define REPORT_H

#include <QtCore/qglobal.h>

#if defined(QTREPORT_LIBRARY)
#  define QTREPORT_EXPORT Q_DECL_EXPORT
#else
#  define QTREPORT_EXPORT Q_DECL_IMPORT
#endif

#endif // REPORT_H
