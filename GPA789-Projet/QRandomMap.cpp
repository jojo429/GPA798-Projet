// QRandomMap.cpp
//
// Description:
// Widget permetant de g�n�rer une carte de valeurs al�atoires et de la transformer en image.
//
//
// Auteurs:
// Alex Gosselin-Pronovost
// Jo� Charest
// F�lixe Girard
// Genevi�ve Dao Phan
//
// Automne 2017

#include "QRandomMap.h"
#include "RandomUniform.h"
#include <math.h>
#include <array>
#include <QColor>
#include <QImage>

QRandomMap::QRandomMap(QWidget *parent)
	: QWidget(parent)
{
	mPixelsMap = QPixmap(513, 513);
	mPainterMap = new QPainter(&mPixelsMap);
}


void QRandomMap::setMap()
{
	
	int id, x, y, average, sum, shift, n;
	int h{ 513 };
	int step{ h - 1 };

	RandomUniform randNumberValue = RandomUniform();
	RandomUniform randNumberSideSize = RandomUniform(-h, h);
	// Initialize the corners of the map
	mMap[0][0] = randNumberSideSize.random();
	mMap[0][h - 1] = randNumberSideSize.random();
	mMap[h - 1][h - 1] = randNumberSideSize.random();
	mMap[h - 1][0] = randNumberSideSize.random();
	int test;
	while (step > 1) {
		id = step / 2;

		// Start the diamond phase of the algorithm
		for (x = id; x < h; x = x + step) {
			for (y = id; y < h; y = y + step) {
				average = (mMap[x - id][y - id] + mMap[x - id][y + id]
					+ mMap[x + id][y + id] + mMap[x + id][y - id]) / 4;
				mMap[x][y] = average + randNumberValue.random(-id, id);
			}
		}

		// Start the square phase of the algorithm
		for (x = 0; x < h; x = x + id)
		{
			if (x%step == 0) {
				shift = id;
			}
			else
			{
				shift = 0;
			}

			for (y = shift; y < h; y = y + step) {
				sum = 0;
				n = 0;

				if (x >= id) {
					sum = sum + mMap[x - id][y];
					n = n + 1;
				}

				if (x + id < h) {
					sum = sum + mMap[x + id][y];
					n = n + 1;
				}

				if (y >= id) {
					sum = sum + mMap[x][y - id];
					n = n + 1;
				}

				if ((y + id) < h) {
					sum = sum + mMap[x][y + id];
					n = n + 1;
				}

				mMap[x][y] = sum / n + randNumberValue.random(-id,id);
			}
		}
		step = id;
	}
}

void QRandomMap::scaleValuesRangeMap(double minScaleValue, double maxScaleValue)
{
	int i, j;

	this->findMinMax();

	for (i = 0; i < 513; ++i) {
		for (j = 0; j < 513; ++j) {
			mMap[i][j] = (((maxScaleValue - minScaleValue)*(mMap[i][j] - mMin)) / (mMax - mMin)) - 0;
		}
	}
}

void QRandomMap::findMinMax()
{
	int i, j;
	mMin = mMap[0][0];
	mMax = mMap[0][0];

	for (i = 0; i < 513; ++i) {
		for (j = 0; j < 513; ++j) {
			if (mMap[i][j] < mMin) {
				mMin = mMap[i][j];
			}
			else if (mMap[i][j] >= mMax) {
				mMax = mMap[i][j];
			}
		}
	}
}

void QRandomMap::drawMap(int rColor, int gColor, int bColor)
{
	int i, j;
	qreal shade, ajustmentRGB;
	QColor mapColor;

	mRColor = rColor;
	mGColor = gColor;
	mBColor = bColor;

	// Permet de faire un d�grad� de la couleur choisie RGB
	ajustmentRGB = (rColor + gColor + bColor) / 3.0;

	// Dessiner la carte
	for (i = 0; i < 513; ++i) {
		for (j = 0; j < 513; ++j) {
			shade = mMap[i][j] / ajustmentRGB;
			mapColor.setRgb(rColor*shade, gColor*shade, bColor*shade);
			mPainterMap->setPen(mapColor);
			mPainterMap->drawPoint(i, j);
		}
	}
}

void QRandomMap::updateDrawMap(int x, int y)
{
	qreal shade, adjustmentRGB;
	QColor mapColor;

	int realX, realY;

	// Retrouver le pixel d'origine avant le redimensionnement
	realX = (int)floor(x / 4.0);
	realY = (int)floor(y / 4.0);

	// Permet de faire un d�grad� de la couleur choisie RGB
	adjustmentRGB = (mRColor + mGColor + mBColor) / 3.0;

	// Mise � jour du dessin de la carte
	shade = mMap[realX][realY] / 150.0;
	mapColor.setRgb(mRColor * shade, mGColor * shade, mBColor * shade);
	mPainterMap->setPen(mapColor);
	mPainterMap->drawPoint(realX, realY);
}

double QRandomMap::getMapValue(int x, int y)
{
	return mMapResize[x][y];
}

void QRandomMap::setMapValue(int x, int y, double value)
{
	int realX, realY;

	// Retrouver le pixel d'origine avant le redimensionnement
	realX = (int)floor(x / 4.0);
	realY = (int)floor(y / 4.0);

	// Ajout de fertilit� � l'emplacement d�sir�
	mMap[realX][realY] = mMap[realX][realY] + value;

	// La fertilit� maximale est de 100.0
	if (mMap[realX][realY] > 100.0) {
		mMap[realX][realY] = 100.0;
	}

	this->resizeMap();
}

void QRandomMap::resizeMap()
{
	int i, j;
	int nextX = 0;
	int nextY = 0;

	for (i = 0; i < 513; ++i) {
		for (j = 0; j < 513; ++j) {
			this->resizeOnePixel(nextX, nextY, i, j);
			if (nextY <= 2048) {
				nextY = nextY + 4;
			}
		}
		if (nextX <= 2048) {
			nextX = nextX + 4;
			nextY = 0;
		}
	}
}

void QRandomMap::resizeOnePixel(int nextPixelIndexX, int nextPixelIndexY, int pixelIndexX, int pixelIndexY)
{
	int i, j;

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			mMapResize[nextPixelIndexX + i][nextPixelIndexY + j] = mMap[pixelIndexX][pixelIndexY];
		}
	}
}

QPixmap QRandomMap::getPixmap()
{
	return mPixelsMap;
}
