#include "pch.h"
#include <iostream>
#include <sstream>
#include <string>
#include "DataStructure.h"
using namespace std;


#define codeB "tsaedsae";
#define codeA "sae";

// 单字符转字符串
string charToString(char c) {
	string str;
	stringstream stream;
	stream << c;
	str = stream.str();
	return str;
}

Char_Queue doit(Char_Stack stack) {
	Char_Queue queue(1024);
	while (!stack.isEmpty())
	{
		char e;
	
		stack.pop(e);
		cout << "doit.e=" << e << endl;
		queue.enQueue(stack.getBase());
		queue.enQueue(e);
	}
	return queue;
}

Char_Queue change(Char_Queue &input ) {
	Char_Stack stack(2048);
	for (int i = 0; i < input.getSize(); i++)
	{
		char e;
		input.deQueue(e);
		cout << "change.e=" << e << endl;
		if(e=='('){
			
			Char_Queue bar = change(input);
			for (int j = 0; j < bar.getSize(); ++j) {
				char ee;
				bar.deQueue(ee);
				cout << "change.ee=" << ee << endl;
				stack.push(ee);
			}
		}
		else if (e == ')') {
			return doit(stack);
		}
		else {
			stack.push(e);
		}
	}
	char temp;
	for (int i = 0; i < stack.getSize(); i++) {
		stack.pop(temp);
		stack.push(temp);
	}
	
	return doit(stack);
}


// 解码
string decode(string input) {

	string output;
	Char_Queue queue(2048);
	int len = input.size();

	for (int i = 0; i < len; i++)
	{
		if (input[i] == 'A') {
			string s = codeA;
			//queue.enQueue(s);
		}
		else if (input[i] == 'B') {
			string s = codeB;
			//queue.enQueue(s);
		}
		else if (input[i] == '(') {
			int j = 0;
			while (input[i + j + 1] != ')') ++j;

			Char_Stack stack(j);
			while (input[++i] != ')')
			{
				stack.push(input[i]);
			}

			for (int i = 0; i < j; i++)
			{
				char e;
				stack.pop(e);
				if (!stack.isEmpty()) {
					output += charToString(stack.getBase()) + charToString(e);
				}
				else {
					output += charToString(e);
				}

			}
		}
		else
			output += input[i];
	}
	return output;
}


// 用户输入
string userInput() {
	string input = "";
	cout << "输入魔王语言（默认为 “B(ehnxgz)B”） ";
	getline(cin, input);
	if (input == "") {
		input = "B(ehnxgz)B";
	}

	return input;
}

// 是否结束
bool isContinue() {
	fflush(stdin);
	cout << "输入 Ctrl-Z 结束";
	char c;
	c = getchar();
	cout << endl;
	fflush(stdin);
	return (c != EOF);
}

// 翻译
string translate(string s) {
	string put = "";
	int size = s.size();
	for (int i = 0; i < size; ++i) {
		switch (s[i])
		{
		case 't':
			put += "天";
			break;
		case 'd':
			put += "地";
			break;
		case 's':
			put += "上";
			break;
		case 'a':
			put += "一只";
			break;
		case 'e':
			put += "鹅";
			break;
		case 'z':
			put += "追";
			break;
		case 'g':
			put += "赶";
			break;
		case 'x':
			put += "下";
			break;
		case 'n':
			put += "蛋";
			break;
		case 'h':
			put += "恨";
			break;
		default:
			put += "口";
			break;
		}
	}
	return put;
}


int main() {
	string s = "B(ehnxgz)B";
	cout << "s:" << s << endl;
	Char_Queue queue(1024);
	for (int i = 0; i < (int)s.size(); i++)
	{
		queue.enQueue(s[i]);
	}
	Char_Queue out = change(queue);
	while (!out.isEmpty()) {
		char c;
		out.deQueue(c);
		cout << c;
	}

}