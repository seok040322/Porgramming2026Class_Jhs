#include <stdio.h>

int g_menu = 0; //모드
float g_mass = 0; //질량
float g_speed = 0; //속도
float g_height = 0; //높이
float g_start_height = 0; //처음 높이
const float G = 9.81f; // 중력가속도

// 메뉴 출력 및 선택 함수
void question(void)
{
    printf("\n1. Kinetic energy  2. Potential energy  3. Free-fall table  0. Exit\n");
    printf("Select: ");

    if (scanf_s("%d", &g_menu) != 1)
    {
        printf("[Warning] Non-numeric characters have been entered.\n");
        while (getchar() != '\n');
        g_menu = -1; // 잘못된 입력 처리용 값
    }
}

// 값 입력 및 유효성 검사 함수
void calculation_mode(void)
{
    while (1)
    {
        int input_success = 1;

        //모드별 입력 처리
        switch (g_menu)
        {
        case 1:
            printf("Mass (kg): ");
            if (scanf_s("%f", &g_mass) != 1)
            {
                input_success = 0;
            }
            printf("Speed (m/s): ");
            if (scanf_s("%f", &g_speed) != 1)
            {
                input_success = 0;
            }
            break;
        case 2:
            printf("Mass (kg): ");
            if (scanf_s("%f", &g_mass) != 1)
            {
                input_success = 0;
            }
            printf("Height (m): ");
            if (scanf_s("%f", &g_height) != 1)
            {
                input_success = 0;
            }
            break;
        case 3:
            printf("Mass (kg): ");
            if (scanf_s("%f", &g_mass) != 1)
            {
                input_success = 0;
            }
            printf("Start height (m): ");
            if (scanf_s("%f", &g_start_height) != 1)
            {
                input_success = 0;
            }
            break;
        }

        // 입력 형식 오류 시 버퍼 비우고 재시도
        if (!input_success)
        {
            printf("[Warning] Invalid input format. Please enter numbers.\n");
            while (getchar() != '\n');
            continue; //왜지? 이건 왜 있어야 하는거여
        }

        // 입력값이 0 이하인지 검사
        int is_valid = 1;
        switch (g_menu)
        {
        case 1:
        {
            if (g_mass <= 0 || g_speed <= 0)
            {
                is_valid = 0;
            }
            break;
        }
        case 2:
        {
            if (g_mass <= 0 || g_height <= 0)
            {
                is_valid = 0;
            }
            break;
        }
        case 3:
        {
            if (g_mass <= 0 || g_start_height <= 0)
            {
                is_valid = 0;
                break;
            }
        }
        }
        if (!is_valid)
        {
            printf("-- Value must be positive, Enter again: \n");
            while (getchar() != '\n');
            continue;
        }

        break;
    }
}

// 계산 및 출력 함수
void calculate(void)
{
    switch (g_menu)
    {
    case 1: // 운동에너지
    {
        float ke = 0.5f * g_mass * g_speed * g_speed;
        if (ke >= 1000.0f)
        {
            printf("Energy : %.3f J (%.3f kJ)\n", ke, ke / 1000.0f);
        }

        else
        {
            printf("Energy : %.3f J\n", ke);
        }
        break;
    }
    case 2: // 위치에너지
    {
        float pe = g_mass * G * g_height;
        if (pe >= 1000.0f)
        {
            printf("Energy : %.3f J (%.3f kJ)\n", pe, pe / 1000.0f);
        }

        else
        {
            printf("Energy : %.3f J\n", pe);
        }

        break;
    }
    case 3: // 자유낙하 테이블
    {
        printf("h(m)\tPE(J)\tKE(J)\tTotal(J)\n");
        float step = g_start_height / 5.0f;
        for (int i = 5; i >= 0; i--)
        {
            float h = step * i;
            float pe = g_mass * G * h;
            float ke = g_mass * G * (g_start_height - h);
            float total = pe + ke;
            printf("%.3f\t%.3f\t%.3f\t%.3f\n", h, pe, ke, total);
        }
        break;
    }
    }
}

int main(void)
{
    while (1)
    {
        question();

        
        switch (g_menu)
        {
        case 0:
        {
            printf("Exiting the program...\n");
            return 0;
        }
        case 1:
        case 2:
        case 3:
        {
            calculation_mode();
            calculate();
            break;
        }
        default:
            break;
        }
    }

    return 0;
}

