#include <stdio.h>
#include <io.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
struct Phrase
{
	char *word;// 파싱된 단어를 저장
};
typedef struct Phrase phrase;
struct file
{
	char name[30];
	int existence = 0;
	int wordnum = 0;
	int countforsorting = 0;
	phrase *words; // 단어들의 배열을 저장
};
struct file *fi;
void findfile(int *c);
void searchingstring(int *c, char string[30]);
void divide_string(int *c);
void randomnumber(int *c, char string[30]);
void sorting(int *c);
int main()
{
	int count = 1;
	char str[30] = { 0 };
	clock_t before;
	double result;
	findfile(&count);
	printf("Please input string that you want: ");
	scanf("%s", str);
	before = clock();
	searchingstring(&count, str);
	divide_string(&count);
	randomnumber(&count, str);
	sorting(&count);
	free(fi);
	result = (double)(clock() - before) / CLOCKS_PER_SEC;
	printf("걸린시간: %5.2f\n", result);
	return 0;
}
void findfile(int *c)
{
	struct _finddata_t fd;
	long handle;
	int result = 1;
	int i = 0;
	handle = _findfirst("c:\*.txt", &fd);
	if (handle == -1)
	{
		printf("No files!!!\n");
		return;
	}
	while (result != -1)
	{
		result = _findnext(handle, &fd);
		(*c)++;
	}
	handle = _findfirst("c:\*.txt", &fd);
	result = 1;
	fi = (struct file *)calloc((*c)-1, sizeof(struct file));
	while (result != -1)
	{
		strcpy(fi[i].name, fd.name);
		result = _findnext(handle, &fd);
		i++;
	}
	
	_findclose(handle);
	return;
}
void searchingstring(int *c, char string[30])
{
	int i;
	int j;
	int n = 0;
	int p = 0;
	char ch = 1;
	int k = 0;
	for (j = 0;; j++)
	{
		if (string[j] == 0)
		{
			break;
		}
		p++;
	}
	for (i = 0; i < (*c) - 1; i++)
	{
		FILE *fp = fopen(fi[i].name, "rt");

		fi[i].existence = 0;
		while ((ch = fgetc(fp)) != EOF)
		{

			if (ch == string[n] || ch == string[n] - 32)
			{
				n++;
			}
			else
			{
				n = 0;
			}
			if (n == p)
			{
				fi[i].existence = 1;
				break;
			}

		}
		fclose(fp);
	}
	printf("검색한 문자열이 존재하는 파일\n");
	for (i = 0; i < (*c) - 1; i++)
	{
		if (fi[i].existence == 1)
		{
			printf("%s\n", fi[i].name);
		}
	}
	printf("\n");
	return;
}
void divide_string(int *c)
{
	int i;
	int j = 0;
	char *result = { 0 };
	int ch = 1;
	int str = 1;
	char wordbuf[2] = { 0 };
	int k = 0;
	for (i = 0; i < (*c) - 1; i++)
	{
		if (fi[i].existence == 1)
		{
			FILE *fp = fopen(fi[i].name, "r");
			j = 0;
			ch = 1;
			k = 0;
			fseek(fp, 0, SEEK_SET);
			while ((ch != EOF))
			{
				ch = fgetc(fp);
				if ((ch < '0')
					|| ('9' < ch&&ch < 'A')
					|| ('Z' < ch&&ch < 'a')
					|| ('z' < ch))
				{
					j++;
					while (1)
					{
						ch = fgetc(fp);
						if (('0' <= ch && ch <= '9')
							|| ('A' <= ch && ch <= 'Z')
							|| ('a' <= ch && ch <= 'z') ||
							(ch == EOF))
						{
							break;
						}
					}
				}
			}
			fi[i].wordnum = j;
			fi[i].words = (phrase *)calloc(fi[i].wordnum, sizeof(phrase));
			ch = 1;
			fseek(fp, 0, SEEK_SET);
			while (ch != EOF)
			{
				fi[i].words->word = (char*)calloc(55, sizeof(char));
				while (1)
				{
					ch = fgetc(fp);
					if (65 <= ch&&ch <= 90)
					{
						ch = ch + 32;
					}
					wordbuf[0] = (char)ch;
					result = &wordbuf[0];
					if ((48 <= wordbuf[0] && wordbuf[0] <= 57)
						|| (65 <= wordbuf[0] && wordbuf[0] <= 90)
						|| (97 <= wordbuf[0] && wordbuf[0] <= 122))
					{
						strcat(fi[i].words->word, result);
					}
					else
					{
						while (1)
						{
							ch = fgetc(fp);
							if (('0' <= ch && ch <= '9')
								|| ('A' <= ch && ch <= 'Z')
								|| ('a' <= ch && ch <= 'z') ||
								(ch == EOF))
							{
								fseek(fp, -1, SEEK_CUR);
								break;
							}
						}
						fi[i].words++;
						break;
					}
				}
				
			}
			fclose(fp);
		}
	}
	return;
}
void randomnumber(int *c, char string[30])
{
	int a;
	int i;
	int j;
	int k=0;
	int l;
	int computer = 0;
	char *result = { 0 };
	int randcount = 0;
	int q;
	for (i = 0; i < strlen(string); i++)
	{
		if (65 <= string[i] && string[i] <= 90)
		{
			string[i] = string[i] + 32;
		}
	}
	for (i = 0; i < (*c) - 1; i++)
	{
		if (fi[i].existence == 1)
		{
            for(q=0;q<fi[i].wordnum;q++)
			   {
                   fi[i].words--;
			   }
		}
	}
	for (i = 0; i < (*c) - 1; i++)
	{
		if (fi[i].existence == 1)
		{
			srand(time(NULL));
			randcount = 0;
			computer = 0;
			while (1)
			{
				computer = (rand() % fi[i].wordnum) + 1;
				for (j = 1; j <= fi[i].wordnum; j++)
				{
					if (computer == j)
					{
						result = strstr(fi[i].words->word, string);
						randcount++;
						break;
					}
					else
					{
						fi[i].words++;
						k++;
					}
				}
				if (result != '\0')
				{
					fi[i].countforsorting = randcount;
					
					break;
				}
				
				else
				{
					for (l = 0; l < k; l++)
					{
						fi[i].words--;
					}
					k = 0;
				}
			}
			k = 0;
		}
	}
	return;
}
void sorting(int *c)
{
	int i;
	int j;
	int l = 1;
	int temp = 0;
	char str[50] = { 0 };
	int count = 0;
	for (i = 0; i < (*c) - 1; i++)
	{
		if (fi[i].existence == 1)
		{
			count++;
		}
	}
	for (i = 0; i < (*c) - 2; i++)
	{
		for (j = 0; j < ((*c-1) - i) - 1; j++)
		{
			if (fi[j].countforsorting > fi[j + 1].countforsorting)
			{
				temp = fi[j].countforsorting;
				fi[j].countforsorting = fi[j + 1].countforsorting;
				fi[j + 1].countforsorting = temp;
				strcpy(str, fi[j].name);
				strcpy(fi[j].name, fi[j + 1].name);
				strcpy(fi[j + 1].name, str);
			}
		}
	}
	printf("\n\n--------------------------------------------------------------------------------------------------\n\n\n");
	printf("RANKING: 검색한 문자열을 포함하는 단어를 가장 먼저 찾은 텍스트 파일\n");
	for (i = (*c-1)-count; i < (*c)-1; i++)
	{
		printf("%d등. 파일 이름: %s  단어를 뽑은 횟수: %d\n\n", l, fi[i].name, fi[i].countforsorting);
		l++;
	}
	return;
}
















