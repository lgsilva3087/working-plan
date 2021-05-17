TEMPLATE = lib

QT       += core gui widgets printsupport

CONFIG += c++11

TARGET = qtreport

DEFINES += QTREPORT_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x059000

MOC_DIR += $$OUT_PWD/../shit
RCC_DIR += $$OUT_PWD/../shit
OBJECTS_DIR += $$OUT_PWD/../shit

DESTDIR += $$OUT_PWD/../lib
DLLDESTDIR = $$OUT_PWD/../bin

SOURCES += \
        source/report-item.cpp \
        source/print-manager.cpp \
        source/report-canvas.cpp \
        source/report-image.cpp \
        source/report-table.cpp \
        source/report-text.cpp \
        source/report-cell.cpp \
        source/report-widget.cpp \
    source/report-page-break.cpp

HEADERS += \
        include/report.h \
        include/report-item.h \
        include/print-manager.h \
        include/report-canvas.h \
        include/report-image.h \
        include/report-table.h \
        include/report-text.h \
        include/report-cell.h \
        include/report-widget.h \
    include/report-page-break.h

RESOURCES += \
    resources.qrc

DISTFILES += \
    todo.txt
