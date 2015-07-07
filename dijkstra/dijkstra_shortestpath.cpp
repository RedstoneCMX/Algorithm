#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
dijkstra算法简介
dijkstra算法是用于求有向图或无向图中某点到其余各点的最短距离

1.用邻接矩阵GA来表示带权的有向图或无向图，设定V为所有顶点集合，S为已找到从v0出发的最短路径的终点的集合，
它的初始状态为空集。与之相对的集合设为U=V-S，那么从v0出发到图上其余各顶点可能达到的最短路径长度的初值为：
dist[i]=weight[v0,vi];vi是V中的顶点
2.选择vj，使得dist[j]=min{dist[i]|vi属于集合V-S}，那么vj就是当前求得的一条从v0出发的最短路径的终点。
令S=S U {vj}
3.修改从v0出发到集合V-S上任一顶点vk可达的最短路径长度。如果dist[j]+weight[j,k]<dist[k]，
则修改dist[k]为dist[k]=dist[j]+weight[j,k]
4.重复2和3共n-1次，就可求得从v0到图上各顶点的最短路径长度，即dist数组

而本题中其实就是一道典型的dijkstra算法题，求出A到A-G各点的最短路径，再根据每个村子的人数，
即可求出各点到A村的总路程
同理可求出其他各点到A-G各点的最短路径，求出其对应的到该村的总路程，
通过比较哪个村的总路程最少即可判断将小学建在哪个村子
*/


#define MAXCOST 99999	//一个最大数

//用邻接矩阵来表示该无向图各点之间的边的权值，weight[i][j]表示i和j结点之间的边的权值，
//两点之间没有连线的话就赋值为MAXCOST，同时由于是无向图，所以weight[i][j]=weight[j][i]，
//但在有向图中两者有可能不相等
int weight[7][7]={{0,5,2,MAXCOST,MAXCOST,MAXCOST,MAXCOST},
				  {5,0,MAXCOST,2,7,MAXCOST,MAXCOST},
				  {2,MAXCOST,0,7,MAXCOST,4,MAXCOST},
				  {MAXCOST,2,7,0,6,2,MAXCOST},
				  {MAXCOST,7,MAXCOST,6,0,1,3},
				  {MAXCOST,MAXCOST,4,2,1,0,6},
				  {MAXCOST,MAXCOST,MAXCOST,MAXCOST,3,6,0}};

//每个顶点的人数
int cost[7]={30,40,25,20,50,60,60};

//用于记录每个点到各点的最短距离，比如dist[p]表示的是p点找到其他各点的最短距离组成的数组，
//其中dist[p][p]表示p到p的最短距离，即0
int dist[7][7]={0};
int used[7]={0};

//记录最优的解的那个点
struct BESTPOINT{
	char point;
	int total;
};
int main()
{
	int n=7;
	int i=0,j=0,p=0;
	int k=0;

	//最外层循环，循环n次，找到每个点到其他各点的最短距离，存在dist数组中
	for(p=0;p<n;p++)
	{
		//每次都必须对used进行初始化，初始化为0，used数组记录的是分成的两类节点的，
		//used[i]=0表示U=V-S集合内的，=1表示S集合内的，见上述注释中的dijkstra算法简介
		memset(used,0,sizeof(used));

		//初始化dist[p]数组，表示初始时p点和其他节点的最短距离的初始值，其中dist[p][p]=0
		for(i=0;i<n;i++)
		{
			dist[p][i]=weight[p][i];
		}
		//循环n-1次
		for(i=0;i<n-1;i++)
		{
			//设定一个最大值求出V-S集合中最小的dist[p][j]
			int tmin=MAXCOST;
			for(j=0;j<n;j++)
			{
				if(!used[j]&&tmin>dist[p][j])
				{
					tmin=dist[p][j];
					k=j;
				}
			}
			//将找到的最小的dist[p][k]并放入S集合中，即修改used[k]的值为1
			used[k]=1;

			//更新最短路径，见最上的注释，dijkstra算法简介的步骤3
			for(j=0;j<n;j++)
			{
				if(dist[p][k]+weight[k][j]<dist[p][j])
					dist[p][j]=dist[p][k]+weight[k][j];
			}
		}
	}

	
	//记录最优解的那个点
	BESTPOINT bestpoint;
	//初始化
	bestpoint.point='A';
	bestpoint.total=MAXCOST;
	
	//上面已经求出了每个点对应到各点的最短距离，现求出每个点对应的总路程
	for(p=0;p<n;p++)
	{
		printf("%c到A-G点的最短距离分别为:",'A'+p);
		
		//记录总路程
		int total_s=0;
		for(i=0;i<n;i++)
		{
			if(i==n-1)
				printf("%d.",dist[p][i]);
			else
				printf("%d,",dist[p][i]);
			total_s+=dist[p][i]*cost[i];
		}
		printf("若小学建在%c村，总路程为:%d\n\n",'A'+p,total_s);

		//求解最短的总路程的那个点
		if(bestpoint.total>total_s)
		{
			bestpoint.point='A'+p;
			bestpoint.total=total_s;
		}
	}

	printf("因此最好建在%c村，此时总路程最短，为:%d\n\n",bestpoint.point,bestpoint.total);
	system("pause");
	return 0;

}