#-------------------------------------------------
#
# Project created by QtCreator 2018-10-27T18:20:13
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = auverdionControl
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

CONFIG(debug, debug|release) {
  message( "Debug" )
  DEFINES += DEBUG
} else {
  message( "Release" )
  DEFINES += RELEASE
}

macx {
include(./vektorraum/vektorraum.pri)
}

linux {
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
               src/dsp/HomeCinema71 \
               ../SIGMASTUDIO/8channels

SOURCES += \
        main.cpp \
        MainWindow.cpp \
        src/DialogReleaseNotes.cpp \
        src/QPreset.cpp \
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
        src/DialogReleaseNotes.h \
        src/QPreset.h \
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
        src/dsp/DspPlugIn.hpp \
        ../SIGMASTUDIO/8channels/8channels_IC_1.h \
        ../SIGMASTUDIO/8channels/8channels_IC_1_REG.h \
        ../SIGMASTUDIO/8channels/8channels_IC_1_PARAM.h \
        src/LogFile.h

FORMS += \
        MainWindow.ui \
        src/DialogReleaseNotes.ui \
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
        src/QPreset.ui \
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
    auverdionControl.qrc


macx {
  message( "Building for macOS" )

  QMAKE_CFLAGS += -gdwarf-2
  QMAKE_CXXFLAGS += -gdwarf-2
  QMAKE_CFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
  QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CXXFLAGS_RELEASE_WITH_DEBUGINFO
  QMAKE_OBJECTIVE_CFLAGS_RELEASE =  $$QMAKE_OBJECTIVE_CFLAGS_RELEASE_WITH_DEBUGINFO
  QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.13
  QMAKE_INFO_PLIST = $${PWD}/macos/Info.plist

  DEFINES += __MACOSX__
  DEFINES += MATLIB_USE_UINT64
  DEFINES += __NOSNDFILE__
  DEFINES += USE_APPLEVDSP
  #DEFINES += DEMO

  LIBS += -framework CoreFoundation -framework Accelerate

  ICON = $${PWD}/rc/appicon.icns

  # Name of the application signing certificate
  APPCERT = "3rd Party Mac Developer Application: Raphael Knoop"

  # Name of the installer signing certificate
  INSTALLERCERT = "3rd Party Mac Developer Installer: Raphael Knoop"

  # Bundle identifier for your application
  BUNDLEID = com.raphaelknoop.auverdioncontrol

  # Name of the entitlements file (only needed if you want to sandbox the application)
  ENTITLEMENTS = $${PWD}/macos/auverdionControl.entitlements

  OTHER_FILES += $${ENTITLEMENTS}

  APP_DSPPLUGIN_JSON.files = $${PWD}/extras/dspplugins.json
  APP_DSPPLUGIN_JSON.path = Contents/Resources
  QMAKE_BUNDLE_DATA += APP_DSPPLUGIN_JSON

  APP_DSPPLUGIN_8CHANNELS.files = /Users/rkn/Documents/freeDSP/freeDSP-aurora/SOURCES/SIGMASTUDIO/8channels/TxBuffer_IC_1.dat /Users/rkn/Documents/freeDSP/freeDSP-aurora/SOURCES/SIGMASTUDIO/8channels/NumBytes_IC_1.dat
  APP_DSPPLUGIN_8CHANNELS.path = Contents/Resources/8channels
  QMAKE_BUNDLE_DATA += APP_DSPPLUGIN_8CHANNELS

  codesign.depends  += all
  codesign.commands += $$dirname(QMAKE_QMAKE)/macdeployqt $${TARGET}.app -appstore-compliant;

  # Extract debug symbols
  codesign.commands += dsymutil $${TARGET}.app/Contents/MacOS/$${TARGET} -o $${TARGET}.app.dSYM;

  # Sign frameworks and plug-ins (uncomment and change to suit your application)
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtDBus.framework/Versions/5/QtDBus;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtSvg.framework/Versions/5/QtSvg;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets;
  #codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtSerialPort.framework/Versions/5/QtSerialPort;
  codesign.commands += codesign -f -s \"$${APPCERT}\" $${TARGET}.app/Contents/Frameworks/QtNetwork.framework/Versions/5/QtNetwork;

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
  
  #QMAKE_CFLAGS += -gdwarf-2
  #QMAKE_CXXFLAGS += -gdwarf-2

  DEFINES += __WIN__
  DEFINES += MATLIB_USE_UINT64
  DEFINES += __NOFFT__
  DEFINES += __NOSNDFILE__

  RC_ICONS = $${PWD}/rc/appicon.ico

  TARGET_DIR = $${OUT_PWD}/release/dspplugins/8channels
  TARGET_SRC_TXBUFFER = E:/Documents/freeDSP/freeDSP-aurora/SOURCES/SIGMASTUDIO/8channels/TxBuffer_IC_1.dat
  TARGET_DEST_TXBUFFER = $$TARGET_DIR/TxBuffer_IC_1.dat
  TARGET_SRC_NUMBYTES = E:/Documents/freeDSP/freeDSP-aurora/SOURCES/SIGMASTUDIO/8channels/NumBytes_IC_1.dat
  TARGET_DEST_NUMBYTES = $$TARGET_DIR/NumBytes_IC_1.dat

  TARGET_DIR ~= s,/,\\,g
  TARGET_SRC_TXBUFFER ~= s,/,\\,g
  TARGET_DEST_TXBUFFER ~= s,/,\\,g
  TARGET_SRC_NUMBYTES ~= s,/,\\,g
  TARGET_DEST_NUMBYTES ~= s,/,\\,g

  QMAKE_POST_LINK +=$$quote(cmd /c if not exist "$${TARGET_DIR}" mkdir $${TARGET_DIR} $$escape_expand(\n\t))
  QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${TARGET_SRC_TXBUFFER} $${TARGET_DEST_TXBUFFER}$$escape_expand(\n\t))
  QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${TARGET_SRC_NUMBYTES} $${TARGET_DEST_NUMBYTES}$$escape_expand(\n\t))

  product.depends += all

  # Build the product package
  DEPLOY_CMD = $$shell_quote($$shell_path($$dirname(QMAKE_QMAKE)/windeployqt.exe))
  DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/release/$${TARGET}.exe))
  product.commands += $$quote( $${DEPLOY_CMD} $${DEPLOY_TARGET} $$escape_expand(\n\t))
  product.commands += $$quote( $$shell_quote($$shell_path($$dirname(QMAKE_QMAKE)/../../../Tools/QtCreator/bin/jom.exe)) -f Makefile.Release clean $$escape_expand(\n\t))

  product.commands += $$quote(cd release $$escape_expand(\n\t))
  product.commands += $$quote( $$shell_quote($$shell_path($$dirname(QMAKE_QMAKE)/../../../Tools/QtInstallerFramework/3.1/bin/archivegen.exe)) auverdionControl.7z * $$escape_expand(\n\t))
  product.commands += $$quote(cd.. $$escape_expand(\n\t))

  product.commands += $$quote(cmd /c move /y $$shell_quote($$shell_path($${OUT_PWD}/release/auverdionControl.7z)) $$shell_quote($$shell_path($${PWD}/installer/win64/packages/com.auverdion.auverdionControl/data/auverdionControl.7z))$$escape_expand(\n\t))

  product.commands += $$quote( $$shell_quote($$shell_path($$dirname(QMAKE_QMAKE)/../../../Tools/QtInstallerFramework/3.1/bin/binarycreator.exe))  -c $$shell_quote($$shell_path($${PWD}/installer/win64/config/config.xml)) -p $$shell_quote($$shell_path($${PWD}/installer/win64/packages)) $$shell_quote($$shell_path($${PWD}/installer/win64/auverdionInstaller.exe)) $$escape_expand(\n\t))

  QMAKE_EXTRA_TARGETS += product


}

linux {
  message( "Building for Linux" )

  #QMAKE_CFLAGS += -gdwarf-2
  #QMAKE_CXXFLAGS += -gdwarf-2

  DEFINES += __LINUX__
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
