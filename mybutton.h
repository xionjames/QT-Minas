/***************************************************************************
 *   Copyright (C) 2009 by Jhon Freitez,,,   *
 *   xion@Arween   *
 ***************************************************************************/
#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

/**
	@author Jhon Freitez,,, <xion@Arween>
*/
class MyButton : public QPushButton
{
Q_OBJECT
private:
    int row, col;
    bool ready;

public:
    MyButton(int, int);
    ~MyButton();
    
    void mousePressEvent(QMouseEvent * event);
    void setReady(bool);

signals:
    void clicked(int, int);
    void clicked2(int, int);
};

#endif
