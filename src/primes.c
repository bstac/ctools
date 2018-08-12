#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

static int debug_level=false;
static bool print_list=false;


int* CalculateNPrimes(int n)
{
	int minimum=2;
	int skip=2;
	if(n < minimum)
	{
		printf("must be atleast %d\n",minimum);
		exit(1);
	}
	int * list = malloc(sizeof(int) * n);
	list[0]=2; //cheat
	list[1]=3; //start on odd number
        int i;
	for(i=minimum;i<n;i++)
	{
		if(debug_level){printf(" - debug i %d\n",i);}
		int j=list[i-1] + skip;//start value, will be odd
		bool flag = false; //have we found the next prime
		while(!flag)
		{
			if(debug_level)printf(" - debug j %d\n",j);
			flag = true; //assume yes until prooven no
			int k;//check j against k, k is prime, j is unkown
			for(k=0;list[k]<sqrt(j);k++)
			{
				//printf(" - debug k %d\n",k);
				//printf(" - debug list at k %d\n",list[k]);
				if(j%list[k]==0)
				{//not a prime, set flag
					flag=false;
					break; //break to skip continued search
				}
			}
			if(flag)
			{
				if(debug_level){printf(" - debug list[i] at add -  %d\n",list[i]);}
				list[i]=j;
			}
			j+=skip;//only check the odds
		}
	}
	return list;
}



int main(int argc, char *argv[])
{
	int i,j,k;
	for(i=0;i<argc;i+=1 )
	{
		if(debug_level){printf("\tvalue of arg\t%d\t->\t%s\n", i, argv[i]);}
		if(strcmp(argv[i],"d")==0||strcmp(argv[i],"-d")==0||strcmp(argv[i],"--debug")==0)
		{debug_level=true;}
		if(strcmp(argv[i],"p")==0||strcmp(argv[i],"-p")==0||strcmp(argv[i],"--print")==0)
                {print_list=true;}
		if(strcmp(argv[i],"h")==0||strcmp(argv[i],"-h")==0||strcmp(argv[i],"--help")==0)
		{
			printf("Prime - Usage\n\t\t ex. \"prime 300 -p -d\" \n\t...");
			printf(" (note - options cannot be grouped without a space)\n");
			printf("\t...option 1 is required and is the number of primes to list");
			printf("\t-d\t=\tdebug comments will be printed to the console\n");
			printf("\t-p\t=\tprint the list of primes to the console\n");
			exit(0);
		}
	}
	if(argc < 2)
	{
		printf("need number of primes...\n");
		return 1;
	}
	j=atoi(argv[1]);
	int * list = CalculateNPrimes(j);
	if(list)
	{
		//print the primes
		for(k=0;k<j;k++)
		{
			if(print_list){printf("\tprime\t\t%d\t\t->\t\t%d\n", k+1,list[k]);}
		}
		if(list)
		{
			free(list);
		}
	}
	exit(0);
}

