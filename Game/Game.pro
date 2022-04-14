TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia multimediawidgets

CONFIG += c++14

SOURCES += \
    actor.cpp \
    actoritem.cpp \
    city.cpp \
    creategame.cpp \
    dialog.cpp \
    gameengine.cpp \
    gamer.cpp \
    gamewindow.cpp \
    main.cc \
    passenger.cpp \
    resource.cpp \
    statistics.cpp \
    stop.cpp \
    vehicle.cpp


win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib \
    $$PWD/../Game

DEPENDPATH += \
    $$PWD/../Course/CourseLib

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
    dialog.ui \
    gamewindow.ui

HEADERS += \
    actor.hh \
    actoritem.hh \
    city.h \
    dialog.h \
    gameengine.hh \
    gamer.hh \
    gamewindow.h \
    passenger.h \
    resource.hh \
    statistics.h \
    stop.h \
    vehicle.h
    CourseLib/interfaces/iactor.hh


RESOURCES += \
    8-bit.wav \
    Tampere3050.png \
    Vessapaperi.png \
    bat.png \
    kasidesi.png \
    mask.png \    
    roll.wav \
    bussi.png \
    matkustaja.png \
    pysäkki.png \
    DRONE.png \
    top_scores.txt \
    Super.wav \
    dialog_intro.txt










