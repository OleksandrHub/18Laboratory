#include <iostream>
#include <stdlib.h>
#include "function.h"
using namespace std;


int main(){
	string input;
    system("chcp 1251 > nul");
	clear();
	cout << " \t \t \t МІНІСТЕРСТВО ОСВІТИ І НАУКИ " << endl;
	cout << " \t \t ТЕРНОПІЛЬСЬКИЙ НАЦІОНАЛЬНИЙ ТЕХНІЧНИЙ " << endl;
	cout << " \t \t \t УНІВЕРСИТЕТ ІМ. І. ПУЛЮЯ" << endl;
    cout << "\n \n" << endl;
	cout << "\t  \t \t  Лабораторна робота на тему:" << endl;
	cout << "\t \t \t  'База даних учнів класу'" << endl;
	cout << "\n \n \n \n \n" << endl;
	cout << "\t \t \t \t \t \t \t  Підготував студент " << endl;
	cout << "\t \t \t \t \t \t \t  групи СН-11" << endl;
	cout << "\t \t \t \t \t \t \t  Кліщ О. В." << endl;
	cout << "\t \t \t \t \t \t \t  Версія: 1.2025.05.04" << endl;
	cout << "Натисніть Enter, щоб продовжити ";
	getline(cin, input);
	menu();
	return 0;
}