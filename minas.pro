SOURCES += main.cpp \
 frmgame.cpp \
 mybutton.cpp \
 mylabel.cpp
TEMPLATE = app
QT += gui widgets
CONFIG += warn_on \
	  thread \
          qt
TARGET = mines
DESTDIR = bin
RESOURCES = application.qrc
FORMS += frmGame.ui

HEADERS += frmgame.h \
mybutton.h \
 mylabel.h
