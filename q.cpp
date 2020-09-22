#include<cstdio>
#include<cstring>
#include<ctime>
char ans[11],start[10];
bool isUsed[11];
int changeId[9][4]={{-1,-1,3,1},{-1,0,4,2},{-1,1,5,-1},
					{0,-1,6,4},{1,3,7,5},{2,4,8,-1},
					{3,-1,-1,7},{4,6,-1,8},{5,7,-1,-1}
					};//0������0->8��λ�ú�ú���Щλ�ý��� 
const int M=400000;//9��=362800��������鿪40W�㹻�� 
int num[M],len=0,des=123804765;//num�洢�������У�len��ʾ���еĸ���Ҳ����9����desΪĿ��״ֱ̬����������ʾ���ڱȽ� 
bool isV[M];//bfsʱ�ж�״̬�Ƿ���ֹ���isV���±��num���±�һһ��Ӧ����ʾĳ�������Ƿ���ֹ�
//ͨ��isV��num������ĳ�����е���ϳɵ�����int��bool�Ĺ�ϵ����ʵSTL����mapʵ����key-->value����������Ϊkey��value��bool���� 
int que[M][3];//0-->����,1-->������0��λ��,2-->���� 
void swap(char *c,int a,int b){//�����ַ����е�����λ�� 
	char t=c[a];
	c[a]=c[b];
	c[b]=t;
}
void paiLie(int n,int k){//���Ѳ���0-8��ȫ���� 
	for(int i=0;i<n;i++){
		if(!isUsed[i]){
			ans[k]=i+'0';
			isUsed[i]=1;
			if(k==n){//�Ѿ���n��ת���洢 
				ans[k+1]='\0';
				sscanf(ans+1,"%d",&num[len++]);
			}
			else
				paiLie(n,k+1);
			isUsed[i]=0;//����һ�� 
		}
	}
}
int halfFind(int l,int r,int n){//���ֲ��� 
	int mid=l+(r-l)/2;
	if(num[mid]==n)return mid;
	else if(l<r&&num[mid]>n)return halfFind(l,mid-1,n);
	else if(l<r&&num[mid]<n) return halfFind(mid+1,r,n);
	return -1;
}
int bfs(int n,int p){
	int head=0,tail=1,temp;//head��ͷ��tail��β 
	que[head][0]=n,que[head][1]=p,que[head][2]=head;//��ʼ״̬���浽��ͷ�������õ�ǰ����Ϊ0 
	while(head!=tail){//���в�Ϊ����������� 
		char cur[10];//���ڱ��浱ǰ״̬���ַ��� 
		int  pos=que[head][1];//��ǰ״̬��0��λ�� 
		sprintf(cur,"%09d",que[head][0]);//int-->char*�����09d������Ҫ�������㲻���� 
		for(int i=0;i<4;i++){//��չ��ǰ��״̬�����������ĸ����� 
			int swapTo=changeId[pos][i];//��Ҫ���Ǹ�λ�ý��� 
			if(swapTo!=-1){//-1�򲻽��� 
				swap(cur,pos,swapTo);//����0��λ�õõ���״̬ 
				sscanf(cur,"%d",&temp);//��״̬ת��Ϊint���浽temp 
				if(temp==des)//�����Ŀ��״̬�򷵻ص�ǰ״̬�Ĳ���+1 
					return que[head][2]+1;
				int k=halfFind(0,len,temp);//û�з��ؾͲ��ҵ�ǰ���е�λ�ã�����������±���ΪisV���±� 
				if(!isV[k]){//��� û�г��ֹ����������״̬���� 
					que[tail][0]=temp,que[tail][1]=swapTo,que[tail][2]=que[head][2]+1;
					tail++;	
					isV[k]=1;
				}
				swap(cur,pos,swapTo);//һ����״̬��������һ��Ҫ�ǵý�������0�������� 
			}
		}
		head++;
	}
}
int main(){
	int n,i=-1,count=0;
	paiLie(9,1);//�Ƚ�0-8��ȫ���а������������������num���� 
	scanf("%s",start);//�����ʼ״̬ 
	while(start[++i]!='0');//���ҳ�ʼ״̬0��λ�� 
	sscanf(start,"%d",&n);//�ַ���ת��Ϊ���� 
	//int s=clock();
	if(n!=des)//�ж�����״̬�Ƿ����Ŀ��״̬ 
		count=bfs(n,i); 
	printf("%d\n",count);
	//printf("%.6lf",double(clock()-s)/CLOCKS_PER_SEC);
	return 0;
