#include"SerialPort.h"
//#include<string>
using namespace std;
//stringתLPCWSTR
LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(orig.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

char ascii2hex(char ch)
{
	//int hex = 0;
	//if ((ch >= '0') && (ch <= '9'))
	//{
	//	hex = ch - '0';
	//}
	//else if ((ch >= 'A') && (ch <= 'F'))
	//{
	//	hex = ch - 'A' + 10;
	//}
	//else if ((ch >= 'a') && (ch <= 'f'))
	//{
	//	hex = ch - 'a' + 10;
	//}
	//else
	//{
	//	hex = -1;
	//}
	//return hex;

	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;// ch - '0';
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else return (-1);
}

//Com:�˿ںţ���COM3
CSerialPort::CSerialPort(unsigned int Com)
{
	string str = "COM" + to_string(Com);
	hcom = CreateFile(stringToLPCWSTR(str), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hcom == INVALID_HANDLE_VALUE)
	{
		printf("�򿪴���ʧ�ܣ�\n");
		system("pause");
		exit(0);
	}
	SetupComm(hcom, 1024, 1024);
	DCB dcb;
	GetCommState(hcom, &dcb);
	dcb.BaudRate = 115200;
	dcb.ByteSize = 8;
	dcb.Parity = 0;
	dcb.StopBits = 1;
	SetCommState(hcom, &dcb);
}


//Com���˿ں�����COM1��BaudRate�������ʣ�ByteSize������λ��StopBits��ֹͣλ��Parity����żУ��
CSerialPort::CSerialPort(unsigned int Com /*= 1*/, unsigned int BaudRate /*= CBR_115200*/, unsigned int ByteSize /*= 8*/, BYTE Parity /*= 'N'*/, BYTE StopBits /*= 1*/)
{
	string str = "COM" + to_string(Com);
	hcom = CreateFile(stringToLPCWSTR(str), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hcom == INVALID_HANDLE_VALUE)
	{
		cout << "�򿪴���ʧ�ܣ�" << endl;
		system("pause");
		exit(0);
	}
	SetupComm(hcom, 1024, 1024);
	DCB dcb;
	GetCommState(hcom, &dcb);
	dcb.BaudRate = BaudRate;
	dcb.ByteSize = ByteSize;
	dcb.Parity = Parity;
	dcb.StopBits = StopBits;
	SetCommState(hcom, &dcb);
}

//��������
void CSerialPort::SendData(string str)
{
	string temp_str = str;


	char temp_hex[1024] = { '\0' };
	//char temp_hex[1024] = { 0xff, 0xfe, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00 };
	//char temp_hex[1024] = { 0xff, 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; 
	//char temp_hex[1024] = { 0xff, 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00 };
	int strLen = temp_str.length();

	char* temp_char = (char*)temp_str.c_str();

	int i, j;
	for (j = 0, i = 0; i < strLen; i++)   //�ַ�������ո�
	{
		if (temp_char[i] != ' ')
		{
			temp_char[j] = temp_char[i];
			j++;
		}
	}
	temp_char[j] = '\0';//�ַ�������

	//int l = sizeof(temp_char)-1;
	//for (j = 0, i = 0; i<l; i += 2)//ת��Ϊ16����  ��"ef"ת��Ϊ0xef
	for (j = 0, i = 0; temp_char[i] != '\0'; i += 2)//ת��Ϊ16����  ��"ef"ת��Ϊ0xef
	{
		if (temp_char[i] == '0'&&temp_char[i + 1] == '0')
		{
			//temp_hex[j] = '0x00';
			//temp_hex[j] = (unsigned char)(0);
			;
		}
		else
		{
			temp_hex[j] = (unsigned char)(ascii2hex(temp_char[i]) * 16 + ascii2hex(temp_char[i + 1]));
		}
		j++;
	}

	string strMsg(temp_hex);
	const char* data = strMsg.data();
	//int len = sizeof(data)-1;
	DWORD dwWrittenLen = 0;//strlen(data)
	if (!WriteFile(hcom, data, strlen(data), &dwWrittenLen, NULL))
	{
		cout << "��������ʧ�ܣ�" << endl;
	}
	else
	{
		cout << "�����ڷ������ݳɹ���" << endl;
	}
	
	////////////////////=====do your work after this line=====//////////////////////
	////////////////////=====source code=====//////////////////////
	//string Message = str;
	////string Message = "dj1mcs(2,1)";
	//string Wrap = Message + "\r\n";
	//const char* data = Wrap.data();
	//DWORD dwWrittenLen = 0;
	//if (!WriteFile(hcom, data, strlen(data), &dwWrittenLen, NULL))
	//{
	//	cout << "��������ʧ�ܣ�" << endl;
	//}
	//cout << "�����ڷ������ݳɹ���" << endl;
	//////////////////////////////////////////////////////////////////////////////////////////////

}

//��������
void CSerialPort::ReceieveData()
{
	Sleep(500);
	char ReceiveBuff[1024] = {};

	DWORD wCount;//��ȡ���ֽ��� 
	BOOL bReadStat;
	bReadStat = ReadFile(hcom, ReceiveBuff, 1024, &wCount, NULL);
	if (!bReadStat)
	{
		cout << "������ʧ�ܣ�" << endl;

	}
	else
	{
		cout << ReceiveBuff << endl;
	}
}
//��ȡ�˿�״̬
void CSerialPort::GetComStatus()
{
	HANDLE hcom;
	//Ĭ�ϼ��COM�˿ڵķ���ֵ��
	hcom = INVALID_HANDLE_VALUE;
	BOOL ret = false;
	//��һ����COM   �˿ڼ��
	for (int i = 1; i <= 32; i++)
	{

		string   comname = "COM" + to_string(i);
		//��COM�˿ڣ������ؼ��ֵ
		hcom = CreateFileA(comname.c_str(),     // �򿪴���
			GENERIC_READ | GENERIC_WRITE,  //��д��ʽ
			0, //���ܹ���
			NULL, //��ȫ���ԣ�һ�㲻����ΪNULL
			OPEN_EXISTING,   //���Ѵ��ڵ��豸
			FILE_ATTRIBUTE_NORMAL,  //��ͨ�ļ�����
			0);       //��ģ��
		//���޷���ָ��COM�˿�
		if (hcom == INVALID_HANDLE_VALUE)
		{

			//ȡ�ô�����Ϣ
			DWORD   err = ::GetLastError();
			//��   err   Ϊ   2   ������COM�˿���δ��װ
			if (err != 2)
			{
				cout << "�˿�" << i << "δ��װ" << endl;
			}
		}
		else
		{
			cout << "�˿�" << i << "����" << endl;
			ret = CloseHandle(hcom);
			if (!ret)
			{
				cout << "�رմ���ʧ��!!" << endl;
			}
			//else
			//{
			//    printf("success");
			//}
		}

	}
}