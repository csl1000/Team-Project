#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void UserLogin(char []);
void DoctorLogin(char []);
void Login();

int main()
{
	printf("Welcome to Smart Health Prediction System!\n");
	printf("Please Login first to continue...\n");
	Login();

	return 0;
}

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
	FILE *fp1, *fp2;    //����� �����͸� Read
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