TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS += \
    qtreport \
    working-plan

working-plan.depends += qtreport

