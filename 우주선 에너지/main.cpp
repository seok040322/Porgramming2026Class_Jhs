#include <stdio.h>

int g_energy = 0;      // 입력값
int g_flag = 1;        // 오류 판별 변수
int g_E_Onumber = 0;   // 짝수/홀수 판별 변수 (0: 짝수, 1: 홀수)
int steps = 0;         // 총 단계 수

void question(void) // 입력 함수, 숫자, 문자, 정수,실수 판별도 같이 함
{
    printf("Enter the engine's energy amount : ");

    if (scanf("%d", &g_energy) != 1) // 1차 판별: 숫자인지 문자인지 구분하는 경우
    {
        printf("[Warning] Characters other than numbers have been entered.\n");
        while (getchar() != '\n'); // 버퍼 청소
        g_flag = 1;                // 재입력 신호
        return;
    }

    // 2차 판별: 숫자는 맞지만 뒤에 소수점(.)이나 다른 문자가 이어지는 경우
    char next_char = getchar(); // getchar() : 키보드 표준 입력(stdin)으로부터 딱 한 개의 문자(글자)를 읽어와서 반환하는 함수

    if (next_char != '\n') /* 2.1이 입력되었다면 위에 scanf에서 %d로 정수형 2만 데이터로 뽑아가고 .1은 메모리에 버퍼로 남겨둔
    이때 위에 getchar로 위에 입력 받고 버퍼로 남아 있던 0.1을 가지고 와 \n와 비교후 \n이라면 넘어가고 아니라면 if문 안으로 들어 간다*/
    {
        printf("[Warning] Decimals or trailing characters are not allowed. Please enter an integer.");

        if (next_char != -1) // -1=EOF : 파일의 끝, 더이상 읽을 데이터 값이 없다는 것을 알려줌
        {
            while (getchar() != '\n'); // 남은 버퍼 찌꺼기 청소
        }

        g_flag = 1; // 재입력 신호
        return;
    }

    // 추가 검사: 에너지는 1 이상의 양의 정수여야 함
    if (g_energy <= 0)
    {
        printf("[Error] Energy must be a positive integer. Please enter again.\n");
        g_flag = 1; // 재입력 신호
        return;
    }

    g_flag = 0; // 정상 입력
}

void Discriminator(void) // 짝수 홀수 판별기
{
    if (g_energy % 2 == 0)
    {
        g_E_Onumber = 0;
    }
    else
    {
        g_E_Onumber = 1;
    }
}

void calculation(void) // 계산
{
    if (g_E_Onumber == 0)
    {
        g_energy = g_energy / 2;
        printf("%d -> ", g_energy);
        steps = steps + 1;
    }
    else if (g_E_Onumber == 1)
    {
        g_energy = (g_energy * 3) + 1;
        printf("%d -> ", g_energy);
        steps = steps + 1;
    }
}

void max_altitude1(void)
{
    int max_altitude = 0; // 최대 도달 에너지 저장 변수

    max_altitude = g_energy; // 초기 입력값도 최대값 후보로 지정

    printf("Sequence : %d -> ", g_energy);

    // 에너지가 1이 될 때까지 반복
    while (g_energy != 1)
    {
        Discriminator(); // 짝수 홀수 판별 수행
        calculation();   // 계산 수행

        // 최대 도달 높이(에너지) 갱신
        if (g_energy > max_altitude)
        {
            max_altitude = g_energy;
        }
    }

    printf("\nEscape successful!\n");
    printf("Total steps : %d\n", steps);
    printf("Maximum altitude reached : %d\n", max_altitude);

    return;
}

int main(void)
{
    // 올바른 숫자가 입력될 때까지 반복
    while (g_flag == 1)
    {
        question();
    }

    max_altitude1();

    printf("\n\n-----------Press any key to exit.----------");
    getchar();
    getchar();

    return 0;
}

/**scanf는 정수 데이터만 딱 골라 먹고, 그 바로 뒤에 붙어있는 문자는 버퍼에 그대로 남겨둡니다.
getchar()는 그 남겨진 첫 번째 문자가 무엇인지 확인합니다.
? 케이스 A: 사용자가 정상 정수 100을 입력하고 엔터를 친 경우
    ? 버퍼 상태: 100\n
    ? scanf가 100을 먹고, 버퍼에는 \n만 남습니다.
    ? getchar()가 남은 \n을 읽어서 next_char에 저장합니다.
    ? if (next_char != '\n') 조건이 거짓(False)이 되므로 2차 판별 if문을 그냥 통과합니다.
    ? 최종적으로 g_flag = 0이 되며 정상 입력으로 처리됩니다.
? 케이스 B: 사용자가 실수 12.34를 입력하고 엔터를 친 경우
    ? 버퍼 상태: 12.34\n
    ? scanf는 정수 부분인 12만 쏙 빼먹고 멈춥니다. 버퍼에는 .34\n이 남습니다.
    ? getchar()가 실행되면서 버퍼의 맨 앞 문자인 소수점(.)을 읽어 유효성 검사를 합니다.
    ? next_char가 .이므로 != '\n' 조건이 참(True)이 되어 if문 안으로 진입합니다.
? 케이스 C: 사용자가 숫자 뒤에 문자를 붙여 100abc라고 입력한 경우
    ? 버퍼 상태: 100abc\n
    ? scanf는 100만 먹고 멈춥니다. 버퍼에는 abc\n이 남습니다.
    ? getchar()가 문자 a를 읽어옵니다.
    ? 엔터가 아니므로 if문 안으로 진입하여 에러를 잡아냅니다.*/