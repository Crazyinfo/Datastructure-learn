#include<stdio.h>
#define MAX 255

/*�Ż�˼�룺������ǰ���next�����ָʾ���Ӵ�����һ��Ԫ�����Ƚϣ�
�����Ԫ����ԭ�����Ӵ��е��Ǹ�Ԫ������ȵģ������������Ƚϻ���ʧ�ܡ�
�����ͨ����next������Ż������Ż�KMP�㷨�����Ա�����ת����һ�β�ƥ������Ķ�����ת�� 
*/

//�������� 
void StrintoTorS(char *TS, char *chars);  //������chars�ַ������Ƹ�Ŀ�괮S��ģʽ��T 
void GetintoNext(char *TN, int *next0);  //����KMP�㷨�γ�next0���飬ָʾƥ��������Ӵ���ƥ�����һ��Ԫ�� 
void BetterNext(char *Tb, int *bnext);  //��KMP�㷨��next��������Ż� 
int StrMatch(char *S0, char *T0, int pos);  //�����Ż����next�������ƥ�� 


int main()
{
	int j = 0;
	char T[MAX], S[MAX];
	char chars1[] = "cabdabaabcabaabadcb";
	char chars2[] = "abaaba";
	StrintoTorS(S, chars1);
	StrintoTorS(T, chars2);
	int k = StrMatch(S, T, 1);
	if(k)
		printf("\n\nThe mainstring S='%s'\nThe substring T='%s'\n\n******Start matching on %d position******\n",
				chars1, chars2, k);
	else
		printf("\n\nThe mainstring S='%s'\nThe substring T='%s'\n\n******Match failure******",
				chars1, chars2);
}

//������chars��ֵ��Ŀ���ģʽ��TS
void StrintoTorS(char *TS, char *chars)
{
	TS[0] = 0;  //�׸�Ԫ�ش��洮Ԫ�صĸ���
	int i = 0;
	while(chars[i])
	{
		TS[i+1] = chars[i];
		i++;
		TS[0] = i;
	}
}

//�г�ģʽ��T�е�next����ֵ,������next����
void GetintoNext(char *TN, int *next0)
{
	int i = 1, j = 0;
	next0[i] = 0;
	while(i<TN[0])
	{
		if(j==0 || TN[i]==TN[j])
		{
			i++;j++;
			next0[i] = j;
		}
		else
		{
			j = next0[j];
		}
	} 
}

//�Ľ�:����next�����ָ����������һ��Ԫ�أ������Ԫ����ԭ������ͬʱ��Ӧ���Ľ��������γɵ�next�Ͻ��иĽ� 
void BetterNext(char *Tb, int *bnext)
{
	int i = 2;
	while(bnext[i])
	{
		if(Tb[i]==Tb[bnext[i]])
		{
			bnext[i] = bnext[bnext[i]];
			i++;
		}
		else
		{
			i++;
		}
	}
}

//ģʽ����Ŀ�괮��ƥ�� 
int StrMatch(char *S0, char *T0, int pos)
{
	int i = pos, j = 1;
	int k = 1, m = 1;
	int next[MAX];
	GetintoNext(T0, next);
	printf("the next of origin KMP:");
	//���ԭ���γɵ�next���� 
	while(T0[k])
	{
		printf("%d ",next[k]);
		k++;
	}
	printf("\nthe next of better KMP:"); 
	BetterNext(T0, next);
	//����Ż��γɵ�next����
	while(T0[m])
	{
		printf("%d ",next[m]);
		m++;
	}
	while(i<=S0[0] && j<=T0[0])
	{
		if(j==0 || S0[i]==T0[j])
		{
			i++;j++;
		}
		else
		{
			j = next[j];
		}
	}
	//����ƥ��������ƥ���λ�� 
	if(j>T0[0])
		return i-T0[0];
	else
		return 0;
}
