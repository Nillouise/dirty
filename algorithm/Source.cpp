// checkConsole.cpp : Defines the entry point for the console application.
//
#include<iostream>
#include<cstdio>
using namespace std;
int num = 0;
int h[8];
int xie1[15];
int xie2[15];

int dfs(int c)
{
	if (c == 7)
	{
		for (int i = 0;i < 8;i++)
		{
			cout << h[i];
			
		}
		cout << endl;
	}

	if (c == 8)
	{
		num++;
		return 0;
	}

	for (int i = 0;i < 8;i++)
	{
		if (h[i] == 0)
		{
			if (xie1[c + i] == 0)
			{
				if (xie2[c - i+ 7 ] == 0)
				{
					h[i] = 1;
					xie1[c + i] = 1;
					xie2[c - i + 7 ] = 1;
					dfs(c + 1);
					h[i] = 0;
					xie1[c + i] = 0;
					xie2[7+ c - i] = 0;
				}
			}
		}
	}
//	return 0;
}

int main()
{
	dfs(0);

	return num;
	return 0;
}

