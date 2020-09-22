#include<cstdio>
#include<cstring>
#include<ctime>
char ans[11],start[10];
bool isUsed[11];
int changeId[9][4]={{-1,-1,3,1},{-1,0,4,2},{-1,1,5,-1},
					{0,-1,6,4},{1,3,7,5},{2,4,8,-1},
					{3,-1,-1,7},{4,6,-1,8},{5,7,-1,-1}
					};//0出现在0->8的位置后该和哪些位置交换 
const int M=400000;//9！=362800，因此数组开40W足够了 
int num[M],len=0,des=123804765;//num存储所有排列，len表示排列的个数也就是9！，des为目的状态直接用整数表示便于比较 
bool isV[M];//bfs时判断状态是否出现过；isV的下标和num的下标一一对应，表示某种排列是否出现过
//通过isV和num建立起某种排列的组合成的整数int和bool的关系，其实STL中有map实现了key-->value，用排列作为key，value用bool即可 
int que[M][3];//0-->排列,1-->排列中0的位置,2-->步数 
void swap(char *c,int a,int b){//交换字符串中的两个位置 
	char t=c[a];
	c[a]=c[b];
	c[b]=t;
}
void paiLie(int n,int k){//深搜产生0-8的全排列 
	for(int i=0;i<n;i++){
		if(!isUsed[i]){
			ans[k]=i+'0';
			isUsed[i]=1;
			if(k==n){//已经有n个转换存储 
				ans[k+1]='\0';
				sscanf(ans+1,"%d",&num[len++]);
			}
			else
				paiLie(n,k+1);
			isUsed[i]=0;//回溯一步 
		}
	}
}
int halfFind(int l,int r,int n){//二分查找 
	int mid=l+(r-l)/2;
	if(num[mid]==n)return mid;
	else if(l<r&&num[mid]>n)return halfFind(l,mid-1,n);
	else if(l<r&&num[mid]<n) return halfFind(mid+1,r,n);
	return -1;
}
int bfs(int n,int p){
	int head=0,tail=1,temp;//head队头，tail队尾 
	que[head][0]=n,que[head][1]=p,que[head][2]=head;//初始状态保存到对头，并设置当前步数为0 
	while(head!=tail){//队列不为空则继续搜索 
		char cur[10];//用于保存当前状态的字符串 
		int  pos=que[head][1];//当前状态中0的位置 
		sprintf(cur,"%09d",que[head][0]);//int-->char*这里的09d至关重要，否则算不出答案 
		for(int i=0;i<4;i++){//扩展当前的状态，上下左右四个方向 
			int swapTo=changeId[pos][i];//将要和那个位置交换 
			if(swapTo!=-1){//-1则不交换 
				swap(cur,pos,swapTo);//交换0的位置得到新状态 
				sscanf(cur,"%d",&temp);//新状态转换为int保存到temp 
				if(temp==des)//如果是目标状态则返回当前状态的步数+1 
					return que[head][2]+1;
				int k=halfFind(0,len,temp);//没有返回就查找当前排列的位置，将查出来的下标作为isV的下标 
				if(!isV[k]){//如果 没有出现过，则将这个新状态进队 
					que[tail][0]=temp,que[tail][1]=swapTo,que[tail][2]=que[head][2]+1;
					tail++;	
					isV[k]=1;
				}
				swap(cur,pos,swapTo);//一个新状态处理完了一定要记得将交换的0交换回来 
			}
		}
		head++;
	}
}
int main(){
	int n,i=-1,count=0;
	paiLie(9,1);//先将0-8的全排列按照升序产生出来存入num数组 
	scanf("%s",start);//输入初始状态 
	while(start[++i]!='0');//查找初始状态0的位置 
	sscanf(start,"%d",&n);//字符串转换为整数 
	//int s=clock();
	if(n!=des)//判断输入状态是否就是目的状态 
		count=bfs(n,i); 
	printf("%d\n",count);
	//printf("%.6lf",double(clock()-s)/CLOCKS_PER_SEC);
	return 0;
