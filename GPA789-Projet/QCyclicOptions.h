#ifndef Q_CYCLIC_OPTIONS_H
#define Q_CYCLIC_OPTIONS_H

#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QGroupBox>

class QCyclicOptions : public QWidget
{
	Q_OBJECT

public:
	QCyclicOptions(QWidget *parent = Q_NULLPTR);
	QCyclicOptions(QString caption, QString iconName, QString averageName,
		QString variationName, QString cycleName, int averageMin, int averageMax,
		int variationMin, int variationMax, int cycleMin, int cycleMax);
	~QCyclicOptions();

private:
	QString mCaption;

	QPixmap mIcon;

	QSlider *mAverageSlider;
	QSlider *mVariationSlider;
	QSlider *mCycleSlider;

	QLabel *mIconLabel;
	QLabel *mAverageLabel;
	QLabel *mVariationLabel;
	QLabel *mCycleLabel;
	QLabel *mAverageValue;
	QLabel *mVariationValue;
	QLabel *mCycleValue;

	QGridLayout *mCyclicOptionsGridLayout;

	QHBoxLayout *mLayout;

	QGroupBox *mCyclicOptionsGroupBox;

protected slots:
	void updateValues();
};

#endif //Q_CYCLIC_OPTIONS_H