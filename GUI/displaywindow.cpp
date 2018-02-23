#include "displaywindow.h"
#include "imageManipulation.h"
#include "dialoguesave.h"

using namespace std;

DisplayWindow::DisplayWindow(vector<celestialBody *> const& listObject, double fov, QWidget *parent)
    : QWidget(parent), listObject(listObject), im(NULL)
{
    //Initialize pointing vector as the mean of position vector of the celestials object
    vecteur<double, 3> pointingVector({0.,0.,0.});
    for(size_t i =0; i < listObject.size(); i++)
    {
        pointingVector += listObject[i]->getCoordinate()/listObject[i]->getCoordinate().norm();
    }
    pointingVector/=pointingVector.norm();

    mainLayout = new QHBoxLayout(this);
    menuLayout = new QVBoxLayout;
    mainLayout->addLayout(menuLayout);

    image = new QLabel;
    mainLayout->addWidget(image);

    orientation = new frameOrientation(fov,pointingVector);
    menuLayout->addWidget(orientation);
    connect(orientation,SIGNAL(fovChange(double)),this,SLOT(updateFov(double)));
    connect(orientation,SIGNAL(pointingChange(vecteur<double,3>)),this,SLOT(updatePointingVector(vecteur<double,3>)));

    dtBox = new QScienceSpinBox;
    dtBox->setPrefix("dt : ");
    dtBox->setSuffix(" s");
    dtBox->setMinimum(0);
    dtBox->setMaximum(numeric_limits<double>::max());
    menuLayout->addWidget(dtBox);
    dtButton = new QPushButton("Avancer d'un pas de temps");
    menuLayout->addWidget(dtButton);
    connect(dtButton,SIGNAL(clicked(bool)),this,SLOT(timeIncrease()));


    ndtBox = new QSpinBox;
    ndtBox->setPrefix("x : ");
    ndtBox->setMinimum(0);
    ndtBox->setMaximum(numeric_limits<int>::max());
    menuLayout->addWidget(ndtBox);
    ndtButton = new QPushButton("Avancer de x pas de temps");
    menuLayout->addWidget(ndtButton);
    connect(ndtButton,SIGNAL(clicked(bool)),this,SLOT(timeIncreaseMultipleStep()));
    progress_dt = 0;
    timer_dt = new QTimer();
    timer_dt->setInterval((int)(1000./30.));
    connect(timer_dt,SIGNAL(timeout()),this,SLOT(timeIncrease()));


    printButton = new QPushButton("Sauvegarder");
    menuLayout->addStretch();
    menuLayout->addWidget(printButton);
    connect(printButton,SIGNAL(clicked(bool)),this,SLOT(save()));

    obs = new Observer(pointingVector,fov, {800,800});
    obs->set_objectList(listObject);
    updateImage();
}

DisplayWindow::~DisplayWindow()
{
    delete orientation;
    delete ndtBox;
    delete ndtButton;
    delete timer_dt;
    delete dtBox;
    delete dtButton;
    delete printButton;
    delete image;
    delete menuLayout;
    delete mainLayout;
    delete obs;
    if(im != NULL)
    {
        free(im);
    }
}

void DisplayWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_Plus:
        orientation->zoomIn();
        break;
    case Qt::Key_E:
    case Qt::Key_Minus:
        orientation->zoomOut();
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        orientation->downTurn();
        break;
    case Qt::Key_Z:
    case Qt::Key_Up:
        orientation->upTurn();
        break;
    case Qt::Key_Q:
    case Qt::Key_Left:
        orientation->leftTurn();
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        orientation->rightTurn();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void DisplayWindow::updateFov(double newFov)
{
    obs->set_fov(newFov);
    updateImage();
}

void DisplayWindow::updatePointingVector(const vecteur<double, 3> &newPointingVector)
{
    obs->set_pointingVector(newPointingVector);
    updateImage();
}

void DisplayWindow::updateImage()
{
    if(im != NULL)
    {
        free(im);
    }
    im = convertImageRGB32(obs->getImage());
    image->setPixmap(QPixmap::fromImage(QImage(im,800,800, QImage::Format_RGB32)));
}

void DisplayWindow::save()
{
    dialogueSave *dialog = new dialogueSave(listObject,orientation->get_fov(),orientation->get_pointing());
    dialog->show();
    dialog->setAttribute( Qt::WA_DeleteOnClose );
}

void DisplayWindow::timeIncrease()
{
    for(size_t i = 0; i < listObject.size(); i++)
    {
        listObject[i]->timeStep(dtBox->value());
    }
    updateImage();

    //in case of multiple timestep procedure
    if(timer_dt->isActive())
    {
        progress_dt++;
        if(progress_dt >= ndtBox->value())
        {
            timer_dt->stop();
        }
    }
}

void DisplayWindow::timeIncreaseMultipleStep()
{
    if(!timer_dt->isActive())
    {
        progress_dt=0;
        timer_dt->start();
    }
}
