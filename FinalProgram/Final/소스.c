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

char userID[20]; // user의 아이디 저장공간



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
	int LoginTimes = 0;    //로그인 실패 횟수 체크,5번 이상 로그인 실패->종료
	int LoginNumber = 0;    //로그인 성공 체크,로그인 성공->LoginNumber=1
	char ID[100];    //사용자 입력한 ID,Password 저장
	char PW[100];
	char UserID[1000];    //저장된 데이터에 환자 의사 ID,Password를 가져옴
	char UserPW[1000];
	char DoctorID[1000];
	char DoctorPW[1000];
	FILE* fp1, * fp2;    //저장된 데이터를 Read
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

void search(char word[], int cnt[])
{
	FILE* fp = NULL;
	int line = 0;
	for (int i = 0; i < STRING_SIZE; i++) // 0으로 배열 초기화.
	{
		cnt[i] = 0;
	}

	fp = fopen("DiseaseSearch.txt", "r"); // 데이터 파일을 읽어들임.

	if (fp != NULL)
	{
		char buffer[STRING_SIZE];

		while (!feof(fp)) // 문서 끝에 도달할 때까지 읽음.s
		{
			fgets(buffer, sizeof(buffer), fp); // 한줄씩 읽어들임.
			char* ptr = strtok(buffer, " "); // 공백 단위로 끊음. Symptom이나 입력에서 공백은 _ 로 했으므로 공백이 token 단위가 된다.

			while (ptr != NULL)
			{
				// int com = strcmp(word, ptr);
				if (strstr(ptr, word)) // 입력된 단어가 token에 있는지 확인. 해당 단어가 없으면 NULL이 되어 if문이 실행되지 않음. 해당 단어 존재 시 if문 실행.
				{
					cnt[line]++; // 해당 단어가 존재할 시 0이 된다. 그리하여 해당 줄에 해당 단어가 있는지 확인하는 cnt를 증가시킨다. 이를테면 1번째 줄에 있을 경우, cnt[0]이 1 증가.

				}
				ptr = strtok(NULL, " ");

				// printf("%d : %d\n", line, cnt[line]);

			}

			line++; // 줄을 증가.
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

	for (int i = 0; i < STRING_SIZE; i++) // cnt 배열에서 가장 큰 수를 찾음.
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
		readByte = fgets(buffer, sizeof(buffer), fp); // 1줄씩 읽음. readByte에 저장.
		if (cnt[j] == max) // cnt 중 max인 값을 출력. 즉, 연관성이 가장 큰 결과를 출력.
		{
			strcpy(tempStr, readByte); // tempStr에 해당 줄을 복사.
			char* ptr = strtok(buffer, " "); // 해당 줄에는 병명과 증상들이 있으므로 한번 공백 단위로 끊어서 처음에 오는 병명을 ptr에 저장.
			printf("결과 : %s\n", ptr); // 그리고 ptr에 있는 병명을 출력.
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
	int doctor_index = 0; // doctor배열의 index
	char file_line[50]; // 파일 읽을 때 1줄을 받아들이는 변수
	int counter = 0;
	int minimum = 0; // Cost, Distance 비교를 위한 변수
	int index = 0; 
	int distance[20];
	char doctor_name[20];


	FILE* fp;
	fp = fopen("doctorinfo.txt", "r");
	if (fp == NULL) // 파일이 없을 때 예외처리
	{
		printf("Can't find file\n");
		exit(1);
	}
	else
	{
		while (!feof(fp)) // 파일 끝까지 읽어냄
		{
			// 파일 형식은 고정임으로 파일에서 5가지의 정보를 각각 doctor 구조체 배열에 한개씩 삽입
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

			doctor_index++; // doctor 배열에 다음 원소 접근
		}
	}

	fclose(fp);

	switch (sort_kind)// 입력된 sort_kind를 통해 3가지 접근 방식 제공
	{
	case DISTANCE: // 거리순일때
		for (int i = 0; i < doctor_index; i++) // 루트를 사용하지 않아도 거리 비교는 가능함으로(거리는 항상 0보다 크니) 환자와 각 의사들의 거리를 구함
		{
			distance[i] = abs(doctor[i].local_x - user.local_x) * abs(doctor[i].local_x - user.local_x) + abs(doctor[i].local_y - user.local_y) * abs(doctor[i].local_y - user.local_y);
		}

		minimum = distance[0];
		for (int i = 0; i < doctor_index; i++)
		{
			if (distance[i] < minimum) // 기존 최솟값보다 거리가 작다면 그것으로 최솟값 대체, index값 저장
			{
				minimum = distance[i];
				index = i;
			}
		}
		printf("%s %d %d %c %d\n", doctor[index].name, doctor[index].local_x, doctor[index].local_y, doctor[index].grade, doctor[index].cost);
		break;
	case GRADE: // 평점순일때
		for (int i = 0; i < doctor_index; i++)
		{
			if (doctor[i].grade == 'A')
			{
				printf("%s %d %d %c %d\n", doctor[i].name, doctor[i].local_x, doctor[i].local_y, doctor[i].grade, doctor[i].cost);
				counter++;
				index = i; // 제일 높은 평점의 의사의 index를 저장해둠
			}
		}

		if (counter == 0) // 모든 의사들의 평점이 A가 아니라면 B를 확인 할 수 있도록 도와줌
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
	case COST: // 가격순, 위 거리순과 유사한 방식
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

	strcpy(doctor_name, doctor[index].name); // 결과로 생성된  index를 가지고 최적의 조건을 갖는 의사의 이름을 복사함

	return doctor_name;
}

int main()
{
	int button = 0; // 1이면 증상검색, 2면 의료진 검색

	int a[STRING_SIZE]; // 입력한 1번째 증상에 대한 cnt 배열.
	int b[STRING_SIZE]; // 입력한 2번째 증상에 대한 cnt 배열.
	int c[STRING_SIZE]; // 입력한 3번째 증상에 대한 cnt 배열.

	char word1[MAX_WORD]; // 입력될 1번째 증상.
	char word2[MAX_WORD]; // 입력될 2번째 증상.
	char word3[MAX_WORD]; // 입력될 3번째 증상.


	// UC-1 log-in 부분
	printf("Welcome to Smart Health Prediction System!\n");
	printf("Please Login first to continue...\n");
	Login();

	// 밑으로는 UC-2 증상검색, UC-3 의사 검색 부분
	printf("\n 1 : 증상 검색, 2 : 의료진 검색  ");
	scanf_s("%d",&button);

	if (button == 1)
	{
		printf("<입력을 넘기려면 0을 입력하고 엔터를 쳐주세요>.\n");

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

		for (int i = 0; i < STRING_SIZE; i++) // 각 증상에 대한 cnt 배열을 0으로 초기화.
		{
			a[i] = 0;
			b[i] = 0;
			c[i] = 0;
		}

		search(word1, &a); // 1번째로 입력된 증상에 대해 각 줄에 있는지 여부 확인.
		search(word2, &b); // 2번째로 입력된 증상에 대해 각 줄에 있는지 여부 확인.
		search(word3, &c); // 3번째로 입력된 증상에 대해 각 줄에 있는지 여부 확인.

		for (int i = 0; i < STRING_SIZE; i++)  // 3가지 cnt에 대해 합쳐진 cnt 배열인 final.
		{
			final[i] = a[i] + b[i] + c[i];
		}

		result(final); // final 배열을 넘겨주어서 가장 연관성 높은 줄을 출력.
	}
	else if (button == 2)
	{
		User_data user;
		if (strcmp(userID, "User1")) // 이미 로그인이 되었음으로 예외처리 필요 없음
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

		printf("\n 정렬 순서를 정하세요 (1 : 거리순, 2 : 평점순, 3 : 가격순)   : ");
		scanf_s("%d", &sort_kind);
		;
		printf("\n가장 적합한 의사는 %s 입니다", findDoctor(sort_kind, user));
		// 이후 video, audio 연결은 제외햇습니다.
	}
	else
	{
		printf("\n 잘못된 입력입니다.");
	}
	

	return 0;
}
