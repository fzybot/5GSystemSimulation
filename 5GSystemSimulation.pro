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
    mainwindow.cpp \
    src/equipment/equipment.cpp \
    src/equipment/gNodeB.cpp \
    src/equipment/user_equipment.cpp \
    src/equipment/walker.cpp \
#    src/qcustomplot/qcustomplot.cpp \
    src/phy/Channel/bandwidth.cpp \
    src/phy/Channel/radiochannel.cpp \
    src/scheduler/scheduler.cpp \
    src/simulation/simulation.cpp \
    src/visualization/heatmap.cpp

HEADERS += \
    mainwindow.h \
    src/antenna/antenna.h \
    src/equipment/gNodeB.h \
    src/phy/Channel/bandwidth.h \
    src/phy/Channel/radiochannel.h \
    src/phy/propagation_models.h \
    src/common_parameters.h \
    src/equipment/equipment.h \
    src/equipment/user_equipment.h \
    src/equipment/walker.h \
#    src/qcustomplot/qcustomplot.h \
    src/scenarios/tests.h \
    src/scheduler/scheduler.h \
    src/simulation/simulation.h \
    src/visualization/heatmap.h \
    src/visualization/mapquickwidget.h


LIBS += -llapack -lblas -larmadillo

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



