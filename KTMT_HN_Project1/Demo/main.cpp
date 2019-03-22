#include"QInt.h"

int main()
{
	QInt *q1 = new QInt();

	BigInt *b1 = new BigInt("1001");

	cout << b1->getBigInt() << " /2 = " << q1->DivideStringForTwo(b1->getBigInt()) << endl;
	cout << q1->DecToBin(*b1) << endl;
}