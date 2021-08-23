

//////////Либрарии///////////////
#include "stdio.h"
#include "windows.h"
#include "math.h"
//////////////Объявление глобальных переменных и ф-ций////////////////
void Determinant(int);
int N;
float **a,**arr,*b,znam=1;

void main()
{
	SetConsoleOutputCP(1251);
	printf("ПРОГРАММА ДЛЯ РЕШЕНИЯ СИСТЕМ ЛИНЕЙНЫХ УРАВНЕНИЙ НЕОГРАНИЧЕНОГО КОЛИЧЕСТВА\n\nУкажите количество уравнений в системе:");
	do{scanf("%d",&N);}while(N==0);
//////////////////Определение размерности масивов/////////////
	b=new float[N];
	a=new float*[N];
	for(int i=0;i<N;i++)
	{
		a[i]=new float[N];
	}
	arr=new float*[N];
	for(i=0;i<N;i++)
	{
		arr[i]=new float[N];
	}
//////////////////ввод системы с клавиатуры////////////////////
	for(i=0;i<N;i++)
	{
		printf("Введите коэфициенты при неизвестных %d-го уравнения.\n",i+1);
		for(int j=0;j<N;j++)
		{
			printf("X%d : ",j+1);
			scanf("%f",&a[i][j]);
		}
	}
	for(i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
			arr[i][j]=a[i][j];
	}
	printf("Теперь введите свободные члены соответственно.\n");
	for(i=0;i<N;i++)
	{
		printf("%d-го уравнения : ",i+1);
		scanf("%f",&b[i]);
	}
/////////////////высчет определителя////////////////////
	for(i=0;i<N-1;i++)
	{
		Determinant(i);
	}
////////////////подсчёт знаменателя/////////////////////
	for(i=0;i<N-2;i++)
	{
		for(int j=0;j<N-2-i;j++)
			znam*=a[j][j];
	}
	float A=a[N-1][N-1]/znam;
	printf("\nОпределитель А = %f\n\n",A);
////////////////вывод решения на экран//////////////////
	if(A!=0)
	{
	float X;
	for(i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			for(int k=0;k<N;k++)
			a[j][k]=arr[j][k];
		}
		for(j=0;j<N;j++)
		{
			a[j][i]=b[j];
		}
		for(j=0;j<N-1;j++)
		{
			Determinant(j);
		}
		znam=1;
		for(int k=0;k<N-2;k++)
		{
			for(j=0;j<N-2-k;j++)
				znam*=a[j][j];
		}
		X=a[N-1][N-1]/(znam*A);
		printf("X%d/A = %f\n",i+1,X);
	}}
	else
	{printf("Система не решается методом Крамера, т.к. определитель равен \"0\"");}
	scanf(" ");
}
////////////////ф-ция замены элементов в матрице//////////////
void Determinant(int i)
{
	int i1,j1,j;
	i1=i;
	j1=i;
	for(i=i1+1;i<N;i++)
	{for(j=i1+1;j<N;j++)
	{a[i][j]=a[i][j]*a[i1][j1]-a[i1][j]*a[i][j1];}}
}
