/***************************************************************************
 *   Copyright (C) 2009 by Jhon Freitez,,,   *
 *   xion@Arween   *
 ***************************************************************************/


#include <QApplication>
#include "frmgame.h"

int main(int argc, char *argv[])
{
      Q_INIT_RESOURCE(application);
      QApplication app(argc, argv);
      frmGame * mw = new frmGame();
      mw->show();
      return app.exec();
}

