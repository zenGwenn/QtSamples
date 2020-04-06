# QT -= gui
QT       += core gui

TARGET = aftonWindow

CONFIG += c++11 console
CONFIG -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "../libraries/glm-master/glm"

SOURCES += \
        main.cpp \
        # sphere.cpp \
        transform3d.cpp \
        # vec3.cpp \
        window.cpp

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target

HEADERS += \
    transform3d.h \
    # vec3.h \
    vertex.h \
    window.h

RESOURCES += \
    resources.qrc

# DISTFILES += \
#    shaders/simple.frag \
#    shaders/simple.vert

DISTFILES += \
    sph.fsh \
    sph.vsh
