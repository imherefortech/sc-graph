TEMPLATE = lib
TARGET = $$qtLibraryTarget(sc-graph)

DESTDIR = ../bin

OBJECTS_DIR = obj
MOC_DIR = moc

win32 {
    CONFIG += qt console
    INCLUDEPATH += "../depends/sc-memory-win32/include"
    LIBS += $$quote(-L"../depends/sc-memory-win32/") -lsc_memoryd
}

HEADERS += \
    sc_graph_generator.h \
    sc_graph_struct.h \
    sc_graph_prerequest.h \
    sc_graph_main.h \
    sc_graph_keynodes.h \
    sc_graph_element.h \
    sc_graph_types.h

SOURCES += \
    sc_graph_generator.c \
    sc_graph_struct.c \
    sc_graph_keynodes.c \
    sc_graph_main.c \
    sc_graph_element.c \
    sc_graph_types.c
