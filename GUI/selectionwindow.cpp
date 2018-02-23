#include "selectionwindow.h"

selectionWindow::selectionWindow(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    starWidget = new QWidget;
    starLayout = new QVBoxLayout;
    starWidget->setLayout(starLayout);
    starCounter = 1;
    addStar();

    starArea = new QScrollArea;
    starArea->setWidgetResizable(true);
    starArea->setWidget(starWidget);
    mainLayout->addWidget(starArea);


    buttonLayout = new QHBoxLayout;
    mainLayout->addLayout(buttonLayout);

    addStarButton = new QPushButton("Ajouter une etoile");
    buttonLayout->addWidget(addStarButton);
    connect(addStarButton,SIGNAL(clicked(bool)),this,SLOT(addStar()));

    launchButton = new QPushButton("Lancement simulation");
    buttonLayout->addWidget(launchButton);
    connect(launchButton, SIGNAL(clicked(bool)),this,SLOT(launchSimulation()));

}

selectionWindow::~selectionWindow()
{
    for(size_t i = 0; i < simulationInput.size(); i++)
    {
        delete simulationInput[i];
    }
    simulationInput.clear();

    delete addStarButton;
    delete launchButton;
    delete buttonLayout;

    for(size_t i = 0; i < (size_t) starInput.size(); i++)
    {
        delete starInput[i];
    }

    delete starLayout;
    delete starWidget;
    delete starArea;

    delete mainLayout;
}

void selectionWindow::addStar()
{
    starInput.append(new frameStar("Etoile "+QString::number(starCounter)));
    starCounter++;
    starLayout->addWidget(starInput.last());
    connect(starInput.last(),SIGNAL(suppression(frameStar*)),this,SLOT(suppressStar(frameStar*)));
}


void selectionWindow::suppressStar(frameStar* star2delete)
{
    starLayout->removeWidget(star2delete);
    starLayout->update();
    for(size_t i = 0; i < (size_t) starInput.size(); i++)
    {
        if(starInput[i] == star2delete)
        {
            starInput.remove(i);
            i--;
        }
    }
}

void selectionWindow::launchSimulation()
{
    hide();
    createStar();
    simulationDisplay = new DisplayWindow(simulationInput,1e-6);
    simulationDisplay->setAttribute( Qt::WA_DeleteOnClose );
    simulationDisplay->show();
    connect(simulationDisplay,SIGNAL(destroyed(QObject*)),this,SLOT(show()));
}

void selectionWindow::createStar()
{
    for(size_t i = 0; i < simulationInput.size(); i++)
    {
        delete simulationInput[i];
    }
    simulationInput.clear();

    for(size_t i = 0; i < starInput.size(); i++)
    {
        simulationInput.push_back(new star(starInput[i]->getMass(),starInput[i]->getPosition(),starInput[i]->getSpeed(),starInput[i]->getTemperature(),starInput[i]->getRadius()));
    }
}
