#include <string.h>
#include <iostream>
#include <fstream>
// #include <stdio.h>
// #include <conio.h> // For not GNU compiler
// #include <cmath>
using namespace std;

// Шаблон для реальных программ. Все по unix пути! (:
// Главная переменная - строка, которая может иметь пробелы. Жесткие тригерры опций в виде строки.
// Поддержка стандартных входов-выходов, проверенно на конвеере.
// Поддержка аргументов и их свободного использования. (Пр.: prog --help или prog -k -d ил prog -dk)
// Поддержка внешних файло для ввода вывода. Информация в хелпе.

int arguments(int a, string c[10], string& in, string& out, string& options)
{
	int size;
	string help="Использование: "+c[0]+" [ключ] ... [файл] ...\n~Описание этой программы~\n\n  -h,	--help	Показать эту справку и выйти\n  -o [файл]	Записать результат в [файл]\n  -i [файл]	Читать данные из [файл]\n  -k		Тестовый параметр\n  -d		Режим отладки\n";
	options="0000000000";
	
	for (int i=1;i<a;i++)		// --help
	{
	if (c[i]=="--help")
		{
		cout<<help;
		return 1;
		}
	}
		
	for (int i=1;i<a;i++)		// Взятие аргументов
	{
		if ((c[i].length()>1)&&(c[i][0]=='-'))
		{
			size=c[i].length();
			for (int j=1;j<size;j++)
			{
				switch(c[i][j])
				{
				case ('h'): cout<<help; return 1; break;
				case ('o'): out=c[i+1]; break;
				case ('i'): in=c[i+1]; break;
				case ('d'): options[0]='1'; break;
				case ('k'): options[1]='1'; break;
				default: cout<<c[0]<<": Неизвестный ключ  -- «"<<c[i][j]<<"»\nПопробуйте \'"<<c[0]<<" --help\' для получения более подробного описания.\n"; return 1; break;		
				}
			}
		}
	}
	
	return 0;
}

int read(string fin, string& main_string)
{
	if (fin=="")	getline( cin, main_string ); // Стандартный ввод. Берем строку (с пробелами) и ложим в главную переменную
	else 
		{
		ifstream in;
		in.open( fin.c_str() );
		getline( in, main_string ); // Чтение из файла
		in.close();
		}
	return 0;
}


int write(string fout, string& main_string)
{
	if (fout=="") cout<<main_string<<'\n'; // Стандартный вывод. Выводим нашу главную переменную.
	else 
		{
		ofstream out;
		out.open( fout.c_str() );
		out<<main_string<<'\n'; // Запись в файл
		out.close();
		}
	return 0;
}

int main(int a, char* b[10])
{
	string arg[10],fin,fout,options,main_string;	
	for (int i=0;i<a;arg[i]=b[i],i++);	// Все аргументы в строки

	if (arguments(a,arg,fin,fout,options)) return 1; // Обрабатываем аргументы, если что - выходим
	
	if (options[0]=='1') // Debug prework
	{
	cout<<"Number of arguments: "<<(a-1)<<"\n this is: \n"; // Аргументы
	for (int i=1;i<a;cout<<arg[i]<<'\n',i++);
	cout<<"\nOptions\ndk--------\n"<<options<<"\nВходной файл: "<<fin<<"\nВыходной файл: "<<fout<<"\n\n"; // Debug опции, входной и выходной файлы
	cout<<"Вывести переменные среды [Y/n]? ";
	char debugquest;
	scanf("%c",&debugquest);
	if ((debugquest=='y')||(debugquest=='Y'))
	for (int i=a;i<a+47;printf("%s",b[i]),printf("%c",'\n'),i++); // Вывести входные данные и всякие вкусняшки окружающей среды
	cout<<'\n';
	scanf("%c",&debugquest); 
	}
	
	// Опция задаеться как n-й символ строки options равынй или не равный символу "1"
	
	read(fin,main_string);
	if (options[0]=='1') cout<<"\nГлавная переменная после входа: "<<main_string<<'\n'; // Debug input
	
	
	// Здесь наша программа выполняет свои главные функции. Пишем это в отдельную функцию, переменные string option, string& main_string.
	
	
	if (options[0]=='1') cout<<"\nГлавная переменная после работы, но до выхода: "<<main_string<<"\n\n"; // Debug output
	write(fout,main_string);
	return 0;
}
