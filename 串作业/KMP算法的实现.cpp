#include<stdio.h>
#define MAX 255

/*优化思想：如果我们按照next数组的指示换子串的另一个元素来比较，
但这个元素与原来的子串中的那个元素是相等的，这样和主串比较还是失败。
因此想通过对next数组的优化进而优化KMP算法。可以避免跳转后再一次不匹配产生的二次跳转。 
*/

//函数申明 
void StrintoTorS(char *TS, char *chars);  //将数组chars字符串复制给目标串S或模式串T 
void GetintoNext(char *TN, int *next0);  //按照KMP算法形成next0数组，指示匹配过程中子串不匹配的下一跳元素 
void BetterNext(char *Tb, int *bnext);  //对KMP算法中next数组进行优化 
int StrMatch(char *S0, char *T0, int pos);  //利用优化后的next数组进行匹配 


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

//将数组chars赋值给目标或模式串TS
void StrintoTorS(char *TS, char *chars)
{
	TS[0] = 0;  //首个元素储存串元素的个数
	int i = 0;
	while(chars[i])
	{
		TS[i+1] = chars[i];
		i++;
		TS[0] = i;
	}
}

//列出模式串T中的next函数值,并存入next数组
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

//改进:根据next数组的指数跳到另外一个元素，而这个元素与原来的相同时，应当改进，故在形成的next上进行改进 
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

//模式串与目标串的匹配 
int StrMatch(char *S0, char *T0, int pos)
{
	int i = pos, j = 1;
	int k = 1, m = 1;
	int next[MAX];
	GetintoNext(T0, next);
	printf("the next of origin KMP:");
	//输出原来形成的next数组 
	while(T0[k])
	{
		printf("%d ",next[k]);
		k++;
	}
	printf("\nthe next of better KMP:"); 
	BetterNext(T0, next);
	//输出优化形成的next数组
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
	//根据匹配结果返回匹配的位置 
	if(j>T0[0])
		return i-T0[0];
	else
		return 0;
}
