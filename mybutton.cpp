/***************************************************************************
 *   Copyright (C) 2009 by Jhon Freitez,,,   *
 *   xion@Arween   *
 ***************************************************************************/
#include "mybutton.h"

MyButton::MyButton(int r, int c) : QPushButton("")
{
    row = r;
    col = c;
    ready = true;
    //connect(this, SIGNAL(clicked()), this, SLOT(listo()));
}


MyButton::~MyButton()
{
}

void MyButton::mousePressEvent(QMouseEvent * event) {
    if (ready)
        if (event->button() == Qt::LeftButton)
            emit clicked(row, col);
        else if (event->button() == Qt::RightButton)
            emit clicked2(row, col);
    else
        event->ignore();
}

void MyButton::setReady(bool b)
{
    ready = b;
}
