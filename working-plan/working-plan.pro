QT += core gui widgets printsupport sql

CONFIG += c++11

TEMPLATE = app
DESTDIR = $$OUT_PWD/../bin
TARGET = vertex-working-plan

RC_ICONS = $${PWD}/resources/icons/icon.ico

LIBS += -L$$OUT_PWD/../lib

LIBS += -lqtreport

INCLUDEPATH += $$PWD/../qtreport/include

SOURCES += main.cpp\
        mainwindow.cpp \
    database-manager.cpp \
    utils.cpp \
    delegates/icon-delegate.cpp \
    delegates/date-delegate.cpp \
    working-plan.cpp \
    settings-widget.cpp \
    hollidays-widget.cpp \
    settings.cpp \
    delegates/time-delegate.cpp \
    delegates/spinbox-delegate.cpp \
    delegates/combobox-delegate.cpp \
    tasks-page.cpp \
    working-plan-cell.cpp \
    task.cpp \
    core-settings.cpp

HEADERS  += mainwindow.h \
    database-manager.h \
    utils.h \
    delegates/icon-delegate.h \
    delegates/date-delegate.h \
    working-plan.h \
    settings-widget.h \
    hollidays-widget.h \
    settings.h \
    delegates/time-delegate.h \
    delegates/spinbox-delegate.h \
    delegates/combobox-delegate.h \
    tasks-page.h \
    working-plan-cell.h \
    task.h \
    core-settings.h

RESOURCES += \
    resources.qrc
