#include <stdio.h>
#include <string.h>
#define MAX 1000
#define LEFT 1
#define BOTTOM 2
#define DIAG 3
/*
The recurrence which I have used to solve the problem is as follows:
(Assuming the strings start from index 1, i.e. A[1..n] contains the string)

c[x,y]= 0 if x>y
      = 1 if x=y
      = 2+c[x+1,y-1] if A[x]=A[y]
      = max{c[x+1,y],c[x,y-1], otherwise.

We maintain a serparate array s to store the information for constructing the
solution. Each cell either stores LEFT, BOTTOM, DIAG to indicate how to proceed,
just as in LCS, but here the way and the direction the problem is solved is a bit
different. 

While writing the actual C program, only while accessing A[x] as per the above 
convention, just access A[x-1].  
*/
int c[MAX+2][MAX+1]={0};
char s[MAX+1][MAX+1]={0};

void display(char* A,int i,int j)
{
	if (i>j)
		return;
	if(i==j)
		printf("%c",A[i-1]);
	else if (s[i][j]==DIAG)
	{
		printf("%c",A[i-1]);
		display(A,i+1,j-1);
		printf("%c",A[i-1]);
	}
	else if (s[i][j]==LEFT)
		display(A,i,j-1);
	else
		display(A,i+1,j);
}

void LPS(char* A, int n)
{
	int i,j;
	for (i=1;i<=n;i++)
		c[i][i]=1;
	for(i=n-1;i>=1;i--)
		for(j=i+1;j<=n;j++)
			if(A[i-1]==A[j-1])
			{
				c[i][j]=2+c[i+1][j-1];
				s[i][j]=DIAG;
			}
			else if(c[i+1][j]>c[i][j-1])
				{
					c[i][j]=c[i+1][j];
					s[i][j]=BOTTOM;
				}
			else {
					c[i][j]=c[i][j-1];
					s[i][j]=LEFT;
			}
	
	printf("THE LENGTH OF THE LONGEST PALINDROMIC SEQUENCE : %d\n",c[1][n]);
	printf("THE PALINDROMIC SEQUENCE : ");
	display(A,1,n);
	printf("\n");
}
			
int main()
{
	char str[100];
	printf("ENTER THE STRING : ");
	scanf("%s",str);
	int n=strlen(str);
	LPS(str,n);
}
