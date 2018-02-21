#include <iostream>
#include <QApplication>
#include "GUI/displaywindow.h"

#include <QCoreApplication>
#include "task.h"


int main (int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Task parented to the application so that it
    // will be deleted by the application.
    Task *task = new Task(&a);

    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));

    // This will run the task from the application event loop.
    QTimer::singleShot(0, task, SLOT(run()));
    return a.exec();
}

/*
int main (int argc, char *argv[])
{
    QApplication a(argc, argv);
    sphericalSource star(2.e30,vecteur<double,3>({0.,0.,2.4e20}),vecteur<double,3>({0.,0.,0.}),vecteur<double,3>({1.,1.,1.}),3.e11);
    sphericalSource star2(2.e30,vecteur<double,3>({5e12,5e12,2.4e20}),vecteur<double,3>({0.,0.,0.}),vecteur<double,3>({1.,1.,1.}),3.e11);
    gravitationalLense body(2.e30,vecteur<double,3>({0.,0.,1.2e20}),vecteur<double,3>({0,0,0}));
    //DisplayWindow b({&star, &body},1e-7);
    DisplayWindow b({&star2},1e-7);
    //DisplayWindow b({&star2, &body},1e-7);
    b.show();
    return a.exec();
}
*/
