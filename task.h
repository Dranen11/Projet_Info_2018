/*  For testing purpose only
 *
 *
*/

#ifndef TASK_H
#define TASK_H

#include <QImage>
#include <QCoreApplication>
#include "star.h"
#include "observer.h"
#include "GUI/imageManipulation.h"

#include <QtCore>
#include <QObject>


#define DX 300
#define DY 300

using namespace std;


class Task : public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0) : QObject(parent) {}
    virtual ~Task() {}

public slots:
    void run()
    {
        star star1(2.e30,vecteur<double,3>({0.,0.,2.4e20}),vecteur<double,3>({0.,0.,0.}),7000,3.e11);
        star star2(2.e30,vecteur<double,3>({0.,0.,1.2e20}),vecteur<double,3>({0.,0.,0.}),11000,3.e11);
        sphericalSource test1(2.e30,vecteur<double,3>({0.,0.,1.2e20}),vecteur<double,3>({0.,0.,0.}),vecteur<double,3>({1.,0.,0.}),3.e11);
        Observer obs(vecteur<double,3>({0.,0.,1.}),1e-7,{DX,DY},16);
        obs.set_objectList({&star2, &star1});
        //obs.set_objectList({&test1});

        unsigned char* image = convertImageRGB32(obs.getImage());

        QImage rendu(image, DX, DY, QImage::Format_RGB32);
        rendu.save("test.bmp");
        delete image;
        emit finished();
    }

signals:
    void finished();
};

#endif // TASK_H

