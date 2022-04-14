QT += testlib
QT += widgets
QT += gui

CONFIG += qt warn_on depend_includepath testcase console
QT += multimedia


CONFIG += sdk_no_version_check

TARGET = tst_unittest

DEFINES += SRCDIR=\\\"$$PWD/\\\"

TEMPLATE = app

INCLUDEPATH += \
    $$PWD/../Course/CourseLib \
    $$PWD/../Game

DEPENDPATH += \
    $$PWD/../Course/CourseLib
    $$PWD/../Game

HEADERS += ../Game/statistics.h \
    ../Game/actor.hh \
    ../Game/actoritem.hh \
    ../Game/city.h \
    ../Game/dialog.h \
    ../Game/gameengine.hh \
    ../Game/gamer.hh \
    ../Game/gamewindow.h \
    ../Game/passenger.h \
    ../Game/resource.hh \
    ../Game/stop.h \
    ../Game/vehicle.h


SOURCES +=  tst_unittest.cpp \
    ../Game/statistics.cpp \
    ../Game/actor.cpp \
    ../Game/actoritem.cpp \
    ../Game/city.cpp \
    ../Game/dialog.cpp \
    ../Game/gameengine.cpp \
    ../Game/gamer.cpp \
    ../Game/gamewindow.cpp \
    ../Game/passenger.cpp \
    ../Game/resource.cpp \
    ../Game/stop.cpp \
    ../Game/vehicle.cpp

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    ../Game/dialog.ui \
    ../Game/gamewindow.ui

RESOURCES += test_score.txt
