#include <stdio.h>
#include <stdlib.h>
#define N 100              //ͼ�е��������󲻳���100
#define Zero 1000       //�����㲻��ͨʱ��������ȨֵΪ1000

int v_number;         //���ڴ���ߵ�����������ͱ߶�Ӧ��ȨֵȨֵ
int v_list[N];
int e_weight[N][N];
int e_count = 0;

void build_G()         //ͼ�Ľ���
{
    int i,j;
    printf("������������ͼ�ж���ĸ�����\n");
    scanf("%d",&v_number);
    printf("�����붥��ı�ţ�\n");
    for(i = 0; i < v_number; i++)
    {
        scanf("%d",&v_list[i]);
    }
    printf("�������Ȩֵ�ı߱�\n");
    for (i=1; i<v_number; i++)
    {
        for (j=0; j<i; j++)
        {
            scanf("%d",&e_weight[i][j]);
            if (e_weight[i][j] == 0)
            {
                e_weight[i][j]= Zero;
            }
            e_weight[j][i] = e_weight[i][j];
        }
    }
    for (i = 0; i<v_number; i++)
    {
        e_weight[i][i] = 0;
    }
}

void  print_G()        //ͼ�Ĵ�ӡ
{
    int i,j;
    printf("������Լ���Ӧ�ı߱����£�(ȨֵΪ1000��������㲻��ͨ��\n");
    printf("\n");
    printf("������ ");
    for(i=0; i<v_number; i++)
    {
        printf("  (%d)  ",v_list[i]);
    }
    printf("\n");
    for (i = 0; i<v_number; i++)
    {
        printf("    (%d)",v_list[i]);
        for (j = 0; j<v_number; j++)
        {
            printf("%7d",e_weight[i][j]);
        }
        printf("\n");
    }
}

void sort_weight(int a[],int n)  //���ڶ�Kruskal�㷨��Ȩֵ���������
{
    int i,j,k,temp;
    for(i=0; i<n; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if(a[j]<a[k])
                k=j;
        }
        temp=a[k];
        a[k]=a[i];
        a[i]=temp;
    }
}

void Kruskal()
{
    int sum=0,flag=0;
    int i,j,s,m;
    int Fa[v_number];   //Fa[i]��ʾi������
    int e_sort_weight[N]; //Ȩֵ������
    for (i=1; i<v_number; i++)
    {
        for (j=0; j<i; j++)
        {
            e_sort_weight[e_count] = e_weight[i][j];
            e_count++;
        }
    }
    sort_weight(e_sort_weight,e_count);//��Ȩֵ�����������
    for (i=0; i<v_number; i++)  //��Fa�����ʼ����ÿ�������Լ�������
        Fa[i] = i;
    for (s=0; s<e_count &&!flag; s++) //��e_sort_weight[s]��ʼ����С��
    {
        for (i=1; i<v_number && !flag; i++)
        {
            for (j=0; j<i&&!flag; j++)   //����С�߶�Ӧ��������
            {
                if (e_sort_weight[s] == e_weight[i][j]&&Fa[i]!=Fa[j]) //�������������ͬ������ѡ���������ˣ���������Ȧ
                {
                    for (m=0; m<v_number; m++) //���ӵ��������㣬������һ������������֪��õ�����������������û��һ�������㣬��ʹ����һ����(i)��Ϊ��������������
                    {
                        if (Fa[m] == Fa[i])
                        {
                            Fa[m] = i;
                        }
                    }
                    Fa[i] = Fa[j];     //ʹһ������Ϊ��һ����ĸ���
                    sum+=e_sort_weight[s]; //�ҵ�һ�����ʵ���С�ߣ��ۼ�
                }
                for (m=0; m<v_number; m++)  //�ҵ�һ��������ȣ�����Fa[i]=j,Fa[j]=m,��ͨ����ѭ����õ�Fa[i]=m
                {
                    int ancestor = m;
                    while(ancestor!=Fa[ancestor])
                    {
                        ancestor= Fa[ancestor];
                    }
                    Fa[m] =ancestor;
                }
                flag =1;
                for (m=1; m<v_number; m++)//��ÿһ����������ͬ������С�������������
                {
                    if(Fa[0]!= Fa[m])
                        flag = 0;
                }
            }
        }
    }
    printf("��С��������ȨֵΪ��%d\n",sum);
}

void Prim()
{
    int min_weight[v_number];
    int v_connection[v_number];
    int i,min_number,v;
    int countnumber = 0;
    int sum = 0;
    int flag = 1;
    for (i=0; i<v_number; i++)
    {
        min_weight[i] = e_weight[0][i];  //���һ����Ϊ��ʼ�㣬�������������㵽��һ����ľ���
    }
    min_weight[0] = Zero;  //�Լ����Լ�֮�����С����Ϊ0
    for(i = 0; i<v_number; i++)
    {
        v_connection[i] = 1;        //����õ㻹δ������С��������
    }
    v_connection[0] = 0;
    while(flag)
    {
        min_number = Zero;
        for (i=0; i<v_number;i++)
        {
              if (v_connection[i]==0)  //����õ��Ѿ�����ͼ�У��򲻿���
              {
                  continue;
              }
              if (min_weight[i]<min_number)
              {
                  min_number = min_weight[i]; //�ҵ�����Сֵ(���Ѿ�����ĵ�)
                  v = i;                //����õ�
              }
        }
        v_connection[v] = 0;
        sum = sum + min_weight[v];
        for (i=0; i<v_number;i++)  //��min_weight������и���
        {
              if (v_connection[i]==0)
              {
                  continue;
              }
              if (e_weight[v][i]<min_weight[i])//��������㵽�µĽ����ľ������ǰ�ĸ�С������min_weight����Ķ�Ӧֵ
              {
                  min_weight[i] = e_weight[v][i];
              }
        }
        countnumber++;     //Prim�㷨��ѭ������Ϊͼ�е���-1
        if (countnumber == v_number-1)
        {
           flag =0;
        }

    }
     printf("��С��������ȨֵΪ��%d\n",sum);
}
int main()
{
    build_G();
    print_G();
    int n;
    int flag = 1;
    while(flag)
    {
        printf("���������֡�1������Prim�㷨���������֡�2������Kruskal�㷨�����������������������\n");
        scanf("%d",&n);
        if (n == 1)
            Prim();
        else if (n == 2)
            Kruskal();
        else
            flag = 0;
    }

    return 0;
}















