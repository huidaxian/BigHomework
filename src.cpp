#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<conio.h>
#include<ctime>
#include<windows.h>
#include<fstream>
#include<map>
#include<stdarg.h>
#define fuck while(!_kbhit())
using namespace std;
struct item {
	int lei;
	int sx;
	int fuckyou;
} op[30];
struct tasks {
	string ddes;
	int killg[200];
	int t;
	int tox,toy;
} tk[30];
struct Player {
	string name;
	int hp;
	int maxhp;
	int exp;
	int mexp;
	int level;
	int damage;
	double mor;
	int nowmap; //nowMap
	int nowplc[2];
	int money;
	item bag[100];
	tasks mytask[10]; //myTask
	int bagnum;
	int tasknum;
	//ACSII=1;
} p;
struct guai {
	string name,des;
	int hp;
	int damage;
	int level;
	int explost;
	double mor;
	int lost;
	int task[10];
	int tasknum;
} g[200];
struct RAM_map {
	char fnndp[100][100];
	int hang,lie;
	int myx,myy;
	int chuansong[10][4];
	int totchs;
} mmp[100];
HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int x,int y) {
	COORD pos= {y,x};
	SetConsoleCursorPosition(hConsole,pos);
}//移动光标
struct NPC {
	int x,y;
	string saying;
	int whichmap;
} NPCC[2000];
int totmap=0,totguai=0,totNPC;
void prch(string a,int n) {
	for(int i=0; i<a.size(); i++) {
		cout<<a[i];
		Sleep(n);
	}
}//特效输出字符串（一个一个输出）
void realloadg(char a[]) {
	ifstream fin(a);
	while(fin>>g[totguai].name) {
		fin>>g[totguai].des;
		fin>>g[totguai].damage;
		fin>>g[totguai].hp;
		fin>>g[totguai].lost;
		fin>>g[totguai].level;
		fin>>g[totguai].mor;
		fin>>g[totguai].explost;
		totguai++;
	}
}//从文件直接读入怪物数据
void saveall(char a[]) {
	ofstream saveto(a);
	saveto<<p.name<<endl;
	saveto<<p.hp<<endl;
	saveto<<p.damage<<endl;
	saveto<<p.exp<<endl;
	saveto<<p.maxhp<<endl;
	saveto<<p.mexp<<endl;
	saveto<<p.mor<<endl;
	saveto<<p.level<<endl;
	saveto.close();
}//保存玩家信息
void loadsave(char a[]) {
	ifstream getfrom(a);
	getfrom>>p.name;
	getfrom>>p.hp;
	getfrom>>p.damage;
	getfrom>>p.exp;
	getfrom>>p.maxhp;
	getfrom>>p.mexp;
	getfrom>>p.mor;
	getfrom>>p.level;
	getfrom.close();
}//读取玩家信息
void load(int n) {
	srand(clock());
	for(int i=1; i<=100; i+=abs(rand()%10)) {
		cout<<"█"<<i<<"%";
		if(i==90||i==91||i==93||i==94)
			Sleep(1000);
		Sleep(n);
		cout<<"\b\b";
		if(i>=10)cout<<"\b";
		if(i>=100)cout<<"\b";
	}
	system("cls");
	prch("加载完成\n",10);
}//假装在加载 (可以将加载函数加进去，就可以真的加载了)
void loadNPC() {
	ifstream fin("NPC.in");
	{
		while(fin>>NPCC[totNPC].whichmap) {
			fin>>NPCC[totNPC].x;
			fin>>NPCC[totNPC].y;
			fin>>NPCC[totNPC].saying;
			totNPC++;
		}
	}
	fin.close();
}//读入NPO信息
void loaditem() {
	ifstream weapon("weapon.in");

	weapon.close();
}//还没做完的武器加载系统
void readallmap() { ////////此处重点！！！！
	char na[]="map00.in";//地图保存文件
	char fa[]="chs00.in";//地图传送点保存文件
	for(int i=0; i<=10; i++) { //10为地图总数
		na[4]='0'+i%10;
		fa[4]='0'+i%10;
		na[3]='0'+i/10;
		fa[3]='0'+i/10;
		//跳到第i张地图

		ifstream readmap(na);
		ifstream readchs(fa);
		totmap++;
		int t=0;
		while(readmap>>mmp[totmap].fnndp[t]) { //读入地图
			mmp[totmap].lie=strlen(mmp[totmap].fnndp[t]);
			for(int j=0; j<mmp[totmap].lie; j++)
				if(mmp[totmap].fnndp[t][j]==1)
					mmp[totmap].myx=i,mmp[totmap].myy=j;
			t++;
		}
		int js=0;
		while(readchs>>mmp[totmap].chuansong[js][0]) { //读入对应的传送点
			readchs>>mmp[totmap].chuansong[js][1];
			readchs>>mmp[totmap].chuansong[js][2];
			readchs>>mmp[totmap].chuansong[js][3];
			js++;
		}
		mmp[totmap].totchs=js;//处理传送点信息
		mmp[totmap].lie=strlen(mmp[totmap].fnndp[1]);
		mmp[totmap].hang=t-1;
		readmap.close();
	}
}
void pguai(guai a) {
	cout<<"\n--------------------\n";
	cout<<a.des<<"的"<<a.name<<endl;
	cout<<"剩余血量："<<a.hp<<endl;
	cout<<"攻击力："<<a.damage<<endl;
	cout<<"护甲："<<a.mor<<endl;
	cout<<"等级："<<a.level<<endl;
	cout<<"\n--------------------\n";
}//属性显示
void pmy() {
	puts("\n--------------------\n");
	cout<<p.name<<endl;
	puts("剩余血量：");
	cout<<p.hp<<"/"<<p.maxhp<<endl;
	puts("攻击力：");
	cout<<p.damage<<endl;
	puts("护甲：");
	cout<<p.mor<<endl;
	puts("经验:");
	cout<<p.exp<<"/"<<p.mexp<<endl;
	puts("等级：");
	cout<<p.level<<endl;
	puts("\n--------------------\n");
}//属性显示


//此处为骚操作，可以不用看
char makechoice(int bb,int a,...) { //不定变量读入
	va_list arg_ptr;
	va_start(arg_ptr,a);//不定变量读入格式
	char cho[1000];
	char arg;
	for(int i=0; i<a; i++) {
		arg=va_arg(arg_ptr,int);//获取不定变量
		cho[i]=arg;
	}
	va_end(arg_ptr);
	char cz;
	int i=0;
	int t=0;
	while(1) { //通过键盘AD进行选择
		while(!_kbhit()) {
			t++;
			Sleep(1);
			if(t>=bb)
				return ' ';
		}
		cz=getch();
		if(cz==13)break;
		if(cz=='a'||cz=='A')if(i>0)i--;;;;
		if(cz=='d'||cz=='D')if(i<a-1)i++;;;;
		cout<<"\b"<<cho[i];
	}
	return cho[i];//返回选择的结果
}





void levelup() {
	if(p.exp>=p.mexp) {
		prch("你升级了!!",100);
		pmy();
		p.damage*=1.1;
		p.maxhp*=1.1;
		p.mor+=0.5;
		p.hp=p.maxhp;
		p.exp-=p.mexp;
		p.level++;
		p.mexp*=1.2;
		cout<<"属性改变为:"<<endl;
		pmy();
		getch();
		system("cls");
	}
}//等级提升
int atk(guai a) {
	srand(clock());
	Sleep(500);
	while(1) {
		getch();
		system("cls");
		pmy();
		pguai(a);
		prch("你他娘想干嘛？\n 1 打不过跑求了 \n 2 打他一炮\n",10);
		int timet=0;
		char cz=makechoice(200,2,'1','2');
		if(cz=='1') {
			int moved=abs(rand()*rand())%20;
			if(moved==0) {
				prch("\n耶~，屁娃娃还跑脱了\n",10);
				return -1;
			} else
				prch("\n跑得脱马脑壳\n",10);
		} else if(cz=='2') {
			int moved=abs(clock()*(clock()+1)*(clock()+1))%10+p.damage;
			prch("\n"+p.name+"弄了"+a.name,10);
			cout<<moved;
			prch("那么多的血\a",10);
			a.hp-=moved;
			if(moved>p.damage*100)
				Sleep(20),prch("\n吨起子的伤害！！！\a\n",10);
		}
		if(a.hp<=0) {
			prch("\n你弄死了"+a.des+"的"+a.name+'\n',1);
			return true;
		}
		int moved=abs(clock()*(clock()+1)*(clock()+1))%10+a.damage;
		prch("\n你遭对面弄了",10);
		cout<<moved;
		prch("点血\n",10);
		p.hp-=moved;
		if(p.hp<=0) {
			prch("rua!,你糟了\n",1);
			return false;
		}
	}
}//炫酷(笑)的战斗过程
void outmap(RAM_map a) {
	system("cls");
	for(int i=0; i<a.hang; i++) {
		int x=strlen(a.fnndp[i]);
		for(int j=0; j<x; j++) {
			if(i==a.myx&&j==a.myy)
				cout<<char(1);
			else
				cout<<a.fnndp[i][j];
		}
		cout<<endl;
	}
	Sleep(1);
}//在新地图显示时输出地图
void movemap(int x,int y,RAM_map &a,int &xxx) {
	for(int i=0; i<a.totchs; i++) {
		if(x==a.chuansong[i][0]&&y==a.chuansong[i][1]) {
			int xx=mmp[a.chuansong[i][2]].chuansong[a.chuansong[i][3]][0];
			int yy=mmp[a.chuansong[i][2]].chuansong[a.chuansong[i][3]][1];
			xxx=a.chuansong[i][2];
			a=mmp[xxx];
			a.myx=xx;
			a.myy=yy;
			return ;
		}
	}
}//因为传送点较少，所以我暴力判断下一个位置是不是传送点 以及传送点是那张图
void hinpc(int x,int y,int xxx) {
	for(int i=0; i<totNPC; i++) {
		if(x==NPCC[i].x&&y==NPCC[i].y&&xxx==NPCC[i].whichmap) {
			prch(NPCC[i].saying+"\n",10);
			getch();
			return;
		}
	}
}//暴力判断NPC的位置是不是下一个位置，如果是，输出NPC对应语句
int tansuo(int xxx) { //地图的核心操作!!!
	RAM_map a=mmp[xxx]; //取得当前地图
	outmap(a);
	int curxxx=xxx;
	char cur=' ';//cur用来存储选择的结果
	while(1) {
		char move=getch();
		if(move==27)//ESC的ASCII码
			break;
		if(move==13)//忘记是什么的ASCII码
			cur=' ';
		if(move=='W'||move=='w') {
			if(a.myx>=1&&a.fnndp[a.myx-1][a.myy]=='-') { //判断是否越界以及下一个点是普通点还是传送点
				cout<<"                                          \n";//因为最后一行可能有NPC的话，输出空格给他清空
				gotoxy(a.myx,a.myy);//光标先到达本来的位置
				cout<<a.fnndp[a.myx][a.myy];//输出这个位置地图本来的字符覆盖掉玩家字符
				a.myx--;//坐标移动
				gotoxy(a.myx,a.myy);//到达移动后位置
				cout<<char(1);//输出玩家位置
				gotoxy(11,0);//光标移动到地图外（接下来要实时输出玩家信息）
			} else { //如果是NPC先和NPC说话，然后直接判断下一个点是不是传送点（两者不会矛盾）
				hinpc(a.myx-1,a.myy,xxx);
				movemap(a.myx-1,a.myy,a,xxx);
			}
			cur='w';//上一步操作是w（因为以后可能要用所以先存着）
		}
		if(move=='S'||move=='s') { //以后操作类似,建议折叠观看
			if(a.myx<a.hang-1&&a.fnndp[a.myx+1][a.myy]=='-') {
				cout<<"                                          \n";
				gotoxy(a.myx,a.myy);
				cout<<a.fnndp[a.myx][a.myy];
				a.myx++;
				gotoxy(a.myx,a.myy);
				cout<<char(1);
				gotoxy(11,0);
			} else {
				hinpc(a.myx+1,a.myy,xxx);
				movemap(a.myx+1,a.myy,a,xxx);
			}
			cur='s';
		}
		if(move=='A'||move=='a') {
			if(a.myy>=1&&a.fnndp[a.myx][a.myy-1]=='-') {
				cout<<"                                          \n";
				gotoxy(a.myx,a.myy);
				cout<<a.fnndp[a.myx][a.myy];
				a.myy--;
				gotoxy(a.myx,a.myy);
				cout<<char(1);
				gotoxy(11,0);
			} else {
				hinpc(a.myx,a.myy-1,xxx);
				movemap(a.myx,a.myy-1,a,xxx);
			}
			cur='a';
		}
		if(move=='D'||move=='d') {
			if(a.myy<a.lie-1&&a.fnndp[a.myx][a.myy+1]=='-') {
				cout<<"                                          \n";
				gotoxy(a.myx,a.myy);
				cout<<a.fnndp[a.myx][a.myy];
				a.myy++;
				gotoxy(a.myx,a.myy);
				cout<<char(1);
				gotoxy(11,0);
			} else {
				hinpc(a.myx,a.myy+1,xxx);
				movemap(a.myx,a.myy+1,a,xxx);
			}
			cur='d';
		}

		if(curxxx!=xxx)//地图切换
			outmap(a),curxxx=xxx;

		gotoxy(11,0);//回到地图外（因为不放心所以又加了一遍）
		pmy();

		//
		/*
		p.nowmap=xxx;
		p.nowplc[0]=a.myx;
		p.nowplc[1]=a.myy;*/
		//outmap(a);
//		cout<<a.myx<<" "<<a.myy<<" "<<endl;
		/*		用来测试的操作，显示坐标。
				puts("按esc以退出\n");*/
	}

}
int gaoshi() {
	prch("搞啥子事？\n",10);
	prch("\n1-到处看看\n2-探索模式\n",10);
	char cz=makechoice(100000,2,'1','2');
	if(cz=='1') {
		int k=clock();
		Sleep(1);
		k*=(clock()+1);
		k%=min(p.level,totguai);
		k++;
		guai a=g[k];
		prch("WoW!一只"+a.des+"的"+a.name+"出现了\n",10);

		int result=atk(a);
		if(result==1) {
			prch("获得",10);
			int ex=a.explost+rand()%(a.level+5);
			cout<<ex;
			prch("点经验",10);
			p.exp+=ex;
			getch();
			levelup();
		}
	} else if(cz=='2') {
		tansuo(1);
	}

}
int main() { //主程序
	//随机
	srand(time(0));
	//设置窗口大小
	system("mode con cols=44 lines=35");
	//加载
	readallmap();
	realloadg("g.in");
	readallmap();
	load(1);
	loadNPC();

	getch();
	prch("一个川味十足的开发中游戏\n",10);
	getch();
	system("cls");
	prch("载入存档？\n是-1，否-2\n",10);
	char ch=makechoice(100000,2,'1','2');
	system("cls");
	if(ch=='2') { //初始信息
		cout<<endl;
		prch("你TM是辣个？\n",10);
		cin>>p.name;
		p.hp=150;
		p.maxhp=150;
		p.exp=0;
		p.mexp=50;
		p.level=1;
		p.mor=0;
		p.damage=10;
	} else {
		prch("你要读取哪个存档？\n",10);
		string a;
		cin>>a;
		char wo[100]= {};
		for(int i=0; i<a.size(); i++)
			wo[i]=a[i];
		loadsave(wo);
		load(1);
		prch("载入成功",10);
	}
	while(1) {
		system("cls");
		prch("你想组啥？\n搞事-1\n商店（未完成）-2\n存档-3\n属性-4\n",1);
		char cz;
		cz=makechoice(10000000,4,'1','2','3','4');
		//其他都没做，就谢了这些
		if(cz=='1')
			gaoshi();
		if(cz=='3') {
			prch("你要存成什么存档？\n",10);
			string a;
			cin>>a;
			char wo[100]= {};
			for(int i=0; i<a.size(); i++)
				wo[i]=a[i];
			saveall(wo);
			prch("存档成功\b",10);
		}
		if(cz=='4')
			pmy(),system("pause");
	}
	return 0;
}
