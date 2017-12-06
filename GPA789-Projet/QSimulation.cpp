#include "QSimulation.h"
#include "QSimulationMenu.h"
#include <QSplitter>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QTimer>

QSimulation::QSimulation(QForestScene & forestScene, QEnvironment & environment, QWidget *parent)
	: QWidget(parent)
{

	

	QSimulationMenu * SimulationMenu = new QSimulationMenu;
	QHBoxLayout * mainLayout = new QHBoxLayout;


	QGraphicsView *mForestView = new QGraphicsView();
	mForestView->setRenderHint(QPainter::Antialiasing);
	mForestView->setScene(&forestScene);


	mainLayout->addWidget(mForestView);
	mainLayout->addWidget(SimulationMenu);
	
	setLayout(mainLayout);

	mTimer = new QTimer(this);
	//connect(mTimer, SIGNAL(timeout()), &environment, SLOT(advance()));
	connect(mTimer, SIGNAL(timeout()), &forestScene, SLOT(advance()));
	mTimer->start(50);

}

QSimulation::~QSimulation()
{
}
