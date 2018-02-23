#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H

#include <QWidget>
#include <QVector>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <vector>

#include "displaywindow.h"
#include "framestar.h"
#include "star.h"

class selectionWindow : public QWidget
{
    Q_OBJECT
public:
    explicit selectionWindow(QWidget *parent = 0);
    virtual ~selectionWindow();

signals:

protected slots:
    void addStar();
    void suppressStar(frameStar* star2delete);

    void launchSimulation();
    void createStar();

protected:
    QVBoxLayout *mainLayout;

    QScrollArea  *starArea;
    QWidget *starWidget;
    QVBoxLayout *starLayout;
    QVector<frameStar*> starInput;
    size_t starCounter;
    std::vector<celestialBody*> simulationInput;
    DisplayWindow* simulationDisplay;

    QHBoxLayout *buttonLayout;
    QPushButton *addStarButton;
    QPushButton *launchButton;
};

#endif // SELECTIONWINDOW_H
