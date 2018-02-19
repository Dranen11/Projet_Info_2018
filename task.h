#ifndef TASK_H
#define TASK_H

#include <QImage>
#include <QCoreApplication>
#include "sphericalSource.h"
#include "gravitationalLense.h"
#include "observer.h"
#include "GUI/imageManipulation.h"

#include <QtCore>
#include <QObject>


#define DX 100
#define DY 100

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
        sphericalSource star(2.e30,vecteur<double,3>({0.,0.,2.4e20}),vecteur<double,3>({0.,0.,0.}),vecteur<double,3>({1.,1.,1.}),3.e11);
        sphericalSource star2(2.e30,vecteur<double,3>({0.,0.,2.4e20}),vecteur<double,3>({0.,0.,0.}),vecteur<double,3>({1.,1.,1.}),3.e11);
        gravitationalLense body(2.e30,vecteur<double,3>({0.,0.,1.2e20}),vecteur<double,3>({0,0,0}));
        Observer obs(vecteur<double,3>({0.,0.,1.}),1e-8,{DX,DY});
        //obs.set_objectList({&star, &body});
        obs.set_objectList({&star2});
        std::vector<std::vector<vecteur<double,3>>> im = obs.getImage();
        unsigned char* image = convertImageRGB32(obs.getImage());

        for(size_t i = 0; i< DX; i++)
        {
            for(size_t j = 0; j< DY; j++)
            {
                for(size_t k = 0; k <4; k++)
                {
                    if(image[i*DY*4+j*4+k]>0.)
                    {
                        qDebug()<<image[i*100+j*4+k]<< " ";
                    }
                }
            }
        }

        QImage rendu(image, DX, DY, QImage::Format_RGB32);
        rendu.save("test.jpg");
        delete image;
        emit finished();
    }

signals:
    void finished();
};

#endif // TASK_H

