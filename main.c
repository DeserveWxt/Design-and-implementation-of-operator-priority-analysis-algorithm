#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char formula[200];					//����ʽ
}grammarElement;

grammarElement gramOldSet[200];			//ԭʼ�ķ��Ĳ���ʽ��
grammarElement gramNewSet[200];			//չ����Ĳ���ʽ��

int NUM;								//ԭʼ�ķ�����ʽ����
int newNUM;								//չ������ķ��Ĳ���ʽ������
int VTnum;								//�ս������
int VNnum;								//���ս������
char VT[200];							//�ս��
char VN[200];							//���ս��
char firstVT[100][100];					//������ʽ�Ҳ���firstVT��
char lastVT[100][100];					//������ʽ�󲿵�lastVT��
char table[100][100];					//������ȷ�����

void GramInit(grammarElement gram[])							//�ķ���ʼ��
{
	char s[4] = "end";
	NUM = 1;
	printf_s("�������ķ��������ַ���ʹ�á�$�����棬	end������\n");
	for (;;)
	{
		scanf_s("%s", &gram[NUM].formula, 200);
		if (!(strcmp(gram[NUM].formula, s)))
		{
			NUM--;
			break;
		}
		NUM++;
	}
	printf_s("\n");
}

void JudgeGram(grammarElement gram[],int n)						//�ж��ķ��Ƿ�������ķ�
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; gram[i].formula[j] != '\0'; j++)
		{
			if (gram[i].formula[0] < 'A' || gram[i].formula[0]>'Z' || gram[i].formula[1] != '-' || gram[i].formula[2] != '>' || ((gram[i].formula[j]>='A' && gram[i].formula[j]<='Z') && (gram[i].formula[j+1] >= 'A' && gram[i].formula[j+1] <= 'Z')))
			{
				printf_s("���ķ���������ķ�!");
				exit(0);
			}
		}
	}
}

void open(grammarElement gram[], int n)							//���ķ�չ��
{
	newNUM = 0;
	int length;
	for (int i = 1; i <= n; i++)
	{
		firstVT[i][0] = gram[i].formula[0];
		lastVT[i][0] = gram[i].formula[0];
		for (int j = 3; gram[i].formula[j] != '\0'; j++)
		{
			if (j == 3 || gram[i].formula[j] == '|')
			{
				newNUM++;
				length = 2;
				gramNewSet[newNUM].formula[0] = gram[i].formula[0];
				gramNewSet[newNUM].formula[1] = gram[i].formula[1];
				gramNewSet[newNUM].formula[2] = gram[i].formula[2];
			}
			if (gram[i].formula[j] == '|')
				continue;
			gramNewSet[newNUM].formula[++length] = gram[i].formula[j];
		}
	}
}

void PrintGram(grammarElement gram[], int n)					//����ķ�
{
	for (int i = 1; i <= n; i++)
		printf_s("%d\t%s\n", i, &gram[i].formula);
	printf_s("\n");
}

void ExtSymbol(grammarElement gram[], int n)					//��ȡ���з���
{
	VTnum = 0;
	VNnum = 0;
	int k;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; gram[i].formula[j] != '\0'; j++)
		{
			if (j == 1 || j == 2 || gram[i].formula[j] == '|')
				continue;
			if (gram[i].formula[j] >= 'A' && gram[i].formula[j] <= 'Z')
			{
				for (k = 1; k <= VNnum; k++)
					if (gram[i].formula[j] == VN[k])
						break;
				if (k == VNnum + 1)
					VN[++VNnum] = gram[i].formula[j];
			}
			else
			{
				for (k = 1; k <= VTnum; k++)
					if (gram[i].formula[j] == VT[k])
						break;
				if (k == VTnum + 1)
				{
					VT[++VTnum] = gram[i].formula[j];
					table[VTnum][0] = gram[i].formula[j];
					table[0][VTnum] = gram[i].formula[j];
				}
			}
		}
	}
}

void PrintSymbol(char c[], int len)								//�������
{
	for (int i = 1; i <= len; i++)
		printf_s("%c\t", c[i]);
	printf_s("\n");
}

void print_f(char a[100][100], int n, int tag)					//���firstVT����lastVT��
{
	for (int i = 1; i <= n; i++)
	{
		if (tag == 0)
			printf_s("firstVT(%c)={", a[i][0]);
		else
			printf_s("lastVT(%c)={", a[i][0]);
		for (int j = 1; a[i][j] != '\0'; j++)
		{
			printf_s("%c", a[i][j]);
			if (a[i][j + 1] != '\0')
				printf_s(",");
		}
		printf_s("}\n");
	}
}

void firstvt(grammarElement gramNewSet[], int newNUM)			//��firstVT��
{
	int tag;
	int k;
	for (int i = newNUM; i >= 1; i--)
	{
		for (int j = VNnum; j >= 1; j--)
		{
			if (firstVT[j][0] == gramNewSet[i].formula[0])
			{
				if (gramNewSet[i].formula[3] < 'A' || gramNewSet[i].formula[3] > 'Z')
				{
					tag = 0;
					for (k = 1; firstVT[j][k] != '\0'; k++)
					{
						if (gramNewSet[i].formula[3] == firstVT[j][k])
						{
							tag = 1;
							break;
						}
					}
					if (tag == 0)
						firstVT[j][k] = gramNewSet[i].formula[3];
				}
				else if (gramNewSet[i].formula[3] >= 'A' && gramNewSet[i].formula[3] <= 'Z')
				{
					for (int m = 1; m <= VNnum; m++)
					{
						if (firstVT[m][0] == gramNewSet[i].formula[3])
						{
							for (int n = 1; firstVT[m][n] != '\0'; n++)
							{
								tag = 0;
								for (k = 1; firstVT[j][k] != '\0'; k++)
								{
									if (firstVT[m][n] == firstVT[j][k])
									{
										tag = 1;
										break;
									}
								}
								if (tag == 0)
									firstVT[j][k] = firstVT[m][n];
							}
						}
					}
					if (gramNewSet[i].formula[4] != '\0' && (gramNewSet[i].formula[4] < 'A' || gramNewSet[i].formula[4]>'Z'))
					{
						tag = 0;
						for (k = 1; firstVT[j][k] != '\0'; k++)
						{
							if (gramNewSet[i].formula[4] == firstVT[j][k])
							{
								tag = 1;
								break;
							}
						}
						if (tag == 0)
							firstVT[j][k] = gramNewSet[i].formula[4];
					}
				}
			}
		}
	}
}

void lastvt(grammarElement gramNewSet[], int newNUM)			//��lastVT��
{
	int tag;
	int k;
	int x;
	for (int i = newNUM; i >= 1; i--)
	{
		for (int j = VNnum; j >= 1; j--)
		{
			if (lastVT[j][0] == gramNewSet[i].formula[0])
			{
				x = 3;
				while (gramNewSet[i].formula[x] != '\0')
					x++;
				if (gramNewSet[i].formula[x-1] < 'A' || gramNewSet[i].formula[x-1] > 'Z')
				{
					tag = 0;
					for (k = 1; lastVT[j][k] != '\0'; k++)
					{
						if (gramNewSet[i].formula[x-1] == lastVT[j][k])
						{
							tag = 1;
							break;
						}
					}
					if (tag == 0)
						lastVT[j][k] = gramNewSet[i].formula[x-1];
					}
				else if (gramNewSet[i].formula[x-1] >= 'A' && gramNewSet[i].formula[x-1] <= 'Z')
				{
					for (int m = 1; m <= VNnum; m++)
					{
						if (lastVT[m][0] == gramNewSet[i].formula[x-1])
						{
							for (int n = 1; lastVT[m][n] != '\0'; n++)
							{
								tag = 0;
								for (k = 1; lastVT[j][k] != '\0'; k++)
								{
									if (lastVT[m][n] == lastVT[j][k])
									{
										tag = 1;
										break;
									}
								}
								if (tag == 0)
									lastVT[j][k] = lastVT[m][n];
							}
						}
					}
					if (gramNewSet[i].formula[x-2] != '>' && (gramNewSet[i].formula[x-2] < 'A' || gramNewSet[i].formula[x-2]>'Z'))
					{
						tag = 0;
						for (k = 1; lastVT[j][k] != '\0'; k++)
						{
							if (gramNewSet[i].formula[4] == lastVT[j][k])
							{
								tag = 1;
								break;
							}
						}
						if (tag == 0)
							lastVT[j][k] = gramNewSet[i].formula[x-2];
					}
				}
			}
		}
	}
}

void wxt(char c1, char c2, char c3)
{
	for (int i = 1; i <= VTnum; i++)
	{
		if (table[i][0] == c1)
		{
			for (int j = 1; j <= VTnum; j++)
			{
				if (table[0][j] == c2)
				{
					table[i][j] = c3;
					break;
				}
			}
			break;
		}
	}
}

void StrTable(grammarElement gramNewSet[], int newNUM)			//����������ȷ�����
{
	for (int i = 1; i <= newNUM; i++)
	{
		for (int k = 3; gramNewSet[i].formula[k] != '\0'; k++)
		{
			if ((gramNewSet[i].formula[k] < 'A' || gramNewSet[i].formula[k]>'Z') && gramNewSet[i].formula[k + 1] != '\0' && (gramNewSet[i].formula[k + 1] < 'A' || gramNewSet[i].formula[k + 1]>'Z'))
				wxt(gramNewSet[i].formula[k], gramNewSet[i].formula[k + 1], '=');
			if ((gramNewSet[i].formula[k] < 'A' || gramNewSet[i].formula[k]>'Z') && gramNewSet[i].formula[k + 2] != '\0' && (gramNewSet[i].formula[k + 2] < 'A' || gramNewSet[i].formula[k + 2]>'Z') && (gramNewSet[i].formula[k+1]>='A'&& gramNewSet[i].formula[k + 1] <= 'Z'))
				wxt(gramNewSet[i].formula[k], gramNewSet[i].formula[k + 2], '=');
			if ((gramNewSet[i].formula[k] < 'A' || gramNewSet[i].formula[k]>'Z') && gramNewSet[i].formula[k + 1] != '\0' && (gramNewSet[i].formula[k + 1] >= 'A' && gramNewSet[i].formula[k + 1] <= 'Z'))
			{
				for (int m = 1; m <= VTnum; m++)
				{
					if (firstVT[m][0] == gramNewSet[i].formula[k + 1])
					{
						for (int n = 1; firstVT[m][n] != '\0'; n++)
							wxt(gramNewSet[i].formula[k], firstVT[m][n], '<');
						break;
					}
				}
			}
			if ((gramNewSet[i].formula[k] >= 'A' && gramNewSet[i].formula[k] <= 'Z') && gramNewSet[i].formula[k + 1] != '\0' && (gramNewSet[i].formula[k + 1] < 'A' || gramNewSet[i].formula[k + 1] > 'Z'))
			{
				for (int m = 1; m <= VTnum; m++)
				{
					if (lastVT[m][0] == gramNewSet[i].formula[k])
					{
						for (int n = 1; lastVT[m][n] != '\0'; n++)
							wxt(lastVT[m][n], gramNewSet[i].formula[k + 1], '>');
						break;
					}
				}
			}
		}
	}
	VT[++VTnum] = '#';
	table[VTnum][0] = '#';
	table[0][VTnum] = '#';
	for (int i = 1; i <= VTnum; i++)
	{
		if (table[0][i] == ')')
			continue;
		if (table[0][i] == '#')
			table[VTnum][i] = '=';
		else
			table[VTnum][i] = '<';
	}
	for (int i = 1; i <= VTnum; i++)
	{
		if (table[i][0] == '(')
			continue;
		if (table[i][0] == '#')
			table[i][VTnum] = '=';
		else
			table[i][VTnum] = '>';
	}
}

void PrintTable()												//���������ȷ�����
{
	for (int i = 0; i <= VTnum; i++)
	{
		for (int j = 0; j <= VTnum; j++)
		{
			printf_s("%c\t", table[i][j]);
		}
		printf_s("\n\n");
	}
}

int lxm(char c1, char c2)
{
	for (int i = 1; i <= VTnum; i++)
	{
		if (table[i][0] == c1)
		{
			for (int j = 1; j <= VTnum; j++)
			{
				if (table[0][j] == c2)
				{
					if (table[i][j] == '>')
						return 1;
					if (table[i][j] == '=')
						return 0;
					if (table[i][j] == '<')
						return -1;
				}
			}
		}
	}
}

int JVT(char c)
{
	for (int i = 1; i <= VTnum; i++)
	{
		if (VT[i] == c)
		{
			return 1;
		}
	}
	return 0;
}

int JVN(char c)
{
	for (int i = 1; i <= VNnum; i++)
	{
		if (VN[i] == c)
		{
			return 1;
		}
	}
	return 0;
}

void JE()
{
	printf("��������ʽ:(exit�˳�)\n");
	char str[100] = {0};
	char c[5] = "exit";
	char S[100] = {0};
	int i, j, k, tag;
	char a, b, p;
	for (;;)
	{
		scanf_s("%s", &str,100);
		if (!strcmp(str, c))
			break;
		else
		{
			for (p = 0; str[p] != '\0'; p++)
				;
			str[p] = '#';
			k = 1;
			S[k] = '#';
			i = 0;
			tag = 0;
			while((a = str[i]) != '\0')
			{
				if (JVT(S[k]) == 1)
					j = k;
				else
					j = k - 1;
				while (lxm(S[j], a) == 1)
				{
					do
					{
						b = S[j];
						if (JVT(S[j-1]) == 1)
							j = j - 1;
						else
							j = j - 2;
					} while (lxm(S[j], b) != -1);
					
					if (JVN(S[j + 1]) && S[j + 2] == '\0')
					{
						for (int y = 1; y <= newNUM; y++)
						{
							if (gramNewSet[y].formula[3] == S[j+1])
							{
								S[j + 1] = gramNewSet[y].formula[0];
								break;
							}
						}
					}
					else if (JVN(S[j + 1]) && JVT(S[j + 2]))
					{
						for (int y = 1; y <= newNUM; y++)
						{
							if (gramNewSet[y].formula[4] == S[j + 2])
							{
								S[j + 1] = gramNewSet[y].formula[0];
								break;
							}
						}
					}
					else if (S[j + 1] == '(' && S[j + 3] == ')')
					{
						for (int y = 1; y <= newNUM; y++)
						{
							if (gramNewSet[y].formula[3] == S[j + 1])
							{
								S[j + 1] = gramNewSet[y].formula[0];
								break;
							}
						}
					}
					else
					{
						for (int y = 1; y <= newNUM; y++)
						{
							if (gramNewSet[y].formula[3] == 'i')
							{
								S[j + 1] = gramNewSet[y].formula[0];
								break;
							}
						}
					}
					
					k = j + 1;
					if (a == '#')
					{
						if (k == 2)
							printf("��ȷ!\n\n");
						else
							printf("����!\n\n");
						tag = 1;
						break;
					}
				}
				if (tag == 1)
					break;
				k = k + 1;
				S[k] = a;
				i++;
			}
		}
	}
}

int main()
{
	GramInit(gramOldSet);							//�ķ���ʼ��

	JudgeGram(gramOldSet,NUM);						//�ж��Ƿ�������ķ�

	open(gramOldSet, NUM);							//���ķ�չ��

	printf_s("չ������ķ�Ϊ��\n");
	PrintGram(gramNewSet, newNUM);					//���չ�����ķ�

	ExtSymbol(gramNewSet, newNUM);					//��ȡ���з���

	printf_s("�ս����");
	PrintSymbol(VT, VTnum);							//��������ս��

	printf_s("���ս����");
	PrintSymbol(VN, VNnum);							//������з��ս��

	firstvt(gramNewSet, newNUM);					//��firstVT��
	printf_s("\nfirstVT����\n");
	print_f(firstVT, VNnum, 0);						//���firstVT��

	lastvt(gramNewSet, newNUM);						//��lastVT��
	printf_s("\nlastVT����\n");
	print_f(lastVT, VNnum, 1);						//���lastVT��
	
	StrTable(gramNewSet, newNUM);					//������������ȷ�����
	PrintTable();									//���������ȷ�����
	
	JE();

	return 0;
}