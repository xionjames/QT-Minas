/***************************************************************************
 *   Copyright (C) 2009 by Jhon Freitez,,,   *
 *   xion@Arween   *
 ***************************************************************************/

#ifndef FRMGAME_H
#define FRMGAME_H

#define MINA -1
#define NADA 0

#define C1 "<font color=blue>1</font>"
#define C2 "<font color=green>2</font>"
#define C3 "<font color=red>3</font>"
#define C4 "<font color=cyan>4</font>"
#define C5 "<font color='#FF00FF'>5</font>"
#define C6 "<font color=pink>6</font>"
#define C7 "<font color=black>7</font>"
#define C8 "<font color='#999999'>8</font>"
#define CMINA "<img src=':/bang.png' width=35>"
#define BMINA ":/mine.png"
#define CFLAG ":/flag.png"
#define CFLAG2 ":/flag-question.png"

#include <QDialog>
#include <QList>
#include <QLabel>
#include "ui_frmGame.h"
#include "mybutton.h"
#include "mylabel.h"

struct celda {
    MyButton * boton;
    int valor;
    MyLabel * label;
    int estado;
    
    void operator++(int) {
        if (valor != MINA)
            valor++;
    }
};

struct pos {
    int x, y;
};

class frmGame : public QDialog, private Ui::frmGame
{
  Q_OBJECT

public:
  frmGame(QWidget* parent = 0 );
  ~frmGame();
    void crearJuego(int, int);
    void marcar();
    void pintar();
    QList<struct pos> around(int, int);
    void matar();
    void descubrir(int, int);
    void ganar();
  /*$PUBLIC_FUNCTIONS$*/

public slots:
  /*$PUBLIC_SLOTS$*/

protected:
    struct celda celdas[8][8];
    int restan;
    bool comenzo;
  /*$PROTECTED_FUNCTIONS$*/

protected slots:
    void newGame();
  /*$PROTECTED_SLOTS$*/

protected slots:
    void clickeado(int, int);
    void banderear(int, int);
    void destapar(int, int);
    void releasar(int, int);
};

#endif

