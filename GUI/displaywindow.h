#ifndef DISPLAYWINDOWS_H
#define DISPLAYWINDOWS_H

#include <vector>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
#include <QTimer>

#include "frameorientation.h"

#include "../celestialBody.h"
#include "../observer.h"


//window for visualising the simulation and interact with it
class DisplayWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayWindow(std::vector<celestialBody *> const& listObject, double fov, QWidget *parent = 0);
    virtual ~DisplayWindow();

signals:

protected slots:
    void updateImage();
    void updatePointingVector(vecteur<double,3> const& newPointingVector);
    void updateFov(double newFov);
    void save();
    void timeIncrease();
    void timeIncreaseMultipleStep();

protected:
    virtual void keyPressEvent(QKeyEvent * event); //keyboard input managment

    //Object to take in count for the simulation
    std::vector<celestialBody *> listObject;
    Observer *obs;
    unsigned char* im;

    //Object to display in the window
    QHBoxLayout *mainLayout;
    QVBoxLayout *menuLayout;

    //object for control simulation time
    QScienceSpinBox *dtBox;
    QPushButton *dtButton;
    QSpinBox *ndtBox;
    QPushButton *ndtButton;
    QTimer *timer_dt;
    size_t progress_dt;

    //mainImage
    QLabel *image;

    //orientation control
    frameOrientation *orientation;
    //print image control
    QPushButton *printButton;

};

#endif // DISPLAYWINDOWS_H
