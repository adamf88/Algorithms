#include <stdio.h>
#include <algorithm>

using namespace std;

#define BUF_SIZE 400
char bufor[BUF_SIZE + 1 + 30];
char *buf_pointer;
char *end_pointer;

bool end_of_buffer()
{
	return buf_pointer == end_pointer;
}

void init()
{
	buf_pointer = bufor;
	int readed = fread(bufor, 1, BUF_SIZE, stdin);
	end_pointer = bufor + readed;

	if (readed)
	{
		--end_pointer;

		//read last number to end
		while ( (*end_pointer & 16) && readed )
		{
			++end_pointer;
			readed = fread(end_pointer, 1, 1, stdin);
		}

		if (*end_pointer & 16)
		{
			++end_pointer;
			*end_pointer = ' ';
		}

		//read white spaces 
		for (; (*buf_pointer & 16) == false;)
		{
			++buf_pointer;
			if (buf_pointer >= end_pointer)
			{
				init();
			}
		}
	}
}

void read_int(unsigned& l)
{
	char *data = buf_pointer;

	if (end_of_buffer()) 
		return;

	l = 0;

	while (*data & 16)
	{
		l *= 10;
		l += *data & 15; //-40
		++data;
	}

	//read white spaces 
	for (; (*data & 16) == false;)
	{
		++data;
		if (data >= end_pointer)
		{
			init();
			data = buf_pointer;
		}
	}

	buf_pointer = data;
}


int main()
{
	unsigned a, b, n;
	init();
	read_int(n);
	while (n--)
	{
		read_int(a);
		read_int(b);
		printf("%d\n", __gcd((int)a, (int)b));
	}
	return 0;
}