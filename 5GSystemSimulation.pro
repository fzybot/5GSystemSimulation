QT       += gui widgets qml positioning positioning-private location quickwidgets datavisualization charts

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
    src/core/NetworkManager.cpp \
    src/core/Simulator.cpp \
    src/equipment/antenna/Beam.cpp \
    src/protocols/PacketSegment.cpp \
    src/protocols/bearers/QoS/QoSProfile.cpp \
    src/equipment/mobility/ConstantPosition.cpp \
    src/protocols/Protocol.cpp \
    src/protocols/bearers/ServiceTrafficProfile.cpp \
    src/protocols/bearers/Bearer.cpp \
    src/protocols/bearers/RadioBearer.cpp \
    src/protocols/mac_layer/AMC/AMCEntity.cpp \
    src/protocols/mac_layer/CellMacEntity.cpp \
    src/protocols/mac_layer/TransportBlock.cpp \
    src/protocols/mac_layer/UeMacEntity.cpp \
    src/protocols/phy/Manipulator.cpp \
    src/protocols/phy/Symbol.cpp \
    src/visualization/ChartGroupWidget.cpp \
    src/visualization/Chartable.cpp \
    src/visualization/HeatmapModel.cpp \
    src/visualization/UEModel.cpp \
    src/visualization/data/DataSource.cpp \
    src/visualization/menu/SettingsDialog.cpp \
    src/visualization/menu/mainWindow.cpp \
    src/core/CartesianCoordinates.cpp \
    src/equipment/Cell.cpp \
    src/equipment/Equipment.cpp \
    src/equipment/UserEquipment.cpp \
    src/equipment/Walker.cpp \
    src/equipment/antenna/AntennaArray.cpp \
    src/equipment/gNodeB.cpp \
    src/equipment/mobility/Mobility.cpp \
    src/protocols/phy/Physical.cpp \
    src/protocols/phy/propagationModels.cpp \
    src/protocols/phy/Channel/Bandwidth.cpp \
    src/protocols/phy/Channel/RadioChannel.cpp \
    src/protocols/Packet.cpp \
    src/protocols/mac_layer/MacEntity.cpp \
    src/protocols/pdcp_layer/PdcpEntity.cpp \
    src/protocols/rlc_layer/RlcEntity.cpp \
    src/protocols/rrc_layer/RrcEntity.cpp \
    src/protocols/mac_layer/scheduler/Scheduler.cpp \
    src/simulation/Simulation.cpp \
    src/visualization/Custom3dSurface.cpp \
    src/visualization/Custom3dSurfaceWidget.cpp \
    src/visualization/Heatmap.cpp \
    src/visualization/Map.cpp \
    src/visualization/MapQuickWidget.cpp \
    src/visualization/menu/TabMenu.cpp \
    src/visualization/data/plotData/Novosibirsk_storeys_heights.cpp \
    src/visualization/data/plotData/nskStoreysHeights.cpp \
    src/visualization/data/plotData/scaleTest.cpp \
    src/visualization/data/plotData/interpolationNskStoreysHeights.cpp \

HEADERS += \
    src/configs/equipmentConfig.h \
    src/core/NetworkManager.h \
    src/core/Simulator.h \
    src/debug.h \
    src/equipment/antenna/Beam.h \
    src/protocols/PacketSegment.h \
    src/protocols/bearers/QoS/QoSProfile.h \
    src/equipment/mobility/ConstantPosition.h \
    src/protocols/Protocol.h \
    src/protocols/bearers/ServiceTrafficProfile.h \
    src/protocols/bearers/Bearer.h \
    src/protocols/bearers/RadioBearer.h \
    src/protocols/mac_layer/AMC/miesmEffSINR.h \
    src/protocols/mac_layer/AMC/AMCEntity.h \
    src/protocols/mac_layer/AMC/AMCParameters.h \
    src/protocols/mac_layer/AMC/miesmParameters.h \
    src/protocols/mac_layer/CellMacEntity.h \
    src/protocols/mac_layer/TransportBlock.h \
    src/protocols/mac_layer/UeMacEntity.h \
    src/protocols/phy/Manipulator.h \
    src/protocols/phy/Symbol.h \
    src/protocols/phy/modulationOrderValues.h \
    src/scenarios/modulationPerformance.h \
    src/scenarios/schedulerAnalysis.h \
    src/scenarios/simple.h \
    src/scenarios/testModel.h \
    src/visualization/ChartGroupWidget.h \
    src/visualization/Chartable.h \
    src/visualization/HeatmapModel.h \
    src/visualization/UEModel.h \
    src/visualization/data/DataSource.h \
    src/visualization/menu/SettingsDialog.h \
    src/visualization/menu/mainWindow.h \
    src/commonParameters.h \
    src/core/CartesianCoordinates.h \
    src/equipment/Cell.h \
    src/equipment/Equipment.h \
    src/equipment/UserEquipment.h \
    src/equipment/Walker.h \
    src/equipment/antenna/AntennaArray.h \
    src/equipment/gNodeB.h \
    src/equipment/mobility/Mobility.h \
    src/protocols/phy/Physical.h \
    src/protocols/phy/propagationModels.h \
    src/protocols/phy/Channel/Bandwidth.h \
    src/protocols/phy/Channel/RadioChannel.h \
    src/protocols/Packet.h \
    src/protocols/mac_layer/MacEntity.h \
    src/protocols/pdcp_layer/PdcpEntity.h \
    src/protocols/rlc_layer/RlcEntity.h \
    src/protocols/rrc_layer/RrcEntity.h \
    src/scenarios/tests.h \
    src/protocols/mac_layer/scheduler/Scheduler.h \
    src/simulation/Simulation.h \
    src/visualization/Custom3dSurface.h \
    src/visualization/Custom3dSurfaceWidget.h \
    src/visualization/Heatmap.h \
    src/visualization/Map.h \
    src/visualization/MapQuickWidget.h \
    src/visualization/menu/TabMenu.h \
    src/visualization/settingsTemplate.h


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


