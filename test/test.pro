TEMPLATE = app
DESTDIR = ../bin

INCLUDEPATH += ../

DEFINES += QT_COMPILATION

win32 {
    CONFIG += qt console
    INCLUDEPATH += "../depends/sc-memory-win32/include"
    LIBS += $$quote(-L"../depends/sc-memory-win32/") -lsc_memoryd
    LIBS += $$quote(-L$$DESTDIR) -lsc-graphd
}

SOURCES += \
    main.cpp \
    utils.cpp \
    tests/test_graph_gen.cpp \
    tests/test_graph_modify.cpp

HEADERS += \
    utils.h \
    prerequest.h \
    test.h \
    tests/test_graph_gen.h \
    tests/test_graph_modify.h
