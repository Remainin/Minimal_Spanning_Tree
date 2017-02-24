#include <stdio.h>
#include <stdlib.h>
#define N 100              //图中点的数量最大不超过100
#define Zero 1000       //当两点不连通时，设置其权值为1000

int v_number;         //用于储存边的总数，点表，和边对应的权值权值
int v_list[N];
int e_weight[N][N];
int e_count = 0;

void build_G()         //图的建立
{
    int i,j;
    printf("请输入所构造图中顶点的个数：\n");
    scanf("%d",&v_number);
    printf("请输入顶点的编号：\n");
    for(i = 0; i < v_number; i++)
    {
        scanf("%d",&v_list[i]);
    }
    printf("请输入带权值的边表：\n");
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

void  print_G()        //图的打印
{
    int i,j;
    printf("顶点表以及相应的边表如下：(权值为1000代表此两点不连通）\n");
    printf("\n");
    printf("顶点编号 ");
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

void sort_weight(int a[],int n)  //用于对Kruskal算法中权值数组的排序
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
    int Fa[v_number];   //Fa[i]表示i的祖先
    int e_sort_weight[N]; //权值的数组
    for (i=1; i<v_number; i++)
    {
        for (j=0; j<i; j++)
        {
            e_sort_weight[e_count] = e_weight[i][j];
            e_count++;
        }
    }
    sort_weight(e_sort_weight,e_count);//对权值数组进行排序
    for (i=0; i<v_number; i++)  //对Fa数组初始化，每个点是自己的祖先
        Fa[i] = i;
    for (s=0; s<e_count &&!flag; s++) //从e_sort_weight[s]开始找最小边
    {
        for (i=1; i<v_number && !flag; i++)
        {
            for (j=0; j<i&&!flag; j++)   //找最小边对应的两个点
            {
                if (e_sort_weight[s] == e_weight[i][j]&&Fa[i]!=Fa[j]) //若两点的祖先相同，则不能选择这条边了，否则会产生圈
                {
                    for (m=0; m<v_number; m++) //连接的这两个点，必须有一个点是其他已知与该点相连的祖先慢，若没有一个点满足，则使其中一个点(i)作为他所在树的祖先
                    {
                        if (Fa[m] == Fa[i])
                        {
                            Fa[m] = i;
                        }
                    }
                    Fa[i] = Fa[j];     //使一个点最为另一个点的父亲
                    sum+=e_sort_weight[s]; //找到一条合适的最小边，累加
                }
                for (m=0; m<v_number; m++)  //找到一个点的祖先，例如Fa[i]=j,Fa[j]=m,则通过次循环会得到Fa[i]=m
                {
                    int ancestor = m;
                    while(ancestor!=Fa[ancestor])
                    {
                        ancestor= Fa[ancestor];
                    }
                    Fa[m] =ancestor;
                }
                flag =1;
                for (m=1; m<v_number; m++)//若每一个点祖先相同，则最小生成树建立完毕
                {
                    if(Fa[0]!= Fa[m])
                        flag = 0;
                }
            }
        }
    }
    printf("最小生成树的权值为：%d\n",sum);
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
        min_weight[i] = e_weight[0][i];  //设第一个点为初始点，保存所有其他点到第一个点的距离
    }
    min_weight[0] = Zero;  //自己与自己之间的最小距离为0
    for(i = 0; i<v_number; i++)
    {
        v_connection[i] = 1;        //代表该点还未接入最小生成树中
    }
    v_connection[0] = 0;
    while(flag)
    {
        min_number = Zero;
        for (i=0; i<v_number;i++)
        {
              if (v_connection[i]==0)  //如果该点已经接入图中，则不考虑
              {
                  continue;
              }
              if (min_weight[i]<min_number)
              {
                  min_number = min_weight[i]; //找到与最小值(到已经接入的点)
                  v = i;                //保存该点
              }
        }
        v_connection[v] = 0;
        sum = sum + min_weight[v];
        for (i=0; i<v_number;i++)  //对min_weight数组进行更新
        {
              if (v_connection[i]==0)
              {
                  continue;
              }
              if (e_weight[v][i]<min_weight[i])//如果其他点到新的接入点的距离比以前的更小，更新min_weight数组的对应值
              {
                  min_weight[i] = e_weight[v][i];
              }
        }
        countnumber++;     //Prim算法的循环次数为图中点数-1
        if (countnumber == v_number-1)
        {
           flag =0;
        }

    }
     printf("最小生成树的权值为：%d\n",sum);
}
int main()
{
    build_G();
    print_G();
    int n;
    int flag = 1;
    while(flag)
    {
        printf("请输入数字“1”代表Prim算法，输入数字“2”代表Kruskal算法，输入其他数字则结束程序\n");
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















