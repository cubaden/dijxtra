#include<iomanip>
#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

#define word unsigned int

using namespace std;

int i, j, n, p, xn, xk;

int flag[11];
word c[11][11], l[11];
char s[80], path[80][11];

int min(int n)
{
	int i, result;
	for(i=0;i<n;i++)
	    if(!(flag[i])) 
		    result=i;

	for(i=0;i<n;i++)
		if((l[result]>l[i])&&(!flag[i])) 
			result=i;

	return result;
}

word minim(word x, word y)
{
	if(x<y)
		return x;
	return y;
}

void main()
{   
    setlocale(LC_ALL, "ukr");
	cout<<"Введіть кількість точок: ";
	cin>>n;
	for(i=0;i<n;i++)
	    for(j=0;j<n;j++) c[i][j]=0;

	for(i=0;i<n;i++)
    	for(j=i+1;j<n;j++)
        {
            cout<<"Введіть відстань від x"<<i+1<<" до x"<<j+1<<": ";
            cin>>c[i][j];
        }

	cout<<" ";

	for(i=0;i<n;i++) cout<<" X"<<i+1;

	cout<<endl<<endl;

	for(i=0;i<n;i++)
    {
        printf("X%d",i+1);
	    for(j=0;j<n;j++)
		{
		    printf("%6d",c[i][j]);
		    c[j][i]=c[i][j];
	    }
		printf("\n\n");
    }

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
        	if(c[i][j]==0) c[i][j]=65535; //безкінечність
	
    cout<<"Введіть початкові точки: ";
	cin>>xn;
	cout<<"Введіть кінцеві точки: ";
	cin>>xk;
	xk--;
	xn--;
	
    if(xn==xk)
	{
	    cout<<"Початкова і кінцева точки збігаються."<<endl;
        getch();
        return;
	}

	for(i=0;i<n;i++)
	{
		flag[i]=0;
		l[i]=65535;
	}
	
    l[xn]=0;
	flag[xn]=1;
	p=xn;
	itoa(xn+1,s,10);
	
    for(i=1;i<=n;i++)
	{
		strcpy(path[i],"X");
		strcat(path[i],s);
	}
	
    do
	{
	    for(i=0;i<n;i++)
	    if((c[p][i]!=65535)&&(!flag[i])&&(i!=p))
	    {
		    if(l[i]>l[p]+c[p][i])
	        {
		        itoa(i+1,s,10);
		        strcpy(path[i+1],path[p+1]);
		        strcat(path[i+1],"-X");
		        strcat(path[i+1],s);
	        }
		    l[i]=minim(l[i],l[p]+c[p][i]);
        }
		p=min(n);
		flag[p]=1;
	}
	while(p!=xk);

	if(l[p]!=65535)
	{
        cout<<"Шлях: "<<path[p+1]<<endl;
        cout<<"Довжина шляху: "<<l[p]<<endl;
	}
	else
        cout<<"Такого шляху не існує"<<endl;
    getch();
}