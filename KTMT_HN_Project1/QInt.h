#pragma once
#include<string>
#include<iostream>
using namespace std;
struct QInt
{
	unsigned int	data[4];
	QInt()
	{
		data[0] = data[1] = data[2] = data[3] = 0;
	}
};
//Hàm hỗ trợ
void StringToBit(string &s, bool *&bit);		//Chuyển chuỗi thành bit
QInt ToTwoComplement(QInt x);					//Chuyển sang dạng bù 2
bool GetBit(QInt x, int pos);					//Trả về giá trị của bit thứ pos trong QInt x
void SetBit(QInt &x, int pos, bool bit);		//Gán cho bit thứ pos của x giá trị 'bit'
string GetDecimal(QInt x);						//Trả về giá trị thập phân của QInt (chuỗi)
string DecToBin(string s);						//Chuyển số QInt thập phân thành chuỗi nhị phân
string DivideStringForTwo(string s);			//Chia chuỗi cho 2
string MultiStringForTwo(string s);				//Nhân chuỗi cho 2
string PlusStrings(string s1, string s2);		//Cộng 2 chuỗi
string ComputeExponentOfTwo(int exp);			//Tính giá trị 2^exp

//Nhập xuất
void ScanQInt(QInt &x);							//Nhập số QInt dạng thập phân từ bàn phím
void ScanBinQInt(QInt &x);
void ScanBinQInt(QInt &x, string s);			//Nhập số QInt dạng nhị phân từ chuỗi
void ScanQInt(QInt &x, string s);				//Nhập số QInt dạng thập từ chuỗi
void PrintQInt(QInt x);							//In dạng thập phân của số QInt
void PrintBinQInt(QInt x);						//In dạng nhị phân của số QInt
void ScanBit(bool *&bit);						//Nhập dãy bit nhị phân
//Chuyển đổi
bool*  DecToBin(QInt x);						//Chuyển số QInt thập phân về mảng bool nhị phân
QInt BinToDec(bool *bit);						//Chuyển mảng bool nhị phân về số QInt 
string BinToHex(bool *bit);						//Trả về chuỗi dạng hexa từ số nhị phân
string DecToHex(QInt x);						//Trả về chuỗi dạng hexa từ số thập phân
//Operator
QInt operator + (QInt x1, QInt x2);
QInt operator - (const QInt &x1, const QInt &x2);
QInt operator * (const QInt &x1, const QInt &x2);
QInt operator / (QInt Q, QInt M);
//So sánh
bool operator==(const QInt &x1, const QInt &x2);
bool operator!=(const QInt &x1, const QInt &x2);
bool operator>(const QInt &x1, const QInt &x2);
bool operator<(const QInt &x1, const QInt &x2);
bool operator>=(const QInt &x1, const QInt &x2);
bool operator<=(const QInt &x1, const QInt &x2);
//Phép toán trên bit
QInt operator <<(const QInt &x1, int n);
QInt operator >>(const QInt &x1, int n);
QInt operator |(const QInt &x1, const QInt &x2);
QInt operator ^(const QInt &x1, const QInt &x2);
QInt operator~(const QInt &x1);
QInt operator&(const QInt &a, const QInt &b);

