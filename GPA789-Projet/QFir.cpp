// QFir.cpp
//
// Description:
// Classe contenant les donn�es particuli�res � un arbre de type Sapin.
//
//
// Auteurs:
// Alex Gosselin-Pronovost
// Jo� Charest
// F�lixe Girard
// Genevi�ve Dao Phan
//
// Automne 2017

#include "QFir.h"
#include <QBrush>
#include <QPainter>
#include <QColor>

// Tables de facteurs environmentaux sp�cifiques � un Sapin
GaussianTable QFir::mPrecipitationGrowFactor(28, 6, 25);
GaussianTable QFir::mLuminosityGrowFactor(200, 30, 10000, -100);
GaussianTable QFir::mTemperatureGrowFactor(150, 15, 900, -75);

// Tables de croissance sp�cifique � un Sapin
GaussianTable QFir::mGrowTable(500, 0, 50000);

QFir::QFir(QEnvironment const & environment, QForestScene & forestscene, int lifeSpan, treeType tree, generalType type)
	: QTrees{ environment ,forestscene, lifeSpan, tree, type }
{
	// Couleurs et textures sp�cifiques � un Sapin
	mLeafColor.setRgb(31, 86, 33);
	mTrunkColor.setRgb(38, 43, 3);
	mPen.setColor(Qt::black);
	mPen.setWidth(0.1);
}

void QFir::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	//Dessine le tronc
	mBrush.setColor(mTrunkColor);
	mBrush.setStyle(Qt::SolidPattern);
	painter->setOpacity(1);
	painter->setBrush(mBrush);
	painter->setPen(mPen);
	painter->drawEllipse(mCenter, mTrunkRadius, mTrunkRadius);

	//Dessine les feuilles
	mPen.setColor(Qt::white);
	mBrush.setColor(mLeafColor);
	mBrush.setStyle(Qt::Dense1Pattern);
	painter->setBrush(mBrush);
	painter->drawEllipse(mCenter, mLeafRadius, mLeafRadius);
}

// Les quatres fonctions suivantes retournent les tables de facteurs environmentaux et de croissance du sapin
GaussianTable & QFir::growTable()
{
	return mGrowTable;
}
GaussianTable & QFir::precipirationGrowFactorTable()
{
	return mPrecipitationGrowFactor;
}
GaussianTable & QFir::luminosityGrowFactorTable()
{
	return mLuminosityGrowFactor;
}
GaussianTable & QFir::temperatureGrowFactorTable()
{
	return mTemperatureGrowFactor;
}