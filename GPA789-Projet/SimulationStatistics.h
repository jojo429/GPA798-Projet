// SimulationStatistics.h
//
// Description:
// Classe contenant les statistiques de la simulation
//
//
// Auteurs:
// Alex Gosselin-Pronovost
// Jo� Charest
// F�lixe Girard
// Genevi�ve Dao Phan
//
// Automne 2017

#ifndef SIMULATION_STATISTICS_H
#define SIMULATION_STATISTICS_H

class SimulationStatistics
{
public:
	SimulationStatistics() = default;
	~SimulationStatistics() = default;

	//Mise � disposition des donn�es pour calculer diverses statistique
	//et l'affichage graphique de l'�volution de la simulation
	double mPrecipitation{ 0.0 };
	double mWind{ 0.0 };
	double mTemperature{ 0.0 };
	double mLuminosity{ 0.0 };
	int mNumberOfTrees{ 0 };
	int mNumberOfOak{ 0 };
	int mNumberOfFir{ 0 };
	int mNumberOfBirch{ 0 };
	int mNumberOfHazel{ 0 };
	int mNumberOfSeeds{ 0 };
	int mNumberOfGermination{ 0 };
	int mNumberOfSquirrel{ 0 };

};

#endif

