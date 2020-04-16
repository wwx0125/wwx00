#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20 
using namespace std;
//创建图 
typedef struct ArcNode
{   
    int adj;
	struct ArcNode *next;  
}ArcNode; 
typedef struct 
{
    char data;
    int indegree,outdegree;
    ArcNode *firstarc;             
}VNode;
typedef struct
{
	VNode vertices[MAX];
	int vexnum,arcnum;
}Graph;
int GetPosition(Graph &G,char vex)
{
	int i;
	for(i=0;i<G.vexnum;i++)
	{
		if(vex==G.vertices[i].data)
		    return i;
	}
	return -1;
}
int Insert(Graph &G,int m,int n)
{
	ArcNode *p,*q;
	p=new ArcNode;
	p->adj=n;
	p->next=NULL;
	q=G.vertices[m].firstarc;
	G.vertices[m].firstarc=p;
	p->next=q;
	return 1; 
}
int Creat(Graph &G)
{
	cin>>G.vexnum;
	int i,m,n;
	for(i=0;i<G.vexnum;i++)
	{
		cin>>G.vertices[i].data;
		G.vertices[i].indegree=0;
		G.vertices[i].outdegree=0;
		G.vertices[i].firstarc=NULL;
	}
	cin>>G.arcnum;
	char out,in;
	for(i=0;i<G.arcnum;i++)
	{
		cin>>out>>in;
		m=GetPosition(G,out);
		n=GetPosition(G,in);
		Insert(G,m,n);
	}
	return 1;
} 	

 
bool visited[MAX];
//深度优先遍历
int FirstAdjVex(Graph G,int v);
int NextAdjVex(Graph G,int v,int w);
void DFS(Graph G,int v)
{
	visited[v]=1;
	cout<<G.vertices[v].data<<"  ";
	for(int w=FirstAdjVex(G,v);w!=-1;w=NextAdjVex(G,v,w))
	{
		if(!visited[w])
		    DFS(G,w);
	}	
}
void DFSTraverse(Graph G) 
{
	int v;
	for(v=0;v<G.vexnum;v++)
	{
		visited[v]=0;
	}
	for(v=0;v<G.vexnum;v++)
	{
		if(!visited[v])
		    DFS(G,v);
	}
}

//队列创建
typedef struct QNode 
{
	int data;
	struct QNode *next;
}QNode,*Queueptr;
typedef struct
{
	Queueptr front;
	Queueptr rear;
}LinkQueue;
int InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=new QNode;
	if(!Q.front)exit(1);
	Q.front->next=NULL;
	return 1;
}
int EnQueue(LinkQueue &Q,int e)
{
	Queueptr p=new QNode;
	if(!p)exit(1);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p; 
	return 0;
}
int QueueEmpty(LinkQueue Q) 
{   
   if(Q.front==Q.rear) return 1; 
   else  return 0; 
} 
int DeQueue(LinkQueue &Q,int &e)
{
	if(QueueEmpty(Q)) return 0; 
	Queueptr p=Q.front->next;     
	e=p->data;   
	Q.front->next=p->next;   
	if(Q.rear==p) Q.rear=Q.front;
	delete p; 
	p=NULL; 
	return 0; 
} 

//广度优先遍历
void BFSTraverse(Graph G) 
{
	int v,u,w;
	for(v=0;v<G.vexnum;v++)
	{
		visited[v]=0;
	} 
	LinkQueue Q; 
    InitQueue(Q); 
    for(v=0;v<G.vexnum;v++)
	{
		if(visited[v]==0)
		{
			visited[v]=1;
			cout<<G.vertices[v].data<<"  ";
			EnQueue(Q,v);
			while(!QueueEmpty(Q))
			{
				DeQueue(Q,u);
				for(w=FirstAdjVex(G,u);w!=-1;w=NextAdjVex(G,u,w))
				{
					if(!visited[w])
					{
						visited[w]=1;
						cout<<G.vertices[w].data<<"  ";
						EnQueue(Q,w);
					}
				} 
			}
		}
	} 
} 


int FirstAdjVex(Graph G,int v)
{
	if(v<0||v>MAX)return -1;
	ArcNode *p=G.vertices[v].firstarc;
	if(p!=NULL)return p->adj;
	else return -1; 
}

int NextAdjVex(Graph G,int v,int w)
{
	if(v<0||v>MAX) return -1;
	if(w<0||w>MAX) return -1;
	ArcNode *p=G.vertices[v].firstarc;
	while(p!=NULL&&p->adj!=w)p=p->next;
	if(p->next!=NULL) return p->next->adj;
	else return -1;
}

int main()
{
	Graph G;
	Creat(G);
	DFSTraverse(G);
	cout<<endl;
	BFSTraverse(G);
}


