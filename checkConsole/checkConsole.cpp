// checkConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
using namespace std;
int count = 0;
int h[8];
int xie1[8];
int xie2[8];

int dfs(int c)
{
	if (c == 8)
	{
		count++;
		return 0;
	}
	for (int i = 0;i < 8;i++)
	{
		if (h[i] == 0)
		{
			if (xie1[(c + i)%8] == 0)
			{
				if (xie2[(c - i + 8) % 8] == 0)
				{
					h[i] = 1;
					xie1[(c + i) % 8] = 1;
					xie1[(8 + c - i) % 8] = 1;
					dfs(c + 1);
					h[i] = 0;
					xie1[(c + i) % 8] = 0;
					xie1[(8 + c - i) % 8] = 0;
				}
			}
		}
	}
}

int main()
{
    return 0;
}

