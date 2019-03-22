#pragma once
#include<string>
#include<iostream>
using namespace std;
class BigInt
{
private:
	string bigInt;
public:
	string getBigInt()
	{
		return bigInt;
	}
	BigInt(string bigInt)
	{
		this->bigInt = bigInt;
	}
};
class QInt
{
private:
	int data[4];
public:

	QInt()
	{
	}
	//Nhập QInt 
	void ScanQInt()
	{
		string s;
		cin.ignore();
		getline(cin, s);
	}
	//Hàm hỗ trợ: Chia chuỗi cho 2
	//Use		:  Chuyển đổi Cơ số 10 sang 2
	string DivideStringForTwo(string s)
	{
		//s là chuỗi số được nhập vào
		//result là chuỗi kết quả của phép chia cho 2
//		string	s = x.getBigInt();
		string	result = "";
		//temp lưu số bị chia
		int		temp = 0;
		bool	R = 0;			// R: Phần dư
		int		l = s.length();	// l: chiều dài chuỗi số
		int		pos = 0;		//pos: vị trí điền vào kết quả (res)
		for (int i = 0; i < l; i++)
		{
			//Nếu phép chia đang có dư
			if (temp != 0)
			{
				temp = 10 + s[i] - '0';
				result  += temp / 2 + '0';
			//	R = temp % 2;
				temp = temp % 2;
			}
			//Nếu s[i] nhỏ hơn 2
			else
			if (s[i] - '0' < 2)
			{
				result += '0';
				temp = s[i] - '0';
			}
			//Trường hợp s[i] là số lớn hơn 2
			else
			if (s[i] - '0' >= 2)
			{
				result += (s[i] - '0') / 2 +'0';
				temp = (s[i] - '0') % 2;
			}
		}
		while (result[0] == '0' && result.length() > 1) result.erase(0,1);
		return result;
	}
	//Thay đổi giá trị bit ở vị trí pos
	void ChangeBitValue(int pos, bool bit)
	{
		//Bit  0 - 31 : data[0]
		//Bit 32 - 63 : data[1]
		//Bit 64 - 95 : data[2]
		//Bit 96 - 127: data[3]
		if (pos >= 0 && pos < 32)
		{
			if (bit)
				data[0] | (1 << (32 - pos - 1));
			else 
				data[0] & (~(1 << (32 - pos - 1)));
		}
		if (pos >= 32 && pos < 63)
		{
			if (bit)
				data[1] | (1 << (32 - pos - 1));
			else
				data[1] & (~(1 << (32 - pos - 1)));
		}
		if (pos >= 64 && pos < 95)
		{
			if (bit)
				data[2] | (1 << (32 - pos - 1));
			else
				data[2] & (~(1 << (32 - pos - 1)));
		}
		if (pos >= 96 && pos < 127)
		{
			if (bit)
				data[3] | (1 << (32 - pos - 1));
			else
				data[3] & (~(1 << (32 - pos - 1)));
		}

	}
	string DecToBin(BigInt x)
	{
		data[0] = data[1] = data[2] = data[3] = 0;
		string	s = x.getBigInt(); // s: chuỗi số nhập vào
		bool	isNegative = false;	// isNegative: mặc định só nhập vào là số dương
		string	result = "";
		//Kiểm tra số âm hay dương
		if (s[0] == '-')
		{
			isNegative = true; // Check true nếu là số âm
			s.erase(0);
		}
		//Chuyển sang dạng thập phân của số dương và gán vào data;
		//Demo
		while (this->DivideStringForTwo(s) != "0")
		{
			if ((s[s.length() - 1] - '0') % 2 != 0) result = '1' + result;
			else result = '0' + result;
			s = DivideStringForTwo(s);
		}
		if (s[s.length() - 1] == '1') result = '1' + result;
		else result = '0' + result;
		return result;
	}
	~QInt()
	{
	}
};

