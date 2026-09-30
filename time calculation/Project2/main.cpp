#include <stdio.h>
#include <string.h>


int main(void)
{ 
	//변수 선언
	int ntotal = 0;
	double nsecond = 0;
	int nhour = 0;
	int nminute = 0;
	
	printf("Please enter the total time in seconds. : ");
	scanf_s("%d", &ntotal);
	nhour = (int)(ntotal / 3600); //초를 시간으로 변환
	nminute = (int)(ntotal % 3600) / 60; //초를 분으로 변환
	nsecond = (ntotal % 3600) % 60; // 나머지를 초로 변환

	printf(" %d seconds is equal to %d hours %d minutes %g seconds.", ntotal, nhour, nminute, nsecond);

	return 0;
}
