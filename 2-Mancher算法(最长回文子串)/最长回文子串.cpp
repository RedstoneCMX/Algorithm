#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#define MIN(x,y)   ((x)<(y)? (x):(y))
using namespace std;
int main()
{
	int N=0;
	cin>>N;
	string str;
	int i=0;
	for(i=0;i<N;i++)
	{
		cin>>str;
		int len=str.length();
		 
		char *temp_str=new char[2*len+3];
		int p=0,q=1;
		temp_str[0]='$';
		temp_str[1]='#';
		for(p=0,q=2;p<len;p++,q+=2)
		{
			temp_str[q]=str[p];
			temp_str[q+1]='#';
		}

		temp_str[2*len+2]='\0';
		int *help=new int[2*len+2];
		int mx=0,n=2*len+2;
		int id,i;
		for(i=1;i<n;i++)
		{
			if(mx>i)
				help[i]= MIN(help[2*id-i],help[id]+id-i);
			else
				help[i]=1;
			for(;temp_str[i+help[i]]==temp_str[i-help[i]];help[i]++);
			if(help[i]+i>mx)
			{
				mx=help[i]+i;
				id=i;
			}

		}

		int max=0;
		for(i=1;i<n;i++)
		{
			if(max<help[i])
				max=help[i];
		}
		cout<<max-1<<endl;
		delete[] temp_str;
		delete[] help;
	}
	
//	system("pause");
	return 0;
}