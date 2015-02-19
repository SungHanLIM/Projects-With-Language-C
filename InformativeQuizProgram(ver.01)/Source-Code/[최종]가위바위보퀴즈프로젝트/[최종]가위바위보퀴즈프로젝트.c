#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct quiz_q
{
	char answer[20];//��
	char told[100];
	char hint[100]; //��Ʈ
}quiz_q;

quiz_q quiz[10];						//����ü �迭 (10����)
void init01();							//���繮�� �Լ� ����
void init02();							//����繮�� �Լ� ����
int gawi(int i, int quiz_count);		//���������� 
void one_print(int quiz_count);			//������ȣ���
void two_print(int i);					//���� ���
void solution();						//���� ���� 
void emoticon();						//�̸�Ƽ�� ����� ���� �Լ�

static int ok[10];
int i=0,j = 0;							//for���� ���� ����
char temp02;							//���� �ٽ�Ǯ�� (y/n)
int temp01=0;							//'�޴� ����'�� ���� 0,1 ���� ��� ����		

int main(void)
{
	char name[10];			//����ǥ ID�Է�
	char num_board[5][12] =   // ������
	{
		"Excellent  ", "Good       ", "Nice       ", "Not bad    ", "HaveToStudy"
	};
	int point[5] =    // ����
	 {
		100, 80, 60, 40, 20
	 };
	char inpName[5];  // ����� �Է¹��� ID
	int inpPoint=0;    //����� �Է¹��� ����
	
	int selection = 0;//�޴����� selection����
	int count = 0,temp,quiz_count = 1;
	char answel[10];


	int temp01=1;
	while(temp01){
	for(j=0;j<10;j++) //�迭 �ʱ�ȭ
	{
		ok[j] = 0;
	}
	printf("\n");
	printf("����������������������������������������������������\n");
	printf("��  ���� ����*����*�� ���α׷�                    ��\n");
	printf("����������������������������������������������������\n");

	printf("����������������������������������������������������\n");
	printf("��  (1) ��    ��                                  ��\n");
	printf("��  (2) �� �� ��                                  ��\n");
	printf("��  (3) ����Ȯ��                                  ��\n");
	printf("��  (4) ����ȯ��                                  ��\n");
	printf("��  (5) ��    ��                                  ��\n");
	printf("����������������������������������������������������\n");
	printf("�� �޴��� �����ϼ��� : "); //�޴�����.
	fflush(stdin);
	scanf("%d", &selection);

		switch(selection)
		{
		case 1://����
			init01();
			printf("�� I  D : ");
			scanf("%s", inpName);
			while(1)
			{
				srand(time(NULL));		
				one_print(quiz_count); //��� 
				while(1) //���� �ߺ��˻�
				{
					i = rand()%10;
					if(ok[i] == 0)
					{
						ok[i] = 1;
						break;
					}
				}
	    
				two_print(i); //��� 
				temp = gawi(i,quiz_count); 
				one_print(quiz_count);
				two_print(i);
				
				if(temp==1)
				{
					printf("��Ʈ : %s \n",quiz[i].hint);	//��Ʈ
				}

				printf("����  >> ");
				scanf("%s",answel);

				if(!strcmp(quiz[i].answer,answel))
				{
					inpPoint+=10;	//������ �� ���� �� ������ 10���� ����
					printf("�����Դϴ�. �������� �̵� [Enter] \n");
				}
				else
				{
					printf("Ʋ�Ƚ��ϴ�. �������� �̵� [Enter] \n");
				}
				quiz_count++;
				getch();		//���۸޸� �ڸ� ���� getch() ȣ��
				system("cls");
		
				if(quiz_count==10)
				{
					printf("\n\n�� %s���� ȹ�� ������ %3d�� �Դϴ�.\n", inpName,inpPoint);
					break;
				}
			}
			break;
		case 2://�����
			init02();
			printf("�� I  D : ");
			scanf("%s", inpName);
			while(1)
			{
				srand(time(NULL));		
				one_print(quiz_count); //��� 
				while(1) //���� �ߺ��˻�
				{
					i = rand()%10;
					if(ok[i] == 0){
						ok[i] = 1;
						break;
					}
				}
	    
				two_print(i); //��� 
				temp = gawi(i,quiz_count); 
				one_print(quiz_count);
				two_print(i);

				if(temp==1)
				{
					printf("��Ʈ : %s \n",quiz[i].hint);	//��Ʈ
				}

				printf("����  >> ");
				scanf("%s",answel);
	
				if(!strcmp(quiz[i].answer,answel))
				{
					printf("<����> Enter Key�� �Է��Ͻø� ���� ������ �Ѿ�ϴ�. \n");
				}
				else
				{
					printf("<����> Enter Key�� �Է��Ͻø� ���� ������ �Ѿ�ϴ�. \n");
				}
				quiz_count++;
				getch();
				system("cls");

				if(quiz_count==10)
				{
					printf("\n\n�� %s���� ȹ�� ������ %3d�� �Դϴ�.\n", inpName,inpPoint);
					break;
				}
			}
			break;
		case 3://����Ȯ��
			solution();//����Ȯ�� �Լ� ȣ��
			break;
		case 4://����ȯ��
			
			printf("����������������������������������������������������\n");
			printf("  �� �� �� ȯ ��\n");
			printf("����������������������������������������������������\n");
			printf("�� I  D : ");
 			scanf("%s", &name);
 			printf("�� �� ��: ");
			scanf("%d", &inpPoint);
			printf("����������������������������������������������������\n");
			printf("  �� ������ ���� ȯ��ǥ\n");
			printf("����������������������������������������������������\n");
			for (i=0; i<5; i++)
			{
				printf("State : %-10s �� �� : %3d ~%3d\n\n", num_board[i], point[i],point[i]-20);
			}
			printf("����������������������������������������������������\n");
			printf("  �� %10s���� ���� : %3d��\n",name,inpPoint);
			printf("����������������������������������������������������\n");
			

			break;
		case 5://����
			return 0; // ���α׷� ����.
		default:
			printf("\n\a");						//escape ���� 'wa' �����
			printf("��CAUTION!������������������������������������������\n");
			printf("��   �ٽ� �Է��ϼ���.                             ��\n");
			printf("����������������������������������������������������\n\n");
		}
		printf("�޴��� ���ư��ðڽ��ϱ�?(y/n)\n");
		scanf("%s",&temp02);
		if(temp02 == 'y' || temp02 == 'Y')
		{
			temp01 = 1;
			system("cls");
			continue;
		}
		else
		{
			system("cls");
			printf("�� ����������� ���α׷��� �̿��� �ּż� �����մϴ�.\n");
			return 0;
		}
	}
}

//������ȣ
void one_print(int quiz_count)
{
		printf("\n");
		printf("������������������������������������������������������������������������\n");
		printf("������ %2d��							      ��\n",quiz_count);
		printf("������������������������������������������������������������������������");
}
//���� ���
void two_print(int i)
{
		printf("\n");
		printf("������������������������������������������������������������������������\n");
		printf("  %s\n",quiz[i].told);
		printf("������������������������������������������������������������������������\n\n");
			
}
//���� ����
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
	strcpy(quiz[4].told,"10000���ǿ� ������ ������ �̸��� �����Դϱ�?");
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
//����� ����
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
//����Ȯ��<����*�����>
void solution()
{
	printf("  �ñ�  ��\n");
	printf("  (1)100���� ������ ������ �̸� : �̼���\n");
	printf("  [Hint] �źϼ�\n");
	printf("  (2)1000���ǿ� ������ ������ �̸� : �����Ȳ\n");
	printf("  [Hint]������������ ���ʸ� ���� ����, ���ư��� �������� �ǹ�\n");
	printf("  (3)5000���ǿ� ������ ������ �̸� : ��������\n");
	printf("  [Hint]�ɻ��Ӵ��� �Ƶ�\n");
	printf("  (4)10000���ǿ� ������ ������ �̸� : �������\n");
	printf("  [Hint]�ƹ�����\n");
	printf("  (5)10000���ǿ� ������ ������ �̸� : �Ż��Ӵ�\n");
	printf("  [Hint]�����ó\n");
	printf("  (6)1592~1598��, �� ���ʿ� ���� �츮���� ħ���� �Ϻ����� �ο� : �����ֶ�\n");
	printf("  [Hint]�ѻ��ø\n");
	printf("  (7)��Ȳ�ĸ� �����ϰ� �Ϻ����� ��ȭ�� ȹå�� ���� : ���̻纯\n");
	printf("  [Hint]�Ϻ� �ڰ��� �溹�� ħ�� ���\n");
	printf("  (8)8��15���� '�����' : ������\n");
	printf("  [Hint]������, ��� �豸, ���� ��âȣ\n");
	printf("  (9)�������� �νŸŸŸ� ����, ���� ������ �Ŷ��� ���� : �庸��\n");
	printf("  [Hint]�ٴ��� ��\n");
	printf("  (10)���翬�ձ�(5��)�� 5õ�� ����� �� ���� �¸��� ���� �屺�� �̸� : ���\n");
	printf("  [Hint]���� ������ �屺\n");
	printf("\n");
	printf("  �ü����\n");
	printf("  (1)�� 1�� ��������� 4�⵿�� ���ӵǾ���.\n");
	printf("  [Hint]1918�� 11�� 11�� ������ �׺����� ����.\n");
	printf("  (2)���ݱ����� �η� ���翡�� ���� ū �θ�� ��� ���ظ� ���� ����\n");
	printf("  :��2���������\n");
	printf("  [Hint]���ձ� ���̿� ������ ���� �Ը��� ����\n");
	printf("  (3)Ʈ���̸񸶴� �׸����� Ʈ���̸� ����Ʈ�� �� �������� ������ �Ͽ���.\n");
	printf("  [HintTrojan Horse\n");
	printf("  (4)��Ʋ���� ��2����������� ���������� �л��� £������ �ڻ��Ͽ���.\n");
	printf("  [Hint]������ ��ġ���̸� �����ڷ� �Ҹ���.\n");
	printf("  (5)�Ϻ��� ���ָ������ ���� �̱��� 2�������� �پ��� �Ǿ���.\n");
	printf("  [Hint]ǳ���ϰ� ���� ���ָ� ����� ���� �� ������ ���� �̸�\n");
	printf("  (6)�ܴٸ�ũ: ������ ������� �ı⿡ �������� ���⿡�� ���� �������� �ҳ�.\n");
	printf("  [Hint]����� ���� 19�� �ɴٿ� ���̿� ȭ�� ����.\n");
	printf("  (7)��¡������ �߱��� �ܱ��� ���� ������ �ٴ����� �����̸� ����������̴�.\n");
	printf("  [Hint]��������\n");
	printf("  (8)�������:18���� �߿� �������� ���۵� ������Ű� ��ȸ������ ������ ����.\n");
	printf("  [Hint]����ȭ\n");
	printf("  (9)������������:\n");
	printf("  ��1�� ������� �� ���￡ �¸��� ���ձ��� ������ ������ ��ȭ����.\n");
	printf("  [Hint]�� �������� ������ �ؿܽĹ����� ��� ���, ���� �� ���並 �Ҿ���.\n");
	printf("  (10)���� �� �繰�� ������ ����鿡�� �˸� �����شٴ� ���� ���� : ���˺�\n");
	printf("  [Hint]\n");
	printf("  15���� ����,�뷮 �������� ������ ������ �ҷ�����Ű�� ���� ������ �Ǹ����� ��.\n");
}
//����������
int gawi(int i,int quiz_count) //0��� 1�̱� 2��
{
	char *psr[3] = {"����","����","��"};
	int com, you, count = 0;
	int win = 0,t;
		
	printf("�� ��ǻ�Ϳ��� ����*����*�� ( �̱�� ��Ʈ ���� )\n");
	printf("�� Enter Key�� ������ ����� ���۵˴ϴ�.\n");
	getch();	
	system("cls");
		
	
	one_print(quiz_count);
	two_print(i);
	emoticon();						//�̸�Ƽ�� ���	
	srand((unsigned)time(NULL));
	com = rand()%3 + 1;
	printf("     ����(1), ����(2), ��(3) �����Է� [  ]\b\b\b ");
	scanf("%d",&you);
			
	printf("��ǻ�ʹ� %s, ����� %s\n",psr[com-1],psr[you-1]);
	printf("\n");
	printf("��� : ");

	if(com==1){
		if(you==1) { printf("�����ϴ�. \n"); }
		else if(you == 2) { printf("����� �̰���ϴ�. \n"); count++;}
		else if(you == 3) { printf("��ǻ�Ͱ� �̰���ϴ�. \n"); }
	}else if(com == 2){
		if(you==1) { printf("��ǻ�Ͱ� �̰���ϴ�. \n"); }
		else if(you == 2) { printf("�����ϴ�.\n"); }
		else if(you == 3) { printf("����� �̰���ϴ�.\n"); count++;}
	}else{
		if(you == 1) { printf("����� �̰���ϴ�.\n"); count++;}
		else if(you == 2) { printf("��ǻ�Ͱ� �̰���ϴ�.\n"); }
		else { printf("�����ϴ�.\n"); }
	}
	printf("\n");
	printf("�� Enter Key�� �Է��Ͻ� ��, ������ �������ּ���.\n\n");	
	getch();
	system("cls");
	return count;
}
//���������� �̸�Ƽ��
void emoticon()
{
	printf("      **   **               *  *  *  *      \n");   
	printf("      **   **               *  *  *  *      \n");
	printf("      **   **     ******    **********      \n");
	printf("       ** **     ********   *************   \n");
	printf("      *******    ********   **********      \n");
	printf("      *******    ********    *********      \n");
	printf("       ******     ******     ********       \n");
}

