/**
 * Author: Katherine Gerot
 * Date: October 9, 2019
 *
 * Newton's Divided Differences for weather stations
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set(double* x, double* y, int s);


int main(int argc, char **argv) {
	int n = 4, station = atoi(argv[1]);
	double p = atof(argv[2]);
	
	switch(station) {
		case 1:	case 2: n = 9; break;
		default: break;
	}
	double x[n], f[n];
	set(x, f, station);
	
	double N[n][n];
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			N[i][j] = 0;
			
		}
	}
	
	//Newton's Divided Differences
	//initializing N[0...n][0]
	for(int i = 0; i < n; i++) {
		N[i][0] = f[i];
		
	}
	printf("%g\n", N[0][0]);
	//continuing with approximation
	for(int i = 1; i < n; i++) {
		printf("%g ", N[i][0]);
		for(int j = 1; j <= i; j++) {
			N[i][j] = (N[i][j-1] - N[i-1][j-1]) / (x[i] - x[i-j]);
			printf("%8.4lf ", N[i][j]);
		}			
		printf("\n");
	}
	
	//Polynomial
	double approx = 0;
	for(int i = 0; i < n; i++) {
		double product = 1;
		for(int j = 0; j < i; j++) {
			product *= p - x[j];
		}
		approx += product * N[i][i]; //*N[][]?
	}
	
	printf("Weather Station %d PM 2.5 at T = %g ~= %g\n", station, p, approx);
	
	return 0;
}

/**
 * Sets weather station
**/
void set(double* x, double* f, int s) {
	double x1[9] = {1,5,8,12,15,19,22,26,29}, f1[9] = {30,33,35,27,29,32,35,37,39};
	double x2[9] = {2,4,9,11,16,18,23,25,30}, f2[9] = {36,35,30,28,34,32,36,37,40};
	double x3[4] = {6,13,20,27}, f3[4] = {42,36,38,40};
	double x4[4] = {7,14,21,28}, f4[4] = {32,34,36,35};
	double x5[4] = {5,10,15,20}, f5[4] = {28,30,33,31};
	double x6[4] = {8,15,22,29}, f6[4] = {30,37,42,44};
	switch(s) {
		case 1: memcpy(x, x1, sizeof(x1));
				memcpy(f, f1, sizeof(f1)); break;
		case 2: memcpy(x, x2, sizeof(x2));
				memcpy(f, f2, sizeof(f2)); break;
		case 3: memcpy(x, x3, sizeof(x3));
				memcpy(f, f3, sizeof(f3)); break;
		case 4: memcpy(x, x4, sizeof(x4));
				memcpy(f, f4, sizeof(f4)); break;
		case 5: memcpy(x, x5, sizeof(x5));
				memcpy(f, f5, sizeof(f5)); break;
		case 6: memcpy(x, x6, sizeof(x6));
				memcpy(f, f6, sizeof(f6)); break;
	}
}