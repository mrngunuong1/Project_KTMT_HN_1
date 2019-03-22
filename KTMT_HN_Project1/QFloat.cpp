#include"QFloat.h"
#include"QInt.h"
QFloat::QFloat()
{
	data[0] = data[1] = data[2] = data[3] = 0;
}
QFloat::QFloat(string s)
{
	data[0] = data[1] = data[2] = data[3] = 0;

	string pre_comma;
	string post_comma;
	int l = s.length();
	int i = 0;
	if (s[0] == '-')
	{
		SetBit(0, 1);
		i++;
	}
	for (i; i < l; i++)
	{
		if (s[i] != '.') pre_comma += s[i];
		else break;
	}
	for (i = i + 1; i < l; i++)
	{
		post_comma += s[i];
	}
	string pre_bin = PreComma_to_Binary(pre_comma), post_bin = PostComma_to_Binary(pre_comma, post_comma);
	int exp = CalcExponent(pre_bin, post_bin);
	WriteToExponent(exp);
	WriteToFraction(exp, pre_bin, post_bin);
}
void QFloat::ScanQFloat()
{
	string s;
	fflush(stdin);
	getline(cin, s);
	*this = QFloat(s);
}
void QFloat::ScanBinQFloat(string s)
{
	int l = s.length();
	int i = 0;
	for (i; i < l; i++)
	{
		this->SetBit(i, s[i] - '0');
	}
	for (i; i < l; i++)
	{
		this->SetBit(i, 0);
	}
}
void QFloat::SetBit(char pos, bool bit)
{
	if (bit)
	{
		data[pos / 32] = data[pos / 32] | (1 << (32 - pos % 32 - 1));
	}
}
bool QFloat::GetBit(char pos)
{
	return (data[pos / 32] >> (32 - pos % 32 - 1)) & 1;
}
string QFloat::MultiStringForTwo(string s)
{
	int temp = false;
	string result;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		if (temp != 0)
		{
			temp = 2 * (s[i] - '0') + 1;
			result = char((temp % 10) + '0') + result;
			if (temp / 10 != 0)
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
//	while (result[0] == '0' && result.length() > 1) result.erase(0, 1);
	return result;
}
string QFloat::DivideStringForTwo(string s)
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
string QFloat::PreComma_to_Binary(string s)
{
	string bin;
	while (s != "0")
	{
		if ((s[s.length() - 1] - '0') % 2 == 0) bin = '0' + bin;
		else bin = '1' + bin;
		s = this->DivideStringForTwo(s);
	}
	if (bin == "") bin = "0";
	return bin;
}
bool isOne(string s)
{
	if (s.length() == 1) return false;
	if (s[0] == '1')
	{
		for (int i = 1; i< s.length(); i++)
		if (s[i] != '0') return false;
	}
	else return false;
	return true;
}
string QFloat::PostComma_to_Binary(string pre, string s)
{
	string bin;
	int i = 0;
	int exp = 0;
	exp = CalcExponent(pre) - 127;
	if (exp == 0)
	{
		while (true)
		{
			if (s[0] - '0' >=5) {
				s = MultiStringForTwo(s);
				s.erase(0, 1);
				break;
			}
			else  s = MultiStringForTwo(s);
		}
	}
	int ll= 0;
	while (i < number_bits_of_fraction - exp)
	{
		if (isOne(s) && ll < s.length()) {
			bin += '1';
			break;
		}
		else
		{
			ll = s.length();
			if (s[0] - '0' >= 5) {
				bin += '1';
				s = MultiStringForTwo(s);
				s.erase(0, 1);
			}
			else {
				bin += '0';
				s = MultiStringForTwo(s);
			}
		}
		i++;
	}
	return bin;
}
int QFloat::CalcExponent(string pre, string post)
{
	int l1 = pre.length(), l2 = post.length();
	for (int i = 0; i < l1; i++)
	{
		if (pre[i] == '1') return 127 + (l1 - i - 1);
	}
	for (int i = 0; i < l2; i++)
	{
		if (post[i] == '1') return 127 - i -1;
	}
	return 0;
}
int QFloat::CalcExponent(string pre)
{
	int l1 = pre.length();
	for (int i = 0; i < l1; i++)
	{
		if (pre[i] == '1') return 127 + (l1 - i - 1);
	}
	return 0;
}
void QFloat::WriteToExponent(int exp)
{
	int i = number_bits_of_sign_exponent - 1;
	while (i>=0)
	{
		this->SetBit(i, exp % 2);
		exp = exp / 2;
		i--;
	}
}
void QFloat::WriteToFraction(int exp, string pre, string post)
{
	int k = exp - 127, i = number_bits_of_sign_exponent;
	int l1 = pre.length(), l2 = post.length();
	if (k<0)
	{
		k = -k;
		for (i; i < 128; i++)
		{
			this->SetBit(i , post[k++] - '0');
		}
	}
	else
	{
		while (k > 0)
		{
			this->SetBit(i, pre[l1 - k] - '0');
			i++;
			k--;
		}
		k = 0;
		for (i; i < 128; i++)
		{
			this->SetBit(i, post[k++] - '0');
		}
	}
}
void QFloat::PrintQFloat()
{
	for (int i = 0; i < 128; i++)
	{
		cout << GetBit(i);
		if (i == 15) cout << " ";
	}
}
bool QFloat::isZero()
{
	for (int i = 0; i < 128; i++)
	{
		if (GetBit(i) == 1) return false;
	}
	return true;
}
string QFloat::Decimal()
{
	if (this->isZero()) return "0.0";
	string result;
	if (GetBit(0) == 1) result += '-';
	int exp = 0;
	for (int i = 1; i < number_bits_of_sign_exponent; i++)
	{
		exp += GetBit(i) << (number_bits_of_sign_exponent - i - 1);
	}
	exp = exp - 127;
	string pre_comma;
	string post_comma;

	if (exp >0) pre_comma = "1";
	if (exp < 0)
	{
		post_comma.insert(0, 1, '1');
		post_comma.insert(0, -exp - 1, '0');
	}
	int i = number_bits_of_sign_exponent;
	for (i; i < number_bits_of_sign_exponent + exp; i++)
	{
		pre_comma += GetBit(i) + '0';
	}
	for (i; i < 128; i++)
	{
		post_comma += GetBit(i) + '0';
	}

	QInt pre_num, post_num;
	ScanBinQInt(pre_num, pre_comma);
	string pre = GetDecimal(pre_num);
	
	int nonsense_bits = 0;
	for (int i = post_comma.length() - 1; i >= 0; i--)
	{
		if (post_comma[i] == '1') break;
		else nonsense_bits++;
	}

	int  k = 1;
	int max;
	ScanQInt(post_num, "1");
	QInt num5, num10;
	ScanQInt(num5, "5");
	ScanQInt(num10, "10");
	if (number_bits_of_fraction - nonsense_bits - exp> 25)
	{
		max = 25;
	}
	else max = number_bits_of_fraction - nonsense_bits - exp;
	for (int i = 0; i < max; i++)
	{
		post_num = post_num * num10;
		if (post_comma[i] == '1')
		{
			QInt temp;
			ScanQInt(temp, "1");
			for (int j = 1; j <= k; j++)
				temp = temp *num5;
			post_num = post_num + temp;
			string s = GetDecimal(post_num);
		}
		k++;
	}
	string s = GetDecimal(post_num);
	result += pre + "." + GetDecimal(post_num).erase(0,1);
	return result;
}
QFloat QFloat::BinToDec(bool *bit)
{
	for (int i = 0; i < 128; i++)
		this->SetBit(i, bit[i]);
	return *this;
}