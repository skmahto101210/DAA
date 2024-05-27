#include<stdio.h>
#include<stdlib.h>

long long power(int x,int y)
{
	if(y==0)return 1;
	else if(y&1)return x*power(x,y/2)*power(x,y/2);
	else return power(x,y/2)*power(x,y/2);
}

int countdigit(int num)
{
	int size=0;
	while(num)
	{
		num=num/10;
		size++;
	}
	return size;
}
int max(int a,int b)
{
	return a<b?b:a;
}
long long karatsuba(long long x,long long y,int r)
{
	if(x<10||y<10)
		return x*y;
	int digit= max(countdigit(x),countdigit(y));
	int pow=power(r,digit/2);
	long xh=x/pow;
	long xl=x%pow;
	long yh=y/pow;
	long yl=y%pow;
	long long a=karatsuba(xh,yh,r);
	long long d=karatsuba(xl,yl,r);
	long long e=karatsuba(xh+xl,yh+yl,r)-a-d;
	return a*pow*pow+e*pow+d;
}

int main()
{
	FILE* fptr=fopen("file_input5_1.txt","r");
	long long x,y,temp;
	while(!feof(fptr))
	{
		if(fscanf(fptr,"%lld",&temp)==1)
		{
			x=temp;
			break;
		}
	}
	while(!feof(fptr))
	{
		if(fscanf(fptr,"%lld",&temp)==1)
		{
			y=temp;
			break;
		}
	}
	fclose(fptr);
	fptr=fopen("output_file5_1.txt","wa");
	fputs("Multiplication:-\n",fptr);
	fprintf(fptr,"\t%lld X %lld = %lld",x,y,karatsuba(x,y,10)); 
	fclose(fptr);
	
	return 0;
}
