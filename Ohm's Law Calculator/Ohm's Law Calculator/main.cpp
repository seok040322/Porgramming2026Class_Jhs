#include <stdio.h>

int g_birth1 = 0;       // 모드 선택 (1: V, 2: I, 3: R, 0: Exit)
int g_flag = 1;

float Voltage = 0;
float Current = 0;
float Resistance = 0;

// 메뉴 출력 및 모드 입력 함수
void question(void)
{
    printf("\n1. Voltage  2. Current  3. Resistance  0. Exit\n");
    printf("Select: ");

    // 입력값 검증 (숫자 입력 여부)
    if (scanf_s("%d", &g_birth1) != 1)
    {
        printf("[Warning] Non-numeric characters have been entered.\n");
        while (getchar() != '\n'); // 입력 버퍼 비우기
        g_flag = 1;
        return;
    }

    // 메뉴 범위 검사
    if (g_birth1 < 0 || g_birth1 > 3)
    {
        printf("[Warning] Please enter a number between 0 and 3.\n");
        g_flag = 1;
        return;
    }

    g_flag = 0;
}

// 두 값을 입력받고 양수인지 검사하는 함수
void calculation_mode(void)
{
    while (1)
    {
        int input_count = 0;

        switch (g_birth1)
        {
        case 1: // Current, Resistance 입력
            printf("Current (A) Resistance (ohm) : ");
            input_count = scanf_s("%f %f", &Current, &Resistance);
            break;

        case 2: // Voltage, Resistance 입력
            printf("Voltage (V) Resistance (ohm) : ");
            input_count = scanf_s("%f %f", &Voltage, &Resistance);
            break;

        case 3: // Voltage, Current 입력
            printf("Voltage (V) Current (A) : ");
            input_count = scanf_s("%f %f", &Voltage, &Current);
            break;
        }

        // 입력 형식이 잘못되었을 때 (숫자가 아니거나 2개를 다 안 적었을 때)
        if (input_count != 2)
        {
            printf("[Warning] Invalid input format. Please enter two numbers.\n");
            while (getchar() != '\n'); // 버퍼 비우기
            continue;
        }

        // 입력값은 모두 0보다 커야 함
        int is_positive = 1;
        if (g_birth1 == 1 && (Current <= 0 || Resistance <= 0)) is_positive = 0;
        if (g_birth1 == 2 && (Voltage <= 0 || Resistance <= 0)) is_positive = 0;
        if (g_birth1 == 3 && (Voltage <= 0 || Current <= 0)) is_positive = 0;

        if (!is_positive)
        {
            printf("-- Value must be positive, Enter again: \n");
            while (getchar() != '\n'); // 버퍼 비우기
            continue;
        }

        // 정상 입력을 받았으므로 루프 탈출
        break;
    }
}

// 옴의 법칙 계산 및 V, I, R, P 출력 함수
void calculate(void)
{
    switch (g_birth1)
    {
    case 1: // V = I * R
        Voltage = Current * Resistance;
        break;

    case 2: // I = V / R
        Current = Voltage / Resistance;
        break;

    case 3: // R = V / I
        Resistance = Voltage / Current;
        break;
    }

    // 전력 P = V * I 계산
    float Power = Voltage * Current;

    // 결과 출력
    printf("V = %.3f V,  I = %.3f A,  R = %.3f ohm,  P = %.3f W\n", Voltage, Current, Resistance, Power);
}

int main(void)
{
    while (1)
    {
        question();

        // 올바른 메뉴 입력이 아니면 다시 메뉴 출력
        if (g_flag == 1) continue;

        // 0 선택 시 종료
        if (g_birth1 == 0)
        {
            printf("Exiting program.\n");
            break;
        }

        calculation_mode(); // 두 값 입력받기
        calculate();        // 계산 및 출력
    }

    return 0;
}

