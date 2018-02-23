#ifndef FRAMEORIENTATION_H
#define FRAMEORIENTATION_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include "QScienceSpinBox.h"

#include "../vecteur.h"

//class for controling the FOV and the orientation of the view in the simulation
class frameOrientation : public QGroupBox
{
    Q_OBJECT
public:
    explicit frameOrientation(double initFov, vecteur<double,3> initPointing, QWidget *parent = 0);
    virtual ~frameOrientation();

    double get_fov() const;
    vecteur<double, 3> get_pointing() const;

signals:
    void fovChange(double fov); //emit when a new FOV is defined
    void pointingChange(vecteur<double, 3> const& pointing); //emit when the pointing vector is emit

public slots:
    //slots for making slight change of FOV or on the pointing vector
    void leftTurn();
    void rightTurn();
    void upTurn();
    void downTurn();
    void zoomIn();
    void zoomOut();

protected slots:
    void changePointing();
    void changeFov();

protected:
    //main
    QVBoxLayout *mainLayout;
    QGroupBox *fovFrame;
    QGroupBox *pointingFrame;
    QGroupBox *buttonFrame;

    //fovFrame
    QVBoxLayout *fovLayout;
    QScienceSpinBox *fovBox;

    //PointingFrame
    QGridLayout *pointingLayout;
    QScienceSpinBox *thetaBox;
    QScienceSpinBox *phiBox;
    QLabel *thetaLabel;
    QLabel *phiLabel;

    //ButtonFrame
    QGridLayout *buttonLayout;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *leftTurnButton;
    QPushButton *rightTurnButton;
    QPushButton *upTurnButton;
    QPushButton *downTurnButton;
};

#endif // FRAMEORIENTATION_H
