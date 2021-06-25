QT       += gui widgets qml positioning positioning-private location quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = qmlwidget
#TEMPLATE = app
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainWindow.cpp \
    src/core/CartesianCoordinates.cpp \
    src/equipment/Cell.cpp \
    src/equipment/Equipment.cpp \
    src/equipment/UserEquipment.cpp \
    src/equipment/Walker.cpp \
    src/equipment/antenna/Antenna.cpp \
    src/equipment/antenna/AntennaArray.cpp \
    src/equipment/gNodeB.cpp \
#    src/qcustomplot/qcustomplot.cpp \
    src/mobility/Mobility.cpp \
    src/phy/Physical.cpp \
    src/phy/propagationModels.cpp \
    src/phy/Channel/Bandwidth.cpp \
    src/phy/Channel/RadioChannel.cpp \
    src/phy/Signal.cpp \
    src/protocols/Packet.cpp \
    src/protocols/mac_layer/MacEntity.cpp \
    src/protocols/pdcp_layer/PdcpEntity.cpp \
    src/protocols/rlc_layer/RlcEntity.cpp \
    src/protocols/rrc_layer/RrcEntity.cpp \
    src/scheduler/Scheduler.cpp \
    src/simulation/Simulation.cpp \
    src/visualization/Heatmap.cpp \
    src/visualization/MapQuickWidget.cpp

HEADERS += \
    mainWindow.h \
    src/commonParameters.h \
    src/core/CartesianCoordinates.h \
    src/equipment/Cell.h \
    src/equipment/Equipment.h \
    src/equipment/UserEquipment.h \
    src/equipment/Walker.h \
    src/equipment/antenna/Antenna.h \
    src/equipment/antenna/AntennaArray.h \
    src/equipment/gNodeB.h \
    src/mobility/Mobility.h \
    src/phy/Physical.h \
    src/phy/propagationModels.h \
    src/phy/Channel/Bandwidth.h \
    src/phy/Channel/RadioChannel.h \
    src/phy/Signal.h \
#    src/qcustomplot/qcustomplot.h \
    src/protocols/Packet.h \
    src/protocols/mac_layer/MacEntity.h \
    src/protocols/pdcp_layer/PdcpEntity.h \
    src/protocols/rlc_layer/RlcEntity.h \
    src/protocols/rrc_layer/RrcEntity.h \
    src/scenarios/tests.h \
    src/scheduler/Scheduler.h \
    src/simulation/Simulation.h \
    src/visualization/Heatmap.h \
    src/visualization/MapQuickWidget.h


unix: LIBS += -llapack -lblas -larmadillo
win32: INCLUDEPATH += $$PWD/libs

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore
    src/qml/map.qml

RESOURCES += \
    src/application.qrc \
    src/qml.qrc


