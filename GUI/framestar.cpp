#include "framestar.h"
#include <limits>

using namespace std;

//Function for creating easily QScienceSpinBox
QScienceSpinBox* createBox(QString suffix, bool large, QString prefix = "")
{
    QScienceSpinBox* result = new QScienceSpinBox;
    result->setSuffix(suffix);
    result->setPrefix(prefix);
    if(large)
    {
        result->setMinimum(numeric_limits<double>::lowest());
    }
    else
    {
        result->setMinimum(0.);
    }
    result->setMaximum(numeric_limits<double>::max());
    return result;
}

frameStar::frameStar(QString title, QWidget *parent)
    :QGroupBox(title, parent)
{
    mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    massLabel = new QLabel("Masse :");
    mainLayout->addWidget(massLabel);
    massBox = createBox(" kg", false);
    mainLayout->addWidget(massBox);


    positionFrame = new QGroupBox("Position");
    mainLayout->addWidget(positionFrame);

    positionLayout = new QVBoxLayout;
    positionFrame->setLayout(positionLayout);

    positionBox[0] = createBox(" m",true, "x :");
    positionBox[1] = createBox(" m",true, "y :");
    positionBox[2] = createBox(" m",true, "z :");
    positionLayout->addWidget(positionBox[0]);
    positionLayout->addWidget(positionBox[1]);
    positionLayout->addWidget(positionBox[2]);


    speedFrame = new QGroupBox("Vitesse");
    mainLayout->addWidget(speedFrame);

    speedLayout = new QVBoxLayout;
    speedFrame->setLayout(speedLayout);

    speedBox[0] = createBox( "m/s",true, "x :");
    speedBox[1] = createBox(" m/s",true, "y :");
    speedBox[2] = createBox(" m/s",true, "z :");
    speedLayout->addWidget(speedBox[0]);
    speedLayout->addWidget(speedBox[1]);
    speedLayout->addWidget(speedBox[2]);


    temperatureLabel = new QLabel("Temperature de surface:");
    mainLayout->addWidget(temperatureLabel);
    temperatureBox = createBox(" K",false);
    mainLayout->addWidget(temperatureBox);

    radiusLabel = new QLabel("Rayon :");
    mainLayout->addWidget(radiusLabel);
    radiusBox = createBox(" m",false);
    mainLayout->addWidget(radiusBox);

    deleteButton = new QPushButton(QString((QChar) 0x274C));
    mainLayout->addWidget(deleteButton);
    connect(deleteButton,SIGNAL(clicked(bool)),this,SLOT(suppressionCall()));
    connect(deleteButton,SIGNAL(clicked(bool)),this,SLOT(deleteLater()));
}

frameStar::~frameStar()
{
    delete deleteButton;
    delete radiusLabel;
    delete radiusBox;
    delete temperatureBox;
    delete temperatureLabel;

    delete speedBox[0];
    delete speedBox[1];
    delete speedBox[2];
    delete speedLayout;
    delete speedFrame;

    delete positionBox[0];
    delete positionBox[1];
    delete positionBox[2];
    delete positionLayout;
    delete positionFrame;

    delete massLabel;
    delete massBox;

    delete mainLayout;
}

vecteur<double, 3> frameStar::getPosition() const
{
    vecteur<double, 3> position({positionBox[0]->value(),positionBox[1]->value(),positionBox[2]->value()});
    return position;
}

vecteur<double, 3> frameStar::getSpeed() const
{
    vecteur<double, 3> speed({speedBox[0]->value(),speedBox[1]->value(),speedBox[2]->value()});
    return speed;
}

double frameStar::getTemperature() const
{
    return temperatureBox->value();
}

double frameStar::getMass() const
{
    return massBox->value();
}

double frameStar::getRadius() const
{
    return radiusBox->value();
}

void frameStar::suppressionCall()
{
    emit suppression(this);
}
