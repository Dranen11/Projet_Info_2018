#ifndef FRAMESTAR_H
#define FRAMESTAR_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include "QScienceSpinBox.h"
#include "vecteur.h"

class frameStar : public QGroupBox
{
    Q_OBJECT
public:
    explicit frameStar(QString title, QWidget *parent = NULL);
    virtual ~frameStar();

    vecteur<double, 3> getPosition() const;
    vecteur<double, 3> getSpeed() const;
    double getTemperature() const;
    double getRadius() const;
    double getMass() const;

signals:
    void suppression(frameStar*);

protected slots:
    void suppressionCall();

protected :
    QHBoxLayout *mainLayout;

    QLabel *massLabel;
    QScienceSpinBox *massBox;

    QGroupBox *positionFrame;
    QVBoxLayout *positionLayout;
    QScienceSpinBox *positionBox[3];

    QGroupBox *speedFrame;
    QVBoxLayout *speedLayout;
    QScienceSpinBox *speedBox[3];

    QScienceSpinBox *temperatureBox;
    QLabel *temperatureLabel;
    QScienceSpinBox *radiusBox;
    QLabel *radiusLabel;

    QPushButton *deleteButton;
};

#endif // FRAMESTAR_H
