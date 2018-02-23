#include "dialoguesave.h"
#include "../observer.h"
#include "imageManipulation.h"
#include <QFileDialog>

QSpinBox* createSpinBox()
{
    QSpinBox* result = new QSpinBox;
    result->setMinimum(0);
    result->setMaximum(100000);
    return result;
}

dialogueSave::dialogueSave(std::vector<celestialBody *> const& listObject, double fov, vecteur<double,3> pointingVector, QWidget *parent) : QWidget(parent), listObject(listObject), fov(fov), pointingVector(pointingVector)
{
    mainLayout = new QGridLayout;
    this->setLayout(mainLayout);

    xResolutionLabel = new QLabel("Resolution axe X :");
    mainLayout->addWidget(xResolutionLabel,0,0);
    yResolutionLabel = new QLabel("Resolution axe Y :");
    mainLayout->addWidget(yResolutionLabel,1,0);
    subSampleLabel = new QLabel("subSample :");
    mainLayout->addWidget(subSampleLabel,2,0);

    xResolutionBox = createSpinBox();
    mainLayout->addWidget(xResolutionBox,0,1);
    yResolutionBox = createSpinBox();
    mainLayout->addWidget(yResolutionBox,1,1);
    subSampleBox = createSpinBox();
    mainLayout->addWidget(subSampleBox,2,1);

    saveButton = new QPushButton("Sauvegarder");
    mainLayout->addWidget(saveButton,3,0,1,2);
    connect(saveButton,SIGNAL(clicked(bool)),this,SLOT(save()));
}

dialogueSave::~dialogueSave()
{
    delete saveButton;
    delete xResolutionBox;
    delete xResolutionLabel;
    delete yResolutionBox;
    delete yResolutionLabel;
    delete subSampleBox;
    delete subSampleLabel;
    delete mainLayout;
}

void dialogueSave::save()
{
    QString file = QFileDialog::getSaveFileName();
    Observer obs(pointingVector,fov, {xResolutionBox->value(),yResolutionBox->value()});
    obs.set_objectList(listObject);
    unsigned char* im = convertImageRGB32(obs.getImage());
    QImage final(im,xResolutionBox->value(),yResolutionBox->value(), QImage::Format_RGB32);
    final.save(file);
    delete im;
    this->deleteLater();
}

