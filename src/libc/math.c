#include "math.h"

int pow(int num, int exp)
{
	if (exp < 0) {
		return 0;
	}
	if (exp == 0) return 1;
	if (exp == 1) return num;

	int ret = num;
	for (; exp > 1; exp --){
		ret *= num;
	}
	return ret;
}