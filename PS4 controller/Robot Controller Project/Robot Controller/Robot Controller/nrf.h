#ifndef NRF_H
#define NRF_H

#include <Windows.h>
#include "math.h"
#include "matrix.h"
#include "geometry.h"
#include "Switches.h"

class VecPosition;

using namespace math;
typedef matrix<double> MatrixD; //matrix double

class nrf
{

public:
	static void go(VecPosition vp, double ww, bool shoot_or_chip, short int kick_power, char id);
	static void convert_robot_velocity_to_wheels_velocity(VecPosition vv, double ww, AngRad rteta, MatrixD &V_send_out);
	static void set_velocity(MatrixD V, char id);
	static void write_on_port();
	static char output[30/**NUM_OF_CONTROLLERS*/];
	static void set_kick(bool shoot_or_chip, short int kick_power, char id);
private:
	
	static char ID;
	//MatrixD V(4, 1);	//velocity matrix
	static HANDLE hComm;
	static DWORD numOfBytesToWrite;
	static DWORD numOfBytesWritten;
	static LPCSTR portName;
	static DCB dcbSerialParams;
	static MatrixD V;
	static bool status;
	static bool ftime;
};
#endif // NRF_H









