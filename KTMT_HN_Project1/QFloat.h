#ifndef _QFLOAT_H_
#define _QFLOAT_H_
#include<fstream>
#include<string>
#include<iostream>
#include<math.h>
#define number_bits_of_fraction 112
#define number_bits_of_sign_exponent 16
using namespace std;
class QFloat
{
private:
	void SetBit(char pos, bool bit);			//Bật tắt bit thứ pos
	bool GetBit(char pos);						//Trả về giá trị của bit thứ pos
	string PreComma_to_Binary(string s);				//Chuyển chuỗi số đăng trước dấu phẩy thành nhị phân
	string PostComma_to_Binary(string pre, string s);	//Chuyển chuỗi số sau dấu phẩy thành nhị phân
	string QFloat::MultiStringForTwo(string s);			//Nhân chuỗi cho 2
	string DivideStringForTwo(string s);				//Chia chuỗi cho 2
	int QFloat::CalcExponent(string pre, string post);	//Tính exponent
	int QFloat::CalcExponent(string pre);				//Tính exponent khi chỉ có số trước dấu phẩy, hàm hỗ trợ hàm WriteToFraction
	void QFloat::WriteToExponent(int exp);				//Ghi bit vào phần Exponent
	void QFloat::WriteToFraction(int exp, string pre, string post);	//Ghi bit vào phần fraction
	bool isZero();										//Kiểm tra số 0
protected:
	int data[4];	//lưu trữ 32 x 4 = 128 bit của QFloat
public:
	QFloat();			//default constructor
	QFloat(string s);	//KHởi tạo QFloat truyền vào chuỗi là số thực hệ 10
	void ScanBinQFloat(string s);	//Truyền chuỗi nhị phân s vào data
	void ScanQFloat();				//Nhập qfloat dạng thập phân
	void PrintQFloat();				//Xuất qfloat dạng nhị phân
	QFloat BinToDec(bool *bit);		//Chuyển hệ 2 thành 10
	bool * DecToBin();				//Chuyển hệ 10 thành 2
	string Decimal();				//Trả về chuỗi thập phân
};

#endif