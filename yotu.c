
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DICE_COUNT 5
#define GAME_COUNT 5

// 족보 종류
#define NONE 0
#define ONE_PAIR 1
#define TRIPLE 2
#define FOUR_CARD 3
#define FULL_HOUSE 4
#define STRAIGHT 5
#define YACHT 6


// 족보 이름 출력
const char* getCategoryName(int category)
{
    switch (category)
    {
        case ONE_PAIR:
            return "원페어";
        case TRIPLE:
            return "트리플";
        case FOUR_CARD:
            return "포카드";
        case FULL_HOUSE:
            return "풀하우스";
        case STRAIGHT:
            return "스트레이트";
        case YACHT:
            return "요트";
        default:
            return "없음";
    }
}


// 주사위 굴리기
void rollDice(int dice[])
{
    int i;

    for (i = 0; i < DICE_COUNT; i++)
    {
        dice[i] = rand() % 6 + 1;
    }
}


// 주사위 눈의 개수 세기
void countDice(int dice[], int count[])
{
    int i;

    for (i = 1; i <= 6; i++)
    {
        count[i] = 0;
    }

    for (i = 0; i < DICE_COUNT; i++)
    {
        count[dice[i]]++;
    }
}


// 풀하우스 판정
int isFullHouse(int count[])
{
    int i;
    int hasThree = 0;
    int hasTwo = 0;

    for (i = 1; i <= 6; i++)
    {
        if (count[i] == 3)
            hasThree = 1;

        if (count[i] == 2)
            hasTwo = 1;
    }

    return hasThree && hasTwo;
}


// 스트레이트 판정
// 연속된 눈이 4개 이상이면 스트레이트
int isStraight(int count[])
{
    int i;
    int consecutive = 0;

    for (i = 1; i <= 6; i++)
    {
        if (count[i] > 0)
        {
            consecutive++;

            if (consecutive >= 4)
                return 1;
        }
        else
        {
            consecutive = 0;
        }
    }

    return 0;
}


// 족보 판정
int getCategory(int count[])
{
    int i;

    // 요트
    for (i = 1; i <= 6; i++)
    {
        if (count[i] == 5)
            return YACHT;
    }

    // 포카드
    for (i = 1; i <= 6; i++)
    {
        if (count[i] == 4)
            return FOUR_CARD;
    }

    // 풀하우스
    if (isFullHouse(count))
        return FULL_HOUSE;

    // 스트레이트
    if (isStraight(count))
        return STRAIGHT;

    // 트리플
    for (i = 1; i <= 6; i++)
    {
        if (count[i] == 3)
            return TRIPLE;
    }

    // 원페어
    for (i = 1; i <= 6; i++)
    {
        if (count[i] == 2)
            return ONE_PAIR;
    }

    // 아무 족보도 없음
    return NONE;
}


// 점수 계산
int calculateScore(int category, int count[])
{
    int i;

    switch (category)
    {
        // 원페어
        case ONE_PAIR:
            for (i = 1; i <= 6; i++)
            {
                if (count[i] == 2)
                    return i * 2;
            }
            break;

        // 트리플
        case TRIPLE:
            for (i = 1; i <= 6; i++)
            {
                if (count[i] == 3)
                    return i * 3;
            }
            break;

        // 포카드
        case FOUR_CARD:
            for (i = 1; i <= 6; i++)
            {
                if (count[i] == 4)
                    return i * 4;
            }
            break;

        // 풀하우스
        case FULL_HOUSE:
            return 25;

        // 스트레이트
        case STRAIGHT:
            return 30;

        // 요트
        case YACHT:
            return 50;

        // 없음
        default:
            return 0;
    }

    return 0;
}


// 주사위 출력
void printDice(int dice[])
{
    int i;

    printf("\n  ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐\n");

    printf("  │ %d │ │ %d │ │ %d │ │ %d │ │ %d │\n",
           dice[0],
           dice[1],
           dice[2],
           dice[3],
           dice[4]);

    printf("  └───┘ └───┘ └───┘ └───┘ └───┘\n");
}


int main()
{
    int dice[DICE_COUNT];
    int count[7];

    int category;
    int score;
    int totalScore = 0;

    // 결과 기록
    int categoryHistory[GAME_COUNT];
    int scoreHistory[GAME_COUNT];

    int round;

    // 난수 초기화
    srand((unsigned int)time(NULL));

    printf("========================================\n");
    printf("          🎲 주사위 게임 - 요트 🎲\n");
    printf("========================================\n");

    printf("\n총 %d판을 진행합니다!\n", GAME_COUNT);
    printf("Enter를 누르면 주사위를 굴립니다.\n");

    // 5판 진행
    for (round = 0; round < GAME_COUNT; round++)
    {
        printf("\n\n----------------------------------------\n");
        printf("                %d 판\n", round + 1);
        printf("----------------------------------------\n");

        printf("\n[Enter] 를 눌러 주사위를 굴리세요!");

        // Enter 입력 대기
        getchar();

        // 주사위 굴리기
        rollDice(dice);

        printf("\n🎲 주사위를 굴립니다...\n");

        // 잠시 결과 표시
        printf("두구두구두구...\n");

        // 주사위 출력
        printDice(dice);

        // 주사위 개수 계산
        countDice(dice, count);

        // 족보 판정
        category = getCategory(count);

        // 점수 계산
        score = calculateScore(category, count);

        // 결과 저장
        categoryHistory[round] = category;
        scoreHistory[round] = score;

        // 총점 누적
        totalScore += score;

        printf("\n★ 족보 : %s\n", getCategoryName(category));
        printf("★ 점수 : %d점\n", score);
        printf("★ 현재 총점 : %d점\n", totalScore);

        // 다음 판 안내
        if (round < GAME_COUNT - 1)
        {
            printf("\n다음 판으로 넘어갑니다.");
        }
    }


    // 최종 결과
    printf("\n\n========================================\n");
    printf("              🏆 게임 결과 🏆\n");
    printf("========================================\n");

    for (round = 0; round < GAME_COUNT; round++)
    {
        printf("%d판 : %-10s %2d점\n",
               round + 1,
               getCategoryName(categoryHistory[round]),
               scoreHistory[round]);
    }

    printf("----------------------------------------\n");
    printf("총점 : %d점\n", totalScore);
    printf("========================================\n");

    printf("\n게임이 종료되었습니다!\n");

    return 0;
}

