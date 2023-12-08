QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../ws/TrafficLightsDemo_target/QtUi.cpp \
    ../ws/TrafficLightsDemo_target/PushButton.cpp \
    ../ws/TrafficLightsDemo_target/TLSystem.cpp \
    ../ws/TrafficLightsDemo_target/TrafficLight.cpp \
    ../ws/TrafficLightsDemo_target/TrafficLightControl.cpp \
    ../ws/TrafficLightsDemo_target/TrafficLightSignals.cpp \
    ../ws/TrafficLightsDemo_target/UnitName.cpp \
    ../ws/TrafficLightsDemo_target/Utils.cpp \
    main.cpp \
    mainwindow.cpp \
    mythread.cpp \
    trafficLightLayout.cpp

HEADERS += \
    ../ws/TrafficLightsDemo_target/QtUi.h \
    ../ws/TrafficLightsDemo_target/PushButton.h \
    ../ws/TrafficLightsDemo_target/TLSystem.h \
    ../ws/TrafficLightsDemo_target/TrafficLight.h \
    ../ws/TrafficLightsDemo_target/TrafficLightControl.h \
    ../ws/TrafficLightsDemo_target/TrafficLightSignals.h \
    ../ws/TrafficLightsDemo_target/UnitName.h \
    ../ws/TrafficLightsDemo_target/Utils.h \
    mainwindow.h \
    mythread.h \
    trafficLightLayout.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx|win32: LIBS += -L$$PWD/../eclipse/rsa_rt/C++/TargetRTS/lib/WinT.x64-MinGw-12.2.0/ -lObjecTime

INCLUDEPATH += $$PWD/../ws/TrafficLightsDemo_target

INCLUDEPATH += $$PWD/../eclipse/rsa_rt/C++/TargetRTS/include
DEPENDPATH += $$PWD/../eclipse/rsa_rt/C++/TargetRTS/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../eclipse/rsa_rt/C++/TargetRTS/lib/WinT.x64-MinGw-12.2.0/ObjecTime.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../eclipse/rsa_rt/C++/TargetRTS/lib/WinT.x64-MinGw-12.2.0/libObjecTime.a

unix:!macx|win32: LIBS += -L$$PWD/../eclipse/rsa_rt/C++/TargetRTS/lib/WinT.x64-MinGw-12.2.0/ -lObjecTimeTypes

INCLUDEPATH += $$PWD/../eclipse/rsa_rt/C++/TargetRTS/target/WinT
DEPENDPATH += $$PWD/../eclipse/rsa_rt/C++/TargetRTS/target/WinT

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../eclipse/rsa_rt/C++/TargetRTS/lib/WinT.x64-MinGw-12.2.0/ObjecTimeTypes.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../eclipse/rsa_rt/C++/TargetRTS/lib/WinT.x64-MinGw-12.2.0/libObjecTimeTypes.a

win32 {
    LIBS += -lwsock32
}

RESOURCES +=
