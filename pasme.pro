#-------------------------------------------------
#
# Project created by QtCreator 2010-12-24T15:52:43
#
#-------------------------------------------------

QT       += core gui

TARGET = pasme
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pasmeGerenciadorOcultacao.cpp \
    estadodaencriptacao.cpp \
    pasmeAlgoritmoDeCriptografiaPASME.cpp \
    pasmeAlgoritmoDeCriptografiaXOR.cpp \
    ajuda.cpp \
    sobre.cpp

HEADERS  += mainwindow.h \
    pasmeConfig.h \
    pasmeGerenciadorOcultacao.h \
    estadodaencriptacao.h \
    pasmeAlgoritmosDeCriptografia.h \
    ajuda.h \
    sobre.h

FORMS    += mainwindow.ui \
    estadodaencriptacao.ui \
    ajuda.ui \
    sobre.ui

LIBS += -lz -lgmpxx -lgmp

RESOURCES += \
    pasme.qrc
