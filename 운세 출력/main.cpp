#include <stdio.h>
int g_birth = 0;
int g_flag = 1; //오류 판별 변수, 0이면 정상 1이면 비정상

void Discrimination(void);
void question(void);
int sum(void);
void Destiny_Script(void);

void question(void) //입력 함수
{
    printf("\n\nEnter your 8-digit birthdate (YYYYMMDD): "); //입력
	
    if (scanf("%d", &g_birth) != 1) //입력 받은 값이 숫자형인지 문자형인지 판별, !는 논리 부정(NOT) 연산자 참과 거짓 상태를 반대로 뒤집는 역할
    {
       		printf("\n----------------------------------------------------------\n");
		printf("[Warning] Characters other than numbers have been entered.");
		printf("\n----------------------------------------------------------");
        while (getchar() != '\n'); // 버퍼에 남은 찌꺼기 문자 청소
		{
			g_flag = 1;// 재입력 필요 신호
		}
        return; // 함수 즉시 종료
    }
    char next_char = getchar(); // 숫자,문자 혼동사용 판별
    if (next_char != '\n')
    {
        printf("\n----------------------------------------------------------\n");
        printf("[Warning] Characters or trailing text cannot be mixed with numbers.");
        printf("\n----------------------------------------------------------");
        
        if (next_char != -1)
        {
            while (getchar() != '\n'); // 남아있는 찌꺼기 문자 청소
        }
        
        g_flag = 1; // 재입력 필요 신호
        return;
    }
	
	
	g_flag = 0; // 문자가 아니라 숫자로 잘 들어왔다면 정상으로 판단 0으로 설정
	
	
    if (g_flag == 0)  // 숫자가 정상적으로 입력된 경우에만 자릿수 판별 함수 실행
    {
        Discrimination();
    }
}
void Discrimination(void) //자릿수 판별 함수
{
    int temp = g_birth;
    int count = 0;

    while (temp > 0) // 숫자를 10씩 나누며 자릿수 카운트
    {
        temp = temp / 10;
        count=count+1;
    }
    if (count != 8) // 자릿수가 8자리가 아닐 경우
    {
       
		printf("\n--------------------------------------------------------------\n");
		printf("[Error] It is not an exactly 8-digit number. (Current digit: %d)",count);
		printf("\n--------------------------------------------------------------");
        g_flag = 1; // 8자리가 아니므로 다시 입력받도록 플래그 설정
    }
    else
    {
        g_flag = 0; // 8자리 정상 통과
		printf("====================================================\n\n");
		printf("Authentication successful! Date of birth entered: %d\n\n",g_birth);
		printf("====================================================\n");
    }
}
int sum(void) // 더하기 함수
{
    int Destiny_Number = g_birth;
    int Destiny_Number_sum = 0;
    int count = 0;
    
	printf("Calculating...\n");
	
	while (count < 8) // 일단 8번 반복
	{
		Destiny_Number_sum =Destiny_Number_sum + Destiny_Number % 10; // 일의 자리를 더함(ex-> 20040322-> Destiny_Number_sum+2)
		Destiny_Number = Destiny_Number / 10;                      // 일의 자리를 날려버리기(ex-> 20040322->2004032)
		count = count + 1;
	}
	printf("First sum of digits : %d count : %d\n", Destiny_Number_sum, count);
	
	while (Destiny_Number_sum >= 10) // 합계가 두 자리 숫자(10 이상)인 동안, 한 자리(10 미만)가 될 때까지 반복해서 더함
    {
        int temp = Destiny_Number_sum; // 현재 합계를 임시 변수에 담고
        Destiny_Number_sum = 0;        // 합계 변수를 초기화
        
        while (temp > 0)
        {
            Destiny_Number_sum = Destiny_Number_sum + temp % 10; // 각 자리를 다시 더함
            temp = temp/10;
			count = count + 1;
        }
        printf("Final sum of digits : %d count : %d\n", Destiny_Number_sum, count);
    }
	
    g_birth = Destiny_Number_sum; // 계산값을 g_birth에 삽입
    printf("Your destiny number is! %d\n", g_birth);
	return 0;
}

void Destiny_Script(void)
{
	printf("============================================================================================\n\n*");
	switch (g_birth)
	{
		case 1:
		{
			printf("Today will be a wonderful day where a small idea leads to a great achievement.\n");
			break;
		}
		case 2:
		{
			printf("There are strong signs that a troublesome problem will finally be neatly resolved today.\n");
			break;
		}
		case 3:
		{
			printf("Unexpected good news or a stroke of luck may find you from an unexpected place.\n");
			break;
		}
		case 4:
		{
			printf("Today, focusing on solid fundamentals is more advantageous than taking on overly ambitious challenges.\n");
			break;
		}
		case 5:
		{
			printf("A warm word from someone around you will bring great strength and inspiration today.\n");
			break;
		}
		case 6:
		{
			printf("You will notice careful details that others miss, earning recognition for your abilities.\n");
			break;
		}
		case 7:
		{
			printf("Taking a brief moment to pause and recharge will grant you even greater energy.\n");
			break;
		}
		case 8:
		{
			printf("Complicated and tangled matters will smoothly sort themselves out like unwinding a skein of yarn.\n");
			break;
		}
		case 9:
		{
			printf("Your steady efforts will shine, making today a day of remarkable accomplishments.\n");
			break;
		}
	}
	printf("\n============================================================================================\n");
	return;
}
int main(void)
{
    // 올바른 8자리 숫자가 들어올 때까지 반복
    while (g_flag == 1)
    {
        question(); // 입력
    }
	sum();
	Destiny_Script();
	
	printf("\n\n-----------Press any key to exit.----------");
    getchar();
    getchar();
    return 0;
}
