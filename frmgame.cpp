/***************************************************************************
 *   Copyright (C) 2009 by Jhon Freitez,,,   *
 *   xion@Arween   *
 ***************************************************************************/


#include "frmgame.h"
#include "time.h"
#include <QLabel>
#include <QMessageBox>

frmGame::frmGame(QWidget* parent)
: QDialog( parent ), Ui::frmGame()
{
	setupUi(this);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            celdas[i][j].valor = 0;
            celdas[i][j].estado = 0;
            celdas[i][j].boton = new MyButton(i, j);
            celdas[i][j].boton->setIconSize(QSize(35, 35));
            celdas[i][j].boton->resize( 45, 45 );
            celdas[i][j].boton->setMaximumSize( 45, 45 );
            celdas[i][j].boton->setMinimumSize( 45, 45 );
            celdas[i][j].boton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
            celdas[i][j].boton->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
            celdas[i][j].boton->setFocusPolicy( Qt::NoFocus );
            //connect(but, SIGNAL(clicked()), but, SLOT(hide()));
            connect(celdas[i][j].boton, SIGNAL(clicked(int, int)), this, SLOT(clickeado(int, int)));
            connect(celdas[i][j].boton, SIGNAL(clicked2(int, int)), this, SLOT(banderear(int, int)));

            celdas[i][j].label = new MyLabel(i, j);
            celdas[i][j].label->setFont( QFont("Courier New", 28, QFont::Bold) );
            celdas[i][j].label->setAlignment(Qt::AlignCenter);
            celdas[i][j].label->resize( 45, 45 );
            celdas[i][j].label->setMaximumSize( 45, 45 );
            celdas[i][j].label->setMinimumSize( 45, 45 );
            celdas[i][j].label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
            celdas[i][j].label->setTextFormat( Qt::RichText );
            celdas[i][j].label->setFrameShape( QFrame::Box );
            celdas[i][j].label->setFrameShadow( QFrame::Sunken );
            connect(celdas[i][j].label, SIGNAL(clicked3(int, int)), this, SLOT(destapar(int, int)));
            connect(celdas[i][j].label, SIGNAL(released3(int, int)), this, SLOT(releasar(int, int)));

            gameLayout->addWidget(celdas[i][j].label, i, j);
            gameLayout->addWidget(celdas[i][j].boton, i, j);
        }
    
    
    newGame();
    connect(btnNew, SIGNAL(clicked()), this, SLOT(newGame()));
}

frmGame::~frmGame()
{
}

/*$SPECIALIZATION$*/


void frmGame::clickeado(int a, int b)
{
    //QMessageBox::information(0, "", QString("%1 - %2").arg(a).arg(b));
    if (!comenzo) {
        comenzo = true;
        crearJuego(a, b);
    }
    
    descubrir(a,b);
    
    if (celdas[a][b].valor == MINA && celdas[a][b].estado != 1)
        matar();
}

void frmGame::crearJuego(int a, int b)
{
    qsrand(time(NULL));
    for (int i=0; i<10; i++) {
        int r = qrand() % 8;
        int c = qrand() % 8;
        if (celdas[r][c].valor == 0 && (r != a && c != b))
            celdas[r][c].valor = MINA;
        else
            i--;
    }
    
    marcar();
    pintar();
    btnNew->setIcon(QIcon(":/face-cool.png"));
}

void frmGame::marcar()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            if (celdas[i][j].valor == MINA) {
                QList<struct pos> ppp = around(i, j);
                for (int g=0; g<ppp.size(); g++)
                    celdas[ppp.value(g).x][ppp.value(g).y]++;
            }
        }
}

void frmGame::pintar()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            QString aa = "";
            switch (celdas[i][j].valor) {
            case 0: aa = "";
                    break;
            case 1: aa = C1;
                    break;
            case 2: aa = C2;
                    break;
            case 3: aa = C3;
                    break;
            case 4: aa = C4;
                    break;
            case 5: aa = C5;
                    break;
            case 6: aa = C6;
                    break;
            case 7: aa = C7;
                    break;
            case 8: aa = C8;
                    break;
            case MINA: aa = CMINA;
                    break;
            }
            celdas[i][j].label->setText(aa);
        }
}

QList<struct pos> frmGame::around(int r, int c)
{
    QList<struct pos> lista;
    
    if (c > 0) {
        struct pos pp = { r, c-1 };
        lista.push_back(pp);
    }
    
    if (c < 7) {
        struct pos pp = { r, c+1 };
        lista.push_back(pp);
    }
    
    if (r > 0) {
        struct pos pp = { r-1, c };
        lista.push_back(pp);
    }
    
    if (r < 7) {
        struct pos pp = { r+1, c };
        lista.push_back(pp);
    }
    
    if (r > 0 && c > 0) {
        struct pos pp = { r-1, c-1 };
        lista.push_back(pp);
    }
        
    if (r < 7 && c < 7) {
        struct pos pp = { r+1, c+1 };
        lista.push_back(pp);
    }
        
    if (r > 0 && c < 7) {
        struct pos pp = { r-1, c+1 };
        lista.push_back(pp);
    }
        
    if (r < 7 && c > 0) {
        struct pos pp = { r+1, c-1 };
        lista.push_back(pp);
    }
    
    return lista;
}

void frmGame::banderear(int a, int b)
{
    if (celdas[a][b].estado == 0) {
        celdas[a][b].estado = 1;
        celdas[a][b].boton->setIcon(QIcon(CFLAG));
    } else if (celdas[a][b].estado == 1) {
        celdas[a][b].estado = 2;
        celdas[a][b].boton->setIcon(QIcon(CFLAG2));
    } else {
        celdas[a][b].estado = 0;
        celdas[a][b].boton->setIcon(QIcon());
    }
}

void frmGame::newGame()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            celdas[i][j].valor = 0;
            celdas[i][j].estado = 0;
            celdas[i][j].label->clear();
            celdas[i][j].boton->show();
            celdas[i][j].boton->setIcon(QIcon());
            celdas[i][j].boton->setReady(true);
        }

    btnNew->setIcon(QIcon(":/face-smile.png"));
    restan = 54;
    comenzo = false;
}

void frmGame::matar()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            if (!celdas[i][j].boton->isHidden())
                celdas[i][j].boton->setReady(false);
            if (celdas[i][j].estado!=1 && celdas[i][j].valor == MINA) {
                celdas[i][j].boton->setIcon(QIcon(BMINA));
            }
        }
    btnNew->setIcon(QIcon(":/face-sad.png"));
    //QMessageBox::critical(0,"Aviso","Perdiste.");
}


void frmGame::descubrir(int a, int b)
{
    if (celdas[a][b].estado != 1 && !celdas[a][b].boton->isHidden()) {
        celdas[a][b].boton->hide();
        restan--;
        if (restan == 0) {
            ganar();
        } else
            if ( celdas[a][b].valor == 0 ) {
                QList<struct pos> ppp = around(a, b);
                for (int g=0; g<ppp.size(); g++)
                    descubrir(ppp.value(g).x, ppp.value(g).y);
            }
    }
}

void frmGame::ganar()
{
    btnNew->setIcon(QIcon(":/face-win.png"));
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            if (!celdas[i][j].boton->isHidden())
                celdas[i][j].boton->setReady(false);
                
            if (celdas[i][j].estado!=1 && celdas[i][j].valor == MINA) {
                celdas[i][j].boton->setIcon(QIcon(CFLAG));
            }
        }
}

void frmGame::destapar(int a, int b)
{
    if (celdas[a][b].valor > 0 && celdas[a][b].valor < 9) {
        
        QList<struct pos> ppp = around(a, b);
        int flaged = 0;
        for (int g=0; g<ppp.size(); g++)
            if (celdas[ppp.value(g).x][ppp.value(g).y].estado == 1 )
                flaged++;
        if (flaged == celdas[a][b].valor) {
            for (int g=0; g<ppp.size(); g++)
                clickeado(ppp.value(g).x, ppp.value(g).y);
        } else {
            for (int g=0; g<ppp.size(); g++)
                if (!celdas[ppp.value(g).x][ppp.value(g).y].boton->isHidden() && celdas[ppp.value(g).x][ppp.value(g).y].estado != 1) {
                    celdas[ppp.value(g).x][ppp.value(g).y].boton->setDown(true);
                }
        }
    }
}

void frmGame::releasar(int a, int b)
{
    QList<struct pos> ppp = around(a, b);
    for (int g=0; g<ppp.size(); g++)
        if (!celdas[ppp.value(g).x][ppp.value(g).y].boton->isHidden() && celdas[ppp.value(g).x][ppp.value(g).y].estado != 1) {
            celdas[ppp.value(g).x][ppp.value(g).y].boton->setDown(false);
        }
}
