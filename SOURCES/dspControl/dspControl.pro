#-------------------------------------------------
#
# Project created by QtCreator 2018-10-27T18:20:13
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = dspControl
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

macx {
include(./vektorraum/vektorraum.pri)
}

win32 {
include(vektorraum\vektorraum.pri)
}

INCLUDEPATH += src \
               src/figure \
               src/dsp \
               src/dsp/8channels \
               src/dsp/4FIRs \
               src/dsp/HomeCinema71

SOURCES += \
        main.cpp \
        MainWindow.cpp \
        src/figure/ccolormap.cpp \
        src/figure/QFigure.cpp \
        src/QDspBlock.cpp \
        src/QPeq.cpp \
        src/QHighPass.cpp \
        src/QLowPass.cpp \
        src/QChannel.cpp \
        src/QGain.cpp \
        src/QPhase.cpp \
        src/QDelay.cpp \
        src/QHighShelv.cpp \
        src/QLowShelv.cpp \
        src/dsp/freeDSP-Aurora.cpp \
        src/dialoglicense.cpp \
        src/QInputSelect.cpp \
        src/QOutputSelect.cpp \
        src/QCrossover.cpp \
        src/DialogSettings.cpp \
        src/QVolumeSlider.cpp \
        src/QFir.cpp \
        src/dsp/8channels/PlugIn8Channels.cpp \
        src/dsp/4FIRs/PlugIn4FIRs.cpp \
        src/dsp/HomeCinema71/PlugInHomeCinema71.cpp

HEADERS += \
        MainWindow.hpp \
        src/figure/ccolormap.h \
        src/figure/QDialogAxisProperties.h \
        src/figure/QFigure.h \
        src/QDspBlock.hpp \
        src/QPeq.hpp \
        src/QHighPass.hpp \
        src/QLowPass.hpp \
        src/QChannel.hpp \
        src/QGain.hpp \
        src/QPhase.hpp \
        src/QDelay.hpp \
        src/QHighShelv.hpp \
        src/QLowShelv.hpp \
        src/QCrossover.hpp \
        src/dsp/freeDSP-Aurora.hpp \
        src/dialoglicense.hpp \
        src/QInputSelect.hpp \
        src/QOutputSelect.hpp \
        src/DialogSettings.hpp \
        src/QVolumeSlider.hpp \
        src/QFir.hpp \
        src/dsp/8channels/PlugIn8Channels.hpp \
        src/dsp/HomeCinema71/PlugInHomeCinema71.hpp \
        src/dsp/4FIRs/PlugIn4FIRs.hpp \
        src/QDialogDemoSelector.hpp \
        src/dsp/DspPlugIn.hpp

FORMS += \
        MainWindow.ui \
        src/QDspBlock.ui \
        src/QPeq.ui \
        src/QHighPass.ui \
        src/QLowPass.ui \
        src/QChannel.ui \
        src/QGain.ui \
        src/QPhase.ui \
        src/QDelay.ui \
        src/QHighShelv.ui \
        src/QLowShelv.ui  \
        src/QCrossover.ui \
        src/dialoglicense.ui \
        src/QInputSelect.ui \
        src/QOutputSelect.ui \
        src/QFir.ui \
        src/DialogSettings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    dspcontrol.qrc


macx {
  QT += serialport

  QMAKE_CFLAGS += -gdwarf-2
  QMAKE_CXXFLAGS += -gdwarf-2
  QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
  QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
  QMAKE_OBJECTIVE_CFLAGS_RELEASE =  $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
  QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
  QMAKE_INFO_PLIST = $${PWD}/macos/Info.plist

  DEFINES += __MACOSX__
  DEFINES += MATLIB_USE_UINT64
  DEFINES += __NOSNDFILE__
  DEFINES += USE_APPLEVDSP
  DEFINES += DEMO

  LIBS += -framework CoreFoundation -framework Accelerate

  ICON = $${PWD}/rc/appicon.icns

  # Name of the application signing certificate
  APPCERT = "3rd Party Mac Developer Application: Raphael Knoop"

  # Name of the installer signing certificate
  INSTALLERCERT = "3rd Party Mac Developer Installer: Raphael Knoop"

  # Bundle identifier for your application
  BUNDLEID = com.raphaelknoop.dspcontrol

  # Name of the entitlements file (only needed if you want to sandbox the application)
  ENTITLEMENTS = $${PWD}/macos/dspControl.entitlements

  OTHER_FILES += $${ENTITLEMENTS}

  codesign.depends  += all
  codesign.commands += /Users/rkn/Qt5.12.0/5.12.0/clang_64/bin/macdeployqt $${TARGET}.app -appstore-compliant;


  # Extract debug symbols
  codesign.commands += dsymutil $${TARGET}.app/Contents/MacOS/$${TARGET} -o $${TARGET}.app.dSYM;

  # Sign frameworks and plug-ins (uncomment and change to suit your application)
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtDBus.framework/Versions/5/QtDBus;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtSvg.framework/Versions/5/QtSvg;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtSerialPort.framework/Versions/5/QtSerialPort;

  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/bearer/libqgenericbearer.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/iconengines/libqsvgicon.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqgif.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqicns.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqico.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqjpeg.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqmacheif.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqmacjp2.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqsvg.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqtga.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqtiff.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqwbmp.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/imageformats/libqwebp.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/platforms/libqcocoa.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/printsupport/libcocoaprintersupport.dylib;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/PlugIns/styles/libqmacstyle.dylib;

  # Sign the application bundle, using the provided entitlements
  codesign.commands += codesign -f -s \"$${APPCERT}\" -i $${BUNDLEID} -v --entitlements \"$${ENTITLEMENTS}\" $${TARGET}.app;

  product.depends += all

  # Build the product package
  product.commands += productbuild --component $${TARGET}.app /Applications --sign \"$${INSTALLERCERT}\" $${TARGET}.pkg

  QMAKE_EXTRA_TARGETS += codesign product copyfiles

}

win32 {
  message( "Building for Windows" )
  QT += serialport

  #QMAKE_CFLAGS += -gdwarf-2
  #QMAKE_CXXFLAGS += -gdwarf-2

  DEFINES += __WIN__
  DEFINES += MATLIB_USE_UINT64
  DEFINES += __NOFFT__
  DEFINES += __NOSNDFILE__
  DEFINES += DEMO

  RC_ICONS = $${PWD}/rc/appicon.ico
 # ICON = $${PWD}/rc/appicon.icns

}

ios {

  HEADERS += src/myviewcontroller.h

  OBJECTIVE_SOURCES += src/myviewcontroller.mm

  QMAKE_CFLAGS += -gdwarf-2
  QMAKE_CXXFLAGS += -gdwarf-2
  QMAKE_INFO_PLIST = ios/Info.plist

  DEFINES += __IOS__
  DEFINES += MATLIB_USE_UINT64
  DEFINES += __NOFFT__
  DEFINES += __NOSNDFILE__
  DEFINES += DEMO

  appicon.files = $$files($$PWD/rc/ios/*.png)
  QMAKE_BUNDLE_DATA += appicon
}
