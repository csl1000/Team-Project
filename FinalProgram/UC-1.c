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
	int LoginTimes = 0;    //로그인 실패 횟수 체크,5번 이상 로그인 실패->종료
	int LoginNumber = 0;    //로그인 성공 체크,로그인 성공->LoginNumber=1
	char ID[100];    //사용자 입력한 ID,Password 저장
	char PW[100];    
	char UserID[1000];    //저장된 데이터에 환자 의사 ID,Password를 가져옴
	char UserPW[1000];    
	char DoctorID[1000];
	char DoctorPW[1000];
	FILE *fp1, *fp2;    //저장된 데이터를 Read
	fp1 = fopen("User.txt", "r");    //환자 로그인 데이터
	fp2 = fopen("Doctor.txt", "r");    //의사 로그인 데이터
	while (LoginNumber == 0)    
	{
		printf("ID:");    //사용자 ID,Password입력
		scanf(" %s", ID);
		printf("PW:");
		scanf(" %s", PW);
		while (strcmp(UserID, "1") != 0 && strcmp(DoctorID, "1") != 0)    //저장된 데이터에 입력한 ID,Password 체크
		{
			fscanf(fp1, "%s", UserID);
			fscanf(fp1, "%s", UserPW);
			fscanf(fp2, "%s", DoctorID);
			fscanf(fp2, "%s", DoctorPW);
			if (strcmp(UserID, ID) == 0 && strcmp(UserPW, PW) == 0)    //입력한 ID,Password가 저장된 데이터랑 일치하면 Login
			{
				printf("\nYou have successfully landing system...\n");
				UserLogin(ID);    //환자 로그인 성공
				LoginNumber = 1;
				break;
			}
			if (strcmp(DoctorID, ID) == 0 && strcmp(DoctorPW, PW) == 0)
			{
				printf("\nYou have successfully landing system...\n");
				DoctorLogin(ID);    //의사 로그인 성공
				LoginNumber = 1;
				break;
			}
		}
		if (strcmp(UserID, "1") == 0 || strcmp(DoctorID, "1") == 0)    //입력한 ID,Password가 저장된 데이터랑 불일치->로그인 실패->다시 입력
		{
			printf("\nLOGIN ERROR:Wrong ID,PW.\n");
			printf("Please try again...\n\n");
			LoginTimes++;    //로그인 실패 횟수 +1
			memset(UserID, 0, sizeof(UserID));    //저장된 데이터를 다시 Read
			memset(UserPW, 0, sizeof(UserPW));
			memset(DoctorID, 0, sizeof(DoctorID));
			memset(DoctorPW, 0, sizeof(DoctorPW));
			rewind(fp1);
			rewind(fp2);
		}
		if (LoginTimes > 4)    //로그인 실패 횟수 5번 이상->종료
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