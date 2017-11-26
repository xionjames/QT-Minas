/***************************************************************************
 *   Copyright (C) 2009 by Jhon Freitez,,,   *
 *   xion@Arween   *
 ***************************************************************************/
#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>
/**
	@author Jhon Freitez,,, <xion@Arween>
*/
class MyLabel : public QLabel
{
Q_OBJECT
private:
    int row, col;
    
public:
    MyLabel(int r, int c);
    ~MyLabel();
    
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    
signals:
    void clicked3(int, int);
    void released3(int, int);
};

#endif
