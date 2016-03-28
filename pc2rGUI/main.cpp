#include "gui.h"
#include <QApplication>
#include <QLayout>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI* w = new GUI;
    QLayout* mainLayout = new QHBoxLayout;
    PlateauWidget* p = new PlateauWidget;
    mainLayout->addWidget(p);
    QWidget* mainWidget = new QWidget;
    QPushButton * b = new QPushButton;
    QPixmap pm("../assets/r_rouge");
    QPixmap sc = pm.scaled(b->size().height(), b->size().width());
    QIcon bi(pm);
    b->setIcon(bi);
    mainLayout->addWidget(b);
    mainWidget->setLayout(mainLayout);
    w->setCentralWidget(mainWidget);
    w->show();
    
    return a.exec();
}
