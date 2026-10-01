QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addname.cpp \
    assignjob.cpp \
    dialog.cpp \
    dialog2.cpp \
    jobadd.cpp \
    jobremove.cpp \
    jobsview.cpp \
    main.cpp \
    loginwindow.cpp \
    payview.cpp \
    removename.cpp \
    schdule.cpp \
    viewpaystub.cpp \
    viewwindow.cpp

HEADERS += \
    addname.h \
    assignjob.h \
    dialog.h \
    dialog2.h \
    jobadd.h \
    jobremove.h \
    jobsview.h \
    loginwindow.h \
    payview.h \
    removename.h \
    schdule.h \
    viewpaystub.h \
    viewwindow.h

FORMS += \
    addname.ui \
    assignjob.ui \
    dialog.ui \
    dialog2.ui \
    jobadd.ui \
    jobremove.ui \
    jobsview.ui \
    loginwindow.ui \
    payview.ui \
    removename.ui \
    schdule.ui \
    viewpaystub.ui \
    viewwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    IDs
