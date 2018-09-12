#pragma once

#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include<windows.h>
#include<string>
#include<iostream>

using namespace std;
/** ����ͨ����
*
*  ����ʵ���˶Դ��ڵĻ�������
*  �����������ָ�����ڵ����ݡ�����ָ�����ݵ�����
*/

class CSerialPort
{
public:
	void SendData(string str);
	void ReceieveData();

	static void GetComStatus();

	//Ĭ�Ϲ��캯����ʼ������
	//            Com�����ں� ��COM1;           BaudRate��������;            ByteSize������λ;      Parity����żУ�� ;   StopBits��ֹͣλ
	CSerialPort(unsigned int Com = 1, unsigned int BaudRate = CBR_115200, unsigned int ByteSize = 8, BYTE Parity = 'N', BYTE StopBits = 1);

	//Com:���ں�,��COM3
	CSerialPort(unsigned int Com=1);
private:
	HANDLE hcom;
};

#endif