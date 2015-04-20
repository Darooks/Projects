#include <stdio.h>
extern __int64  suma_siedmiu_liczb(__int64 v1, __int64 v2, __int64
	v3, __int64 v4, __int64 v5, __int64 v6, __int64 v7);
int main()
{
	__int64 v1 = 123, v2, v3, v4, v5, v6, v7;
	v1 = 1200;
	v2 = 2400;
	v3 = 99999;
	v4 = 44444;
	v5 = 1231523;
	v6 = 5234112;
	v7 = 0xFFFFFF;
	__int64 wartosc_max;
	wartosc_max = suma_siedmiu_liczb(v1, v2, v3, v4, v5, v6, v7);
	printf("\nNajwiekszy element tablicy wynosi %I64d\n",
		wartosc_max);
	return 0;
}