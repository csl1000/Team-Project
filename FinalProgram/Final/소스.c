#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARINGS
#pragma warning(disable : 4996)

#define DISTANCE 1
#define GRADE 2
#define COST 3

#define STRING_SIZE 256
#define MAX_WORD 100


void UserLogin(char[]);
void DoctorLogin(char[]);
void Login();

char userID[20]; // user�� ���̵� �������



typedef struct User_data
{
	char name[20];
	int local_x;
	int local_y;

}User_data;

typedef struct Doctor_data
{
	char name[20];
	int local_x;
	int local_y;
	char grade;
	int cost;
}Doctor_data;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void UserLogin(char[]);
void DoctorLogin(char[]);
void Login();


void Login()
{
	int LoginTimes = 0;    //�α��� ���� Ƚ�� üũ,5�� �̻� �α��� ����->����
	int LoginNumber = 0;    //�α��� ���� üũ,�α��� ����->LoginNumber=1
	char ID[100];    //����� �Է��� ID,Password ����
	char PW[100];
	char UserID[1000];    //����� �����Ϳ� ȯ�� �ǻ� ID,Password�� ������
	char UserPW[1000];
	char DoctorID[1000];
	char DoctorPW[1000];
	FILE* fp1, * fp2;    //����� �����͸� Read
	fp1 = fopen("User.txt", "r");    //ȯ�� �α��� ������
	fp2 = fopen("Doctor.txt", "r");    //�ǻ� �α��� ������
	while (LoginNumber == 0)
	{
		printf("ID:");    //����� ID,Password�Է�
		scanf(" %s", ID);
		printf("PW:");
		scanf(" %s", PW);
		while (strcmp(UserID, "1") != 0 && strcmp(DoctorID, "1") != 0)    //����� �����Ϳ� �Է��� ID,Password üũ
		{
			fscanf(fp1, "%s", UserID);
			fscanf(fp1, "%s", UserPW);
			fscanf(fp2, "%s", DoctorID);
			fscanf(fp2, "%s", DoctorPW);
			if (strcmp(UserID, ID) == 0 && strcmp(UserPW, PW) == 0)    //�Է��� ID,Password�� ����� �����Ͷ� ��ġ�ϸ� Login
			{
				printf("\nYou have successfully landing system...\n");
				UserLogin(ID);    //ȯ�� �α��� ����
				LoginNumber = 1;
				break;
			}
			if (strcmp(DoctorID, ID) == 0 && strcmp(DoctorPW, PW) == 0)
			{
				printf("\nYou have successfully landing system...\n");
				DoctorLogin(ID);    //�ǻ� �α��� ����
				LoginNumber = 1;
				break;
			}
		}
		if (strcmp(UserID, "1") == 0 || strcmp(DoctorID, "1") == 0)    //�Է��� ID,Password�� ����� �����Ͷ� ����ġ->�α��� ����->�ٽ� �Է�
		{
			printf("\nLOGIN ERROR:Wrong ID,PW.\n");
			printf("Please try again...\n\n");
			LoginTimes++;    //�α��� ���� Ƚ�� +1
			memset(UserID, 0, sizeof(UserID));    //����� �����͸� �ٽ� Read
			memset(UserPW, 0, sizeof(UserPW));
			memset(DoctorID, 0, sizeof(DoctorID));
			memset(DoctorPW, 0, sizeof(DoctorPW));
			rewind(fp1);
			rewind(fp2);
		}
		if (LoginTimes > 4)    //�α��� ���� Ƚ�� 5�� �̻�->����
		{
			printf("\nEnter the wrong ID or PW too many times.\n");
			printf("EXIT...");
			getchar();
			break;
		}
	}
	getchar();
}

void UserLogin(char ID[])
{
	printf("\nHello User:%s", ID);
	getchar();
}

void DoctorLogin(char ID[])
{
	printf("\nHello Doctor:%s", ID);
	getchar();
}

void search(char word[], int cnt[])
{
	FILE* fp = NULL;
	int line = 0;
	for (int i = 0; i < STRING_SIZE; i++) // 0���� �迭 �ʱ�ȭ.
	{
		cnt[i] = 0;
	}

	fp = fopen("DiseaseSearch.txt", "r"); // ������ ������ �о����.

	if (fp != NULL)
	{
		char buffer[STRING_SIZE];

		while (!feof(fp)) // ���� ���� ������ ������ ����.s
		{
			fgets(buffer, sizeof(buffer), fp); // ���پ� �о����.
			char* ptr = strtok(buffer, " "); // ���� ������ ����. Symptom�̳� �Է¿��� ������ _ �� �����Ƿ� ������ token ������ �ȴ�.

			while (ptr != NULL)
			{
				// int com = strcmp(word, ptr);
				if (strstr(ptr, word)) // �Էµ� �ܾ token�� �ִ��� Ȯ��. �ش� �ܾ ������ NULL�� �Ǿ� if���� ������� ����. �ش� �ܾ� ���� �� if�� ����.
				{
					cnt[line]++; // �ش� �ܾ ������ �� 0�� �ȴ�. �׸��Ͽ� �ش� �ٿ� �ش� �ܾ �ִ��� Ȯ���ϴ� cnt�� ������Ų��. �̸��׸� 1��° �ٿ� ���� ���, cnt[0]�� 1 ����.

				}
				ptr = strtok(NULL, " ");

				// printf("%d : %d\n", line, cnt[line]);

			}

			line++; // ���� ����.
		}
	}

	fclose(fp);
}

int result(int cnt[])
{
	FILE* fp = NULL;
	int max;
	char buffer[STRING_SIZE];
	char* readByte;
	char* tempStr = malloc(sizeof(char) * 1024);

	max = cnt[0];

	for (int i = 0; i < STRING_SIZE; i++) // cnt �迭���� ���� ū ���� ã��.
	{
		if (max < cnt[i])
		{
			max = cnt[i];
		}
	}

	fp = fopen("DiseaseSearch.txt", "r");

	int j = 0;

	while (!feof(fp))
	{
		readByte = fgets(buffer, sizeof(buffer), fp); // 1�پ� ����. readByte�� ����.
		if (cnt[j] == max) // cnt �� max�� ���� ���. ��, �������� ���� ū ����� ���.
		{
			strcpy(tempStr, readByte); // tempStr�� �ش� ���� ����.
			char* ptr = strtok(buffer, " "); // �ش� �ٿ��� ����� ������� �����Ƿ� �ѹ� ���� ������ ��� ó���� ���� ������ ptr�� ����.
			printf("��� : %s\n", ptr); // �׸��� ptr�� �ִ� ������ ���.
			fclose(fp);
			return 0;
		}
		j++;
	}

	fclose(fp);
}


const char* findDoctor(int sort_kind, User_data user)
{
	Doctor_data doctor[20];
	int doctor_index = 0; // doctor�迭�� index
	char file_line[50]; // ���� ���� �� 1���� �޾Ƶ��̴� ����
	int counter = 0;
	int minimum = 0; // Cost, Distance �񱳸� ���� ����
	int index = 0; 
	int distance[20];
	char doctor_name[20];


	FILE* fp;
	fp = fopen("doctorinfo.txt", "r");
	if (fp == NULL) // ������ ���� �� ����ó��
	{
		printf("Can't find file\n");
		exit(1);
	}
	else
	{
		while (!feof(fp)) // ���� ������ �о
		{
			// ���� ������ ���������� ���Ͽ��� 5������ ������ ���� doctor ����ü �迭�� �Ѱ��� ����
			fgets(file_line, 50, fp); 
			char* temp = strtok(file_line, " ");
			strcpy(doctor[doctor_index].name, temp);
			temp = strtok(NULL, " ");
			doctor[doctor_index].local_x = atoi(temp);
			temp = strtok(NULL, " ");
			doctor[doctor_index].local_y = atoi(temp);
			temp = strtok(NULL, " ");
			doctor[doctor_index].grade = temp[0];
			temp = strtok(NULL, " ");
			doctor[doctor_index].cost = atoi(temp);

			doctor_index++; // doctor �迭�� ���� ���� ����
		}
	}

	fclose(fp);

	switch (sort_kind)// �Էµ� sort_kind�� ���� 3���� ���� ��� ����
	{
	case DISTANCE: // �Ÿ����϶�
		for (int i = 0; i < doctor_index; i++) // ��Ʈ�� ������� �ʾƵ� �Ÿ� �񱳴� ����������(�Ÿ��� �׻� 0���� ũ��) ȯ�ڿ� �� �ǻ���� �Ÿ��� ����
		{
			distance[i] = abs(doctor[i].local_x - user.local_x) * abs(doctor[i].local_x - user.local_x) + abs(doctor[i].local_y - user.local_y) * abs(doctor[i].local_y - user.local_y);
		}

		minimum = distance[0];
		for (int i = 0; i < doctor_index; i++)
		{
			if (distance[i] < minimum) // ���� �ּڰ����� �Ÿ��� �۴ٸ� �װ����� �ּڰ� ��ü, index�� ����
			{
				minimum = distance[i];
				index = i;
			}
		}
		printf("%s %d %d %c %d\n", doctor[index].name, doctor[index].local_x, doctor[index].local_y, doctor[index].grade, doctor[index].cost);
		break;
	case GRADE: // �������϶�
		for (int i = 0; i < doctor_index; i++)
		{
			if (doctor[i].grade == 'A')
			{
				printf("%s %d %d %c %d\n", doctor[i].name, doctor[i].local_x, doctor[i].local_y, doctor[i].grade, doctor[i].cost);
				counter++;
				index = i; // ���� ���� ������ �ǻ��� index�� �����ص�
			}
		}

		if (counter == 0) // ��� �ǻ���� ������ A�� �ƴ϶�� B�� Ȯ�� �� �� �ֵ��� ������
		{
			for (int i = 0; i < doctor_index; i++)
			{
				if (doctor[i].grade == 'B')
				{
					printf("%s %d %d %c %d\n", doctor[i].name, doctor[i].local_x, doctor[i].local_y, doctor[i].grade, doctor[i].cost);
					counter++;
					index = i;
				}
			}
		}
		if (counter == 0)
		{
			for (int i = 0; i < doctor_index; i++)
			{
				if (doctor[i].grade == 'C')
				{
					printf("%s %d %d %c %d\n", doctor[i].name, doctor[i].local_x, doctor[i].local_y, doctor[i].grade, doctor[i].cost);
					counter++;
					index = i;
				}
			}
		}
		if (counter == 0)
		{
			for (int i = 0; i < doctor_index; i++)
			{
				if (doctor[i].grade == 'D')
				{
					printf("%s %d %d %c %d\n", doctor[i].name, doctor[i].local_x, doctor[i].local_y, doctor[i].grade, doctor[i].cost);
					counter++;
					index = i;
				}
			}
		}
		if (counter == 0)
		{
			for (int i = 0; i < doctor_index; i++)
			{
				if (doctor[i].grade == 'E')
				{
					printf("%s %d %d %c %d\n", doctor[i].name, doctor[i].local_x, doctor[i].local_y, doctor[i].grade, doctor[i].cost);
					counter++;
					index = i;
				}
			}
		}
		if (counter == 0)
		{
			for (int i = 0; i < doctor_index; i++)
			{
				if (doctor[i].grade == 'F')
				{
					printf("%s %d %d %c %d\n", doctor[i].name, doctor[i].local_x, doctor[i].local_y, doctor[i].grade, doctor[i].cost);
					counter++;
					index = i;
				}
			}
		}
		break;
	case COST: // ���ݼ�, �� �Ÿ����� ������ ���
		minimum = doctor[0].cost;
		for (int i = 0; i < doctor_index; i++)
		{
			if (doctor[i].cost < minimum)
			{
				minimum = doctor[i].cost;
				index = i;
			}
		}
		printf("%s %d %d %c %d\n", doctor[index].name, doctor[index].local_x, doctor[index].local_y, doctor[index].grade, doctor[index].cost);
		break;
	}

	strcpy(doctor_name, doctor[index].name); // ����� ������  index�� ������ ������ ������ ���� �ǻ��� �̸��� ������

	return doctor_name;
}

int main()
{
	int button = 0; // 1�̸� ����˻�, 2�� �Ƿ��� �˻�

	int a[STRING_SIZE]; // �Է��� 1��° ���� ���� cnt �迭.
	int b[STRING_SIZE]; // �Է��� 2��° ���� ���� cnt �迭.
	int c[STRING_SIZE]; // �Է��� 3��° ���� ���� cnt �迭.

	char word1[MAX_WORD]; // �Էµ� 1��° ����.
	char word2[MAX_WORD]; // �Էµ� 2��° ����.
	char word3[MAX_WORD]; // �Էµ� 3��° ����.


	// UC-1 log-in �κ�
	printf("Welcome to Smart Health Prediction System!\n");
	printf("Please Login first to continue...\n");
	Login();

	// �����δ� UC-2 ����˻�, UC-3 �ǻ� �˻� �κ�
	printf("\n 1 : ���� �˻�, 2 : �Ƿ��� �˻�  ");
	scanf_s("%d",&button);

	if (button == 1)
	{
		printf("<�Է��� �ѱ���� 0�� �Է��ϰ� ���͸� ���ּ���>.\n");

		printf("\n");

		printf("Symptom 1 : ");
		scanf("%s", &word1);

		printf("\n");

		printf("Symptom 2 : ");
		scanf("%s", &word2);

		printf("\n");

		printf("Symptom 3 : ");
		scanf("%s", &word3);

		printf("\n-------------------------------------\n\n");

		int final[STRING_SIZE];

		for (int i = 0; i < STRING_SIZE; i++) // �� ���� ���� cnt �迭�� 0���� �ʱ�ȭ.
		{
			a[i] = 0;
			b[i] = 0;
			c[i] = 0;
		}

		search(word1, &a); // 1��°�� �Էµ� ���� ���� �� �ٿ� �ִ��� ���� Ȯ��.
		search(word2, &b); // 2��°�� �Էµ� ���� ���� �� �ٿ� �ִ��� ���� Ȯ��.
		search(word3, &c); // 3��°�� �Էµ� ���� ���� �� �ٿ� �ִ��� ���� Ȯ��.

		for (int i = 0; i < STRING_SIZE; i++)  // 3���� cnt�� ���� ������ cnt �迭�� final.
		{
			final[i] = a[i] + b[i] + c[i];
		}

		result(final); // final �迭�� �Ѱ��־ ���� ������ ���� ���� ���.
	}
	else if (button == 2)
	{
		User_data user;
		if (strcmp(userID, "User1")) // �̹� �α����� �Ǿ������� ����ó�� �ʿ� ����
		{
			user.local_x = 20;
			user.local_y = 30;
			strcpy(user.name, "John");
		}
		else if (strcmp(userID, "User2"))
		{
			user.local_x = 40;
			user.local_y = 20;
			strcpy(user.name, "Chris");
		}
		else if (strcmp(userID, "User3"))
		{
			user.local_x = 25;
			user.local_y = 25;
			strcpy(user.name, "Steve");
		}

		int sort_kind = 1;

		printf("\n ���� ������ ���ϼ��� (1 : �Ÿ���, 2 : ������, 3 : ���ݼ�)   : ");
		scanf_s("%d", &sort_kind);
		;
		printf("\n���� ������ �ǻ�� %s �Դϴ�", findDoctor(sort_kind, user));
		// ���� video, audio ������ �����޽��ϴ�.
	}
	else
	{
		printf("\n �߸��� �Է��Դϴ�.");
	}
	

	return 0;
}
