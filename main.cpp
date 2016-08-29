#include "main.h"

using namespace std;

const double G = 0.00000000006674;
const long long C_SQ = 89875517873681764;

string IToA(int n)
{
	string cOut = "";
	int begin = n;
	int DIV;
	int MOD;

	if (n < 0)
	{
		begin = -n;
	}

	DIV = begin;

	do
	{
		MOD = DIV % 10;
		DIV /= 10;

		cOut.insert(cOut.begin(), (char)(MOD + 48));
	} while (DIV > 0);

	if (n < 0)
	{
		cOut.insert(cOut.begin(), '-');
	}

	return cOut;
}

string DToA(double n)
{
	string cOut = "";
	double begin = n;
	int WHOLE;
	double DECIMAL;
	int DIV;
	double MUL;
	int MOD;

	if (n < 0.0)
	{
		begin = -n;
	}

	WHOLE = (int)begin;
	DECIMAL = begin - (double)WHOLE;

	DIV = WHOLE;

	do
	{
		MOD = DIV % 10;
		DIV /= 10;

		cOut.insert(cOut.begin(), (char)(MOD + 48));
	} while (DIV > 0);

	cOut.insert(cOut.end(), '.');

	MUL = DECIMAL;

	do
	{
		MUL *= 10.0;
		DIV = (int)MUL;
		MUL -= DIV;

		cOut.insert(cOut.end(), (char)(DIV + 48));
	} while (MUL > 0.0);

	if (n < 0)
	{
		cOut.insert(cOut.begin(), '-');
	}

	return cOut;
}

int Pow(int x, int y)
{
	bool DIV = false;
	int iOut = 1;
	int n = y;

	if (y < 0)
	{
		n = -y;
		DIV = true;
	}

	for (int i = 0; i < n; i++)
	{
		if (DIV)
		{
			iOut /= x;
		}
		else
		{
			iOut *= x;
		}
	}

	return iOut;
}

int AToI(string cS)
{
	int iOut = 0;
	int msgLen = cS.length();

	for (int i = 0; i < msgLen; i++)
	{
		iOut += (int)(cS[i] - 48) * Pow(10, (msgLen - (i + 1)));
	}

	return iOut;
}

double AToD(string cS)
{
	double dOut = 0.0;
	int msgLen = cS.length();
	int currentPow = msgLen;

	for (int i = 0; i < msgLen; i++)
	{
		if (cS[i] != '.')
		{
			currentPow--;
			dOut += (double)(int)(cS[i] - 48) * (double)(Pow(10, currentPow));
		}
	}

	return dOut;
}

int main()
{
	string sIn;
	int numBod = 0;
	int locBod = 0;
	int conBod = 0;
	double orbSp = 0;
	double conSp = 0;
	int locDis = 0;
	int conDis = 0;
	long double Dg;
	long double Dv;
	long double Dr;
	long double D;
	long double DCon;
	BODY* bodies;

	cout << "NUMBER OF BODIES IN SYSTEM > ";
	getline(cin, sIn);
	numBod = AToI(sIn);
	bodies = new BODY[numBod];

	for (int i = 0; i < numBod; i++)
	{
		cout << "\nE-NOTATION BASE OF BODY " << IToA(i) << " MASS > ";
		getline(cin, sIn);
		bodies[i].MASS_BASE = AToD(sIn);

		cout << "E-NOTATION EXPONENT OF BODY " << IToA(i) << " MASS > ";
		getline(cin, sIn);
		bodies[i].MASS_EXPONENT = AToI(sIn);

		cout << "DISTANCE OF BODY " << IToA(i) << " FROM CENTER OF SYSTEM > ";
		getline(cin, sIn);
		bodies[i].DISTANCE_FROM_CENTER = AToI(sIn);

		cout << "ORBITAL SPEED OF BODY " << IToA(i) << " > ";
		getline(cin, sIn);
		bodies[i].SPEED = AToI(sIn);
	}

	cout << "\nON WHICH BODY IS THE LOCAL OBSERVER? > ";
	getline(cin, sIn);
	locBod = AToI(sIn);

	cout << "ON WHICH BODY IS THE CONTROL OBSERVER? (-1 FOR OUTSIDE SYSTEM) > ";
	getline(cin, sIn);
	conBod = AToI(sIn);

	cout << "\nDISTANCE OF LOCAL OBSERVER FROM CENTER OF LOCAL BODY > ";
	getline(cin, sIn);
	locDis = AToI(sIn);

	cout << "DISTANCE OF CONTROL OBSERVER FROM CENTER OF CONTROL BODY (-1 FOR OUTSIDE SYSTEM) > ";
	getline(cin, sIn);
	conDis = AToI(sIn);

	cout << "\nSPEED OF LOCAL OBSERVER > ";
	getline(cin, sIn);
	orbSp = AToD(sIn);

	cout << "SPEED OF CONTROL OBSERVER > ";
	getline(cin, sIn);
	conSp = AToD(sIn);

	for (int i = 0; i < numBod; i++)
	{
		bodies[i].U_BASE = G * bodies[i].MASS_BASE;
		bodies[i].U_EXPONENT = bodies[i].MASS_EXPONENT;

		if (i == locBod)
		{
			bodies[i].U_BASE /= locDis;
		}

		if (i == conBod)
		{
			bodies[i].U_BASE /= conDis;
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
			}
		}
	}

	long double UDIV;
	long double VDIV;
	long double RDIV;

	long double LOC_U;
	long double CON_U;

	LOC_U = (long double)bodies[locBod].U_BASE;
	LOC_U *= (long double)powl(10, bodies[locBod].U_EXPONENT);

	CON_U = (long double)bodies[conBod].U_BASE;
	CON_U *= (long double)powl(10, bodies[conBod].U_EXPONENT);

	UDIV = LOC_U;
	UDIV *= 2.0;
	UDIV /= C_SQ;

	VDIV = (long double)powl(bodies[locBod].SPEED, 2);
	VDIV /= C_SQ;

	RDIV = (long double)powl(orbSp, 2);
	RDIV /= C_SQ;
	RDIV *= 1.0 / (1.0 - UDIV);

	Dg = 1.0 / sqrt(1.0 - UDIV);
	Dv = 1.0 / sqrt(1.0 - VDIV);
	Dr = 1.0 / sqrt(1.0 - RDIV);

	cout << "\nTIME DILATION DUE TO GRAVITY AT LOCATION OF LOCAL OBSERVER : " << DToA(Dg) << endl;
	cout << "TIME DILATION DUE TO MOTION OF LOCAL BODY : " << DToA(Dv) << endl;
	cout << "TIME DILATION DUE TO MOTION OF LOCAL OBSERVER : " << DToA(Dr) << endl;

	D = 1.0 / sqrt(fabs(1.0 - UDIV - VDIV - RDIV));

	cout << "\nTOTAL TIME DILATION OF LOCAL OBSERVER : " << DToA(D) << endl;

	if (conBod != -1)
	{
		UDIV = CON_U;
		UDIV *= 2.0;
		UDIV /= C_SQ;

		VDIV = (long double)powl(bodies[conBod].SPEED, 2);
		VDIV /= C_SQ;
	}
	else
	{
		UDIV = 0.0;
		VDIV = 0.0;
	}

	RDIV = (double)powl(conSp, 2);
	RDIV /= C_SQ;
	RDIV *= 1.0 / (1.0 - UDIV);

	Dg = 1.0 / sqrt(1.0 - UDIV);
	Dv = 1.0 / sqrt(1.0 - VDIV);
	Dr = 1.0 / sqrt(1.0 - RDIV);

	cout << "\nTIME DILATION DUE TO GRAVITY AT LOCATION OF CONTROL OBSERVER : " << DToA(Dg) << endl;
	cout << "TIME DILATION DUE TO MOTION OF CONTROL BODY : " << DToA(Dv) << endl;
	cout << "TIME DILATION DUE TO MOTION OF CONTROL OBSERVER : " << DToA(Dr) << endl;

	DCon = 1.0 / sqrt(fabs(1.0 - UDIV - VDIV - RDIV));

	cout << "\nTOTAL TIME DILATION OF CONTROL OBSERVER : " << DToA(DCon) << endl;

	cout << "\nTOTAL DIFFERENCE BETWEEN OBSERVERS : " << DToA(fabs(DCon - D)) << endl;

	getline(cin, sIn);

	return 0;
}
