#include <string.h>

struct arguments {
	std::string fin,fout,target,main_string;	// Путь к входному, выходному файлам, объекту, строка-поток программы.
	unsigned char options;			// Обработанный битовый набор аргументов переданных программе.
	char type;						// Тип работы с потоком.
} arg;

std::string vec2string(unsigned char a); // Возвращает строку в виде 0 и 1 из битового вектора.
int arguments(int a, char* c[10], struct arguments& arg); // Обрабатываем аргументы
int debug(int a, char* b[10], struct arguments& arg); // Отладка. Depend: vec2string
int mainwork (struct arguments& arg); // Выполнение основной программы
int iomodule(struct arguments& arg); // Основная функция ввода-вывода. Depend: mainwork
