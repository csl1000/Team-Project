#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 256
#define MAX_WORD 100

void search(char word[], int cnt[])
{
	FILE *fp = NULL;
	int line = 0;
	for (int i = 0; i < STRING_SIZE; i++) // 0으로 배열 초기화.
	{
		cnt[i] = 0;
	}

	fp = fopen("DiseaseSearch.txt", "r"); // 데이터 파일을 읽어들임.

	if (fp != NULL)
	{
		char buffer[STRING_SIZE];

		while (!feof(fp)) // 문서 끝에 도달할 때까지 읽음.
		{
			fgets(buffer, sizeof(buffer), fp); // 한줄씩 읽어들임.
			char *ptr = strtok(buffer, " "); // 공백 단위로 끊음. Symptom이나 입력에서 공백은 _ 로 했으므로 공백이 token 단위가 된다.

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
	FILE *fp = NULL;
	int max;
	char buffer[STRING_SIZE];
	char *readByte;
	char *tempStr = malloc(sizeof(char) * 1024);

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
			char *ptr = strtok(buffer, " "); // 해당 줄에는 병명과 증상들이 있으므로 한번 공백 단위로 끊어서 처음에 오는 병명을 ptr에 저장.
			printf("결과 : %s\n", ptr); // 그리고 ptr에 있는 병명을 출력.
			fclose(fp);
			return 0;
		}
		j++;
	}

	fclose(fp);
}

int main()
{
	int a[STRING_SIZE]; // 입력한 1번째 증상에 대한 cnt 배열.
	int b[STRING_SIZE]; // 입력한 2번째 증상에 대한 cnt 배열.
	int c[STRING_SIZE]; // 입력한 3번째 증상에 대한 cnt 배열.

	char word1[MAX_WORD]; // 입력될 1번째 증상.
	char word2[MAX_WORD]; // 입력될 2번째 증상.
	char word3[MAX_WORD]; // 입력될 3번째 증상.

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

	return 0;
}
