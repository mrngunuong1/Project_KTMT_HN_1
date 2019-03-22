#include "QInt.h"


void ONbit(uint32_t &x, int i)
{
	x = x | (1 << (32 - 1 - i));
}
QInt::QInt()
{
	this->a[0] = this->a[1] = this->a[2] = this->a[3] = 0;
}
void QInt::intialize()
{
	this->a[0] = this->a[1] = this->a[2] = this->a[3] = 0;
}
bool QInt::isZERO() const
{
	for (int i = sizeQInt / sizeof(uint32_t) - 1; i >= 0; i--)
	{
		if (this->a[i] != 0) return false;
	}
	return true;
}
bool QInt::isNeg() const
{
	if (((this->a[0] >> 31) & 1) == 1)
	{
		return true;
	}
	return false;
}
QInt::QInt(string &strBIN)
{
	this->intialize();
	for (int i = strBIN.length() - 1; i >= 0; i--)
	{
		if (strBIN[i] == '1')
		{
			ONbit(a[sizeQInt / sizeof(uint32_t) - 1 - i / 32], (8 * sizeof(uint32_t) + i - strBIN.length()) % 32);
		}
	}
}
QInt QInt:: operator +(QInt b)
{
	QInt res = *this;
	QInt carry;
	while (!(b.isZERO()))// hết (nhớ)
	{
		//carry là những bit cùng là 1 giữa 2 số (biến nhớ cột i)
		carry = res & b;

		//tổng các bit khác nhau của hai số (0 + 1 = 1 , 1+1=0 (nhớ 1 da bỏ vao carry ở trên)).
		res = res ^ b;

		//di chuyển tới cột i+1 để cộng dồn vào res
		b = carry << 1;

	}

	return res;
}
QInt QInt::operator -( QInt b)
{
	return (*this + b.toTWOsComplement());
}
QInt QInt::operator *(QInt b)
{
	QInt res;
	QInt temp = *this;
	QInt One;
	ONbit(One.a[sizeQInt / sizeof(uint32_t) - 1], 31); //Số 1
	bool Neg = false;

	if ((temp.isNeg() && !b.isNeg()) || (!temp.isNeg() && b.isNeg()))//Nếu 2 số trái dấu.
	{
		Neg = true;
	}
	//Nếu âm thì chuyển về dạng số dương
	if (b.isNeg())
	{
		b = ~(b - One);
	}
	if (temp.isNeg())
	{
		temp = ~(temp - One);
	}

	//Nhân hai số dương.
	while (!(b.isNeg() || b.isZERO()))
	{
		if (((b & One) - One).isZERO()) //(ktra trạng thái bit cuối)
		{
			res = res + temp;
		}

		temp = temp << 1; // tuong ung bit i hang i;
		b = b >> 1; //tuong ung bit i hang i .
	}

	//Nếu như 2 số trái dấu.
	if (Neg == true)
	{
		res = ~res + One; //Chuyển res về dạng bù 2.
	}

	return res;
}
QInt QInt::operator /(QInt b)
{
	QInt remainder;
	if (this->isZERO() || b.isZERO())
	{
		return remainder;
	}
	QInt One;
	ONbit(One.a[sizeQInt / sizeof(uint32_t) - 1], 31); //Số 1
	if ((b - One).isZERO())
	{
		return *this;
	}
	QInt quotient = *this;
	int k = sizeQInt*8;
	bool Neg= false;

	if ((quotient.isNeg() && !b.isNeg()) || (!quotient.isNeg() && b.isNeg()))//Nếu 2 số trái dấu.
	{
		Neg = true;
	}

	if (b.isNeg())
	{
		b = ~(b - One); //Nếu âm thì chuyển về dạng số dương
	}
	if (quotient.isNeg())
	{
		quotient = ~(quotient - One); //Nếu âm thì chuyển về dạng số dương
	}
	QInt divisor = b;
	while (k > 0)
	{
		remainder = remainder << 1;
		remainder.a[3] = remainder.a[3] | ((quotient.a[0] >> 31) & 1);
		quotient = quotient << 1;
		remainder = remainder - divisor;
		if (remainder.isNeg())
		{
			remainder = remainder + divisor;
		}
		else
		{
			quotient = quotient | One;
		}
		--k;
	}
	if (Neg)
	{
		quotient = ~quotient + One;
	}
	return quotient;
}
QInt& QInt::operator ~ ()
{
	for (int i = 0; i < sizeQInt / sizeof(uint32_t); i++)
	{
		this->a[i] = ~this->a[i];
	}

	return *this;
}
QInt QInt:: operator & (const QInt &b)
{
	QInt res;
	for (int i = 0; i < sizeQInt / sizeof(uint32_t); i++)
	{
		res.a[i] = this->a[i] & b.a[i];
	}
	return res;
}
QInt QInt::operator | (const QInt &b)
{
	QInt res;
	for (int i = 0; i < sizeQInt / sizeof(uint32_t); i++)
	{
		res.a[i] = this->a[i] | b.a[i];
	}
	return res;
}
QInt QInt::operator ^ (const QInt &b)
{
	QInt res;
	for (int i = 0; i < sizeQInt / sizeof(uint32_t); i++)
	{
		res.a[i] = this->a[i] ^ b.a[i];
	}
	return res;
}
QInt QInt::operator<<(const int & n)
{
	QInt res;

	for (int i = 0; i < sizeQInt / sizeof(uint32_t); i++)
	{
		res.a[i] = this->a[i] << n;
	}

	for (int i = 0; i < sizeQInt / sizeof(uint32_t) - 1; i++)
	{
		res.a[i] = res.a[i] | (this->a[i + 1] >> 31 - n);
	}
	return res;
}
QInt QInt::operator >> (const int & n)
{
	QInt res;

	for (int i = 0; i < sizeQInt / sizeof(uint32_t); i++)
	{
		res.a[i] = this->a[i] >> n;
	}

	for (int i = sizeQInt / sizeof(uint32_t) - 1; i > 0; i--)
	{
		res.a[i] = res.a[i] | (this->a[i - 1] << 31 - n);
	}

	return res;
}
QInt& QInt::operator = (const QInt & b)
{
	if (this != &b)
	{
		for (int i = 0; i <sizeQInt / sizeof(uint32_t); i++)
		{
			this->a[i] = b.a[i];
		}
	}

	return *this;
}

QInt QInt::toTWOsComplement()
{
	QInt One;
	ONbit(One.a[sizeQInt / sizeof(uint32_t) - 1], 31);
	return  (~(*this) + One);
}
string QInt::toBinStr()
{
	string res;
	for (int i = 0; i < sizeQInt / sizeof(uint32_t); i++)
	{
		for (int j = 0; j < 8 * sizeof(uint32_t); j++)
		{
			res.push_back(((this->a[i] >> (8 * sizeof(uint32_t) - 1 - j)) & 1) + '0');
		}
	}
	return res;
}
QInt::~QInt()
{
}
////
string strDECdivTWO(const string &strDEC)
{
	string res;
	int temp = 0;

	for (int i = 0; i < strDEC.size(); i++)
	{
		temp = temp * 10 + (strDEC[i] - '0'); // - '0' ra so

		if (i > 0 || (i == 0 && temp >= 2))
		{
			res.push_back((temp / 2) + '0');// + '0' ra ki tu
		}

		temp = temp % 2;
	}
	return res;
}
string strDECtoBIN(const string & strDEC)
{
	string res;
	bool Neg = false;
	string temp = strDEC;
	if (temp[0] == '-') //số âm.
	{
		temp.erase(temp.begin());
		Neg = true;
	}
	do
	{
		res.push_back(((temp[temp.length() - 1] - '0') % 2) + '0');
		temp = strDECdivTWO(temp);
	} while (temp != "");
	reverse(res.begin(), res.end());
	//Nếu là chuỗi ban đầu là số âm.
	if (Neg == true)
	{
		QInt temp(res);
		res = (temp.toTWOsComplement()).toBinStr();
	}
	return res;

}