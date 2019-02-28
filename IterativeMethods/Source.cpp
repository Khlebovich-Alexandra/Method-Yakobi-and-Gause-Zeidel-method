#include <iostream>
#include <vector>
#include <iomanip>
#include "Header.h"
using namespace std;

int main() {
	const double EPSILON = 0.0001;
	const int DEMENCION = 4;
	const double l = -0.2;
	vector<vector<double>> matrixA = { { 8.30, 2.62 + l, 4.10, 1.90 },
							{ 3.92, 8.45, 7.78 - l, 2.46 },
							{ 3.77, 7.21 + l, 8.04, 2.28 },
							{ 2.21, 3.65 - l, 1.69, 6.99 } };
	vector<double> vectorB = { -10.65 + l, 12.21, 15.45 - l, -8.35 };
	cout << "Start Matrix: " << endl;
	matrixOut(matrixA, vectorB);
	cout << endl;

	subRows(matrixA, vectorB, 1, 2);
	subRows(matrixA, vectorB, 2, 1, 3);
	subRows(matrixA, vectorB, 0, 2, 0.5);
	subRows(matrixA, vectorB, 3, 1);
	cout << "Matrix after casting: " << endl;
	matrixOut(matrixA, vectorB);
	cout << endl;

	// Yakobi
	cout << "Method converges? - " << (sufficientConditionConvergence(matrixA) ? "Yes" : "No") << endl;
	double rateMatrix = matrixRate(matrixA);
	double rateVector = vectorRate(matrixA, vectorB);
	cout << "Rate of matrix: " << rateMatrix << endl;
	cout << "Rate of vector: " << rateVector << endl;
	cout << "Number of operations: k = " << numberOfOperations(rateMatrix, rateVector, EPSILON) << endl;
	vector<vector<double>> matrixB(matrixA);
	vector<double> vectorG(vectorB);
	makeMatrixBvectorG(matrixB, vectorG);
	cout << "Mattrix B and Vector G: " << endl;
	matrixOut(matrixB, vectorG);
	cout << endl;
	auto resultYakobi = methodYakobi(matrixB, vectorG, EPSILON);
	cout << "Result with Yakobi method: " << endl;
	cout << "Vector X: ";
	vectorOut(resultYakobi.first);
	cout << "Number of steps: ";
	cout << resultYakobi.second << endl;
	cout << endl;

	auto resultGauseZeidel = methodGauseZeidel(matrixB, vectorG, EPSILON);
	cout << "Result with Gause-Zeidel method: " << endl;
	cout << "Vector X: ";
	vectorOut(resultGauseZeidel.first);
	cout << "Number of steps: ";
	cout << resultGauseZeidel.second << endl;

	system("pause");
	return 0;
}