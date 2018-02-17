#include "frameorientation.h"
#include <cmath>

#define PERCENT_FOV 0.1
#define FOV_VARIATION 0.05

using namespace std;

frameOrientation::frameOrientation(double initFov, vecteur<double,3> initPointing, QWidget *parent) : QGroupBox("Orientation",parent)
{
    //creation of the main layout and of the different box
    mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    fovFrame = new QGroupBox("Champs de Vue");
    mainLayout->addWidget(fovFrame);
    pointingFrame = new QGroupBox("Vecteur directeur");
    mainLayout->addWidget(pointingFrame);
    buttonFrame = new QGroupBox("Contr" + QString((QChar) 0x00f4) + "le");
    mainLayout->addWidget(buttonFrame);

    //fovFrame initialisation
    fovLayout = new QVBoxLayout;
    fovFrame->setLayout(fovLayout);
    fovBox = new QScienceSpinBox();
    fovLayout->addWidget(fovBox);
    fovBox->setValue(initFov);
    fovBox->setMaximum(2.*M_PI);
    fovBox->setSingleStep(initFov*FOV_VARIATION);
    fovBox->setSuffix(" rad");
    connect(fovBox,SIGNAL(valueChanged(double)),this,SIGNAL(fovChange(double)));
    connect(fovBox,SIGNAL(valueChanged(double)),this,SLOT(changeFov()));

    //PointingFrame initialisation
    array<double, 3> initPointer = initPointing.getPolarCoordinate();

    pointingLayout = new QGridLayout;
    pointingFrame->setLayout(pointingLayout);

    thetaLabel = new QLabel(QString((QChar) 0x03b8) +" : ");
    pointingLayout->addWidget(thetaLabel,0,0);
    phiLabel = new QLabel(QString((QChar) 0x03c6) +" : ");
    pointingLayout->addWidget(phiLabel,1,0);

    thetaBox = new QScienceSpinBox;
    pointingLayout->addWidget(thetaBox,0,1,1,6);
    thetaBox->setValue(initPointer[1]);
    thetaBox->setSingleStep(initFov*PERCENT_FOV);
    thetaBox->setMaximum(M_PI);
    thetaBox->setMinimum(-M_PI);
    thetaBox->setWrapping(true);//set circular box
    thetaBox->setSuffix(" rad");
    connect(thetaBox,SIGNAL(valueChanged(double)),this,SLOT(changePointing()));

    phiBox = new QScienceSpinBox;
    pointingLayout->addWidget(phiBox,1,1,1,-1);
    phiBox->setValue(initPointer[1]);
    phiBox->setMaximum(2.*M_PI);
    phiBox->setSingleStep(initFov*PERCENT_FOV);
    phiBox->setWrapping(true);//set circular box
    phiBox->setSuffix(" rad");
    connect(phiBox,SIGNAL(valueChanged(double)),this,SLOT(changePointing()));


    //ButtonFrame
    buttonLayout = new QGridLayout;
    buttonFrame->setLayout(buttonLayout);

    zoomInButton = new QPushButton("+");
    buttonLayout->addWidget(zoomInButton,0,0);
    connect(zoomInButton,SIGNAL(pressed()),this,SLOT(zoomIn()));

    zoomOutButton = new QPushButton("-");
    buttonLayout->addWidget(zoomOutButton,0,2);
    connect(zoomOutButton,SIGNAL(pressed()),this,SLOT(zoomOut()));

    leftTurnButton = new QPushButton(QString((QChar) 0x2190));
    buttonLayout->addWidget(leftTurnButton,1,0);
    connect(leftTurnButton,SIGNAL(pressed()),this,SLOT(leftTurn()));

    rightTurnButton = new QPushButton(QString((QChar) 0x2192));
    buttonLayout->addWidget(rightTurnButton,1,2);
    connect(rightTurnButton,SIGNAL(pressed()),this,SLOT(rightTurn()));

    upTurnButton = new QPushButton(QString((QChar) 0x2191));
    buttonLayout->addWidget(upTurnButton,0,1);
    connect(upTurnButton,SIGNAL(pressed()),this,SLOT(upTurn()));

    downTurnButton = new QPushButton(QString((QChar) 0x2193));
    buttonLayout->addWidget(downTurnButton,1,1);
    connect(downTurnButton,SIGNAL(pressed()),this,SLOT(downTurn()));

}

frameOrientation::~frameOrientation()
{
    delete downTurnButton;
    delete upTurnButton;
    delete rightTurnButton;
    delete leftTurnButton;
    delete zoomInButton;
    delete zoomOutButton;
    delete buttonLayout;

    delete phiLabel;
    delete thetaLabel;
    delete phiBox;
    delete thetaBox;
    delete pointingLayout;

    delete fovBox;
    delete fovLayout;

    delete buttonFrame;
    delete pointingFrame;
    delete fovFrame;
    delete mainLayout;
}

void frameOrientation::leftTurn()
{
    phiBox->setValue(phiBox->value()+PERCENT_FOV*fovBox->value());
}

void frameOrientation::rightTurn()
{
    phiBox->setValue(phiBox->value()-PERCENT_FOV*fovBox->value());
}

void frameOrientation::upTurn()
{
    thetaBox->setValue(thetaBox->value()+PERCENT_FOV*fovBox->value());
}

void frameOrientation::downTurn()
{
    thetaBox->setValue(thetaBox->value()-PERCENT_FOV*fovBox->value());
}

void frameOrientation::zoomIn()
{
    fovBox->setValue((1.-FOV_VARIATION)*fovBox->value());
}

void frameOrientation::zoomOut()
{
    fovBox->setValue((1.+FOV_VARIATION)*fovBox->value());
}

void frameOrientation::changePointing()
{
    array<double, 3> initPointer = {1.,thetaBox->value(),phiBox->value()};
    vecteur<double, 3> result;
    result.createFromPolarCoordinate(initPointer);
    emit pointingChange(result);
}

void frameOrientation::changeFov()
{
    double fov = fovBox->value();
    phiBox->setSingleStep(fov*PERCENT_FOV);
    thetaBox->setSingleStep(fov*PERCENT_FOV);
    fovBox->setSingleStep(fov*FOV_VARIATION);
}
