#-------------------------------------------------
#
# Project created by QtCreator 2015-04-07T19:48:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
    Parser/TreeNodes.cpp \
    Gui/uvodframe.cpp \
    Gui/editorframe.cpp \
    Gui/diagramframe.cpp \
    Gui/mainwindow.cpp \
    Gui/automatframe.cpp \
    Engine/editorprocess.cpp \
    Parser/automata.cpp \
    Parser/visitor_nodes.cpp \
    Engine/automatprocess.cpp \
    Gui/guibuilder.cpp

HEADERS  += \
    Parser/TreeNodes.hpp \
    Gui/uvodframe.h \
    Gui/editorframe.h \
    Gui/diagramframe.h \
    Gui/mainwindow.h \
    Gui/automatframe.h \
    Engine/editorprocess.h \
    Parser/automata.h \
    Parser/visitor_nodes.h \
    Engine/automatprocess.h \
    Gui/guibuilder.h

FORMS    += \
    Gui/uvodframe.ui \
    Gui/editorframe.ui \
    Gui/diagramframe.ui \
    Gui/mainwindow.ui \
    Gui/automatframe.ui

DISTFILES +=

RESOURCES += \
    images.qrc


#ovaj deo make-a odnosi se na lex i bison

LIBS += -lfl -ly

FLEXSOURCES = Parser/lexer.l
BISONSOURCES = Parser/parser.y

flexsource.input = FLEXSOURCES
flexsource.output = ${QMAKE_FILE_BASE}.cpp
flexsource.commands = flex --header-file=${QMAKE_FILE_BASE}.h -o ${QMAKE_FILE_BASE}.cpp ${QMAKE_FILE_IN}
flexsource.variable_out = SOURCES
flexsource.name = Flex Sources ${QMAKE_FILE_IN}
flexsource.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += flexsource

flexheader.input = FLEXSOURCES
flexheader.output = ${QMAKE_FILE_BASE}.h
flexheader.commands = @true
flexheader.variable_out = HEADERS
flexheader.name = Flex Headers ${QMAKE_FILE_IN}
flexheader.CONFIG += target_predeps no_link

QMAKE_EXTRA_COMPILERS += flexheader

bisonsource.input = BISONSOURCES
bisonsource.output = ${QMAKE_FILE_BASE}.cpp
bisonsource.commands = bison -d --defines=${QMAKE_FILE_BASE}.h -o ${QMAKE_FILE_BASE}.cpp ${QMAKE_FILE_IN}
bisonsource.variable_out = SOURCES
bisonsource.name = Bison Sources ${QMAKE_FILE_IN}
bisonsource.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += bisonsource

bisonheader.input = BISONSOURCES
bisonheader.output = ${QMAKE_FILE_BASE}.h
bisonheader.commands = @true
bisonheader.variable_out = HEADERS
bisonheader.name = Bison Headers ${QMAKE_FILE_IN}
bisonheader.CONFIG += target_predeps no_link

QMAKE_EXTRA_COMPILERS += bisonheader

# kraj za lex i bison
