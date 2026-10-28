#include <stdio.h>

//#define을 사용하여 각 상품의 원래 가격 상수로 지정
#define PRICE_POTION 1000
#define PRICE_SCROLL 2000
#define PRICE_ELIXIR 3000

// 전역 변수 선언
int g_balance = 0;        // 현재 잔액
int g_purchase_count = 0; // 총 구매 횟수 (3번째마다 도깨비의 축복 발동)
int g_choice = 0;         // 사용자 메뉴 선택 번호
int g_flag = 1;           // 입력 오류 판별 변수 (0: 정상, 1: 비정상)

// 함수 프로토타입(선언)
void question(void);
void show_menu(void);
void get_choice(void);
int process_purchase(void); // 잔액 부족 여부를 반환하도록 수정

void question(void) // 초기 잔액 입력 함수
{
    printf("Insert coins (Current Balance): ");

    if (scanf("%d", &g_balance) != 1)
    {
        printf("\n[Warning] Characters other than numbers have been entered.\n\n");
        while (getchar() != '\n'); // 입력 버퍼 청소
        g_flag = 1;
        return;
    }

    // 숫자 뒤에 소수점이나 문자가 섞여 들어온 경우 차단
    char next_char = getchar();

    if (next_char != '\n')
    {
        printf("\n[Warning] Decimals or trailing characters are not allowed.\n\n");

        if (next_char != -1)
        {
            while (getchar() != '\n');
        }

        g_flag = 1;
        return;
    }

    if (g_balance < 0)
    {
        printf("\n[Error] Balance cannot be negative. Please enter again.\n\n");
        g_flag = 1;
        return;
    }

    g_flag = 0; // 정상 입력 완료
}

void show_menu(void) // 자판기 메뉴 출력 함수
{
    printf("------------------------------------------\n");
    printf("\nGoblin's Vending Machine\n");
    printf("1. Red Potion (%d G)\n", PRICE_POTION);
    printf("2. Magic Scroll (%d G)\n", PRICE_SCROLL);
    printf("3. Elixir (%d G)\n", PRICE_ELIXIR);
    printf("0. Exit\n");
}

void get_choice(void) // 메뉴 선택 입력 함수
{
    printf("Select an item: ");

    if (scanf("%d", &g_choice) != 1)
    {
        printf("[Warning] Characters other than numbers have been entered.\n");
        while (getchar() != '\n'); // 버퍼 청소
        g_choice = -1; // 잘못된 선택 값 부여로 예외 처리 유도
        return;
    }

    char next_char = getchar();

    if (next_char != '\n')
    {
        if (next_char != -1)
        {
            while (getchar() != '\n');
        }

        g_choice = -1;
        return;
    }
}

int process_purchase(void) // 상품 구매 및 도깨비 축복(50% 할인) 처리 함수
{
    int item_price = 0;
    int is_discounted = 0;

    switch (g_choice)
    {
        case 1:
            item_price = PRICE_POTION;
            break;

        case 2:
            item_price = PRICE_SCROLL;
            break;

        case 3:
            item_price = PRICE_ELIXIR;
            break;

        default:
            return 1;
    }

    // 정확히 3번째 구매마다 도깨비의 축복(50% 할인) 적용
    int next_count = g_purchase_count + 1;

    if (next_count % 3 == 0)
    {
        is_discounted = 1;
        item_price = item_price / 2; // 50% 할인
    }

    // 잔액 부족 검사
    if (g_balance < item_price)
    {
        printf("Not enough balance!\n");
        return 0; // 잔액 부족을 main()에 전달하여 프로그램 종료
    }

    // 잔액 차감 및 구매 횟수 갱신
    g_balance = g_balance - item_price;
    g_purchase_count = next_count;

    // 구매 결과 출력 (strcpy 없이 선택 번호에 따라 바로 출력)
    if (is_discounted)
    {
        printf("*** GOBLIN'S BLESSING! 50%% DISCOUNT! ***\n");
        printf("[Purchased] ");

        if (g_choice == 1)
        {
            printf("Red Potion");
        }
        else if (g_choice == 2)
        {
            printf("Magic Scroll");
        }
        else if (g_choice == 3)
        {
            printf("Elixir");
        }

        printf(" for %d G. Balance: %d G\n", item_price, g_balance);
    }
    else
    {
        printf("[Purchased] ");

        if (g_choice == 1)
        {
            printf("Red Potion");
        }
        else if (g_choice == 2)
        {
            printf("Magic Scroll");
        }
        else if (g_choice == 3)
        {
            printf("Elixir");
        }

        printf(". \nBalance: %d G\n", g_balance);
    }

    return 1; // 구매 처리가 정상적으로 끝났음을 반환
}

int main(void)
{
    // 올바른 초기 잔액이 입력될 때까지 반복
    while (g_flag == 1)
    {
        question();
    }

    // 무한 루프를 통해 0번(종료)을 누르거나 잔액이 부족해질 때까지 메뉴 제공
    while (1)
    {
        show_menu();
        get_choice();

        if (g_choice == 0) // 종료 선택 시
        {
            printf("Returning %d G. Goodbye!\n", g_balance);
            break;
        }

        if (g_choice < 1 || g_choice > 3)
        {
            printf("[Warning] Please select a valid menu number (0-3).\n");
            continue;
        }

        // 잔액 부족 시 구매 함수가 0을 반환하므로 프로그램 종료
        if (process_purchase() == 0)
        {
            break;
        }
    }

    printf("\n-----------Press any key to exit-----------\n");
    getchar();
    getchar();

    return 0;
}