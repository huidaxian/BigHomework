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
}//�ƶ����
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
}//��Ч����ַ�����һ��һ�������
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
}//���ļ�ֱ�Ӷ����������
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
}//���������Ϣ
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
}//��ȡ�����Ϣ
void load(int n) {
	srand(clock());
	for(int i=1; i<=100; i+=abs(rand()%10)) {
		cout<<"��"<<i<<"%";
		if(i==90||i==91||i==93||i==94)
			Sleep(1000);
		Sleep(n);
		cout<<"\b\b";
		if(i>=10)cout<<"\b";
		if(i>=100)cout<<"\b";
	}
	system("cls");
	prch("�������\n",10);
}//��װ�ڼ��� (���Խ����غ����ӽ�ȥ���Ϳ�����ļ�����)
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
}//����NPO��Ϣ
void loaditem() {
	ifstream weapon("weapon.in");

	weapon.close();
}//��û�������������ϵͳ
void readallmap() { ////////�˴��ص㣡������
	char na[]="map00.in";//��ͼ�����ļ�
	char fa[]="chs00.in";//��ͼ���͵㱣���ļ�
	for(int i=0; i<=10; i++) { //10Ϊ��ͼ����
		na[4]='0'+i%10;
		fa[4]='0'+i%10;
		na[3]='0'+i/10;
		fa[3]='0'+i/10;
		//������i�ŵ�ͼ

		ifstream readmap(na);
		ifstream readchs(fa);
		totmap++;
		int t=0;
		while(readmap>>mmp[totmap].fnndp[t]) { //�����ͼ
			mmp[totmap].lie=strlen(mmp[totmap].fnndp[t]);
			for(int j=0; j<mmp[totmap].lie; j++)
				if(mmp[totmap].fnndp[t][j]==1)
					mmp[totmap].myx=i,mmp[totmap].myy=j;
			t++;
		}
		int js=0;
		while(readchs>>mmp[totmap].chuansong[js][0]) { //�����Ӧ�Ĵ��͵�
			readchs>>mmp[totmap].chuansong[js][1];
			readchs>>mmp[totmap].chuansong[js][2];
			readchs>>mmp[totmap].chuansong[js][3];
			js++;
		}
		mmp[totmap].totchs=js;//�����͵���Ϣ
		mmp[totmap].lie=strlen(mmp[totmap].fnndp[1]);
		mmp[totmap].hang=t-1;
		readmap.close();
	}
}
void pguai(guai a) {
	cout<<"\n--------------------\n";
	cout<<a.des<<"��"<<a.name<<endl;
	cout<<"ʣ��Ѫ����"<<a.hp<<endl;
	cout<<"��������"<<a.damage<<endl;
	cout<<"���ף�"<<a.mor<<endl;
	cout<<"�ȼ���"<<a.level<<endl;
	cout<<"\n--------------------\n";
}//������ʾ
void pmy() {
	puts("\n--------------------\n");
	cout<<p.name<<endl;
	puts("ʣ��Ѫ����");
	cout<<p.hp<<"/"<<p.maxhp<<endl;
	puts("��������");
	cout<<p.damage<<endl;
	puts("���ף�");
	cout<<p.mor<<endl;
	puts("����:");
	cout<<p.exp<<"/"<<p.mexp<<endl;
	puts("�ȼ���");
	cout<<p.level<<endl;
	puts("\n--------------------\n");
}//������ʾ


//�˴�Ϊɧ���������Բ��ÿ�
char makechoice(int bb,int a,...) { //������������
	va_list arg_ptr;
	va_start(arg_ptr,a);//�������������ʽ
	char cho[1000];
	char arg;
	for(int i=0; i<a; i++) {
		arg=va_arg(arg_ptr,int);//��ȡ��������
		cho[i]=arg;
	}
	va_end(arg_ptr);
	char cz;
	int i=0;
	int t=0;
	while(1) { //ͨ������AD����ѡ��
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
	return cho[i];//����ѡ��Ľ��
}





void levelup() {
	if(p.exp>=p.mexp) {
		prch("��������!!",100);
		pmy();
		p.damage*=1.1;
		p.maxhp*=1.1;
		p.mor+=0.5;
		p.hp=p.maxhp;
		p.exp-=p.mexp;
		p.level++;
		p.mexp*=1.2;
		cout<<"���Ըı�Ϊ:"<<endl;
		pmy();
		getch();
		system("cls");
	}
}//�ȼ�����
int atk(guai a) {
	srand(clock());
	Sleep(500);
	while(1) {
		getch();
		system("cls");
		pmy();
		pguai(a);
		prch("����������\n 1 �򲻹������� \n 2 ����һ��\n",10);
		int timet=0;
		char cz=makechoice(200,2,'1','2');
		if(cz=='1') {
			int moved=abs(rand()*rand())%20;
			if(moved==0) {
				prch("\nҮ~��ƨ���޻�������\n",10);
				return -1;
			} else
				prch("\n�ܵ������Կ�\n",10);
		} else if(cz=='2') {
			int moved=abs(clock()*(clock()+1)*(clock()+1))%10+p.damage;
			prch("\n"+p.name+"Ū��"+a.name,10);
			cout<<moved;
			prch("��ô���Ѫ\a",10);
			a.hp-=moved;
			if(moved>p.damage*100)
				Sleep(20),prch("\n�����ӵ��˺�������\a\n",10);
		}
		if(a.hp<=0) {
			prch("\n��Ū����"+a.des+"��"+a.name+'\n',1);
			return true;
		}
		int moved=abs(clock()*(clock()+1)*(clock()+1))%10+a.damage;
		prch("\n�������Ū��",10);
		cout<<moved;
		prch("��Ѫ\n",10);
		p.hp-=moved;
		if(p.hp<=0) {
			prch("rua!,������\n",1);
			return false;
		}
	}
}//�ſ�(Ц)��ս������
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
}//���µ�ͼ��ʾʱ�����ͼ
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
}//��Ϊ���͵���٣������ұ����ж���һ��λ���ǲ��Ǵ��͵� �Լ����͵�������ͼ
void hinpc(int x,int y,int xxx) {
	for(int i=0; i<totNPC; i++) {
		if(x==NPCC[i].x&&y==NPCC[i].y&&xxx==NPCC[i].whichmap) {
			prch(NPCC[i].saying+"\n",10);
			getch();
			return;
		}
	}
}//�����ж�NPC��λ���ǲ�����һ��λ�ã�����ǣ����NPC��Ӧ���
int tansuo(int xxx) { //��ͼ�ĺ��Ĳ���!!!
	RAM_map a=mmp[xxx]; //ȡ�õ�ǰ��ͼ
	outmap(a);
	int curxxx=xxx;
	char cur=' ';//cur�����洢ѡ��Ľ��
	while(1) {
		char move=getch();
		if(move==27)//ESC��ASCII��
			break;
		if(move==13)//������ʲô��ASCII��
			cur=' ';
		if(move=='W'||move=='w') {
			if(a.myx>=1&&a.fnndp[a.myx-1][a.myy]=='-') { //�ж��Ƿ�Խ���Լ���һ��������ͨ�㻹�Ǵ��͵�
				cout<<"                                          \n";//��Ϊ���һ�п�����NPC�Ļ�������ո�������
				gotoxy(a.myx,a.myy);//����ȵ��ﱾ����λ��
				cout<<a.fnndp[a.myx][a.myy];//������λ�õ�ͼ�������ַ����ǵ�����ַ�
				a.myx--;//�����ƶ�
				gotoxy(a.myx,a.myy);//�����ƶ���λ��
				cout<<char(1);//������λ��
				gotoxy(11,0);//����ƶ�����ͼ�⣨������Ҫʵʱ��������Ϣ��
			} else { //�����NPC�Ⱥ�NPC˵����Ȼ��ֱ���ж���һ�����ǲ��Ǵ��͵㣨���߲���ì�ܣ�
				hinpc(a.myx-1,a.myy,xxx);
				movemap(a.myx-1,a.myy,a,xxx);
			}
			cur='w';//��һ��������w����Ϊ�Ժ����Ҫ�������ȴ��ţ�
		}
		if(move=='S'||move=='s') { //�Ժ��������,�����۵��ۿ�
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

		if(curxxx!=xxx)//��ͼ�л�
			outmap(a),curxxx=xxx;

		gotoxy(11,0);//�ص���ͼ�⣨��Ϊ�����������ּ���һ�飩
		pmy();

		//
		/*
		p.nowmap=xxx;
		p.nowplc[0]=a.myx;
		p.nowplc[1]=a.myy;*/
		//outmap(a);
//		cout<<a.myx<<" "<<a.myy<<" "<<endl;
		/*		�������ԵĲ�������ʾ���ꡣ
				puts("��esc���˳�\n");*/
	}

}
int gaoshi() {
	prch("��ɶ���£�\n",10);
	prch("\n1-��������\n2-̽��ģʽ\n",10);
	char cz=makechoice(100000,2,'1','2');
	if(cz=='1') {
		int k=clock();
		Sleep(1);
		k*=(clock()+1);
		k%=min(p.level,totguai);
		k++;
		guai a=g[k];
		prch("WoW!һֻ"+a.des+"��"+a.name+"������\n",10);

		int result=atk(a);
		if(result==1) {
			prch("���",10);
			int ex=a.explost+rand()%(a.level+5);
			cout<<ex;
			prch("�㾭��",10);
			p.exp+=ex;
			getch();
			levelup();
		}
	} else if(cz=='2') {
		tansuo(1);
	}

}
int main() { //������
	//���
	srand(time(0));
	//���ô��ڴ�С
	system("mode con cols=44 lines=35");
	//����
	readallmap();
	realloadg("g.in");
	readallmap();
	load(1);
	loadNPC();

	getch();
	prch("һ����ζʮ��Ŀ�������Ϸ\n",10);
	getch();
	system("cls");
	prch("����浵��\n��-1����-2\n",10);
	char ch=makechoice(100000,2,'1','2');
	system("cls");
	if(ch=='2') { //��ʼ��Ϣ
		cout<<endl;
		prch("��TM��������\n",10);
		cin>>p.name;
		p.hp=150;
		p.maxhp=150;
		p.exp=0;
		p.mexp=50;
		p.level=1;
		p.mor=0;
		p.damage=10;
	} else {
		prch("��Ҫ��ȡ�ĸ��浵��\n",10);
		string a;
		cin>>a;
		char wo[100]= {};
		for(int i=0; i<a.size(); i++)
			wo[i]=a[i];
		loadsave(wo);
		load(1);
		prch("����ɹ�",10);
	}
	while(1) {
		system("cls");
		prch("������ɶ��\n����-1\n�̵꣨δ��ɣ�-2\n�浵-3\n����-4\n",1);
		char cz;
		cz=makechoice(10000000,4,'1','2','3','4');
		//������û������л����Щ
		if(cz=='1')
			gaoshi();
		if(cz=='3') {
			prch("��Ҫ���ʲô�浵��\n",10);
			string a;
			cin>>a;
			char wo[100]= {};
			for(int i=0; i<a.size(); i++)
				wo[i]=a[i];
			saveall(wo);
			prch("�浵�ɹ�\b",10);
		}
		if(cz=='4')
			pmy(),system("pause");
	}
	return 0;
}
