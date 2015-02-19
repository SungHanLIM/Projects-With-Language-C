#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>		//SetConsoleCursorPosition(), GetStdHandle()

int _CommonSense=0;			//�Ϲݻ�� ȹ������
int _Korea=0;				//���� ȹ������
int _World=0;				//����� ȹ������
//##########[���� ���� ����ü, �Լ�, ��������]##########//
typedef struct quiz_q
{
	char answer[20];//����
	char told[100]; //����
	char hint[100]; //��Ʈ
}quiz_q;

quiz_q quiz[10];						//����ü �迭 (10����)
void init01();							//���繮�� �Լ� ����
void init02();							//����繮�� �Լ� ����
void init03();							//�Ϲݻ�Ĺ��� �Լ� ����
void one_print(int quiz_count);			//������ȣ���
void two_print(int i);					//���� ���
void solution_CommonSense();			//��������
void solution_Korea();					//��������
void solution_World();					//��������
int ok[10];								//�����ߺ��˻�
int i=0,j = 0;							//for���� ���� ����
int count=0;
int inpPoint=0;							//����� �Է¹��� ����
int selection = 0;						//�޴����� selection����
int quiz_count = 1;
char answel[10];
//##########[������ ���� ǥ�� �������� �� �Լ�]##########//
void number_check(int k,int i);
void digit_print(int dim[], int line);
int line=0;
int zero[20] =
		{1,1,1,1,
		1,0,0,1,
		1,0,0,1,
		1,0,0,1,
		1,1,1,1};
int one[20] =
		{0,0,1,0,
		0,0,1,0,
		0,0,1,0,
		0,0,1,0,
		0,0,1,0};
int two[20] =
		{1,1,1,1,
		0,0,0,1,
		1,1,1,1,
		1,0,0,0,
		1,1,1,1};
int three[20] =
		{1,1,1,1,
		0,0,0,1,
		1,1,1,1,
		0,0,0,1,
		1,1,1,1};
int four[20] =
		{1,0,0,1,
		1,0,0,1,
		1,1,1,1,
		0,0,0,1,
		0,0,0,1};
int five[20] =
		{1,1,1,1,
		1,0,0,0,
		1,1,1,1,
		0,0,0,1,
		1,1,1,1};
int six[20] =
		{1,1,1,1,
		1,0,0,0,
		1,1,1,1,
		1,0,0,1,
		1,1,1,1};
int seven[20] =
		{1,1,1,1,
		1,0,0,1,
		1,0,0,1,
		0,0,0,1,
		0,0,0,1};
int eight[20] =
		{1,1,1,1,
		1,0,0,1,
		1,1,1,1,
		1,0,0,1,
		1,1,1,1};
int nine[20] =
		{1,1,1,1,
		1,0,0,1,
		1,1,1,1,
		0,0,0,1,
		0,0,0,1};
//##########[���� ���� �������� �� �Լ�]##########//
void display_rule();									//���� �� ��÷ �Խ���
void reel_series(int r[][3]);							//������ ���� �Լ�
void display_reel(char rc[][3],int r[][3],int index);	//������ ���� ���� �Լ�
int game_control(char reel[][3],int reel_num[][3]);		//������ ��Ʈ ���� ��/�� ��� �Լ�
int return_hint(int r[],int *case_n);					//������ ��Ʈ ���� ��/�� ��� �Լ�
int slot_machine();										//���Ըӽ� Display
//##########[�ܼ� â ���� Define ����]##########//
#define col GetStdHandle(STD_OUTPUT_HANDLE)				//�ܼ�â�� �ڵ����� �ޱ� 
#define WHITE SetConsoleTextAttribute( col,0x000f);		//���
#define SKY SetConsoleTextAttribute( col, 0x000b);		//�ϴû�
#define YEL SetConsoleTextAttribute( col, 0x000e);		//�����
#define HIG SetConsoleTextAttribute( col, 0x000d);		//����
//##########[����Ű ASCII�� Define ����]##########//
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN  80
//##########[��������� ���� ����ü]##########//
typedef struct 
{
	char id[12];
	char pass[14];
	char name[12];
	int ranking;
	int score;
	int getScore_CommonSense;							//�Ϲݻ�� ȹ������
	int getScore_Korea;									//���� ȹ������
	int getScore_World;									//����� ȹ������
} person;
//##########[����Ű ASCII�� Define ����]##########//
void front_menu();
//##########[�ʱ�ȭ �Լ�]##########//
void Init_people();										//����������� ���� �ʱ�ȭ�Լ�
void ranking();											//��ŷ�����Լ�
void gotoxy(int x, int y);
//##########[ȸ���� ���� �Լ�]##########//
void search_people(void);								//ȸ���˻�
void new_people(void);									//ȸ������
void Login();											//�α���
void delete_data(void);									//ȸ������
//##########[���� ���� ���� �Լ�]##########//
void save_score(); 
//##########[������ ���� �Լ�]##########//
void master_login(void);								//�����ڸ�� - �α���
void master_menu(void);									//�����ڸ�� - �޴�����
void master_all_print(void);							//�����ڸ�� - ������ں���
void main_print(void);									//����ȭ�� ����Ʈ
//##########[�޴����� �̵� ���� �Լ�]##########//
void move_01(); 
void move_02();
void main_p();
void main_p2();
//##########[��Ÿ ���� ����]##########//
char *file = "person.txt";								//����������� *���ϸ�*
person* d;												//��������½� �����Ҵ�
int total_block;										//����ڰ� ������� ����� ����
person* login_person;									//�α��� ����� ����
void front_menu()			
{
	int select;
	while(1)
	{
		Init_people();					//������� ������ �޸��忡�� �ҷ��´�
		system("cls");
		main_print();
		gotoxy(49,23);					//���θ޴� Ŀ����ǥ����
		scanf("%d",&select);
		fflush(stdin);
		switch(select)
		{
		case 1:							// *ȸ������ 
			system("cls");
			new_people();  
			break;
		case 2:							// *�α���
			system("cls");
			Login();
			break;
		case 3:							// *�˻� 
			system("cls");
			search_people();
			break;
		case 4:							// *��ŷ		
			system("cls");  
			ranking();
			break;
		case 5:							// *������ ���
			system("cls");  
			master_login();				//������ID : �ӽ���  ������PASS : 6411 
			system("cls");
			break;
		case 6:							// *����
			printf("\n\n\n");
			exit(1);		
		default :						 // *1 ~ 6���� ��ȣ�� �ƴ� �ٸ���ȣ�� ���ȴٸ�
			printf("Wrong number. Please re-enter\n");
		}
	} 
}
int main(void)
{	
	front_menu();
	return 0;
}
void gotoxy(int x, int y)
{
	COORD Pos = {x - 1, y - 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void main_print()
{
	YEL;
	printf("    =============================================================== \n");
	printf("                ��   Welcome To My Quiz Program   ��            \n");
	printf("    =============================================================== \n");
	WHITE;
	printf("\t����������������������������������������������\n");
	printf("\t��  1. ȸ������                             ��\n");
	printf("\t����������������������������������������������\n");
	printf("\t����������������������������������������������\n");
	printf("\t��  2. �α���                               ��\n");
	printf("\t����������������������������������������������\n");
	printf("\t����������������������������������������������\n");
	printf("\t��  3. ���� �˻�                            ��\n");
	printf("\t����������������������������������������������\n");
	printf("\t����������������������������������������������\n");
	printf("\t��  4. ��ŷ                                 ��\n");
	printf("\t����������������������������������������������\n");
	printf("\t����������������������������������������������\n");
	printf("\t��  5. ������ ���                          ��\n");
	printf("\t����������������������������������������������\n");
	printf("\t����������������������������������������������\n");
	printf("\t��  6. ����                                 ��\n");
	printf("\t����������������������������������������������\n");
	printf("\t                            ������������������       \n");
	printf("\t                            ��Number : [ ]  ��       \n");
	printf("\t                            ������������������       \n"); 	
}
//##########[ȸ�� �Լ�]##########//
void Init_people()
{
	FILE *fpr;
	fpr = fopen(file,"rb");
	if(fpr == NULL){
		printf("File Open�� �����߻�!");
		exit(1);
	}
	fseek(fpr,0L,SEEK_END);
	total_block = ftell(fpr) / sizeof(person); // ȸ���� ��
	fseek(fpr,0L,SEEK_SET);
	d = (person *)malloc(sizeof(person) * total_block);
	fread(d,sizeof(person),total_block,fpr);
	fclose(fpr);
}
//##########[ȸ�� ã�� �Լ�]##########//
void search_people()
{
	int i, check = 0;
	char name[12];						//�̸��Է¹迭
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t               ��      ID search      ��                   \n");
	printf("\t===========================================================\n\n");
	WHITE;
	printf("\t   ������������������������������������������������������\n");
	printf("\t   ��         Name : ____________           (12�� �̳�)��\n");
	printf("\t   ������������������������������������������������������\n");
	gotoxy(30,7);
	gets(name);							// *�̸� �Է�
	puts("");
	// ******* �̸� �˻� ******* //
	for(i=0;i<total_block;i++)
		if(strcmp(name,d[i].name) == 0)
		{
			puts("");
			check = 1;					 // *����� �̸��� txt���Ͽ� �ִٸ�
			
			printf("\t\t������������������������������������������������\n");
			printf("\t\t����ŷ : %-3d��                                ��\n",d[i].ranking);
			printf("\t\t������������������������������������������������\n");
			printf("\t\t������������������������������������������������\n");
			printf("\t\t���̸� : %-7s                              ��\n",d[i].name); 
			printf("\t\t������������������������������������������������\n");
			printf("\t\t������������������������������������������������\n");
			printf("\t\t��ȹ������  :  %-3d��                          ��\n",d[i].score);
			printf("\t\t������������������������������������������������\n");
			printf("\t\t������������������������������������������������\n");
			printf("\t\t������:%-3d�� �������:%-3d�����Ϲݻ��:%-3d��   ��\n",d[i].getScore_Korea,d[i].getScore_World,d[i].getScore_CommonSense);
			printf("\t\t������������������������������������������������\n");
			HIG;
			printf("\t\t\t   Press Enter Key !!\n");
			getch();
			break;
		}
		if(check == 0)					//����� �̸��� txt���Ͽ� ���ٸ�
		{
			HIG;
			printf("\t\n\t\t\t   Non-existent users !! \n");
            getch();
		}
}		
//##########[ȸ�� ���� �Լ�]##########//
void new_people(void)	
{
	int i,j, check = 0;
	char c;					// ��й�ȣ�� *�� ������Ͽ� �ѱ��ھ� ���ڸ� �Է¹ޱ����� ����
	FILE *fpa;
	person aa;
	FILE *fpr;
	fpa = fopen(file,"ab"); // *txt �ǵڿ� ����
	if(fpa == NULL)
	{
		printf("File Open�� ���� �߻�!");
		exit(1);
	}
	do{
		check = 0;							 // *���̵� �ߺ��˻�( :1�̸� �ߺ� :0�̸� ��밡�� ) 
		system("cls");
		YEL;
		printf("\n");
		printf("\t===========================================================\n");
		printf("\t               ��      Admission      ��                   \n");
		printf("\t===========================================================\n\n");
		WHITE;
		printf("\t   ������������������������������������������������������\n");
		printf("\t   ��          I D : ____________           (12�� �̳�)��\n");
		printf("\t   ������������������������������������������������������\n");
		gotoxy(30,7);
		gets(aa.id);						// *���̵� �Է�
		fpr = fopen(file,"rb"); 
		if(fpr == NULL)
		{
			printf("File Open�� �����߻�!");
			exit(1);
		}
		puts("");
		for(i=0;i<total_block;i++){
			if(strcmp(aa.id,d[i].id) == 0)  // *�Է��� id�� txt�� ����� id�� �Ȱ��ٸ�
			{ 
				HIG;
				printf("\t\t\t Duplicate ID exists !!\n");
				check = 1;					// *�ߺ��ƴٰ� 1�� üũ
				getch();					// *�ƹ�Ű�� �Է¹���
				break;
			}
		}
	}while(check == 1);						// *�ߺ��Ǹ� ���ѷ���
	printf("\t   ������������������������������������������������������\n");
	printf("\t   ��     Password : ____________           (14�� �̳�)��\n");
	printf("\t   ������������������������������������������������������\n");
	// **** ��й�ȣ *�� ����ֱ� **** //
	i = 0;
	while(i<=13)
	{
		gotoxy(30,10);						// *��й�ȣ �Է� ��ǥ
		for(j=0;j<13;j++){					// *13�ڸ� _�� �������
			putchar('_');
		}
		gotoxy(30,10);
		for(j=0;j<i;j++){					//i�� �Է��� �����̱� ������ 
			putchar('*');					//�Է��� ������ŭ *�� �����
		}
		c = getch();						// *���� �Ѱ� �Է¹���(���������ÿ� ����c�� ����)
		if(c == '\r'){						// *Enter �Է½� 
			aa.pass[i] = '\0';				// *������ ���ڴ� NULL����
			break;
		}else if(c == '\b'){				// *Back Space �Է½�
			if(i > 0){						// *i���� 0���� Ŀ������ ó���ڸ����� �ڷ� �з����� ����
				i--;							// *Back Space ��� ������ ���� i�� ��ĭ �ڷ� �о���
			}
		}else{								// *Enter or BackSpace�� �ƴϸ� 
			aa.pass[i++] = c;				// *�н����� �Է�
		}
	}
	puts("");
	puts("");
	printf("\t   ������������������������������������������������������\n");
	printf("\t   ��         Name : ____________            (6�� �̳�)��\n");
	printf("\t   ������������������������������������������������������\n");
	gotoxy(30,13);
	gets(aa.name);							// *�̸� �Է� 
	aa.score = 00;
	aa.ranking=01;
	aa.getScore_CommonSense=0;				//�Ϲݻ�� ���� �ʱ�ȭ
	aa.getScore_Korea=0;					//���� ���� �ʱ�ȭ
	aa.getScore_World=0;					//����� ���� �ʱ�ȭ
	HIG;
    puts("");
	puts("");
    printf("\t\t\t   ����������������������\n");
	printf("\t\t\t   ��  save completed! ��\n"); 
	printf("\t\t\t   ����������������������\n"); 
	getch();
	fseek(fpa,0L,SEEK_END);
	fwrite(&aa,sizeof(person),1,fpa); 
	fclose(fpa);
}
//##########[ȸ�� �α��� �Լ�]##########//
void Login()
{
	long i,j,k;
	int check= 0;						// *���̵�� ��й�ȣ�� �¾Ҵ��� üũ
	int count = 0;						// *���̵�� ��й�ȣ�� 3���̻� Ʋ�ȴ��� üũ
	char id[12];
	char pass[14];
	char c;								// *��й�ȣ�� *�� ����ֱ����� ���� char����
	while(check == 0){					// *���̵�� ����� ���������� ���ѷ���
		YEL;
		printf("\n");
		printf("\t===========================================================\n");
		printf("\t               ��     L o g - i n       ��                 \n");
		printf("\t===========================================================\n\n");
		WHITE;
		printf("\t   ������������������������������������������������������\n");
		printf("\t   ��          I D : ____________           (12�� �̳�)��\n");
		printf("\t   ������������������������������������������������������\n");
		gotoxy(30,7);					// *���̵� �Է� ��ǥ
		gets(id);						// *���̵� �Է¹���
		puts("");
		for(i=0;i<total_block;i++){
			if(strcmp(id,d[i].id) == 0) // *id�� txt�� ����� id�� ��ġ�Ѵٸ�
				break;				    // *break�� �ɾ� i�� �״�� �����ص�
		}
		WHITE;
		printf("\t   ������������������������������������������������������\n");
		printf("\t   ��     Password : ____________           (14�� �̳�)��\n");
		printf("\t   ������������������������������������������������������\n");
		k = 0;
		while(k<=13)					// *��й�ȣ�� �ִ� 14�ڸ����� 
		{
			gotoxy(30,10);				// *��й�ȣ �Է� ��ǥ
			for(j=0;j<13;j++){			// *13�ڸ� _�� �������
				putchar('_');
			}
			gotoxy(30,10);
			for(j=0;j<k;j++){			// *k�� �Է��� �����̱� ������ 
				putchar('*');			// *�Է��� ������ŭ *�� �����
			}
			c = getch();				// *���� �Ѱ� �Է¹���(���������ÿ� ����c�� ����)
			if(c == '\r'){				// *Enter �Է½� 
				pass[k] = '\0';			// *������ ���ڴ� NULL����
				break;
			}else if(c == '\b'){		// *Back Space �Է½�
				if(k > 0){				// *k���� 0���� Ŀ������ ó���ڸ����� �ڷ� �з����� ����
					k--;					// *Back Space ��� ������ ���� k�� ��ĭ �ڷ� �о���
				}
			}else{						// *Enter or BackSpace�� �ƴϸ� 
				pass[k++] = c;			// *�н����� �Է�
			}
		}
		puts("");
		puts("");
		if(strcmp(pass,d[i].pass) == 0){ // *��й�ȣ�� ��ġ�Ѵٸ�
			check = 1;					 // *��ġ�� :1�� check�� ����
			HIG;
			printf("\n\t\t\tConnection and Press Enter Key \n"); 
			login_person = &d[i];		 //Change
			getch();
			system("cls");
			move_01(); 
			break;
		}else{							 // *��й�ȣ�� ��ġ���� ������ �ٽ� ����
			HIG;
			printf("\n\t\t   ID does not exist or Password error !! \n");
			count++;
			getch();
		}
		if(count == 3) {				 // *��й�ȣ 3������ �Է°���* //
			HIG;
			printf("\n\t\t\tPassword three times the error !! \n");
			getch();
			break;
		}
		system("cls");
	}
}
//##########[���� ���� �Լ�]##########//
void save_score()
{
	//## �޸��忡 ������ �����ϱ� ���� ������ ##
	int i; 
	FILE *fpr;
	person aa;	//
	// ** ���� �̸��� ã�� ������ �Է��� ** //
	for(i=0;i<total_block;i++)
	{
		if(strcmp(login_person->id , d[i].id) == 0) // *�̸��� ��ġ�ϸ�
		{
			d[i].getScore_Korea+=_Korea;			//���� ȹ�� ���� ����
			d[i].getScore_World=_World;				//����� ȹ�� ���� ����
			d[i].getScore_CommonSense=_CommonSense; //�Ϲݻ�� ȹ�� ���� ����
			d[i].score += inpPoint;
			break;
		}
	}
	//�������ϱ�//
	for(i=0 ; i<total_block; i++)
		{
			for(j=0 ; j<total_block; j++)
			{
				if (d[i].score < d[j].score)
					d[i].ranking++;
			}
		}
	fflush(stdin);
	// ������ �޸��忡 �ٽ� ���� // 
	fpr = fopen(file,"wb");
	fseek(fpr,0L,SEEK_SET);
	fwrite(d,sizeof(person), total_block, fpr);
	fclose(fpr);	
}
//##########[������ �Լ�]##########//
//##########[������-����]##########//
void delete_data(void)
{
	long i , total_block;
	int check = 0;
	char name[12];
	FILE *fpr;
	fpr = fopen(file,"rb");									 // *���� ����
	if(fpr == NULL){
		printf("File Open�� �����߻�!");
		exit(1);
	}
	fseek(fpr,0L,SEEK_END);
	total_block = ftell(fpr)/sizeof(person);				// *txt�� ����� ȸ����
	fseek(fpr,0L,SEEK_SET);
	fread(d,sizeof(person),total_block,fpr);
	fclose(fpr);
	// ** ����� ���� ��� ** //	
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t               ��    All user information    ��            \n");
	printf("\t===========================================================\n\n");
	puts("");
	WHITE;
	printf("\t ������������������������������������������\n");
	printf("\t ��%-2s ��%-8s     ��%-13s��\n","Ranking","NickName","Score");
	for(i=0;i<total_block;i++)
	{
		if(!strcmp(d[i].name , "Administrator")) continue;  // *������ ���� ���
		printf("\t ��%-2d      ��%-8s     ��%-13d��\n",d[i].ranking,d[i].name,d[i].score);
	}
	printf("\t ������������������������������������������\n");
	// ** ������ �̸��Է��ϰ� ���� ** //
	HIG;
	printf("\n\t    Enter the name of the user to delete and Press Enter\n");
	printf("\t\t[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
	gets(name);												// *�̸��Է�
	for(i=0;i<total_block;i++){
		if(strcmp(name,d[i].name) == 0)						// *�̸��� ��ġ�ϸ�
		{
			check = 1;										// *��ġ�� :1�� check�� ����
			d[i] = d[total_block - 1];						// *������ �����͸� ������Ϳ� �־���
			total_block--;									// *ȸ���� �Ѹ� ����
		}													//(txt�� �����Ҷ� ������ �����ʹ� ������) 
	}
	if(check == 0) 
		HIG;
	printf("No matching data\n"); 
	// ** ������ ���� �Ϸ� ** //
	// ���� �� �޸��忡 �ٽ� ���� // 
	fpr = fopen(file,"wb");
	fseek(fpr,0L,SEEK_SET);
	fwrite(d,sizeof(person), total_block, fpr);				// *������ ȸ���� ������ �� txt�� ����
	fclose(fpr);
	// ** ������ ������ ��� ** // 
	system("cls");
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t         ��   After deleting the list of users    ��       \n");
	printf("\t===========================================================\n\n");
	WHITE;
	printf("\t ������������������������������������������\n");
	printf("\t ��%-2s ��%-8s     ��%-13s��\n","Ranking","NickName","Score");
	for(i=0;i<total_block;i++)
	{
		if(!strcmp(d[i].name , "Administrator")) continue;  // *������ ���� ���
		printf("\t ��%-2d      ��%-8s     ��%-13d��\n",d[i].ranking,d[i].name,d[i].score);
	}
	printf("\t ������������������������������������������\n");
	HIG;
	printf("\n\t\t\tPress any key to return to the menu\n");
	getch();
}	
//##########[������ �α��� �Լ�]##########//
// * ������ ID : �ӽ��� ������ Pass : 6411 * //
void master_login(void)
{
	long i,j,k;
	int check= 0;						// *���̵�� ����� ��ġ�ϴ��� üũ 
	int count  = 0;						// *3���̻� Ʋ�ȴ��� üũ
	char id[12];
	char pass[14];
	char c;
	while(check == 0)
	{									// *���̵�� ��й�ȣ�� ��ġ���� ������ ���ѷ���
		YEL;
		printf("\n");
		printf("\t===========================================================\n");
		printf("\t               ��    Administrator Mode     ��             \n");
		printf("\t===========================================================\n\n");
		WHITE;
		printf("\t   ������������������������������������������������������\n");
		printf("\t   �� Administrator ID : ____________       (12�� �̳�)��\n");
		printf("\t   ������������������������������������������������������\n");
		gotoxy(34,7);					// *���̵� �Է� ��ǥ
		gets(id);						// *���̵� �Է�
		puts("");
		for(i=0;i<total_block;i++)
		{
			if(strcmp(id,"�ӽ���") == 0)// *�����ھ��̵� (�ӽ���)�� ��ġ�ϸ�
				break;                  // * for�� ���߰� i�� ����
		}
		WHITE;
		printf("\t   ������������������������������������������������������\n");
		printf("\t   ��Administrator Password : ____________  (14�� �̳�)��\n");
		printf("\t   ������������������������������������������������������\n");
		// **** ��й�ȣ *�� ����ֱ� **** //
		k = 0;
		while(k<=13)					// *��й�ȣ�� �ִ� 14�ڸ����� 
		{
			gotoxy(39,10);				// *��й�ȣ �Է� ��ǥ
			for(j=0;j<13;j++)
			{
				putchar('_');			// *13�ڸ� _�� �������
			}
			gotoxy(39,10);
			for(j=0;j<k;j++)			// *k�� �Է��� �����̱� ������ 
			{
				putchar('*');			// *�Է��� ������ŭ *�� �����
			}
			c = getch();				// *���� �Ѱ� �Է¹���(���������ÿ� ����c�� ����)
			if(c == '\r')
			{							// *Enter �Է½� 
				pass[k] = '\0';			// *������ ���ڴ� NULL����
				break;
			}
			else if(c == '\b')
			{							// *Back Space �Է½�
				if(k > 0)
				{						// *k���� 0���� Ŀ������ ó���ڸ����� �ڷ� �з����� ����
					k--;					// *Back Space ��� ������ ���� k�� ��ĭ �ڷ� �о���
				}
			}
			else
			{							// *Enter or BackSpace�� �ƴϸ� 
				pass[k++] = c;			// *�н����� �Է�
			}
		}
		puts("");
		puts("");
		if(!strcmp(pass,"6411")){		// *�����ں��(6411)�� ��ġ�ϸ�
			check = 1;					// *while�� ����
			HIG;
            printf("\n\t\t �ӽ��� �� Connection .. Press Enter Key \n"); 
			getch();
			system("cls");
			master_menu();				// *������ �޴� ���
			break;
		}else{
			HIG;
			printf("\n\t\t   ID does not exist or Password error !! \n");	
			getch();
		}
		if(count == 3) {				// *��й�ȣ ���� 3������ ���� *//
			HIG;
			printf("\n\t\t\tPassword three times the error !! \n");
			getch();
			break;
		}
		system("cls");
	}
}
//##########[������ ��� �޴�]##########//
void master_menu()
{
	int select = 0;
	while(select != 3)
	{
		system("cls");
		YEL;
		printf("\n");
		printf("\t===========================================================\n");
		printf("\t               ��     Administrator Mode     ��            \n");
		printf("\t===========================================================\n\n");
		WHITE;
		printf("\t\t����������������������������������������������\n");
		printf("\t\t��  1. View all users                       ��\n");
		printf("\t\t����������������������������������������������\n");
		printf("\t\t����������������������������������������������\n");
		printf("\t\t��  2. Delete User Information              ��\n");
		printf("\t\t����������������������������������������������\n");
		printf("\t\t����������������������������������������������\n");
		printf("\t\t��  3. Exit Admin Mode                      ��\n");
		printf("\t\t����������������������������������������������\n");
		printf("\t\t                                              \n"); 
		printf("\t\t                            ������������������\n");
		printf("\t\t                            ��Number : [ ]  ��\n");
		printf("\t\t                            ������������������\n"); 
		gotoxy(57,17);
		scanf("%d",&select); // *����ڷκ��� ��ȣ�Է¹���
		fflush(stdin);
		
		switch(select)
		{
		case 1:				// *���ȸ����������
			system("cls");
			master_all_print();
			break;
		case 2:				// *ȸ�������� ���� 
			system("cls");
			delete_data(); 
			break; 
		case 3:				// *����
			system("cls");
			HIG;
			printf("\n\n\n\t\t\tExit Admin Mode... \n");
			Sleep(1500);	//1.5����
		default :			// *1 ~ 3�� ��ȣ�� �ƴ϶�� ȭ�� clear
			system("cls");
		}
	}
}
//##########[������ ���- ��� ����� ����]##########//
void master_all_print() 
{
	long i, total_block;
	FILE *fpr;
	person d[50];								// *txt���� �ҷ��� ȸ��(�ִ� 50��)�迭
	fpr = fopen(file,"rb");						// *���� ����
	if(fpr == NULL){
		printf("File Open�� �����߻�!");
		exit(1);
	}
	fseek(fpr,0L,SEEK_END);
	total_block = ftell(fpr) / sizeof(person);	// *txt����� ȸ�� ��
	fseek(fpr,0L,SEEK_SET);
	fread(d,sizeof(person),total_block,fpr);
	fclose(fpr);
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t               ��    All user information    ��            \n");
	printf("\t===========================================================\n\n");
	puts("");
	WHITE;
	printf("\t ������������������������������������������\n");
	printf("\t ��%-2s ��%-8s     ��%-13s��\n","Ranking","NickName","Score");
	for(i=0;i<total_block;i++)
	{
		if(!strcmp(d[i].name , "Administrator")) continue;  
		printf("\t ��%-2d      ��%-8s     ��%-13d��\n",d[i].ranking,d[i].name,d[i].score);
	}
	printf("\t ������������������������������������������\n");
	
	HIG;
	printf("\n\t\t\tPress any key to return to the menu\n");
	getch();
}
//##########[��ŷ �Լ�]##########//
void ranking()
{
	long i, total_block;
	FILE *fpr;
	person d[50];					// *txt���� �ҷ��� ȸ��(�ִ� 50��)�迭
	fpr = fopen(file,"rb");			// *���� ����
	if(fpr == NULL){
		printf("File Open�� �����߻�!");
		exit(1);
	}
	fseek(fpr,0L,SEEK_END);
	total_block = ftell(fpr) / sizeof(person); // *txt����� ȸ�� ��
	fseek(fpr,0L,SEEK_SET);
	fread(d,sizeof(person),total_block,fpr);
	fclose(fpr);
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t               ��    Ranking information    ��            \n");
	printf("\t===========================================================\n\n");
	puts("");
	WHITE;
	printf("\t ������������������������������������������\n");
	printf("\t ��%-2s ��%-8s     ��%-13s��\n","Ranking","NickName","Score");
	for(i=0;i<total_block;i++)
	{
		if(!strcmp(d[i].name , "Administrator")) continue; 
		printf("\t ��%-2d      ��%-8s     ��%-13d��\n",d[i].ranking,d[i].name,d[i].score);
	}
	printf("\t ������������������������������������������\n");
	HIG;
	printf("\n\t\t\tPress any key to return to the menu\n");
	getch();
}
//###############   ����Ǯ�̷� �����̴°�  ###############//
//###############   ����Ǯ��/����/�����޴�  ###############//
void move_01() 
{
	int PosMeX=35, PosMeY=20;
	char c;
	int move = 0;		 //������ ī��Ʈ�Լ�
	main_p();
	gotoxy(PosMeX,PosMeY);
	printf("* User *");
	while(1)			//���� �ݺ�
	{
		if(_kbhit())	//Ű�� �Է��� �����ϰ� Ű�� �ԷµǸ� �Ʒ� ������ ����, ���� Ű�� �ԷµǴ��� �����Ѵ�.
		{
			c=getch(); //���� �ϳ��� �Է¹޴� �Լ�, ���� �ϳ��� �Է¹��� ������ ���Ѵ���ϴ� �Լ�������
					   //_kihit() �Լ��� Ű�� �Էµ� ���� �����ؼ� ��� �ð��� ����
			if(c=='a') PosMeX--;
			else if(c=='d') PosMeX++;
			else if(c=='w') PosMeY--;
			else if(c=='s') PosMeY++;
			system("cls");
			main_p();
			SKY;
			gotoxy(PosMeX,PosMeY);
			if(move % 2 == 0)	printf("���ۦ�");
			else printf("���ۦ�");
			move++;
			//[�����޴�] ����//
			if(( PosMeX == 55 || PosMeX == 56 || PosMeX == 57 || PosMeX == 58 || PosMeX == 59 ) && PosMeY == 15 )
			{
				WHITE;
				gotoxy(10,20);
				printf("===========================================================\n");
				printf("\t                     �� Wait a minute ��                 \n");
				gotoxy(10,22);
				printf("===========================================================\n\n\n");
				Sleep(1500); 
				system("cls");
				break;
			}
			//[����Ǯ��] ����// 
			if( ( PosMeX == 13 || PosMeX == 14 || PosMeX == 15 || PosMeX == 16 || PosMeX == 17 ) && PosMeY == 15 )
			{
				WHITE;
				gotoxy(10,20);
				printf("===========================================================\n");
				printf("\t                     �� Wait a minute ��                 \n");
				gotoxy(10,22);
				printf("===========================================================\n\n\n");
				Sleep(1500); 
				gotoxy(30,20);
				printf("                             ");
				system("cls");
				gotoxy(0,0);
				//���� ����� ��� ���� ȭ������//
				move_02();
				break;
			}
			//[����] ����
			if( ( PosMeX == 35 || PosMeX == 36 || PosMeX == 37 || PosMeX == 38 || PosMeX == 39 ) && PosMeY == 15 )
			{
				int PosMeX=35, PosMeY=20;
				char c;
				int move = 0; 
				WHITE;
				gotoxy(10,20);
				printf("===========================================================\n");
				printf("\t                     �� Wait a minute ��                 \n");
				gotoxy(10,22);
				printf("===========================================================\n\n\n");
				Sleep(1500);
				system("cls");
				main_p2();
				gotoxy(PosMeX,PosMeY);
				printf("* User *");
				while(1) 
				{
					if(_kbhit()) 
					{
						c=getch();
						if(c=='a') PosMeX--;
						else if(c=='d') PosMeX++;
						else if(c=='w') PosMeY--;
						else if(c=='s') PosMeY++;
						system("cls");
						main_p2();
						SKY;
						gotoxy(PosMeX,PosMeY);
						if(move % 2 == 0)	printf("���ۦ�");
						else printf("���ۦ�");
						move++;		
						//�Ϲݻ��
						if(( PosMeX == 55 || PosMeX == 56 || PosMeX == 57 || PosMeX == 58 || PosMeX == 59 ) && PosMeY == 15 )
						{
							system("cls");
							solution_CommonSense();
							_getch();
							break;
						}
						//����
						if( ( PosMeX == 13 || PosMeX == 14 || PosMeX == 15 || PosMeX == 16 || PosMeX == 17 ) && PosMeY == 15 )
						{
							system("cls");
							solution_Korea();
							_getch();
							break;
						}
						//�����
						if( ( PosMeX == 35 || PosMeX == 36 || PosMeX == 37 || PosMeX == 38 || PosMeX == 39 ) && PosMeY == 15 )
						{
							system("cls");
							solution_World();
							_getch();
							break;
						}
					}
				}
				break;
			}
		}
	}
}
//###############   ����/�����/�Ϲݻ��  ###############//
void move_02() 
{
	int PosMeX=35, PosMeY=20;
	char c;
	int move = 0; 
	main_p2();
	gotoxy(PosMeX,PosMeY);
	printf("* User *");
	while(1) 
	{
		if(_kbhit()) 
		{
			c=getch(); 
			if(c=='a') PosMeX--;
			else if(c=='d') PosMeX++;
			else if(c=='w') PosMeY--;
			else if(c=='s') PosMeY++;
			system("cls");
			main_p2();
			SKY;
			gotoxy(PosMeX,PosMeY);
			if(move % 2 == 0)	printf("���ۦ�");
			else printf("���ۦ�");
			move++;
			//�Ϲݻ��
			if(( PosMeX == 55 || PosMeX == 56 || PosMeX == 57 || PosMeX == 58 || PosMeX == 59 ) && PosMeY == 15 )
			{
				init03();
				while(1)
				{
					srand(time(NULL));		
					while(1)					//���� �ߺ��˻�
					{
						i = rand()%10;
						if(ok[i] == 0)
						{
							ok[i] = 1;
							break;
						}
					}
					system("cls");
					count = slot_machine();
					getch();
					system("cls");				
					one_print(quiz_count);
					two_print(i);
					if(count==1)
					{
						printf("��Ʈ : %s \n",quiz[i].hint);
					}
					printf("����  >> ");
					scanf("%s",answel);
					if(!strcmp(quiz[i].answer,answel))
					{
						inpPoint+=10;			//������ �� ���� �� ������ 10���� ����
						printf("�����Դϴ�. �������� �̵� [Enter] \n");
					}
					else
					{
						printf("Ʋ�Ƚ��ϴ�. �������� �̵� [Enter] \n");
					}
					quiz_count++;
					getch();		
					system("cls");
					if(quiz_count==11)
					{
						YEL;
						printf("\n");
						printf("=========================\n");
						printf("��      ȹ�� ����      ��\n");
						printf("=========================\n\n");
						_CommonSense=inpPoint;//�Ϲݻ�� ȹ������ ���� �Ϲݻ��ȹ�������� ����
											  //���� ���� �����ϱ� ����.
						save_score();		  //���� �޸��忡 �Է� �� ����
						//�����гѹ��� ����ǥ��//
						for(line=0;line<=4;line++)
						{
							number_check(inpPoint, line);	
							printf("\n");
						}
						_getch();
						break;
					}
				}
				break;
			}
			//����
			if( ( PosMeX == 13 || PosMeX == 14 || PosMeX == 15 || PosMeX == 16 || PosMeX == 17 ) && PosMeY == 15 )
			{
				init01();
				while(1)
				{
					srand(time(NULL));		
					while(1)					//���� �ߺ��˻�
					{
						i = rand()%10;
						if(ok[i] == 0)
						{
							ok[i] = 1;
							break;
						}
					}
					system("cls");
					count = slot_machine();
					getch();
					system("cls");				
					one_print(quiz_count);
					two_print(i);
					if(count==1)
					{
						printf("��Ʈ : %s \n",quiz[i].hint);
					}
					printf("����  >> ");
					scanf("%s",answel);
					if(!strcmp(quiz[i].answer,answel))
					{
						inpPoint+=10;	
						printf("�����Դϴ�. �������� �̵� [Enter] \n");
					}
					else
					{
						printf("Ʋ�Ƚ��ϴ�. �������� �̵� [Enter] \n");
					}
					quiz_count++;
					getch();		
					system("cls");
					if(quiz_count==11)
					{
						YEL;
						printf("\n");
						printf("=========================\n");
						printf("��      ȹ�� ����      ��\n");
						printf("=========================\n\n");
						_Korea=inpPoint;
						save_score();	
						for(line=0;line<=4;line++)
						{
							number_check(inpPoint, line);	
							printf("\n");	
						}
						_getch();
						break;
					}
				}
				break;
			}
			//�����
			if( ( PosMeX == 35 || PosMeX == 36 || PosMeX == 37 || PosMeX == 38 || PosMeX == 39 ) && PosMeY == 15 )
			{
				init02();
				while(1)
				{
					srand(time(NULL));		
					while(1) 
					{
						i = rand()%10;
						if(ok[i] == 0)
						{
							ok[i] = 1;
							break;
						}
					}
					system("cls");
					count = slot_machine();
					getch();
					system("cls");				
					one_print(quiz_count);
					two_print(i);
					if(count==1)
					{
						printf("��Ʈ : %s \n",quiz[i].hint);	
					}
					printf("����  >> ");
					scanf("%s",answel);
					if(!strcmp(quiz[i].answer,answel))
					{
						inpPoint+=10;	
						printf("�����Դϴ�. �������� �̵� [Enter] \n");
					}
					else
					{
						printf("Ʋ�Ƚ��ϴ�. �������� �̵� [Enter] \n");
					}
					quiz_count++;
					getch();		
					system("cls");
					if(quiz_count==11)
					{
						YEL;
						printf("\n");
						printf("=========================\n");
						printf("��      ȹ�� ����      ��\n");
						printf("=========================\n\n");
						_World=inpPoint;
						save_score();	
						for(line=0;line<=4;line++)
						{
							number_check(inpPoint, line);	
							printf("\n");
						}
						_getch();
						break;
					}
				}
				break;
			}
		}
	}
}
//############### Main01, Main02  ###############//
void main_p()
{
	gotoxy(0,0);
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t                       ��   MENU   ��                      \n");
	printf("\t===========================================================\n\n\n");
	WHITE;
	printf("\t����������   ����������   ����������\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��  <����Ǯ��>  ��   ��    <����>    ��   ��  <�����޴�>  ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t���᦭  ������   ���᦭  ������   ���᦭  ������\n");
	//gotoxy(15,15); //����Ǯ�� �Ա� ��ǥ�� 
	//gotoxy(36,15); //���� �Ա� ��ǥ��
	//gotoxy(58,15); //�����޴� �Ա� ��ǥ�� 
}
void main_p2()
{
	gotoxy(0,0);
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t                       ��   MENU   ��                      \n");
	printf("\t===========================================================\n\n\n");
	WHITE;
	printf("\t����������   ����������   ����������\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��  <��    ��>  ��   ��   <�����>   ��   ��  <�Ϲݻ��>  ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t��              ��   ��              ��   ��              ��\n");
	printf("\t���᦭  ������   ���᦭  ������   ���᦭  ������\n");
	//gotoxy(15,15); //���� �Ա� ��ǥ�� 
	//gotoxy(58,15); //����� �Ա� ��ǥ�� 
	//gotoxy(36,15); //�ͼ��� �Ա� ��ǥ��
}
//##########[���� ����]##########//
void init01()
{
	strcpy(quiz[0].answer,"�̼���"); 
	strcpy(quiz[0].told,"100���� ������ ������ �̸��� �����Դϱ�?");		
	strcpy(quiz[0].hint,"�źϼ�");
	strcpy(quiz[1].answer,"�����Ȳ");
	strcpy(quiz[1].told,"1000���ǿ� ������ ������ �̸��� �����Դϱ�?");
	strcpy(quiz[1].hint,"������������ ���ʸ� ���� ����, ���ư��� �������� �ǹ�");
	strcpy(quiz[2].answer,"��������");
	strcpy(quiz[2].told,"5000���ǿ� ������ ������ �̸��� �����Դϱ�?");
	strcpy(quiz[2].hint,"�ɻ��Ӵ��� �Ƶ�");
	strcpy(quiz[3].answer,"�������");	
	strcpy(quiz[3].told,"10000���ǿ� ������ ������ �̸��� �����Դϱ�?");
	strcpy(quiz[3].hint,"�ƹ�����");
	strcpy(quiz[4].answer,"�Ż��Ӵ�");	
	strcpy(quiz[4].told,"50000���ǿ� ������ ������ �̸��� �����Դϱ�?");
	strcpy(quiz[4].hint,"�����ó");
	strcpy(quiz[5].answer,"�����ֶ�");	
	strcpy(quiz[5].told,"[���]1592~1598��, �� ���ʿ� ���� �츮���� ħ���� �Ϻ����� �ο� :");
	strcpy(quiz[5].hint,"�ѻ��ø");	
	strcpy(quiz[6].answer,"���̻纯");	
	strcpy(quiz[6].told,"[���]��Ȳ�ĸ� �����ϰ� �Ϻ����� ��ȭ�� ȹå�� ���� :");
	strcpy(quiz[6].hint,"�Ϻ� �ڰ��� �溹�� ħ�� ���");
	strcpy(quiz[7].answer,"����");
	strcpy(quiz[7].told,"8��15���� '�����'�̴�. ��ĭ�� �����Դϱ�?");
	strcpy(quiz[7].hint,"������, ��� �豸, ���� ��âȣ");
	strcpy(quiz[8].answer,"�庸��");
	strcpy(quiz[8].told,"�������� �νŸŸŸ� ����, ���� ������ �Ŷ��� ���� :");
	strcpy(quiz[8].hint,"�ٴ��� ��");
	strcpy(quiz[9].answer,"���");	
	strcpy(quiz[9].told,"���翬�ձ�(5��)�� 5õ�� ����� �� ���� �¸��� ���� �屺�� �̸� :");
	strcpy(quiz[9].hint,"���� ������ �屺");
}
//##########[����� ����]##########//
void init02()	
{
	strcpy(quiz[0].answer,"4"); 	
	strcpy(quiz[0].told,"�� 1�� ��������� ��⵿�� ���ӵǾ���. ��ĭ�� �����Դϱ�?");		
	strcpy(quiz[0].hint,"1918�� 11�� 11�� ������ �׺����� ����.");
	strcpy(quiz[1].answer,"��2���������");
	strcpy(quiz[1].told,"[���]���ݱ����� �η� ���翡�� ���� ū �θ�� ��� ���ظ� ���� ���� :");
	strcpy(quiz[1].hint,"���ձ� ���̿� ������ ���� �Ը��� ����");
	strcpy(quiz[2].answer,"Ʈ���̸�");
	strcpy(quiz[2].told,"[���]������� �׸����� Ʈ���̸� ����Ʈ�� �� �������� ������ �Ͽ���.");
	strcpy(quiz[2].hint,"Trojan Horse");
	strcpy(quiz[3].answer,"��Ʋ��");	
	strcpy(quiz[3].told,"����� ��2����������� ���������� �л��� £������ �ڻ��Ͽ���. ");
	strcpy(quiz[3].hint,"������ ��ġ���̸� �����ڷ� �Ҹ���.");
	strcpy(quiz[4].answer,"���ָ�");	
	strcpy(quiz[4].told,"[���]�Ϻ��� �������� ���� �̱��� 2�������� �پ��� �Ǿ���.");
	strcpy(quiz[4].hint,"ǳ���ϰ� ���� ���ָ� ����� ���� �� ������ ���� �̸�");
	strcpy(quiz[5].answer,"�ܴٸ�ũ");	
	strcpy(quiz[5].told,"�����: ������ ������� �ı⿡ �������� ���⿡�� ���� �������� �ҳ�.");
	strcpy(quiz[5].hint,"����� ���� 19�� �ɴٿ� ���̿� ȭ�� ����.");	
	strcpy(quiz[6].answer,"��¡");	
	strcpy(quiz[6].told,"��� ������ �߱��� �ܱ��� ���� ������ �ٴ����� �����̸� ����������̴�.");
	strcpy(quiz[6].hint,"��������");
	strcpy(quiz[7].answer,"�������");
	strcpy(quiz[7].told,"�����:18���� �߿� �������� ���۵� ������Ű� ��ȸ������ ������ ����.");
	strcpy(quiz[7].hint,"����ȭ");
	strcpy(quiz[8].answer,"��������");
	strcpy(quiz[8].told,"���������:��1�� ������� �� ���￡ �¸��� ���ձ��� ������ ������ ��ȭ����.");
	strcpy(quiz[8].hint,"�� �������� ������ �ؿܽĹ����� ��� ���, ���� �� ���並 �Ҿ���.");
	strcpy(quiz[9].answer,"���˺�");	
	strcpy(quiz[9].told,"���� �� �繰�� ������ ����鿡�� �˸� �����شٴ� ���� ����.");
	strcpy(quiz[9].hint,"15���� ����,�뷮 �������� ������ ������ �ҷ�����Ű�� ���� ������ �Ǹ����� ��.");
}
//##########[�Ϲݻ�� ����]##########//
void init03()
{
	strcpy(quiz[0].answer,"����"); 	
	strcpy(quiz[0].told,"���ѹα����� ���� ���ʿ� �ִ� ����?");		
	strcpy(quiz[0].hint,"õ����买 ��423ȣ");
	strcpy(quiz[1].answer,"KTX");
	strcpy(quiz[1].told,"�츮���󿡼� ���� ���� ������ ���ö�� ���� ��Ī��?");
	strcpy(quiz[1].hint,"[Korea Train eXpress]");
	strcpy(quiz[2].answer,"��");
	strcpy(quiz[2].told,"���� �����ð� ������ �� ""��ġ�� ������""��� �Ѵ�.\n���⼭ ""��ġ""�� ���� ��� ������ ����Ű�� ���ΰ�?");
	strcpy(quiz[2].hint,"��� ô�ߵ����� ��κ��� ��ô�ߵ����� �־ �Ű���� ���߰� �Ǵ� ���");
	strcpy(quiz[3].answer,"�Ź�");	
	strcpy(quiz[3].told,"�����̴� ��� ������ �ֹ����ΰ�? ");
	strcpy(quiz[3].hint,"Ư���� �����⸦ ������ ���� �Ҹ��� ��� �� �˷��� �����̴�.");
	strcpy(quiz[4].answer,"��񳭸�");	
	strcpy(quiz[4].told,"[���ڼ���]�׾ ����� �Ǿ �� ���� ������ ���� ���� ���ٴ� ��.");
	strcpy(quiz[4].hint,"��������");
	strcpy(quiz[5].answer,"����ط�");	
	strcpy(quiz[5].told,"[���ڼ���]�κΰ� ȭ���ϰ� �λ��� �Բ� ����.");
	strcpy(quiz[5].hint,"��Ҵ����");	
	strcpy(quiz[6].answer,"�����ұ�");	
	strcpy(quiz[6].told,"[���ڼ���]�� �� ������ ������ �ʴ´ٴ� ��. ���� ���� �غ���.");
	strcpy(quiz[6].hint,"�������");
	strcpy(quiz[7].answer,"�ұ���");
	strcpy(quiz[7].told,"����ž�� �ٺ�ž�� �ִ� ��. �̰��� ����ΰ�?");
	strcpy(quiz[7].hint,"����");
	strcpy(quiz[8].answer,"������");
	strcpy(quiz[8].told,"�ѱ� Ư�� �� ǰ��.");
	strcpy(quiz[8].hint,"õ����买 53ȣ");
	strcpy(quiz[9].answer,"��");	
	strcpy(quiz[9].told,"�츮������ ü���� ���� ���� ���� ����ΰ�?");
	strcpy(quiz[9].hint,"û�� �� ���������� ����ϴ� ���");
}
//##########[���׺� ����]##########//
void solution_Korea()
{
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t                       ��   �� ��   ��                      \n");
	printf("\t===========================================================\n\n\n");
	WHITE;
	printf("  (1)100���� ������ ������ �̸� : �̼���\n");
	printf("  (2)1000���ǿ� ������ ������ �̸� : �����Ȳ\n");
	printf("  (3)5000���ǿ� ������ ������ �̸� : ��������\n");
	printf("  (4)10000���ǿ� ������ ������ �̸� : �������\n");
	printf("  (5)10000���ǿ� ������ ������ �̸� : �Ż��Ӵ�\n");
	printf("  (6)1592~1598��, �� ���ʿ� ���� �츮���� ħ���� �Ϻ����� �ο� : �����ֶ�\n");
	printf("  (7)��Ȳ�ĸ� �����ϰ� �Ϻ����� ��ȭ�� ȹå�� ���� : ���̻纯\n");
	printf("  (8)8��15���� '�����' : ������\n");
	printf("  (9)�������� �νŸŸŸ� ����, ���� ������ �Ŷ��� ���� : �庸��\n");
	printf("  (10)���翬�ձ�(5��)�� 5õ�� ����� �� ���� �¸��� ���� �屺�� �̸� : ���\n");
	printf("\n");
}
void solution_World()
{
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t                       �� �� �� ��  ��                      \n");
	printf("\t===========================================================\n\n\n");
	WHITE;
	printf("  (1)�� 1�� ��������� ��⵿�� ���ӵǾ���. ��ĭ�� �����Դϱ�?\n");		
	printf("  (2)[���]���ݱ����� �η� ���翡�� ���� ū �θ�� ��� ���ظ� ���� ���� :\n");
	printf("  (3)[���]������� �׸����� Ʈ���̸� ����Ʈ�� �� �������� ������ �Ͽ���.\n");
	printf("  (4)����� ��2����������� ���������� �л��� £������ �ڻ��Ͽ���. \n");
	printf("  (5)[���]�Ϻ��� �������� ���� �̱��� 2�������� �پ��� �Ǿ���.\n");
	printf("  (6)�����: ������ ������� �ı⿡ �������� ���⿡�� ���� �������� �ҳ�.\n");
	printf("  (7)��� ������ �߱��� �ܱ��� ���� ������ �ٴ����� �����̸� ����������̴�.\n");
	printf("  (8)�����:18���� �߿� �������� ���۵� ������Ű� ��ȸ������ ������ ����.\n");
	printf("  (9)���������:\n\t��1�� ������� �� ���￡ �¸��� ���ձ��� ������ ������ ��ȭ����.\n");
	printf("  (10)���� �� �繰�� ������ ����鿡�� �˸� �����شٴ� ���� ����.\n");
	printf("\n");
}
void solution_CommonSense()
{
	YEL;
	printf("\n");
	printf("\t===========================================================\n");
	printf("\t                       ��  �Ϲݻ��  ��                      \n");
	printf("\t===========================================================\n\n\n");
	WHITE;
	printf("  (1)���ѹα����� ���� ���ʿ� �ִ� ����?\n");		
	printf("  (2)�츮���󿡼� ���� ���� ������ ���ö�� ���� ��Ī��?\n");
	printf("  (3)���� �����ð� ������ �� ""��ġ�� ������""��� �Ѵ�.\n\t���⼭ ""��ġ""�� ���� ��� ������ ����Ű�� ���ΰ�?\n");
	printf("  (4)�����̴� ��� ������ �ֹ����ΰ�? \n");
	printf("  (5)[���ڼ���]�׾ ����� �Ǿ �� ���� ������ ���� ���� ���ٴ� ��.\n");
	printf("  (6)[���ڼ���]�κΰ� ȭ���ϰ� �λ��� �Բ� ����.\n");
	printf("  (7)[���ڼ���]�� �� ������ ������ �ʴ´ٴ� ��. ���� ���� �غ���.\n");
	printf("  (8)����ž�� �ٺ�ž�� �ִ� ��. �̰��� ����ΰ�?\n");
	printf("  (9)�ѱ� Ư�� �� ǰ��.\n");
	printf("  (10)�츮������ ü���� ���� ���� ���� ����ΰ�?\n");
}
//##########[���� �ӽ�]##########//
int slot_machine()
{
	char reel[6][3]={"��","��","��","��","��","��"};
	int i,reel_num[3][3];
	srand((unsigned)time(NULL));
	printf("  ���Ըӽ� ����\n\n");
	gotoxy(1,17);
	printf("=========================\n");
	printf("\t<<Enter>> \n");
	printf("=========================\n\n");
	display_rule();
	gotoxy(3,5);
	printf("��1 ��2 ��3");
	gotoxy(1,8);
	printf("��������������");
	gotoxy(1,10);
	printf("��������������");
	gotoxy(1,6);
	for(i=0;i<3;i++)
		reel_num[0][i]=rand()%5;
	reel_series(reel_num);
	game_control(reel,reel_num);
	return count;
}
void display_rule()
{
	gotoxy(30,1);
	printf("������������������������\n");
	gotoxy(30,2);
	printf("��Case 1~9 : Hint ���ަ�  ");
	gotoxy(30,3);
	printf("��  ��1   ��2   ��3   ��\n");
	gotoxy(30,4);
	printf("��--------------------��\n");
	gotoxy(30,5);
	printf("�� 1: ��   ��   ��    ��\n");
	gotoxy(30,6);
	printf("�� 2: ��   ��   ��    ��\n");
	gotoxy(30,7);
	printf("�� 3: ��   ��   ��    ��\n");
	gotoxy(30,8);
	printf("�� 4: ��   ��   ��Ÿ  ��\n");
	gotoxy(30,9);
	printf("�� 5: ��   ��   ��Ÿ  ��\n");
	gotoxy(30,10);
	printf("�� 6: ��   ��   ��Ÿ  ��\n");
	gotoxy(30,11);
	printf("�� 7: ��   ��   ��Ÿ  ��\n");
	gotoxy(30,12);
	printf("�� 8: ��   ��   ��Ÿ  ��\n");
	gotoxy(30,13);
	printf("�� 9: ��   ��   ��Ÿ  ��\n");
	gotoxy(30,14);
	printf("������������������������\n");
}
void reel_series(int r[][3])
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			r[j][i]=(r[0][i]+j)%6;
}
void display_reel(char rc[][3],int r[][3],int index)
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=index;j<3;j++)
		{
			gotoxy(3+j*4,7+i*2);
			printf("%s",rc[r[i][j]]);
		}
}
int game_control(char reel[][3],int reel_num[][3])
{
	int i,j,case_num=0,thank,num[3];
	double pst;
	clock_t start,end;
	display_reel(reel,reel_num,0);
	for(i=0;i<3;i++)
	{
		start=clock();
		do
		{
			for(j=i;j<3;j++)
				reel_num[0][j]=reel_num[1][j];
			reel_series(reel_num);
			display_reel(reel,reel_num,i);
			end=clock();
			pst=(double)(end-start)/CLK_TCK;
		}while(!kbhit() || (pst<1));
		num[i]=reel_num[1][i];
	}
	getch();
	thank=return_hint(num,&case_num);
	if(thank==0)
	{
		gotoxy(1,20);
		printf("����������������\n");
		printf("�� �âò΢â� ��\n");
		printf("����������������\n");	
	}
	else
	{
		gotoxy(1,20);
		printf("����������������\n");
		printf("�� �âò΢â� ��\n");
		printf("����������������\n");
	}
	if(case_num)
	{
		gotoxy(1,20);
		printf("����������������\n");
		printf("������Ʈ���ޢæ�\n");
		printf("����������������\n");
		count=1;
	}
	return count;
}
int return_hint(int r[],int *case_num)
{
	int total=0;
	if(r[0]==r[1] && r[1]==r[2] && r[0]==r[2])
	{
		if(r[0]==0)
		{
			total=1;
			*case_num=1;
		}
		else if(r[0]==1)
		{
			total=1;
			*case_num=2;
		}
		else if(r[0]==2)
		{
			total=1;
			*case_num=3;
		}
	}
	else if((r[0]==0 && r[1]==0) || (r[1]==0 && r[2]==0) || (r[0]==0 && r[2]==0))
	{
		total=1;
		*case_num=4;
	}
	else if((r[0]==1 && r[1]==1) || (r[1]==1 && r[2]==1) || (r[0]==1 && r[2]==1))
	{
		total=1;
		*case_num=5;
	}
	else if((r[0]==2 && r[1]==2) || (r[1]==2 && r[2]==2) || (r[0]==2 && r[2]==2))
	{
		total=1;
		*case_num=6;
	}
	else if((r[0]==3 && r[1]==3) || (r[1]==3 && r[2]==3) || (r[0]==3 && r[2]==3))
	{
		total=1;
		*case_num=7;
	}
	else if((r[0]==4 && r[1]==4) || (r[1]==4 && r[2]==4) || (r[0]==4 && r[2]==4))
	{
		total=1;
		*case_num=8;
	}
	else if((r[0]==5 && r[1]==5) || (r[1]==5 && r[2]==5) || (r[0]==5 && r[2]==5))
	{
		total=1;
		*case_num=9;
	}
	return total;
}
//##########[������ȣ ���]##########//
void one_print(int quiz_count)
{
		printf("\n");
		printf("������������������������������������������������������������������������\n");
		printf("������ %2d��							      ��\n",quiz_count);
		printf("������������������������������������������������������������������������");
}
//##########[���� ���]##########//
void two_print(int i)
{
		printf("\n");
		printf("������������������������������������������������������������������������\n");
		printf("  %s\n",quiz[i].told);
		printf("������������������������������������������������������������������������\n\n");
}
//##########[������ ����]##########//
void digit_print(int dim[],int line)
{
	int i;
	WHITE;
	for(i=line*4;i<=line*4+3;i++)
		if(dim[i]==1)
			printf("��");
		else
			printf("  ");
	printf("    ");
}
void number_check(int k,int i)
{
	if(k>=1)
	{
		number_check(k/10,i);
		switch(k%10)
		{
		case 0 :
			digit_print(zero,i);
			break;
		case 1 :
			digit_print(one,i);
			break;
		case 2 :
			digit_print(two,i);
			break;
		case 3 :
			digit_print(three,i);
			break;
		case 4 :
			digit_print(four,i);
			break;
		case 5 :
			digit_print(five,i);
			break;
		case 6 :
			digit_print(six,i);
			break;
		case 7 :
			digit_print(seven,i);
			break;
		case 8 :
			digit_print(eight,i);
			break;
		case 9 :
			digit_print(nine,i);
			break;
		}
	}
}
