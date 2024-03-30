QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ./controller/Calculator_controller.cc \
    ./model/Calculator_model.cc \
    ./view/dialogX.cc \
    main.cpp \
    ./view/calculatorview.cc \
    ./QCustomLib/qcustomplot.cpp

HEADERS += \
    ../controller/Calculator_controller.h \
    ../model/Calculator_model.h \
    ./view/calculatorview.h \
    ./view/dialogX.h \
    ./QCustomLib/qcustomplot.h

FORMS += \
    ./view/calculatorview.ui \
    ./view/dialogX.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
