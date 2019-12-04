#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

const long double G = 6.67408;
const long C = 299792458L;
const long double C_SQ = powl(299792458, 2);

struct BODY
{
	long double MASS_BASE;
	long double MASS_EXPONENT;
	long double DISTANCE_FROM_CENTER;
	long double SPEED;
};

int main()
{
	string sIn;
	int numBod = 0;
	int locBod = 0;
	int conBod = 0;
	long double orbSp = 0.0;
	long double conSp = 0.0;
	long double locDis = 0.0;
	long double conDis = 0.0;
	long double Dg = 0.0;
	long double Dv = 0.0;
	long double Dr = 0.0;
	long double D = 0.0;
	long double DCon = 0.0;
	BODY* bodies;

	cout << "NUMBER OF BODIES IN SYSTEM > ";
	cin >> numBod;
	bodies = new BODY[numBod];

	for (int i = 0; i < numBod; i++)
	{
		cout << "\nE-NOTATION BASE OF BODY " << i << " MASS > ";
		cin >> bodies[i].MASS_BASE;

		cout << "E-NOTATION EXPONENT OF BODY " << i << " MASS > ";
		cin >> bodies[i].MASS_EXPONENT;

		cout << "DISTANCE OF BODY " << i << " FROM CENTER OF SYSTEM > ";
		cin >> bodies[i].DISTANCE_FROM_CENTER;

		cout << "ORBITAL SPEED OF BODY " << i << " > ";
		cin >> bodies[i].SPEED;
	}

	cout << "\nON WHICH BODY IS THE LOCAL OBSERVER? > ";
	cin >> locBod;

	cout << "ON WHICH BODY IS THE CONTROL OBSERVER? (-1 FOR OUTSIDE SYSTEM) > ";
	cin >> conBod;

	cout << "\nDISTANCE OF LOCAL OBSERVER FROM CENTER OF LOCAL BODY > ";
	cin >> locDis;

	cout << "DISTANCE OF CONTROL OBSERVER FROM CENTER OF CONTROL BODY (-1 FOR OUTSIDE SYSTEM) > ";
	cin >> conDis;

	cout << "\nSPEED OF LOCAL OBSERVER > ";
	cin >> orbSp;

	cout << "SPEED OF CONTROL OBSERVER > ";
	cin >> conSp;

	for (int i = 0; i < numBod; i++)
	{
		while (bodies[i].MASS_BASE >= 10.0)
		{
			bodies[i].MASS_BASE /= 10.0;
			bodies[i].MASS_EXPONENT += 1.0;
		}

		while (bodies[i].MASS_BASE < 1.0)
		{
			bodies[i].MASS_BASE *= 10.0;
			bodies[i].MASS_EXPONENT -= 1.0;
		}
	}

	long double U = 0.0;
	long double UDIV;
	long double VDIV;
	long double RDIV;

	for (int i = 0; i < numBod; i++)
	{
		long double additive = bodies[i].MASS_BASE;
		if (bodies[i].MASS_EXPONENT > 12) { additive *= powl(10, 12L); }
		else { additive *= powl(10, bodies[i].MASS_EXPONENT); }
		additive /= powl(fabs(bodies[i].DISTANCE_FROM_CENTER - (bodies[locBod].DISTANCE_FROM_CENTER - locDis)), 2);
		if (bodies[i].MASS_EXPONENT > 12) { additive *= powl(10, bodies[i].MASS_EXPONENT - 12L); }
		U += additive;
	}
	U *= 2.0;
	U *= powl(10, -11);
	U *= G;
	UDIV = U / C_SQ;
	VDIV = bodies[locBod].SPEED / C;
	RDIV = orbSp / C;

	Dg = 1.0 / sqrt(1.0 - UDIV);
	Dv = 1.0 / sqrt(1.0 - VDIV);
	Dr = 1.0 / sqrt(1.0 - RDIV);
	D = 1.0 / sqrt((1.0 - UDIV) * (1.0 - VDIV) * (1.0 - RDIV));

	printf_s("\nTIME DILATION DUE TO GRAVITY AT LOCATION OF LOCAL OBSERVER : %.16Lf\n", Dg);
	printf_s("TIME DILATION DUE TO MOTION OF LOCAL BODY : %.16Lf\n", Dv);
	printf_s("TIME DILATION DUE TO MOTION OF LOCAL OBSERVER : %.16Lf\n", Dr);

	printf_s("\nTOTAL TIME DILATION OF LOCAL OBSERVER : %.16Lf\n", D);

	if (conBod != -1)
	{
		for (int i = 0; i < numBod; i++)
		{
			long double additive = bodies[i].MASS_BASE;
			printf_s("%.4f %.4f\n", bodies[i].MASS_BASE, bodies[i].MASS_EXPONENT);
			if (bodies[i].MASS_EXPONENT > 12) { additive *= powl(10, 12L); }
			else { additive *= powl(10, bodies[i].MASS_EXPONENT); }
			additive /= powl(fabs(bodies[i].DISTANCE_FROM_CENTER - (bodies[conBod].DISTANCE_FROM_CENTER - conDis)), 2);
			if (bodies[i].MASS_EXPONENT > 12) { additive *= powl(10, bodies[i].MASS_EXPONENT - 12L); }
			U += additive;
		}
		U *= 2.0;
		U *= powl(10, -11);
		U *= G;
		UDIV = U / C_SQ;
		VDIV = bodies[conBod].SPEED / C;
	}
	else
	{
		UDIV = 0.0;
		VDIV = 0.0;
	}

	RDIV = conSp / C;

	Dg = 1.0 / sqrt(1.0 - UDIV);
	Dv = 1.0 / sqrt(1.0 - VDIV);
	Dr = 1.0 / sqrt(1.0 - RDIV);
	DCon = 1.0 / sqrt((1.0 - UDIV) * (1.0 - VDIV) * (1.0 - RDIV));

	printf_s("\nTIME DILATION DUE TO GRAVITY AT LOCATION OF CONTROL OBSERVER : %.16Lf\n", Dg);
	printf_s("TIME DILATION DUE TO MOTION OF CONTROL BODY : %.16Lf\n", Dv);
	printf_s("TIME DILATION DUE TO MOTION OF CONTROL OBSERVER : %.16Lf\n", Dr);

	printf_s("\nTOTAL TIME DILATION OF CONTROL OBSERVER : %.16Lf\n", DCon);
	printf_s("\nTOTAL DIFFERENCE BETWEEN OBSERVERS : %.16Lf\n", fabs(DCon - D));

	cin >> sIn;

	return 0;
}