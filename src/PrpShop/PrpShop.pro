# General Configuration
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += release
DESTDIR = ../../bin
RC_FILE = res/PrpShop.rc

# Use libPlasma
INCLUDEPATH += ../../../Plasma/core
LIBS += -L../../../Plasma/bin -lPlasma

# Make VS shut up a bit
win32:QMAKE_CXXFLAGS += /wd4244 /wd4251 /wd4267 /wd4996

# PrpShop Sources
HEADERS += Main.h \
           ../QPlasma.h \
           ../QColorEdit.h \
           ../QLinkLabel.h \
           QKeyDialog.h \
           QPlasmaUtils.h \
           QPlasmaTreeItem.h \
           PRP/QCreatable.h \
           PRP/QKeyList.h \
           PRP/QMatrix44.h \
           PRP/QObjLink.h \
           PRP/QSceneNode.h \
           PRP/Audio/QSoundBuffer.h \
           PRP/Message/QMsgForwarder.h \
           PRP/Modifier/QPythonFileMod.h \
           PRP/Object/QAudioInterface.h \
           PRP/Object/QCoordinateInterface.h \
           PRP/Object/QDrawInterface.h \
           PRP/Object/QSceneObject.h \
           PRP/Object/QSimulationInterface.h \
           PRP/Object/QSynchedObject.h \
           PRP/Surface/QLayer.h \
           PRP/Surface/QLayerAnimation.h \
           PRP/Surface/QLayerSDLAnimation.h \
           PRP/Surface/QMaterial.h \
           PRP/Surface/QMipmap.h
SOURCES += Main.cpp \
           ../QColorEdit.cpp \
           ../QLinkLabel.cpp \
           QKeyDialog.cpp \
           QPlasmaUtils.cpp \
           QPlasmaTreeItem.cpp \
           PRP/QCreatable.cpp \
           PRP/QKeyList.cpp \
           PRP/QMatrix44.cpp \
           PRP/QObjLink.cpp \
           PRP/QSceneNode.cpp \
           PRP/Audio/QSoundBuffer.cpp \
           PRP/Message/QMsgForwarder.cpp \
           PRP/Modifier/QPythonFileMod.cpp \
           PRP/Object/QAudioInterface.cpp \
           PRP/Object/QCoordinateInterface.cpp \
           PRP/Object/QDrawInterface.cpp \
           PRP/Object/QSceneObject.cpp \
           PRP/Object/QSimulationInterface.cpp \
           PRP/Object/QSynchedObject.cpp \
           PRP/Surface/QLayer.cpp \
           PRP/Surface/QLayerAnimation.cpp \
           PRP/Surface/QLayerSDLAnimation.cpp \
           PRP/Surface/QMaterial.cpp \
           PRP/Surface/QMipmap.cpp
RESOURCES += images.qrc
