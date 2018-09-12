#pragma once

#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include<windows.h>
#include<string>
#include<iostream>

using namespace std;
/** 串口通信类
*
*  本类实现了对串口的基本操作
*  例如监听发到指定串口的数据、发送指定数据到串口
*/

class CSerialPort
{
public:
	void SendData(string str);
	void ReceieveData();

	static void GetComStatus();

	//默认构造函数初始化串口
	//            Com：串口号 如COM1;           BaudRate：波特率;            ByteSize：数据位;      Parity：奇偶校验 ;   StopBits：停止位
	CSerialPort(unsigned int Com = 1, unsigned int BaudRate = CBR_115200, unsigned int ByteSize = 8, BYTE Parity = 'N', BYTE StopBits = 1);

	//Com:串口号,如COM3
	CSerialPort(unsigned int Com=1);
private:
	HANDLE hcom;
};

#endif