#pragma once
#include <iostream>
#include <vector>
void matrixOut(std::vector<std::vector<double>>& matrix, std::vector<double>& vectorB);
void vectorOut(std::vector<double> vector);
bool sufficientConditionConvergence(std::vector<std::vector<double>>& matrix);
void subRows(std::vector<std::vector<double>>& matrix, std::vector<double>& vectorB, int minuendRow, int subtrahendRow);
void subRows(std::vector<std::vector<double>>& matrix, std::vector<double>& vectorB, int minuendRow, int subtrahendRow, double coefficient);
double matrixRate(std::vector<std::vector<double>>& matrix);
double vectorRate(std::vector<std::vector<double>>& matrix, std::vector<double>& vectorB);
double vectorRate(std::vector<double>& firstVector, std::vector<double>& secondVector);
int numberOfOperations(double matrixRate, double vectorRate, double epsilon);
std::pair<std::vector<double>, int> methodYakobi(std::vector<std::vector <double>> &matrix, std::vector<double>& vector, double epsilon);
std::pair<std::vector<double>, int> methodGauseZeidel(std::vector<std::vector<double>>& matrix, std::vector<double>&vector, double epsilon);
void makeMatrixBvectorG(std::vector<std::vector<double>>& matrix, std::vector<double>& vector);
bool allIsTrue(std::vector<bool> vector);
