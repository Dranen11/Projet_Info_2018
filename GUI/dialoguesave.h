#ifndef DIALOGUESAVE_H
#define DIALOGUESAVE_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>

#include "celestialBody.h"


//window for saving image of the simulation
class dialogueSave : public QWidget
{
    Q_OBJECT
public:
    explicit dialogueSave(std::vector<celestialBody *> const& listObject, double fov, vecteur<double,3> pointingVector, QWidget *parent = 0);
    ~dialogueSave();

signals:

protected slots:
    void save();

protected:
    QGridLayout *mainLayout;
    QSpinBox* xResolutionBox;
    QSpinBox* yResolutionBox;
    QSpinBox* subSampleBox;
    QLabel* xResolutionLabel;
    QLabel* yResolutionLabel;
    QLabel* subSampleLabel;
    QPushButton *saveButton;
    std::vector<celestialBody *> const& listObject;
    double fov;
    vecteur<double,3> pointingVector;
};

#endif // DIALOGUESAVE_H
