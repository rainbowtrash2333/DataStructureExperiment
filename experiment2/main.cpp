#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <regex>
#include <math.h>
#include <sstream>  
#include "LinkList.h"
using namespace std;

typedef LinkList Polynomial; //����һԪϡ�����ʽ����Polynomial 

class  PolynomialHelper {
public:
	double coef;
	double expn;
	Polynomial* pol;
	PolynomialHelper(Polynomial* pol) {
		this->coef = coef;
		this->expn = expn;
		this->pol = pol;
	}
	~PolynomialHelper() {}
	string input;

	//����һ������ʽ���ж������Ƿ�Ϸ���������ֵ
	bool  inputPolynomial() {
		std::cout << "����һ������ʽ(��ʽ�磺1+x+3X^2-5X^15)" << endl;
		cin >> this->input;
		return  (regex_match(input, regex("((\\+|-)?[0-9.]*((x|X)(?![0-9.])(\\^[0-9]+)?)?)+")));
	};
	
	//��ȡ����ʽ��ϵ����ָ��
	void  getPolynomial() {
		while (!inputPolynomial()) cout << "�����ʽ����" << endl;
		struct  Flag
		{
			bool isPositive = true;
			bool isPoint = false;
			bool isExpn = false;
			bool isX = false;
		}flag;//״̬��

		char *c = (char*)this->input.c_str();
		for (unsigned int i = 0; i < strlen(c); ++i) {

			//��ȡ����
			if (c[i] <= '9' && c[i] >= '0') {

				//�м����
				double foo = c[i] - '0';
				int bar = 1;

				if (flag.isExpn) {
					this->expn = this->expn * 10.0 + foo;
				}
				else {
					if (flag.isPoint) {
						this->coef += pow(0.1, bar++)*foo;
					}
					else {
						this->coef = this->coef * 10.0 + foo;
					}
				}
			}

			else if (c[i] == '.') {
				flag.isPoint = true;
			}

			else if (c[i] == 'X' || c[i] == 'x') {

				if (i == 0) {
					this->coef = 1;
				}

				else if ((c[i - 1] == '-') || (c[i - 1] == '+')) {
					this->coef = 1;
				}

				if (c[i + 1] != '^') {
					this->expn = 1;
				}
				flag.isX = true;
			}

			else if (c[i] == '^') {
				flag.isExpn = true;
			}

			else if (c[i] == '+'&& i != 0) {
				if (!flag.isPositive) {
					this->coef *= -1;
					flag.isPositive = true;
				};

				flag.isPoint = false;
				flag.isExpn = false;
				flag.isX = false;
				AddNode(this->pol, this->coef, this->expn);
				this->coef = 0;
				this->expn = 0;
			}

			else if (c[i] == '-') {
				if (i != 0) {
					if (!flag.isPositive) {
						this->coef *= -1;
					};
					flag.isPoint = false;
					flag.isExpn = false;
					flag.isX = false;
					AddNode(this->pol, this->coef, this->expn);
					this->coef = 0;
					this->expn = 0;
				}
				flag.isPositive = false;
			}

			//���һ��Ԫ�غ�д��һ���ڵ�
			if (i == strlen(c) - 1) {
				if (!flag.isPositive) {
					this->coef *= -1;
				}
				AddNode(this->pol, this->coef, this->expn);
			}

			//	debug
					//cout << "input " << input << endl;
					//cout << "input.length " << strlen(c) << endl;
					//cout << "c[i] " << c[i] << endl;
					//cout << "isPositive "<<flag.isPositive << endl;
					//cout << "isPoint " << flag.isPoint <<endl;
					//cout << "isExpn " << flag.isExpn << endl;
					//cout << "isX " << flag.isX << endl;
					//cout << "coef " << this->coef << endl;
					//cout << "expn " << this->expn << endl;
					//system("pause");

		}
	}
};

void  printPolynomial(Polynomial pol) {
	LinkListBubbleSort(pol);
	Link* index = pol.head;
	string coef, expn, symbol;
	stringstream ss;
	if (index->next == NULL)
		cout << "0" << endl;
	else {
		while (index->next != NULL) {

			if (index->coef > 0 && index != pol.head) symbol = "+";
			else symbol = "";

			if (index->coef == 1 && index->expn != 0) ss << "";
			else if (index->coef == -1 && index->expn != 0) ss << "-";
			else ss << index->coef;


			ss >> coef;
			ss.clear();
			ss.str("");

			if (index->expn == 1) ss << "X";
			else if (index->expn == 0) ss << "";
			else
				ss << "X^" << index->expn;


			ss >> expn;
			ss.clear();
			ss.str("");

			cout << symbol << coef << expn;

			coef = expn = "";
			index = index->next;
		}
	}
	cout << endl;
}

void toDo() {
	int input;
	cout << "���� 1, 2,  ѡ���Ѷ�A B : ";

	cin >> input;
	if (input == 1) {
		Polynomial pol1;
		InitList(pol1);
		PolynomialHelper Pol1help(&pol1);
		Pol1help.getPolynomial();
		cout << "��������ǣ�" << endl;
		printPolynomial(pol1);

	}
	else if (input == 2) {
		char symbol;
		Polynomial pol1;
		InitList(pol1);

		PolynomialHelper Pol1help(&pol1);
		Pol1help.getPolynomial();
		cout << "�������(+-*/)(����Ϊ��): ";
		cin >> symbol;

		Polynomial pol2;
		InitList(pol2);
		if (symbol != '/') {
			PolynomialHelper Po21help(&pol2);
			Po21help.getPolynomial();

		}
		switch (symbol)
		{
		case '+':
			printPolynomial(AddPolyn(pol1, pol2));
			break;
		case '-':
			printPolynomial(SubPolyn(pol1, pol2));
			break;
		case'*':
			printPolynomial(MultiplyPolyn(pol1, pol2));
			break;

		case '/':
			printPolynomial(Derivation(pol1));

			break;

		default:
			cout << "�������" << endl;
			exit(1);
			break;
		}
	}

	else
		cout << "�������" << endl;
	cout << "ллʹ��" << endl;
	
	system("pause");

}

int main() {
	toDo();
	return 0;
}

