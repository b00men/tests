#include <string.h>
using namespace std;

struct arguments {
	string fin,fout,target,main_string,main_string2;		// Путь к входному, выходному файлам, объекту, строка-поток программы.
	unsigned char options;									// Обработанный битовый набор аргументов переданных программе.
	char type,type2;										// Тип работы с потоком.
	int nostr;												// Номер текущей строки\слова\страница.
} arg;

string vec2string(unsigned char a); // Возвращает строку в виде 0 и 1 из битового вектора.
bool findhelp(int a, char* c[10], string help);	// Поиск в сырых аргументах вызова --help.
int arguments(int a, char* c[10], struct arguments& arg); // Обрабатываем аргументы. Depend findhelp
int debug(int a, char* b[10], struct arguments& arg); // Отладка. Depend: vec2string
int mainwork (struct arguments& arg); // Выполнение основной программы
int iomodule(struct arguments& arg); // Основная функция ввода-вывода. Depend: mainwork
char* itoa(int val, int base);