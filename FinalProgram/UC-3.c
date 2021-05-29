#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARINGS
#pragma warning(disable : 4996)

#define DISTANCE 1
#define GRADE 2
#define COST 3

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

const char* findDoctor(int sort_kind, User_data user)
{
	Doctor_data doctor[20];
	int doctor_index = 0;
	char file_line[50];
	int counter = 0;
	int minimum = 0;
	int index = 0;
	int distance[20];
	char doctor_name[20];
	

	FILE* fp;
	fp = fopen("doctor.txt", "r");
	if (fp == NULL)
	{
		printf("Can't find file\n");
		exit(1);
	}
	else
	{
		while (!feof(fp))
		{
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

			doctor_index++;
		}
	}

	fclose(fp);
	

	switch (sort_kind)
	{
		case DISTANCE:
			for (int i = 0; i < doctor_index; i++)
			{
				distance[i] = abs(doctor[i].local_x - user.local_x)* abs(doctor[i].local_x - user.local_x) + abs(doctor[i].local_y - user.local_y) * abs(doctor[i].local_y - user.local_y);
			}

			minimum = distance[0];
			for (int i = 0; i < doctor_index; i++)
			{
				if (distance[i] < minimum)
				{
					minimum = distance[i];
					index = i;
				}
			}
			printf("%s %d %d %c %d\n", doctor[index].name, doctor[index].local_x, doctor[index].local_y, doctor[index].grade, doctor[index].cost);
			break;
		case GRADE:			
			for (int i = 0; i < doctor_index; i++)
			{
				if (doctor[i].grade == 'A')
				{
					printf("%s %d %d %c %d\n", doctor[i].name, doctor[i].local_x, doctor[i].local_y, doctor[i].grade, doctor[i].cost);
					counter++;	
					index = i;
				}
			}
			
			if (counter == 0)
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
		case COST:
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

	strcpy(doctor_name, doctor[index].name);

	return doctor_name;
}

int main()
{
	User_data user;
	user.local_x = 20;
	user.local_y = 30;
	strcpy(user.name, "Junghwan");

	int sort_kind = 1;	

	printf("정렬 순서를 정하세요 (1 : 거리순, 2 : 평점순, 3 : 가격순)   : ");
	scanf_s("%d", &sort_kind);

	printf("가장 적합한 의사의 정보\n");
	printf("%s",findDoctor(sort_kind, user));
}