#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp = fopen("input.txt", "r");
	int nbrOfInputs = 2000;
	int nbrOfInc = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int temp;
	fscanf(fp, "%d", &temp);
	a += temp;
	fscanf(fp, "%d", &temp);
	a += temp;
	b += temp;
	fscanf(fp, "%d", &temp);
	a += temp;
	b += temp;
	c += temp;
	for (int i = 3; i < nbrOfInputs; ++i)
	{
		fscanf(fp, "%d", &temp);
		switch (i % 3)
		{
		case 0:
			b += temp; //last add
			c += temp; //second add
			if (b > a)
				nbrOfInc++; //check if inc
			a = temp;		//first add
			break;
		case 1:
			a += temp;
			c += temp;
			if (c > b)
				nbrOfInc++;
			b = temp;
			break;
		case 2:
			a += temp;
			b += temp;
			if (a > c)
				nbrOfInc++;
			c = temp;
			break;
		}
	}
	fclose(fp);
	printf("number of increases: %d", nbrOfInc);
	return 0;
}