#include <string.h>
#include <iostream>
#include <fstream>
// #include <stdio.h>
// #include <conio.h> // For not GNU compiler
// #include <cmath>
#include "base.h"

// -----Свойства шаблона-----
// Главная программа в отдельной финкции mainwork.
// Главная переменная - строка, которая может иметь символы с любыми кодами (кроме 3 и 4).
// Жесткие тригерры опций в виде бинарного вектора.
// Коды возврата: 0 - все хорошо,
// 1 - "легкая" неудача (ошибка в модуле base.h или кол-во аргументов), 
// 2 - "тяжелая" неудача (ошибка в главной программе).
// Поддержка стандартных входов-выходов (конвеер тоже).
// Поддержка внешних файлов для ввода вывода.
// Поддержка аргументов и их свободного использования. (Пр.: prog --help или prog -k -d ил prog -dk)
// Разные способы работы с входными данными. (см. строку №26)

int main(int a, char* b[10])
{
	string fin,fout,main_string;	
	unsigned char options;
	char stop,type;
	type=1;	// [0-2] Читать все залпом, по словам, по строкам (сразу после прочтения куска - выполнение mainwork).
	stop=0;	// [0-1] Работать со всеми данными, только с первым элементом (см. type).
	
	if (a>20){cout<<"Слишком много аргументов!\n"; return 1;} // Защита от дураков по кол-ву аргументов
	if (arguments(a,b,fin,fout,options)) return 1; // Обрабатываем аргументы, если что - выходим
	if (options&1) debug(a,b,options,fin,fout); // Отладка
	return iomodule(main_string,options,fin,fout,stop,type); // Основная функция ввода-вывода.
}

int mainwork (string& main_string, unsigned char options)
{
	return 0;
}
