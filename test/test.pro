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
    tests/test_graph_modify.cpp \
    tests/test_find_conn_comp.cpp \
    tests/test_search_incident_vertexes.cpp

HEADERS += \
    utils.h \
    prerequest.h \
    test.h \
    tests/test_graph_gen.h \
    tests/test_graph_modify.h \
    tests/test_find_conn_comp.h \
    tests/test_search_incident_vertexes.h
