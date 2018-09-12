#include"SerialPort.h"
using namespace std;


static int flag = 0;

int main()
{
	CSerialPort::GetComStatus();  
	CSerialPort serial(1, 115200, 8, 'N', 1);
	
	//string strSend = {};//instructions of sending
	string strSend = "ff fe 01 00 00 00 00 00 00 00";
	//serial.SendData(strSend);

	while (1)
	{
		serial.SendData(strSend);
		//serial.ReceieveData();
	}

	while (1);
	return 0;
}