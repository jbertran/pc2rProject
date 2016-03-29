#include "gui.h"
#include <QApplication>
#include <QLayout>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI* w = new GUI;
    QLayout* mainLayout = new QHBoxLayout;
    
    // Plateau
    PlateauWidget* p = new PlateauWidget;
    mainLayout->addWidget(p);

    // Sidepanel
    QLayout* sidePanel = new QVBoxLayout;
    mainLayout->addItem(sidePanel);

    // Boutons reset et undo
    QPushButton* undo = new QPushButton("Annuler");
    QPushButton* reset = new QPushButton("Tout annuler");
    QObject::connect(undo, SIGNAL(clicked()), p, SLOT(undo()));
    QObject::connect(reset, SIGNAL(clicked()), p, SLOT(reset()));
    sidePanel->addWidget(undo);
    sidePanel->addWidget(reset);
    
    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    w->setCentralWidget(mainWidget);
    w->show();
    
    return a.exec();
}
