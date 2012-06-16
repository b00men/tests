using namespace std;
string vec2string(unsigned char a) // Возвращает строку в виде 0 и 1 из байта. Нужно для debug
{
	char outchar[8];
	for(int i=7;i>-1;i--)
	{
		if((a>>i)&1) outchar[i]='1';
		else outchar[i]='0';
	}
	return outchar;
}

int arguments(int a, char* c[10], string& in, string& out, unsigned char& options)
{
	string somestring=c[0];
	int size;
	string help="Использование: "+somestring+" [ключ] ... [файл] ...\n~Описание этой программы~\n\n  -h,	--help	Показать эту справку и выйти\n  -o [файл]	Записать результат в [файл]\n  -i [файл]	Читать данные из [файл]\n  -k		Тестовый параметр\n  -d		Режим отладки\n";
	options=0;
	
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
				case ('o'): out=c[i+1]; break;
				case ('i'): in=c[i+1]; break;
				case ('d'): options=options|(1<<0); break;
				case ('k'): options=options|(1<<1); break;
				default: cout<<c[0]<<": Неизвестный ключ  -- «"<<c[i][j]<<"»\nПопробуйте \'"<<c[0]<<" --help\' для получения более подробного описания.\n"; return 1; break;		
				}
			}
		}
	}
	
	return 0;
}

int debug(int a, char* b[10], unsigned char options,  string fin, string fout)
{
	string somestring;
	cout<<"Количество блоков аргументов: "<<(a-1)<<"\nЭто: \n"; // Аргументы
	for (int i=1;i<a;somestring=b[i],cout<<somestring<<'\n',i++);
	cout<<"\nOptions\ndk------\n"<<vec2string(options)<<"\nВходной файл: "<<fin<<"\nВыходной файл: "<<fout<<"\n\n"; // Debug опции, входной и выходной файлы
	cout<<"Вывести переменные среды [Y/n]? ";
	char debugquest;
	scanf("%c",&debugquest);
	if ((debugquest=='y')||(debugquest=='Y'))
	for (int i=a;i<a+47;printf("%s",b[i]),printf("%c",'\n'),i++); // Вывести входные данные и всякие вкусняшки окружающей среды
	cout<<'\n';
	scanf("%c",&debugquest);
	return 0;
}

int mainwork (string& main_string, unsigned char options);

int iomodule(string& main_string, unsigned char options, string fin, string fout,char stop, char type)
{
	char c;
	ifstream in;
	in.open( fin.c_str() );
	ofstream out;
	out.open( fout.c_str() );
	for (int j=1;j==1;)
	{
		main_string="";
		for(int i=1;i==1;)
		{
		(fin=="")?(c=cin.get()):(c=in.get());
		if ((c==-1)||(c==4)||(c==3)) {i=0; stop=1;}
		else main_string=main_string+c;	
		if ((type>0)&&(((c==10)||(c==13))||((type==2)&&((c==9)||(c==32))))) i=0;
		}
		
		if (mainwork(main_string,options)) return 2;
		// Здесь наша программа выполняет свои главные функции.
		
		(fout=="")?(cout<<main_string):(out<<main_string);
		if (stop==1) j=0;
	}
	in.close();
	out.close();
	return 0;
}
