#include "gui.h"
#include <cstdlib>
#include <QApplication>
#include <QTextEdit>
#include <QLineEdit>
#include <QLayout>
#include <QPixmap>

#define HOST "127.0.0.1"
#define PORT 2016

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    GUI* w = new GUI(HOST, PORT);
    
    w->show();

    return a.exec();
}
