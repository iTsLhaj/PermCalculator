#include <stdio.h>
#include <string.h>

int getpermint(int c)
{
	switch (c)
	{
	case 114:
		return 4;
	case 119:
		return 2;
	case 120:
		return 1;
	case '-':
		return 0;
	}
}

void getstrperm(int x, char *p)
{
	
	if(x != 0)
	{
		
		if(x >= 4)
		{
			p[0] = 'r';
			x -= 4;
		}

		if(x >= 2)
		{
			p[1] = 'w';
			x -= 2;
		}

		if(x >= 1)
		{
			p[2] = 'x';
			x -= 1;
		}

	}

}

void help(char *exe_)
{

	printf("\n Usage: %s [OPTION] INPUT\n\n Options: \n\t\t-s | --string	pass a string as an argument \n\t\t\t\te.g: %s -s -rw-rw-r-- \n\t\t-d | --digit	pass a per-integer \n\t\t\t\te.g: %s -d 664\n\n", exe_, exe_, exe_);

}

void s2i(int *permission, char *text)
{
	
	// char *text = "-rwxrwxr-x"; /* 775 */ 
								  /* 664 */

	/*
	 * 0 ---
	 * 1 --x
	 * 2 -w-
	 * 3 -wx
	 * 4 r--
	 * 5 r-x
	 * 6 rw-
	 * 7 rwx
	 */

	/*
	 * [0:3]
	 * [3:6]
	 * [6:9]
	 */

	int counter = 0;

	for(int i = 0; i < 9; i += 3)
	{
		int s = 0;
		for(int j = i+1; j <= i+3; j++)
			s += getpermint(*(j + text));
		permission[counter] = s;
		counter++;
	}

}

int main(int argc, char **argv)
{

	if(argc != 3)
		help(argv[0]);
	else
	{
		if(strcmp(argv[1], "--string") == 0 || strcmp(argv[1], "-s") == 0)
		{
			int permission_[3];
			s2i(permission_, argv[2]);

			for(int i = 0; i < 3; i++)
				printf("%i", permission_[i]);
			printf("\n");
		}
		else if(strcmp(argv[1], "--digit") == 0 || strcmp(argv[1], "-d") == 0)
		{
			printf("-");
			for(int i=0; i < 3; i++)
			{
				char p_[3] = { '-', '-', '-' };
				int d = argv[2][i] - 48;
				getstrperm(d, p_);
				printf("%s", p_);
			}
			printf("\n");
		}
	}


	return 0;
}
