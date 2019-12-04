#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

const double G = 0.0000000000667408;
const long long C_SQ = 89875517873681764LL;

struct BODY
{
	long double MASS_BASE;
	long double MASS_EXPONENT;
	long double DISTANCE_FROM_CENTER;
	long double SPEED;
	long double U_BASE;
	long double U_EXPONENT;
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
		bodies[i].U_BASE = G * bodies[i].MASS_BASE;
		bodies[i].U_EXPONENT = bodies[i].MASS_EXPONENT;

		if (i == locBod)
		{
			bodies[i].U_BASE /= powl(locDis, 2);
		}
		
		if (i == conBod)
		{
			bodies[i].U_BASE /= powl(conDis, 2);
		}

		while (bodies[i].U_BASE >= 10.0)
		{
			bodies[i].U_BASE /= 10.0;
			bodies[i].U_EXPONENT += 1;
		}

		while (bodies[i].U_BASE < 1.0)
		{
			bodies[i].U_BASE *= 10.0;
			bodies[i].U_EXPONENT -= 1;
		}
	}

	for (int i = 0; i < numBod; i++)
	{
		for (int j = 0; j < numBod; j++)
		{
			if (i != j)
			{
				bodies[i].U_BASE += (G * bodies[j].MASS_BASE) / fabs(bodies[i].DISTANCE_FROM_CENTER - bodies[j].DISTANCE_FROM_CENTER);

				while (bodies[i].U_BASE >= 10.0)
				{
					bodies[i].U_BASE /= 10.0;
					bodies[i].U_EXPONENT += 1;
				}

				while (bodies[i].U_BASE < 1.0)
				{
					bodies[i].U_BASE *= 10.0;
					bodies[i].U_EXPONENT -= 1;
				}
			}
		}
	}

	long double UDIV;
	long double VDIV;
	long double RDIV;

	long double LOC_U;
	long double CON_U;

	LOC_U = bodies[locBod].U_BASE;
	CON_U = bodies[conBod].U_BASE;

	UDIV = LOC_U;
	if (bodies[locBod].U_EXPONENT > 12) { UDIV *= powl(10, 12L); }
	else { UDIV *= powl(10, bodies[locBod].U_EXPONENT); }
	UDIV /= C_SQ;
	if (bodies[locBod].U_EXPONENT > 12) { UDIV *= powl(10, bodies[locBod].U_EXPONENT - 12L); }
	UDIV *= 2.0;

	VDIV = powl(bodies[locBod].SPEED, 2);
	VDIV /= C_SQ;

	RDIV = powl(orbSp, 2);
	RDIV /= C_SQ;
	RDIV *= 1.0 / (1.0 - UDIV);

	Dg = 1.0 / sqrt(1.0 - UDIV);
	Dv = 1.0 / sqrt(1.0 - VDIV);
	Dr = 1.0 / sqrt(1.0 - RDIV);
	D = 1.0 / sqrt(fabs(1.0 - UDIV - VDIV - RDIV));

	printf_s("\nTIME DILATION DUE TO GRAVITY AT LOCATION OF LOCAL OBSERVER : %.16Lf\n", Dg);
	printf_s("TIME DILATION DUE TO MOTION OF LOCAL BODY : %.16Lf\n", Dv);
	printf_s("TIME DILATION DUE TO MOTION OF LOCAL OBSERVER : %.16Lf\n", Dr);

	printf_s("\nTOTAL TIME DILATION OF LOCAL OBSERVER : %.16Lf\n", D);

	if (conBod != -1)
	{
		UDIV = CON_U;
		if (bodies[conBod].U_EXPONENT > 12) { UDIV *= powl(10, 12L); }
		else { UDIV *= powl(10, bodies[conBod].U_EXPONENT); }
		UDIV /= C_SQ;
		if (bodies[conBod].U_EXPONENT > 12) { UDIV *= powl(10, bodies[conBod].U_EXPONENT - 12L); }
		UDIV *= 2.0;

		VDIV = powl(bodies[conBod].SPEED, 2);
		VDIV /= C_SQ;
	}
	else
	{
		UDIV = 0.0;
		VDIV = 0.0;
	}

	RDIV = powl(conSp, 2);
	RDIV /= C_SQ;
	RDIV *= 1.0 / (1.0 - UDIV);

	Dg = 1.0 / sqrt(1.0 - UDIV);
	Dv = 1.0 / sqrt(1.0 - VDIV);
	Dr = 1.0 / sqrt(1.0 - RDIV);
	DCon = 1.0 / sqrt(fabs(1.0 - UDIV - VDIV - RDIV));

	printf_s("\nTIME DILATION DUE TO GRAVITY AT LOCATION OF CONTROL OBSERVER : %.16Lf\n", Dg);
	printf_s("TIME DILATION DUE TO MOTION OF CONTROL BODY : %.16Lf\n", Dv);
	printf_s("TIME DILATION DUE TO MOTION OF CONTROL OBSERVER : %.16Lf\n", Dr);

	printf_s("\nTOTAL TIME DILATION OF CONTROL OBSERVER : %.16Lf\n", DCon);
	printf_s("\nTOTAL DIFFERENCE BETWEEN OBSERVERS : %.16Lf\n", fabs(DCon - D));

	cin >> sIn;

	return 0;
}