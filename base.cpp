#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
// #include <stdio.h>
// #include <conio.h> // For not GNU compiler
// #include <cmath>
#include "base.h"

// -----Свойства шаблона-----
// Главная программа в отдельной финкции mainwork.
// Главная переменная - строка, которая может иметь символы с любыми кодами (кроме 3 и 4).
// Жесткие тригерры опций в виде бинарного вектора.
// Коды возврата: 0 - все хорошо,
// 1 - "легкая" неудача (ошибка в модуле оболочки или кол-во аргументов), 
// 2 - "тяжелая" неудача (ошибка в главной программе).
// Поддержка стандартных входов-выходов (конвеер тоже).
// Поддержка внешних файлов для ввода вывода.
// Поддержка аргументов и их свободного использования. (Пр.: prog --help или prog -k -d или prog -dk)
// Разные способы работы с входными данными. (см. строку №25)

using namespace std;
int main(int a, char* b[10])
{
	arg.type=1;	// [0-2] Читать все залпом, по строкам, по словам (сразу после прочтения куска - выполнение mainwork).
	if (a>20){cout<<"Слишком много аргументов!\n"; return 1;} // Защита от дураков по кол-ву аргументов
	if (arguments(a,b,arg)) return 1; // Обрабатываем аргументы, если что - выходим
	if (arg.options&1) debug(a,b,arg); // Отладка
	if (arg.target.empty()) {cout<<"Целевой файл не выбран. Попробуйте «"<<b[0]<<" --help» для справки.\n"; return 1;}
	return iomodule(arg); // Основная функция ввода-вывода.
}

int arguments(int a, char* c[10], struct arguments& arg)
{
	string somestring=c[0];
	int size;
	string help="Использование: «"+somestring+" [ключ] ... [файл] ... »\n"+
				"Оболочка тестирования приложений.\n\n"+
				"  -h,	--help	Показать эту справку и выйти\n"+
				"  -o [файл]	Записать результат в [файл]\n"+
				"  -i [файл]	Читать данные из [файл]\n"+
				"  -t [файл]	Провести тест над [файл]\n"+
				"  -k		Тестовый параметр\n"+
				"  -d		Режим отладки\n";
	arg.options=0;
	
	for (int i=1;i<a;i++)		// --help
	{
	somestring=c[i];
	if (somestring=="--help")
		{
		cout<<help;
		return 1;
		}
	}
		
	for (int i=1;i<a;i++)		// Взятие аргументов
	{
	somestring=c[i];
		if ((somestring!="-")&&(c[i][0]=='-'))
		{
			size=somestring.length();
			for (int j=1;j<size;j++)
			{
				switch(c[i][j])
				{
				case ('h'): cout<<help; return 1; break;
				case ('o'): arg.fout=c[i+1]; break;
				case ('i'): arg.fin=c[i+1]; break;
				case ('t'): arg.target=c[i+1]; break;
				case ('d'): arg.options=arg.options|(1<<0); break;
				case ('k'): arg.options=arg.options|(1<<1); break;
				default: cout<<c[0]<<": Неизвестный ключ  -- «"<<c[i][j]<<"»\n"<<
									 "Попробуйте \'"<<c[0]<<" --help\' для получения более подробного описания.\n";
				return 1; break;		
				}
			}
		}
	}
	
	return 0;
}

int debug(int a, char* b[10], struct arguments& arg)
{
	string somestring;
	cout<<"Количество блоков аргументов: "<<(a-1)<<"\nЭто: \n"; // Аргументы
	for (int i=1;i<a;somestring=b[i],cout<<somestring<<'\n',i++);
	cout<<"\nOptions\ndk------\n"<<vec2string(arg.options)<<"\nВходной файл: "<<arg.fin<<
		  "\nВыходной файл: "<<arg.fout<<"\nЦелевой файл: "<<arg.target<<"\n\n"; // Debug опции, входной и выходной файлы
	cout<<"Вывести переменные среды [Y/n]? ";
	char debugquest;
	scanf("%c",&debugquest);
	if ((debugquest=='y')||(debugquest=='Y'))
	for (int i=a;i<a+47;printf("%s",b[i]),printf("%c",'\n'),i++); // Вывести входные данные и всякие вкусняшки окружающей среды
	cout<<'\n';
	scanf("%c",&debugquest);
	return 0;
}

int iomodule(struct arguments& arg)
{
	char c;
	ifstream in;
	in.open( arg.fin.c_str() );
	ofstream out;
	out.open( arg.fout.c_str() );
	while(true) {			// Цикл на каждую итерацию. См type.
		arg.main_string.clear();
		while (true) {		// Посимвольное считывание.
			(arg.fin.empty())?(c=cin.get()):(c=in.get());
			if (!(((c==32)&&(arg.type==2))||((c==10)&&(arg.type!=0))||(c==EOF))) arg.main_string+=c;
			else break; // Закончили заполнять массив. 32-пробел, 10-"\n"
		}
		if ((c==EOF)&&(arg.main_string.empty())) break;		// Неожиданный конец. Например сразу или в начале строки.
		if (mainwork(arg)) return 2;	// Здесь наша программа выполняет свои главные функции.
		(arg.fout.empty())?(cout<<arg.main_string):(out<<arg.main_string);	// Вывод результатов.
		if (arg.type!=0) (arg.fout.empty())?(cout<<'\n'):(out<<'\n');	// Вывод дополнительных '\n' при режимах "строка" или "слово"
		if (c==EOF) break;
	}

	in.close();
	out.close();
	return 0;
}

string vec2string(unsigned char a)
{
	char outchar[8];
	for(int i=7;i>-1;i--)
	{
		if((a>>i)&1) outchar[i]='1';
		else outchar[i]='0';
	}
	return outchar;
}

int mainwork (struct arguments& arg){

	string command = arg.target + ' ' + arg.main_string;
	system(command.c_str());
	return 0;
}