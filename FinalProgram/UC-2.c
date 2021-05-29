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
	for (int i = 0; i < STRING_SIZE; i++) // 0���� �迭 �ʱ�ȭ.
	{
		cnt[i] = 0;
	}

	fp = fopen("DiseaseSearch.txt", "r"); // ������ ������ �о����.

	if (fp != NULL)
	{
		char buffer[STRING_SIZE];

		while (!feof(fp)) // ���� ���� ������ ������ ����.
		{
			fgets(buffer, sizeof(buffer), fp); // ���پ� �о����.
			char *ptr = strtok(buffer, " "); // ���� ������ ����. Symptom�̳� �Է¿��� ������ _ �� �����Ƿ� ������ token ������ �ȴ�.

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
	FILE *fp = NULL;
	int max;
	char buffer[STRING_SIZE];
	char *readByte;
	char *tempStr = malloc(sizeof(char) * 1024);

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
			char *ptr = strtok(buffer, " "); // �ش� �ٿ��� ����� ������� �����Ƿ� �ѹ� ���� ������ ��� ó���� ���� ������ ptr�� ����.
			printf("��� : %s\n", ptr); // �׸��� ptr�� �ִ� ������ ���.
			fclose(fp);
			return 0;
		}
		j++;
	}

	fclose(fp);
}

int main()
{
	int a[STRING_SIZE]; // �Է��� 1��° ���� ���� cnt �迭.
	int b[STRING_SIZE]; // �Է��� 2��° ���� ���� cnt �迭.
	int c[STRING_SIZE]; // �Է��� 3��° ���� ���� cnt �迭.

	char word1[MAX_WORD]; // �Էµ� 1��° ����.
	char word2[MAX_WORD]; // �Էµ� 2��° ����.
	char word3[MAX_WORD]; // �Էµ� 3��° ����.

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

	return 0;
}
