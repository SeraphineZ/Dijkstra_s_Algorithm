/*
(1)数据结构
	n:城市顶点个数. m:城市间路线的条数. map[][]:地图对应的带权邻接矩阵. dist[]:记录源点u到某顶点的最短路径长度。
	p[]:记录源点到某顶点的最短路径上的该顶点的前一个顶点(前驱).flag[]：flag[i]=true说明顶点i已加入到集合S，否则该顶点属于集合V-S
*/
/*const int N=100;//初始化城市个数，可修改
const int INF=1e7;	//无穷大
int map[N][N],dist[N],p[N],n,m;
bool flag[N];

//(2)初始化源点u到其他各个顶点的最短路径长度，初始化源点u出边邻接点的前驱为u
bool flag[n];//如果flag[i]=true,说明该顶点i已经加入到集合S；否则i属于集合V-S
    for(int i=1;i<=n;i++){
        dist[i]=map[u][i];	//初始化源点u到其他各个顶点的最短路径长度
        flag[i]=false;
        if(dist[i]==INF)
            p[i]=-1;	//说明源点u到顶点i无边相连，设置p[i]=-1
        else
            p[i]=u;	//说明源点u到顶点i有边相连，设置p[i]=u
    }
//(3)初始化集合S，令集合S={u},从源点u的最短路径为0
flag[u]=true;//初始化集合S中，只有一个元素：源点u
dist[u]=0;	//初始化源点u的最短路径为0，自己到自己的最短路径

//(4)找最小.在集合V-S中寻找距离源点u最近的顶点t,若找不到，则跳出循环;否则，将t加入集合S。
int temp=INF,t=u;
    for(int j=1;j<=n;j++){//在集合V-S中寻找距离源点u最近的顶点t
        if(!flag[j] && dist[j]<temp){
            t=j;	//记录距离源点u最近的顶点
            temp=dist[j];
        }
    }
if(t==u) return ;	//找不到t跳出循环
flag[t]=true;	//否则，将t加入集合S

//(5)借东风。考察集合V-S中源点u到t的邻接点j的距离，如果源点u经过t到达j的路径更短，
//	则更新dist[j]=dist[t]+map[t][j],即松弛操作，并记录j的前驱为t;
for(int j=1;j<=n;j++){//更新集合V-S中与t邻接的顶点到u的距离
    if(!flag[j] && map[t][j]<INF){//！flag[j]表示j在v-s集合中，map[t][j]<INF表示t与j邻接
        if(dist[j]>(dist[t]+map[t][j])){//经过t到达j的路径更短
            dist[j]=dist[t]+map[t][j];
            p[j]=t;	//记录j的前驱为t
        }
    }
}
//重复(4)~(5),知道源点u到所有顶点的最短路径被找到
*/

#include<bits/stdc++.h>
using namespace std;
const int N=100;	//城市个数可修改
const int INF=1e7;	//初始化无穷大为.......
int Map[N][N],dist[N],p[N],n,m;	//n为城市个数，m为城市间路线的条数
bool flag[N];	//如果flag[i]=true,说明该顶点i已经加入到集合S；否则i属于集合V-S

void Dijkstra(int u){
    for(int i=1;i<=n;i++){//********>>>--1--<<<******//
        dist[i]=Map[u][i];	//初始化源点u到其他各个顶点的最短路径长度
        flag[i]=false;
        if(dist[i]==INF)
            p[i]=-1;	//说明源点u到顶点i无边相连，设置p[i]=-1
        else
            p[i]=u;	//说明源点u到顶点i有边相连，设置p[i]=u
    }
    flag[u]=true;//初始化集合S中，只有一个元素：源点u
    dist[u]=0;	//初始化源点u的最短路径为0，自己到自己的最短路径
    for(int i=1;i<=n;i++){//********>>>--2--<<<******//
        int temp=INF,t=u;
        for(int j=1;j<=n;j++){//>>--3--<<在集合V-S中寻找距离源点u最近的顶点t
            if(!flag[j] && dist[j]<temp){
                t=j;	//记录距离源点u最近的顶点
                temp=dist[j];
            }
        }
        if(t==u) return;	                    //找不到t跳出循环
        flag[t]=true;	                        //否则，将t加入集合S
        for(int j=1;j<=n;j++){                  //>>--4--<<更新集合V-S中与t邻接的顶点到u的距离
            if(!flag[j] && Map[t][j]<INF){      //！flag[j]表示j在v-s集合中，map[t][j]<INF表示t与j邻接
                if(dist[j]>(dist[t]+Map[t][j]))
                {                               //经过t到达j的路径更短
                    dist[j]=dist[t]+Map[t][j];
                    p[j]=t;	//记录j的前驱为t
                }
            }
        }
    }
}

void findpath(int u)
{
    int x;
    stack<int>s;
    cout << "源点为：" << u << endl;
    for (int i = 1; i <= n; i++)
    {
        x = p[i];
        while (x != -1)
        {
            s.push(x);
            x = p[x];
        }
        cout << "源点到其他各顶点的最短路径为：";
        while (!s.empty())
        {
            cout << s.top() << "--";
            s.pop();
        }
        cout << i << ";最短距离为：" << dist[i] << endl;
    }
}


int main(){
    int u, v, w, st;
    system("color 0d");
    cout << "请输入城市的个数：" << endl;
    cin >> n;
    cout << "请输入城市之间的路线个数" << endl;
    cin >> m;
    cout << "请输入城市之间的路线以及距离" << endl;
    for(int i=1;i<=n;i++)//初始化图的邻接矩阵
        for (int j = 1; j <= n; j++)
        {
            Map[i][j] = INF;//初始化邻接矩阵为无穷大
        }
    while (m--)
    {
        cin >> u >> v >> w;
        Map[u][v] = min(Map[u][v], w);	//邻接矩阵存储，保留最小的距离
    }
    cout << "请输入小明所在的位置：" << endl;
    cin >> st;
    Dijkstra(st);
    cout << "小明所在的位置：" << st << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "小明：" << st << " - " << "要去的位置：" << i << endl;
        if (dist[i] == INF)
            cout << "sorry,无路可达" << endl;
        else
            cout << "最短距离为：" << dist[i] << endl;
    }
    findpath(u);
    return 0;
}
