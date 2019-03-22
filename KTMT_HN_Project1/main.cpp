#include"QInt.h"
#include"QFloat.h"
int main()
{

//	bool bit[5] = { 1, 0, 0, 1, 1 };
	//cout << "Nhap bit: ";
	//bool *bit = NULL;
	//ScanBit(bit);
	//cout << "Bin To Dec :" << GetDecimal(BinToDec(bit)) << endl;
	//cout << "Bin to Hex :" << BinToHex(bit) << endl;
	cout << "nhap so: ";
	QInt q1, q2;
	ScanQInt(q1);
	ScanQInt(q2);
//	QInt q3 = q1 + q2;
	cout << "q1 + q2 = ";
	PrintQInt(q1 + q2);
	cout << endl;
	cout << "q1 - q2 = ";
	PrintQInt(q1 - q2);
	cout << endl;
	cout << "q1 * q2 = ";
	PrintQInt(q1 * q2);
	cout << endl;
	cout << "q1 / q2 = ";
	PrintQInt(q1 / q2);
	cout << endl;
	//cout << "q1 * q2 = ";
	//PrintQInt(q1*q2);
	//cout << endl;
	cout << "q1 << 1 : ";
	PrintQInt(q1 << 1);
	cout << endl;
	cout << "q1 >> 1 : ";
	PrintQInt(q1 >> 1);
	cout << endl;
	cout << "q1 | q2 : ";
	PrintQInt(q1 | q2);
	cout << endl;
	cout << "q1 ^ 1 : ";
	PrintQInt(q1 ^ q2);
	cout << endl;
	cout << "q1 & q2 : ";
	cout << endl;
	cout << "~q1 : ";
	PrintQInt(~q1);
	cout << endl;
	cout << "q1 == q2 : " << ((q1 == q2) ? "true\n" : "false\n");
	cout << "q1 != q2 : " << ((q1 != q2) ? "true\n" : "false\n");
	cout << "q1 > q2 : " << ((q1 > q2) ? "true\n" : "false\n");
	cout << "q1 < q2 : " << ((q1 < q2) ? "true\n" : "false\n");
	cout << "q1 >= q2 : " << ((q1 >= q2) ? "true\n" : "false\n");
	cout << "q1 <= q2 : " << ((q1 <= q2) ? "true\n" : "false\n");

	QInt q3;
	cout << "nhap nhi phan: ";
	ScanBinQInt(q3);
	cout << "vua nhap: ";
	PrintBinQInt(q3);
//	PrintQInt(q1);

	//QFloat qf1;
	//qf1.ScanQFloat();
	////qf1.PrintQFloat();
	////qf1.BinToDec();
	//cout << endl << qf1.GetDecimal();
	//cout << endl << "done" << endl;
	
	//QInt a, b;
	//cout << "Nhap a : ";
	//ScanQInt(a);
	//cout << "Nhap b : ";
	//ScanQInt(b);

	//QInt c = a + b;
	//cout << "c = ";
	//PrintQInt(c);

}