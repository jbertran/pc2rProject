#include "gui.h"
#include <QApplication>
#include <QLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI* w = new GUI;
    QLayout* mainLayout = new QHBoxLayout;
    PlateauWidget* p = new PlateauWidget;
    mainLayout->addWidget(p);
    QWidget* mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
    w->setCentralWidget(mainWidget);
    w->show();
    
    return a.exec();
}
