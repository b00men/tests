#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
int main()
{
	char c;
	while (true) {
		c=cin.get();
		if (!(c==EOF)) {c+=1; cout.put(c); }
		else break;
	}
	return 0;
}