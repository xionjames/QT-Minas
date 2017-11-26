/***************************************************************************
 *   Copyright (C) 2009 by Jhon Freitez,,,   *
 *   xion@Arween   *
 ***************************************************************************/
#include "mylabel.h"

MyLabel::MyLabel(int r, int c) : QLabel("")
{
    row = r;
    col = c;
}


MyLabel::~MyLabel()
{
}

void MyLabel::mousePressEvent(QMouseEvent * event) {
    if (event->button() == Qt::MidButton)
       emit clicked3(row, col);
    else
        event->ignore();
}

void MyLabel::mouseReleaseEvent(QMouseEvent * event) {
    if (event->button() == Qt::MidButton)
       emit released3(row, col);
    else
        event->ignore();
}
