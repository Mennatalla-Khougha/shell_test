#include "main.h"

int _atoi(char *s)
{
	int i = 0;
	int j;
	int n = 0;
	int power = 1;


	while (s[i])
		i++;
	i--;
	for (j = 0; j <= i; j++)
	{
		if (s[i-j] > 47 && s[i-j] < 58)
		{
			n += (s[i-j] - 48) * power;
			power *= 10;
		}
		else
			return (-1);
	}
	return (n);
}

int main(){
	int num = _atoi("k1");
	printf("%d\n", num);
}