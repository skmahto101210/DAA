#include<stdio.h>
#include<stdlib.h>

long long power(int x,int y)
{
	if(y==0)return 1;
	else if(y&1)return x*power(x,y/2)*power(x,y/2);
	else return power(x,y/2)*power(x,y/2);
}

int countdigit(long long num)
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
long long multi(long long x,long long y,int r)
{
	if(x<10||y<10)
		return x*y;
	int digit= max(countdigit(x),countdigit(y));
	int pow=power(r,digit/2);
	long xh=x/pow;
	long xl=x%pow;
	long yh=y/pow;
	long yl=y%pow;
	return multi(xh,yh,r)*pow*pow+(multi(xh,yl,r)+multi(xl,yh,r))*pow+multi(xl,yl,r);
}

int main()
{
	FILE* fptr=fopen("file_input5.txt","r");
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
	fptr=fopen("output_file5.txt","wa");
	fputs("Multiplication:-\n",fptr);
	fprintf(fptr,"\t%lld X %lld = %lld",x,y,multi(x,y,10)); 
	fclose(fptr);
	
	return 0;
}
