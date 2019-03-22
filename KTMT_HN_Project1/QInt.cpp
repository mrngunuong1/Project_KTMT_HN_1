#include"QInt.h"
void ScanQInt(QInt &x)
{
	string s;
	fflush(stdin);
	getline(cin, s);
	string temp = DecToBin(s);
	x.data[0] = x.data[1] = x.data[2] = x.data[3] = 0;
	for (int i = 127 - temp.length() + 1; i <= 127; i++)
	{
		SetBit(x, i, temp[i - 128 + temp.length()] - '0');
	}
}
//Nhập dãy bit
void ScanBinQInt(QInt &x)
{
	string s;
	fflush(stdin);
	getline(cin, s);
	ScanBinQInt(x, s);
}
void ScanBinQInt(QInt &x, string s)
{
	int l = s.length();
	int j = 127;
	for (int i = l - 1; i >= 0; i--)
	{
		SetBit(x, j, s[i] - '0');
		j--;
	}
	for (j; j >= 0; j--)
	{
		SetBit(x, j, 0);
	}
}
void ScanBit(bool *&bit)
{
	if (bit) delete[] bit;
	bit = new bool[128];
	string s;
	fflush(stdin);
	getline(cin, s);
	StringToBit(s, bit);
}
void ScanQInt(QInt &x, string s)
{
	string temp = DecToBin(s);
	x.data[0] = x.data[1] = x.data[2] = x.data[3] = 0;
	for (int i = 127 - temp.length() + 1; i <= 127; i++)
	{
		SetBit(x, i, temp[i - 128 + temp.length()] - '0');
	}
}
void PrintBinQInt(QInt x)
{
	for (int i = 0; i < 128; i++)
		cout << GetBit(x, i);
}
//Hàm hỗ trợ: Chia chuỗi cho 2
//Use		:  Chuyển đổi Cơ số 10 sang 2
string DivideStringForTwo(string s)
{
	//s là chuỗi số được nhập vào
	//result là chuỗi kết quả của phép chia cho 2
	string	result = "";
	//temp lưu số bị chia
	int		temp = 0;
	int		l = s.length();	// l: chiều dài chuỗi số
	for (int i = 0; i < l; i++)
	{
		//Nếu phép chia đang có dư
		if (temp != 0)
		{
			temp = 10 + s[i] - '0';
			result += temp / 2 + '0';
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
			result += (s[i] - '0') / 2 + '0';
			temp = (s[i] - '0') % 2;
		}
	}
	while (result[0] == '0' && result.length() > 1) result.erase(0, 1);
	return result;
}
//Thay đổi giá trị bit ở vị trí pos
void SetBit(QInt &x, int pos, bool bit)
{
	//Bit  0 - 31 : data[0]
	//Bit 32 - 63 : data[1]
	//Bit 64 - 95 : data[2]
	//Bit 96 - 127: data[3]
	if (bit)
	{
		x.data[pos / 32] = x.data[pos / 32] | (1 << (32 - pos % 32 - 1));
	}
}
//Kiểm tra số 0
bool isZero(const QInt &x)
{
	for (int i = 0; i < 128; i++)
	{
		if (GetBit(x, i) == 1) return false;
	}
	return true;
}
//trả về giá trị bit thứ pos
bool GetBit(QInt x, int pos)
{
	return ((x.data[pos / 32] >> (31 - (pos % 32))) & 1);
}
//Chuẩn hóa bool bit
void NormalizeBit(bool *&bit)
{

}
string DecToBin(string s)
{
	if (s == "") return "";
	bool	isNegative = false;	// isNegative: mặc định só nhập vào là số dương
	string	result = "";
	//Kiểm tra số âm hay dương
	if (s[0] == '-')
	{
		isNegative = true;	// Check true nếu là số âm
		s.erase(0, 1);		//Xóa dấu âm đầu chuỗi
	}
	//Chuyển sang dạng thập phân của số dương và gán vào data;
	//Demo
	while (DivideStringForTwo(s) != "0")
	{
		if ((s[s.length() - 1] - '0') % 2 != 0) result = '1' + result;
		else result = '0' + result;
		s = DivideStringForTwo(s);
	}
	if (s[s.length() - 1] == '1') result = '1' + result;
	else result = '0' + result;
	//Xử lí chuyển thành số bù 2 đối với số âm
	if (isNegative)
	{
		int	l = result.length();
		//Chèn các bit 0 vào đầu dãy bit để đủ 128 bit
		result.insert(result.begin(), 128 - l, '0');
		//Chuyển sang dạng bù 1
		for (int i = 0; i < 128; i++)
		{
			result[i] = (result[i] == '0') ? '1' : '0';	
		}
		//Cộng 1 vào số bù 1
		for (int i = 127; i >= 0; i--)
		{
			if (result[i] == '1') result[i] = '0';
			else
			{
				result[i] = '1';
				break;
			}
		}
	}
	return result;
}
//Nhân giá trị của chuỗi cho 2
string MultiStringForTwo(string s)
{
	int temp = false;
	string result;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		if (temp != 0)
		{
			temp = 2 * (s[i] - '0') + 1;
			result = char((temp % 10) + '0') + result;
			if (temp/10 != 0)
			{
				if (i > 0) temp = 1;
				else result = '1' + result;
			}
			else temp = 0;
		}
		else
		{
			temp = 2 * (s[i] - '0');
			result = char((temp % 10) + '0') + result;
			if (temp > 9)
			{
				if (i > 0) temp = 1;
				else result = '1' + result;
			}
			else temp = 0;
		}
	}
	while (result[0] == '0' && result.length() > 1) result.erase(0, 1);
	return result;
}
string PlusStrings(string s1, string s2)
{
	
	string	result;
	int		temp = 0, R = 0;
	while (s1.length() < s2.length())
	{
		s1.insert(0, "0");
	}
	while (s2.length() < s1.length())
	{
		s2.insert(0, "0");
	}
	int		l1 = s1.length();
	for (int i = l1 - 1; i >= 0; i--)
	{
		temp = R + s1[i] - '0' + s2[i] - '0';
		
		if (temp / 10 != 0)
		{
			if (i>0) R = 1;
			else
			{
				result = char(temp % 10 + '0') + result;
				result = char(temp / 10 + '0') + result;
				break;
			}
		}
		else R = 0;
		result = char((temp % 10) + '0') + result;
	}
	while (result[0] == '0' && result.length() > 1) result.erase(0, 1);
	return result;
}
//Tính 2^exp
string ComputeExponentOfTwo(int exp)
{
	if (exp == 0) return "1";
	string result = "1";
	for (int i = 0; i < exp; i++)
	{
		result = MultiStringForTwo(result);
	}
	return result;
}
void StringToBit(string &s, bool *&bit)
{
	//Gán các bit từ chuỗi vào mảng bool bit
	//B1: Gán các phần tử đầu bằng bit 0
	for (int i = 0; i < 128 - s.length(); i++)
	{

		bit[i] = 0;
	}
	//B2: Gán các phần tử trong chuỗi từ s[0] đến hết vào mảng
	int pos = 0;
	for (int i = 128 - s.length(); i < 128; i++)
	{
		bit[i] = s[pos++] - '0';
	}
}
string GetDecimal(QInt x)
{
	bool *bit = DecToBin(x);
	string GetDecimal = "0";
	bool isNegative = 0;
	if (bit[0] == 1)
	{
		//Trừ 1
		for (int i = 127; i >= 0; i--)
		{
			if (!bit[i]) bit[i] = 1;
			else bit[i] = 0;
			if (bit[i] == 0) break;
		}
		//Huỷ dạng bù 1, đưa về dạng không dấu
		for (int i = 0; i < 128; i++)
		{
			bit[i] = (bit[i]) ? 0 : 1;
		}
		isNegative = 1;
	}
	string temp = "";
	for (int i = 128 - 1; i >= 0; i--)
	{
		if (bit[i] == 1) temp = ComputeExponentOfTwo(128 - i - 1);
		GetDecimal = PlusStrings(GetDecimal, temp);
		temp = "";
	}
	if (isNegative) GetDecimal = '-' + GetDecimal;
	delete[] bit;
	return GetDecimal;
}

void PrintQInt(QInt x)
{
	string Decimal = GetDecimal(x);
	cout << Decimal;
}

bool* DecToBin(QInt x)
{
	bool *result = new bool[128];
	for (int i = 0; i < 128; i++)
	{
		result[i] = (x.data[i / 32] & (1 << (32 - (i % 32) - 1)));
	}
	return result;
}

QInt BinToDec(bool *bit)
{
	QInt result;
	result.data[0] = result.data[1] = result.data[2] = result.data[3] = 0;
	for (int i = 0; i < 128; i++)
		SetBit(result, i, bit[i]);
	return result;
}
string BinToHex(bool *bit)
{
	string hex;
	string temp;	//lưu từng nhóm 4 bit
	for (int i = 0; i < 128; i++)
	{
		temp += bit[i] + '0';
		//Nếu đủ 4 bit
		if ((i + 1) % 4 == 0)
		{
			if (temp == "0000")
			{
				if (hex != "") hex += '1';
			}
			else if(temp == "0001") hex += '1';
			else if (temp == "0010") hex += '2';
			else if (temp == "0011") hex += '3';
			else if (temp == "0100") hex += '4';
			else if (temp == "0101") hex += '5';
			else if (temp == "0110") hex += '6';
			else if (temp == "0111") hex += '7';
			else if (temp == "1000") hex += '8';
			else if (temp == "1001") hex += '9';
			else if (temp == "1010") hex += 'A';
			else if (temp == "1011") hex += 'B';
			else if (temp == "1100") hex += 'C';
			else if (temp == "1101") hex += 'D';
			else if (temp == "1110") hex += 'E';
			else if (temp == "1111") hex += 'F';
			temp = "";
		}
	}
	if (hex == "") return "0";
	return hex;
}
string DecToHex(QInt x)
{
	bool *bit = DecToBin(x);
	if (bit)
	return BinToHex(bit);
	else return NULL;
}

bool PlusTwoBit(bool x1, bool x2, bool &memo)
{
	bool result;
	if (x1 == 0 && x2 == 0)
	{
		result = memo;
		memo = 0;
		return result;
	}
	if ((x1 == 1 && x2 == 0) || (x1 == 0 && x2 == 1))
	{
		if (memo == 0) return 1;
		if (memo == 1) return 0;
	}
	if ((x1 == 1 && x2 == 1))
	{
		if (memo == 0)
		{
			memo = 1;
			result = 0;
		}
		else
		{
			memo = 1;
			result = 1;
		}
		return result;
	}
}
bool SubtTwoBit(bool x1, bool x2, bool &memo)
{
	bool result;
	//Trừ 2 bit 0
	if (x1 == 0 && x2 == 0)
	{
		if (memo == 0) return 0;
		else
		{
			memo = 1;
			return 1;
		}
	}
	//Trừ bit 1 cho bit 0
	if (x1 == 1 && x2 == 0)
	{
		//Bit nhớ = 0
		if (memo == 0)
		{
			return 1;
		}
		//Bit nhớ = 1
		if (memo == 1)
		{
			memo = 0;
			return 0;
		}
	}
	//Trừ bit 0 cho bit 1
	if (x1 == 0 && x2 == 1)
	{
		//Bit nhớ = 0
		if (memo == 0)
		{
			memo = 1;
			return 1;
		}
		//Bit nhớ = 1
		if (memo == 1)
		{
			memo = 1;
			return 0;
		}
	}
	// Trừu bit 1 cho bit 1
	if ((x1 == 1 && x2 == 1))
	{
		if (memo == 0)
		{
			memo = 0;
			return 0;
		}
		else
		{
			memo = 1;
			return  1;
		}
	}
}
QInt operator + (QInt x1, QInt x2)
{
	QInt res = x1;	//result chứa kết quả của phép cộng
	//bool *data = new bool [128];
	//bool *n1 = DecToBin(x1), *n2 = DecToBin(x2);
	//bool memo = 0;
	//for (int i = 127; i >= 0; i--)
	//{
	//	data[i] = PlusTwoBit(n1[i], n2[i], memo);
	//}
	//result = BinToDec(data);

	QInt carry;
	while (!isZero(x2))// háº¿t (nhá»›)
	{
		//carry lÃ  nhá»¯ng bit cÃ¹ng lÃ  1 giá»¯a 2 sá»‘ (biáº¿n nhá»› cá»™t i)
		carry = res & x2;

		//tá»•ng cÃ¡c bit khÃ¡c nhau cá»§a hai sá»‘ (0 + 1 = 1 , 1+1=0 (nhá»› 1 da bá» vao carry á»Ÿ trÃªn)).
		res = res ^ x2;

		//di chuyá»ƒn tá»›i cá»™t i+1 Ä‘á»ƒ cá»™ng dá»“n vÃ o res
		x2 = carry << 1;

	}

	return res;
}
QInt operator - (const QInt &x1, const QInt &x2)
{
	QInt result;	//result chứa kết quả phép cộng
	//bool *data = new bool[128];
	//bool *n1 = DecToBin(x1), *n2 = DecToBin(x2);
	//bool memo = 0;
	//for (int i = 127; i >= 0; i--)
	//{
	//	data[i] = SubtTwoBit(n1[i], n2[i], memo);
	//}
	//result = BinToDec(data);
	//delete[] data;
	//delete[] n1;
	//delete[] n2;
	bool memo = 0;
	for (int i = 127; i >= 0; i--)
	{
		SetBit(result , i, SubtTwoBit(GetBit(x1, i), GetBit(x2, i), memo));
	}
	return result;
}

QInt operator <<(const QInt &x1, int n)
{
	if (n < 0) return (x1 >> (-n));
	QInt result;
	for (int i = 0; i <= 127 - n; i++)
	{
		SetBit(result, i, GetBit(x1,i + n));
	}
	for (int i = 128 - n; i < 127; i++)
		result.data[i] = 0;
	return result;
}
QInt operator >>(const QInt &x1, int n)
{
	QInt result;
	if (n < 0) return (x1 << (-n));
	for (int i = 127; i >= n; i--)
	{
		SetBit(result, i, GetBit(x1,i-n));
	}
	for (int i = 0; i < n; i++)
		SetBit(result, i, 0);
	return result;
}
QInt operator |(const QInt &x1, const QInt &x2)
{
	QInt result;
	for (int i = 0; i < 128; i++)
	{
		SetBit(result, i, GetBit(x1, i) | GetBit(x2,i));
	}
	return result;
}
QInt operator ^(const QInt &x1, const QInt &x2)
{
	QInt result;
	for (int i = 0; i < 128; i++)
	{
		SetBit(result, i, GetBit(x1, i) ^ GetBit(x2, i));
	}
	return result;
}
QInt operator & (const QInt &a, const QInt &b)
{
	QInt res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = a.data[i] & b.data[i];
	}
	return res;
}
QInt operator~(const QInt &x1)
{
	QInt result;
	for (int i = 0; i < 128; i++)
	{
		SetBit(result, i, !GetBit(x1, i));
	}
	return result;
}
bool operator==(const QInt &x1, const QInt &x2)
{
	for (int i = 0; i < 128; i++)
	{
		if ((x1.data[i / 32] & (1 << (32 - i % 32 - 1))) != (x2.data[i / 32] & (1 << (32 - i % 32 - 1))))
		return false;
	}
	return true;
}
bool operator !=(const QInt &x1, const QInt &x2)
{
	return !(x1 == x2);
}
bool operator>(const QInt &x1, const QInt &x2)
{
	bool sign1 = GetBit(x1, 0), sign2 = GetBit(x2, 0);
	//TH số dương và số âm
	if (sign1 == 0 && sign2 == 1) return true;
	//TH số âm và số dương
	if (sign1 == 1 && sign2 == 0) return false;
	//TH đều là số dương
	if (sign1 == 0)
	for (int i = 1; i < 128; i++)
	{
		if (GetBit(x1, i) != GetBit(x2,i))
		if (GetBit(x1, i) == 1) return true;
		else return false;
	}
	//TH đều là số âm
	else
	for (int i = 1; i < 128; i++)
	{
		if (((x1.data[i / 32] >> (31 - i % 32)) & 1) != ((x2.data[i / 32] >> (31 - i % 32)) & 1))
		{
			if (((x2.data[i / 32] >> (31 - i % 32)) & 1) == 0) return true;
			else return false;
		}
	}
	return false;
}
bool operator >=(const QInt &x1, const QInt &x2)
{
	return (x1 == x2 || x1 > x2);
}
bool operator <(const QInt &x1, const QInt &x2)
{
	return !(x1 >= x2);
}
bool operator <= (const QInt &x1, const QInt &x2)
{
	return !(x1>x2);
}

QInt operator*(const QInt &x1, const QInt &x2)
{
	bool Q0 = 0;
	QInt A;
	QInt M = x1;
	QInt Q = x2;
	int k = 127;
	while (k >= 0)
	{
		if (GetBit(Q, 127) == 1 && Q0 == 0)
		{
			A = A - M;
		}
		else if (GetBit(Q, 127) == 0 && Q0 == 1)
		{
			A = A + M;
		}
		//Shift right [A,Q,Q0]
		Q0 = GetBit(Q, 127);
		Q = Q >> 1;
		SetBit(Q, 0, GetBit(A, 127));
		A = A >> 1;
		SetBit(A, 0, GetBit(A, 1));
		k--;
	}
	return Q;
}

QInt operator / (QInt Q, QInt M)
{
	QInt A;
	if (GetBit(Q, 0) == 1 && GetBit(M,0) == 1)
	{
		string x1 = GetDecimal(Q), x2 = GetDecimal(M);
		x1.erase(0, 1);
		x2.erase(0, 1);
		ScanQInt(Q, x1);
		ScanQInt(M, x2);
		return (Q / M);
	}
	else if (GetBit(Q, 0) == 1)
	{
		string x = GetDecimal(Q);
		x.erase(0, 1);
		ScanQInt(Q, x);
		return ToTwoComplement(Q / M);
	}
	else if (GetBit(M, 0) == 1)
	{
		string x = GetDecimal(M);
		x.erase(0, 1);
		ScanQInt(M, x);
		return ToTwoComplement(Q / M);
	}
	for (int i = 0; i < 128; i++)
	{
		//Shift Left [A,Q]
		A = A << 1;
		SetBit(A, 127, GetBit(Q, 0));
		Q = Q << 1;

		A = A - M;
		if (GetBit(A, 0) == 1)
		{
			SetBit(Q, 127, 0);
			A = A + M;
		}
		else 
			SetBit(Q, 127, 1);
	}
	return Q;
}
QInt ToTwoComplement(QInt x)
{
	QInt result;
	QInt One;
	ScanQInt(One, "1");
	result = ~x + One;
	return result;
}