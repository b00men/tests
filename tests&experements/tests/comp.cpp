#include <string.h>
#include <iostream>
#include <fstream>
// #include <cstdlib>
// #include <stdio.h>
// #include <conio.h> // For not GNU compiler
// #include <cmath>
#include "comp.h"

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
	//arg.type=2;	// [0-2] Читать все залпом, по строкам, по словам (сразу после прочтения куска - выполнение mainwork).
	if (a>20){cout<<"Слишком много аргументов!\n"; return 1;} // Защита от дураков по кол-ву аргументов
	if (arguments(a,b,arg)) return 1; // Обрабатываем аргументы, если что - выходим
	arg.type=(((arg.options>>1)&1)?(0):(((arg.options>>2)&1)?(2):(1)));		// Взятие режима работы
	arg.type2=(((arg.options>>3)&1)?(0):(((arg.options>>4)&1)?(2):(1)));	// Взятие режима работы
	if (arg.options&1) debug(a,b,arg); // Отладка
	if (arg.target.empty()) {cout<<"Файл второго объекта не выбран. Попробуйте «"<<b[0]<<" --help» для справки.\n"; return 1;}
	return iomodule(arg); // Основная функция ввода-вывода.
}

int arguments(int a, char* c[10], struct arguments& arg)
{
	string somestring=c[0];
	int size;
	string help="Использование: «"+somestring+" [ключ] ... [файл] ... »\n"+
				"Сравнение частей двух текстовых объектов. По умолчанию работает по строкам для обоих объектов.\n"+
				"Вывод различий в виде: {номер сравнения}. Первый объект: \"{различие}\". Второй объект: \"{различие}\".\n\n"+
				"  -h,	--help	Показать эту справку и выйти\n"+
				"  -o [файл]	Записать результат в [файл]\n"+
				"  -i [файл]	Читать данные первого объекта из [файл]\n"+
				"  -I [файл]	Читать данные второго объекта из [файл]\n"+
				"  -a		Для первого объекта работать залпом\n"+
				"			(имеет больший приоритет чем 'w')\n"+
				"  -w		Для первого объекта работать по словам\n"+
				"  -A		Для второго объекта работать залпом\n"+
				"			(имеет больший приоритет чем 'W')\n"+
				"  -W		Для второго объекта работать по словам\n"+
				"  -d		Режим отладки\n";
	arg.options=0;
	
	if (findhelp(a,c,help)) return 1;

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
				case ('I'): arg.target=c[i+1]; break;
				case ('d'): arg.options=arg.options|(1<<0); break;
				case ('a'): arg.options=arg.options|(1<<1); break;
				case ('w'): arg.options=arg.options|(1<<2); break;
				case ('A'): arg.options=arg.options|(1<<3); break;
				case ('W'): arg.options=arg.options|(1<<4); break;
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
	cout<<"\nOptions\ndawAW---\n"<<vec2string(arg.options)<<"\nВходной файл #1: "<<arg.fin<<
		  "\nВыходной файл: "<<arg.fout<<"\nВходной файл #2: "<<arg.target<<"\nРежим работы #1: "<<
		  ((arg.type==0)?("Залпом"):((arg.type==2)?("По словам"):((arg.type==1)?("По строкам"):("ВНИМАНИЕ! Не допустимое значение!"))))
		  <<"\nРежим работы #2: "<<
		  ((arg.type2==0)?("Залпом"):((arg.type2==2)?("По словам"):((arg.type2==1)?("По строкам"):("ВНИМАНИЕ! Не допустимое значение!"))))
		  <<"\n\n"; // Debug опции, входной и выходной файлы
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
	arg.nostr=0;
	bool nowok,allok=true;
	char c,c2;
	ifstream in;
	ofstream out;
	ifstream in2;
	in.open( arg.fin.c_str() );
	in2.open( arg.target.c_str() );
	out.open( arg.fout.c_str() );
	while(true) {			// Цикл на каждую итерацию. См type.
		arg.nostr++;
		arg.main_string.clear();
		arg.main_string2.clear();
		while (true) {		// Посимвольное считывание первого объекта.
			(arg.fin.empty())?(c=cin.get()):(c=in.get());
			if (!(((c==32)&&(arg.type==2))||((c==10)&&(arg.type!=0))||(c==EOF))) arg.main_string+=c;
			else break; // Закончили заполнять массив. 32-пробел, 10-"\n"
		}
		while (true) {		// Посимвольное считывание второго объекта.
			c2=in2.get();
			if (!(((c2==32)&&(arg.type2==2))||((c2==10)&&(arg.type2!=0))||(c2==EOF))) arg.main_string2+=c2;
			else break; // Закончили заполнять массив. 32-пробел, 10-"\n"
		}
		if (((c==EOF)&&(arg.main_string.empty()))&&((c2==EOF)&&(arg.main_string2.empty()))) break;
										// Неожиданный конец. Например сразу или в начале строки.
		nowok=mainwork(arg);	// Здесь наша программа выполняет свои главные функции.
		allok &= nowok;
		if (!nowok) (arg.fout.empty())?(cout<<arg.main_string):(out<<arg.main_string);	// Вывод результатов.
		if (!nowok) (arg.fout.empty())?(cout<<'\n'):(out<<'\n');	// Вывод дополнительных '\n' при режимах "строка" или "слово"
		if ((c==EOF)&&(c2==EOF)) break;
	}
	if (allok) (arg.fout.empty())?(cout<<"Объекты идентичны\n"):(out<<"Объекты идентичны\n");
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

bool findhelp(int a, char* c[10], string help)
{
	string somestring;
	for (int i=1;i<a;i++)
	{
	somestring=c[i];
	if (somestring=="--help")
		{
		cout<<help;
		return true;
		}
	}
	return false;
}

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

int mainwork (struct arguments& arg)
{
	if (arg.main_string==arg.main_string2) return 1;
	string diff=itoa(arg.nostr,10);
	diff+=". Первый объект: \""+arg.main_string+"\". Второй объект: \""+arg.main_string2+"\".";
	arg.main_string=diff;
	return 0;
	
}