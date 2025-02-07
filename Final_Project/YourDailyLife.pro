QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    accounts.cpp \
    daysmaster.cpp \
    formdetail.cpp \
    main.cpp \
    loginfirst.cpp \
    moments.cpp \
    select.cpp \
    todolist.cpp

HEADERS += \
    accounts.h \
    daysmaster.h \
    formdetail.h \
    loginfirst.h \
    moments.h \
    select.h \
    todolist.h

FORMS += \
    accounts.ui \
    daysmaster.ui \
    formdetail.ui \
    loginfirst.ui \
    moments.ui \
    select.ui \
    todolist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = favicon.ico

RESOURCES += \
    R-C.qrc \
    background2.qrc

QT += core gui multimedia
