#include "Header.h"
#include <iomanip>

void matrixOut(std::vector<std::vector<double>>& matrix, std::vector<double>& vectorB)
{
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < matrix[0].size(); j++) {
			std::cout << std::setw(12) << std::setprecision(4) << std::left << matrix[i][j];
		}
		std::cout << std::setw(9) << ' ' << std::setprecision(3) << std::left << vectorB[i];
		std::cout << std::endl;
	}
}

bool sufficientConditionConvergence(std::vector<std::vector<double>>& matrix)
{
	for (size_t i = 0; i < matrix.size(); i++) {
		double sum = 0;
		for (size_t j = 0; j < matrix[0].size(); j++) {
			if (i != j) { 
				sum += abs(matrix[i][j] / matrix[i][i]);
			}
		}
		if (sum >= 1) {
			return false;
		}
	}
	return true;
}

void subRows(std::vector<std::vector<double>>& matrix, std::vector<double>& vectorB, int minuendRow, int subtrahendRow)
{
	for (size_t i = 0; i < matrix[0].size(); i++) {
		matrix[minuendRow][i] -= matrix[subtrahendRow][i];
	}
	vectorB[minuendRow] -= vectorB[subtrahendRow];
}

void subRows(std::vector<std::vector<double>>& matrix, std::vector<double>& vectorB, int minuendRow, int subtrahendRow, double coefficient)
{
	for (size_t i = 0; i < matrix[0].size(); i++) {
		matrix[minuendRow][i] -= coefficient * matrix[subtrahendRow][i];
	}
	vectorB[minuendRow] -= coefficient * vectorB[subtrahendRow];
}

double matrixRate(std::vector<std::vector<double>>& matrix)
{
	double maxRate = 0;
	for (size_t i = 0; i < matrix.size(); i++) {
		double rate = 0;
		for (size_t j = 0; j < matrix[0].size(); j++) {
			if (i != j) {
				rate += abs(matrix[i][j]);
			}
		}
		rate /= abs(matrix[i][i]);
		if (maxRate < rate) {
			maxRate = rate;
		}
	}
	return maxRate;
}

double vectorRate(std::vector<std::vector<double>>& matrix, std::vector<double>& vectorB)
{
	double maxRate = 0;
	for (size_t i = 0; i < matrix.size(); i++) {
		double rate = abs(vectorB[i] / matrix[i][i]);
		if (maxRate < rate) {
			maxRate = rate;
		}
	}
	return maxRate;
}

double vectorRate(std::vector<double>& firstVector, std::vector<double>& secondVector) {
	double maxRate = 0;
	for (size_t i = 0; i < firstVector.size(); i++) {
		double rate = abs(firstVector[i] - secondVector[i]);
		if (maxRate < rate) {
			maxRate = rate;
		}
	}
	return maxRate;

}


int numberOfOperations(double matrixRate, double vectorRate, double epsilon)
{
	return (int)log10(epsilon * (1 - matrixRate) / vectorRate) / log10(matrixRate);
}

std::pair<std::vector<double>, int> methodYakobi(std::vector<std::vector<double>>& matrix, std::vector<double>& vector, double epsilon)
{
	std::vector<double> thisStep(matrix[0].size());
	fill(thisStep.begin(), thisStep.end(), 1);
	std::vector<double> prevStep(matrix[0].size());
	int count = 0;
	do {
		count++;
		prevStep = thisStep;
		for (size_t i = 0; i < matrix.size(); i++) {
			thisStep[i] = 0;
			for (size_t j = 0; j < matrix[0].size(); j++) {
				thisStep[i] += prevStep[j] * matrix[i][j];
			}
			thisStep[i] += vector[i];
		}
	} while (vectorRate(prevStep, thisStep) >= epsilon);

	return std::pair<std::vector<double>, int>(thisStep, count);
}

std::pair<std::vector<double>, int> methodGauseZeidel(std::vector<std::vector<double>>& matrix, std::vector<double>& vector, double epsilon)
{
	std::vector<bool> isLessEpsilon(matrix[0].size());
	fill(isLessEpsilon.begin(), isLessEpsilon.end(), false);
	std::vector<double> thisStep(matrix[0].size());
	fill(thisStep.begin(), thisStep.end(), 1);
	double prev = thisStep[0];
	int count = 0;
	do {
		prev = thisStep[count % thisStep.size()];
		thisStep[count % thisStep.size()] = 0;
		int numberOfRow = count % thisStep.size();
		for (size_t i = 0; i < thisStep.size(); i++)
		{
			thisStep[numberOfRow] += thisStep[i] * matrix[numberOfRow][i];
		}
		thisStep[numberOfRow] += vector[numberOfRow];
		if (abs(prev - thisStep[numberOfRow]) < epsilon) {
			isLessEpsilon[numberOfRow] = true;
		}
		count++;
	} while (!allIsTrue(isLessEpsilon));
	return std::pair<std::vector<double>, int>(thisStep, count);
}

void makeMatrixBvectorG(std::vector<std::vector<double>>& matrix, std::vector<double>& vector)
{
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < matrix[0].size(); j++) {
			if (i != j) {
				matrix[i][j] /= -matrix[i][i];
			}
		}
		vector[i] /= matrix[i][i];
		matrix[i][i] = 0;
	}
}

bool allIsTrue(std::vector<bool> vector)
{
	for (bool flag : vector)
	{
		if (!flag) {
			return false;
		}
	}
	return true;
}


void vectorOut(std::vector<double> vector)
{
	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << ' ';
	}
	std::cout << std::endl;
}
