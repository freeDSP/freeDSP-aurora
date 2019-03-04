SOURCES += $$files($$PWD/*.cpp)
SOURCES += $$files($$PWD/base/*.cpp)
SOURCES += $$files($$PWD/core/*.cpp)
SOURCES += $$files($$PWD/fft/*.cpp)
SOURCES += $$files($$PWD/signal/*.cpp)
SOURCES += $$files($$PWD/statistics/*.cpp)


HEADERS += $$files($$PWD/*.h)
HEADERS += $$files($$PWD/base/*.h)
HEADERS += $$files($$PWD/core/*.h)
HEADERS += $$files($$PWD/fft/*.h)
HEADERS += $$files($$PWD/signal/*.h)
HEADERS += $$files($$PWD/statistics/*.h)

INCLUDEPATH += $$PWD\
               $$PWD/base\
               $$PWD/core\
               $$PWD/fft\
               $$PWD/signal\
               $$PWD/statistics

#macx
#{
#  DEFINES += __MACOSXTest2__
#  DEFINES += MATLIB_USE_UINT64
#}
