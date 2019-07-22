#pragma once
#include <vector>
#include <cmath>
#include <Windows.h>
#include <iostream>

using namespace std;
double getSSIM_CPU(vector<vector<int>> s1, vector<vector<int>> s2, int h, int w, int bit, double pixelRadius);
void getGaussianWeightMatrix(double pixelRadius, vector<vector<double>> *outputMatrix);

double getPSNR_Color_CPU(const unsigned char * s1, const unsigned char * s2, int h, int w);

//double getLABColorDistance(const unsigned char *c1, const unsigned char *c2);
inline double getLABColorDistance(const unsigned char *c1, const unsigned char *c2)
{
	return sqrt((((512 + ((c1[2] + c2[2]) / 2))*(c1[2] - c2[2])*(c1[2] - c2[2])) >> 8) + 4 * (c1[1] - c2[1])*(c1[1] - c2[1]) + (((767 - ((c1[2] + c2[2]) / 2))*(c1[0] - c2[0])*(c1[0] - c2[0])) >> 8));
}