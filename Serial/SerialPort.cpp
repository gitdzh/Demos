#include"SerialPort.h"
//#include<string>
using namespace std;
//string转LPCWSTR
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

//Com:端口号，如COM3
CSerialPort::CSerialPort(unsigned int Com)
{
	string str = "COM" + to_string(Com);
	hcom = CreateFile(stringToLPCWSTR(str), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hcom == INVALID_HANDLE_VALUE)
	{
		printf("打开串口失败！\n");
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


//Com：端口号例如COM1；BaudRate：波特率；ByteSize：数据位；StopBits：停止位；Parity：奇偶校验
CSerialPort::CSerialPort(unsigned int Com /*= 1*/, unsigned int BaudRate /*= CBR_115200*/, unsigned int ByteSize /*= 8*/, BYTE Parity /*= 'N'*/, BYTE StopBits /*= 1*/)
{
	string str = "COM" + to_string(Com);
	hcom = CreateFile(stringToLPCWSTR(str), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hcom == INVALID_HANDLE_VALUE)
	{
		cout << "打开串口失败！" << endl;
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

//发送数据
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
	for (j = 0, i = 0; i < strLen; i++)   //字符串清除空格
	{
		if (temp_char[i] != ' ')
		{
			temp_char[j] = temp_char[i];
			j++;
		}
	}
	temp_char[j] = '\0';//字符串结束

	//int l = sizeof(temp_char)-1;
	//for (j = 0, i = 0; i<l; i += 2)//转换为16进制  即"ef"转换为0xef
	for (j = 0, i = 0; temp_char[i] != '\0'; i += 2)//转换为16进制  即"ef"转换为0xef
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
		cout << "发送数据失败！" << endl;
	}
	else
	{
		cout << "往串口发送数据成功！" << endl;
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
	//	cout << "发送数据失败！" << endl;
	//}
	//cout << "往串口发送数据成功！" << endl;
	//////////////////////////////////////////////////////////////////////////////////////////////

}

//接收数据
void CSerialPort::ReceieveData()
{
	Sleep(500);
	char ReceiveBuff[1024] = {};

	DWORD wCount;//读取的字节数 
	BOOL bReadStat;
	bReadStat = ReadFile(hcom, ReceiveBuff, 1024, &wCount, NULL);
	if (!bReadStat)
	{
		cout << "读串口失败！" << endl;

	}
	else
	{
		cout << ReceiveBuff << endl;
	}
}
//获取端口状态
void CSerialPort::GetComStatus()
{
	HANDLE hcom;
	//默认检测COM端口的返回值
	hcom = INVALID_HANDLE_VALUE;
	BOOL ret = false;
	//逐一进行COM   端口检测
	for (int i = 1; i <= 32; i++)
	{

		string   comname = "COM" + to_string(i);
		//打开COM端口，并返回检测值
		hcom = CreateFileA(comname.c_str(),     // 打开串口
			GENERIC_READ | GENERIC_WRITE,  //读写方式
			0, //不能共享
			NULL, //安全属性，一般不用设为NULL
			OPEN_EXISTING,   //打开已存在的设备
			FILE_ATTRIBUTE_NORMAL,  //普通文件属性
			0);       //无模板
		//若无法打开指定COM端口
		if (hcom == INVALID_HANDLE_VALUE)
		{

			//取得错误信息
			DWORD   err = ::GetLastError();
			//若   err   为   2   ，即此COM端口尚未安装
			if (err != 2)
			{
				cout << "端口" << i << "未安装" << endl;
			}
		}
		else
		{
			cout << "端口" << i << "正常" << endl;
			ret = CloseHandle(hcom);
			if (!ret)
			{
				cout << "关闭串口失败!!" << endl;
			}
			//else
			//{
			//    printf("success");
			//}
		}

	}
}