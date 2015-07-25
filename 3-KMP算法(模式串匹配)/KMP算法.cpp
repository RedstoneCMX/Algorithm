#include<stdio.h>
#include<iostream>
#include<string.h>
using namespace std;
char pattern[10001];
char original[1000001];
void getNext(char *p,int *next)
{
    int j,k;
    next[0]=-1;
    j=0;
    k=-1;
	int len=strlen(p);
	//p[len]='$';
	//p[len+1]='\0';
    while(j<len)
    {
        if(k==-1||p[j]==p[k])    //匹配的情况下,p[j]==p[k]
        {
            j++;
            k++;
            next[j]=k;
        }
        else                   //p[j]!=p[k]
            k=next[k];
    }
}
int KMPMatch(char *s,char *p)
{
    int next[10001];
    int i,j;
    i=0;
    j=0;
    getNext(p,next);
	int count=0;
    while(i<strlen(s))
    {
        if(j==-1||s[i]==p[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];       //消除了指针i的回溯
        }
        if(j==strlen(p))
		{
			j=next[j];
			count++;
		}
    }
    return count;
}
int main()
{
	int N;
	int i=0;
	cin>>N;
	getchar();
	for(i=0;i<N;i++)
	{
		gets(pattern);
		gets(original);

		int count=KMPMatch(original,pattern);
		cout<<count<<endl;
	}
}