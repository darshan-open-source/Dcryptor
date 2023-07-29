QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    filewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    textwidget.cpp

HEADERS += \
    base64.h \
    common.h \
    common2.h \
    filedep.h \
    filewidget.h \
    mainwindow.h \
    textdep.h \
    textwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



RESOURCES += \
    resources.qrc



FORMS +=

win32: LIBS += -L'C:/Program Files/OpenSSL/lib/' -llibcrypto

INCLUDEPATH += 'C:/Program Files/OpenSSL/include'
DEPENDPATH += 'C:/Program Files/OpenSSL/include'
