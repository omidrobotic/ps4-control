#include "nrf.h"
#include <iostream>
#include <windows.h>
#include "math.h"
#include "matrix.h"
#include <chrono>
#include <thread>
#include "geometry.h"
#include <random>
//#include "Socket_udp.h"
//#include "protobuf/grSim_Packet.pb.h"
#include <string>

///convert arguments of functions to const World &world


/*! NRF VARIABLES */
char nrf::output[30/**NUM_OF_CONTROLLERS*/] = {};
char nrf::ID;
//MatrixD V(4, 1);	//velocity matrix
HANDLE nrf::hComm;
DWORD nrf::numOfBytesToWrite = sizeof(output);
DWORD nrf::numOfBytesWritten = 0;
LPCSTR nrf::portName = "\\\\.\\COM4";
DCB nrf::dcbSerialParams = { 0 };
MatrixD nrf::V(4, 1);
bool nrf::status = false;
bool nrf::ftime = true;
/*! NRF VARIABLES */

/*!NRF METHODS */
void nrf::go(VecPosition vp, double ww, bool shoot_or_chip, short int kick_power, char id)
{
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)(ctrl_handler), true);
	convert_robot_velocity_to_wheels_velocity(vp, ww, 0, V);
	set_kick(shoot_or_chip, kick_power, id);
	set_velocity(V, id);
	write_on_port();
}
void nrf::convert_robot_velocity_to_wheels_velocity(VecPosition vv, double ww, AngRad rteta, MatrixD &V_send_out)
{
	//ww -> charkhesh hole mehvar khod.

	MatrixD A(4, 3), V(4, 1), VW1(2, 1), VW(3, 1);

	double R = 90;
	VW(0, 0) = (vv.getX() / 64.5);
	VW(1, 0) = (vv.getY() / 64.5);
	VW(2, 0) = ww;// (ww / 180);

	double modified_coeficient = 1;//0.68
	double bb0 = Deg2Rad(300), bb1 = Deg2Rad(225), bb2 = Deg2Rad(135), bb3 = Deg2Rad(60);

	for (int k = 0; k < 2; k++)
	{
		A(0, 0) = (cos(rteta)*sin(bb0) + sin(rteta)*cos(bb0));     A(0, 1) = (sin(rteta)*sin(bb0) - cos(rteta)*cos(bb0));    A(0, 2) = -R;
		A(1, 0) = (cos(rteta)*sin(bb1) + sin(rteta)*cos(bb1));     A(1, 1) = (sin(rteta)*sin(bb1) - cos(rteta)*cos(bb1));    A(1, 2) = -R;
		A(2, 0) = (cos(rteta)*sin(bb2) + sin(rteta)*cos(bb2));     A(2, 1) = (sin(rteta)*sin(bb2) - cos(rteta)*cos(bb2));    A(2, 2) = -R;
		A(3, 0) = (cos(rteta)*sin(bb3) + sin(rteta)*cos(bb3));     A(3, 1) = (sin(rteta)*sin(bb3) - cos(rteta)*cos(bb3));    A(3, 2) = -R;

		/*MatrixD rotation(3, 3), B(4, 3);
		rotation(0, 0) = cos(rteta); rotation(0, 1) = -sin(rteta ); rotation(0, 2) = 0;
		rotation(1, 0) = sin(rteta); rotation(1, 1) = cos(rteta ); rotation(1, 2) = 0;
		rotation(2, 0) = 0; rotation(2, 1) = 0; rotation(2, 2) = 1;
		double pi = M_PI;
		B(0, 0) = (-0.5 / (cos(pi / 3) + cos(pi / 4)));     B(0, 1) = (0.5 / (sin(pi / 3) + sin(pi / 4)));   B(0, 2) = cos(pi / 4) / ((cos(pi / 3) + cos(pi / 4)) * 2 * R);
		B(1, 0) = (0.5 / (cos(pi / 3) + cos(pi / 4)));      B(1, 1) = (0.5 / (sin(pi / 3) + sin(pi / 4)));    B(1, 2) = cos(pi / 3) / ((cos(pi / 3) + cos(pi / 4)) * 2 * R);
		B(2, 0) = (0.5 / (cos(pi / 3) + cos(pi / 4)));     B(2, 1) = (-0.5 / (sin(pi / 3) + sin(pi / 4)));   B(2, 2) = cos(pi / 3) / ((cos(pi / 3) + cos(pi / 4)) * 2 * R);
		B(3, 0) = (-0.5 / (cos(pi / 3) + cos(pi / 4)));    B(3, 1) = (-0.5 / (sin(pi / 3) + sin(pi / 4)));  B(3, 2) = cos(pi / 4) / ((cos(pi / 3) + cos(pi / 4)) * 2 * R);
		A = B*rotation;*/

		V = modified_coeficient* A * VW;

		double limit_v = 30;
		double swap_v;
		swap_v = limit_v;
		if (fabs(V(0, 0)) > limit_v || fabs(V(1, 0)) > limit_v || fabs(V(2, 0)) > limit_v || fabs(V(3, 0)) > limit_v)
		{

			for (int i = 0; i < 4; i++)
			{
				if (fabs(V(i, 0)) > swap_v)
				{
					swap_v = fabs(V(i, 0));
				}
			}
			modified_coeficient = (limit_v) / (swap_v);

		}
	}

	for (int m = 0; m < 4; m++)
	{
		V(m, 0) = floor((ceil(2 * V(m, 0))) / 2);
	}
	V_send_out = V;
}
void nrf::set_velocity(MatrixD V, char id)
{
	char data[3] = {};	//wheel velocity
	/*cout << V(0, 0)<< endl;
	cout << V(1, 0) << endl;
	cout << V(2, 0) << endl;
	cout << V(3, 0) << endl;
	system("cls");*/
	/*cout << endl<<endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;*/

	data[0] = (((int)V(0, 0) & 0x3F) << 2) | (((int)V(1, 0) & 0x30) >> 4);
	data[1] = (((int)V(1, 0) & 0x0F) << 4) | (((int)V(2, 0) & 0x3C) >> 2);
	data[2] = (((int)V(2, 0) & 0x03) << 6) | (((int)V(3, 0) & 0x3F) << 0);

	output[30  - 1] = id;
	output[30  - 2] = data[0];
	output[30  - 3] = data[1];
	output[30  - 4] = data[2];
	
}
void nrf::set_kick(bool shoot_or_chip, short int kick_power, char id)
{
	char kick = {};

	kick = (kick_power % 8) << 5 | shoot_or_chip << 4;

	output[30 - 5] = kick;
}
void nrf::write_on_port()
{
	if (ftime)
	{
		hComm = CreateFile(portName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);

		dcbSerialParams.BaudRate = CBR_256000;
		dcbSerialParams.ByteSize = 8;
		dcbSerialParams.StopBits = ONESTOPBIT;
		dcbSerialParams.Parity = NOPARITY;

		status = SetCommState(hComm, &dcbSerialParams);
		ftime = false;
	}
	WriteFile(hComm,
		output,
		numOfBytesToWrite,
		&numOfBytesWritten,
		NULL);
}

/*!NRF METHODS */

