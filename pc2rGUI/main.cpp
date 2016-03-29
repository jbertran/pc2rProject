#include "gui.h"
#include <QApplication>
#include <QLayout>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GUI* w = new GUI;
    QLayout* mainLayout = new QVBoxLayout;
    
    // Plateau
    PlateauWidget* p = new PlateauWidget;
    mainLayout->addWidget(p);

    // Sidepanel
    QLayout* sidePanel = new QHBoxLayout;
    mainLayout->addItem(sidePanel);

    // Widget de comptage de coups:
    QLayout* coupsLayout = new QHBoxLayout;
    QLabel* coupsText = new QLabel("Nombre de coups: ", p);
    CoupsLabel* coups = new CoupsLabel(QString::number(0), p);
    QObject::connect(p, SIGNAL(counterIncr()), coups, SLOT(incr()));
    QObject::connect(p, SIGNAL(counterDecr()), coups, SLOT(decr()));
    QObject::connect(p, SIGNAL(counterReset()), coups, SLOT(reset()));
    coupsLayout->addWidget(coupsText);
    coupsLayout->addWidget(coups);
    sidePanel->addItem(coupsLayout);

    // Boutons reset, undo, valider
    QPushButton* undo = new QPushButton("Annuler");
    QPushButton* reset = new QPushButton("Tout annuler");
    QPushButton* valid = new QPushButton("Valider");
    QObject::connect(valid, SIGNAL(clicked()), p, SLOT(valider()));
    QObject::connect(undo, SIGNAL(clicked()), p, SLOT(undo()));
    QObject::connect(reset, SIGNAL(clicked()), p, SLOT(reset()));
    sidePanel->addWidget(valid);
    sidePanel->addWidget(undo);
    sidePanel->addWidget(reset);

    // Bouton d'enchère
    
    // Widget d'enchère
    // QInputDialog* ench = new QInputDialog(
    
    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    w->setCentralWidget(mainWidget);
    w->show();
    
    return a.exec();
}
