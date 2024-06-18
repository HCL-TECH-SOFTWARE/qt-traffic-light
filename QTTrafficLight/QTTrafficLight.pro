# Set the location of the TargetRTS
# Examples are given for the Model RealTime and Code RealTime products respectively

TARGET_RTS_LOCATION = C:\rtist-installations\mrt-12-0-2-hcl\eclipse-cpp-2023-06-R-win32-x86_64\eclipse/rsa_rt/C++/TargetRTS
# TARGET_RTS_LOCATION = C:\Users\MATTIAS.MOHLIN\testarea\install\VSCode\data\extensions\secure-dev-ops.code-realtime-ce-1.0.4\TargetRTS

# Set the location of the target folder (where generated code is placed)

TARGET_FOLDER = C:/github/qt-traffic-light/ws/TrafficLightsDemo_target
# TARGET_FOLDER = C:/git/rtistic-pub-doc/art-samples/QtTrafficLight_target

# Set the location of the source folder (important for Code RealTime, since it uses a handwritten header file IPushButton.h)

# SOURCE_FOLDER = C:\git\rtistic-pub-doc\art-samples\QtTrafficLight\include
SOURCE_FOLDER = $${TARGET_FOLDER}

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $${TARGET_FOLDER}/QtUi.cpp \
    $${TARGET_FOLDER}/PushButton.cpp \
    $${TARGET_FOLDER}/TLSystem.cpp \
    $${TARGET_FOLDER}/TrafficLight.cpp \
    $${TARGET_FOLDER}/TrafficLightControl.cpp \
    $${TARGET_FOLDER}/TrafficLightSignals.cpp \
	$${TARGET_FOLDER}/PedLight.cpp \
	$${TARGET_FOLDER}/PedLightControl.cpp \
    $${TARGET_FOLDER}/UnitName.cpp \
    main.cpp \
    mainwindow.cpp \
    mythread.cpp \
    trafficLightLayout.cpp

HEADERS += \
    $${TARGET_FOLDER}/QtUi.h \
	$${SOURCE_FOLDER}/IPushButton.h \
    $${TARGET_FOLDER}/PushButton.h \
    $${TARGET_FOLDER}/TLSystem.h \
    $${TARGET_FOLDER}/TrafficLight.h \
    $${TARGET_FOLDER}/TrafficLightControl.h \
    $${TARGET_FOLDER}/TrafficLightSignals.h \
	$${TARGET_FOLDER}/PedLight.h \
	$${TARGET_FOLDER}/PedLightControl.h \
    $${TARGET_FOLDER}/UnitName.h \
    mainwindow.h \
    mythread.h \
    trafficLightLayout.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx|win32: LIBS += -L$${TARGET_RTS_LOCATION}/lib/WinT.x64-MinGw-12.2.0 -lObjecTime

INCLUDEPATH += $${TARGET_FOLDER}
INCLUDEPATH += $${SOURCE_FOLDER}

INCLUDEPATH += $${TARGET_RTS_LOCATION}/include
DEPENDPATH += $${TARGET_RTS_LOCATION}/include

win32:!win32-g++: PRE_TARGETDEPS += $${TARGET_RTS_LOCATION}/lib/WinT.x64-MinGw-12.2.0/ObjecTime.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $${TARGET_RTS_LOCATION}/lib/WinT.x64-MinGw-12.2.0/libObjecTime.a

unix:!macx|win32: LIBS += -L$${TARGET_RTS_LOCATION}/lib/WinT.x64-MinGw-12.2.0/ -lObjecTimeTypes

INCLUDEPATH += $${TARGET_RTS_LOCATION}/target/WinT
DEPENDPATH += $${TARGET_RTS_LOCATION}/target/WinT

win32:!win32-g++: PRE_TARGETDEPS += $${TARGET_RTS_LOCATION}/lib/WinT.x64-MinGw-12.2.0/ObjecTimeTypes.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $${TARGET_RTS_LOCATION}/lib/WinT.x64-MinGw-12.2.0/libObjecTimeTypes.a

win32 {
    LIBS += -lwsock32
}

RESOURCES +=

