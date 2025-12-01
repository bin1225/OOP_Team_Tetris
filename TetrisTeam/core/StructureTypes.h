#pragma once

//*********************************
//구조체 선언
//*********************************
struct STAGE {
    //각 스테이지마다의 난이도 설정
    int speed; //숫자가 낮을수록 속도가 빠르다
    int stick_rate; //막대가 나오는 확률 0~99 , 99면 막대기만 나옴
    int clear_line;
};

enum {
    BLACK, /*  0 : 까망 */
    DARK_BLUE, /*  1 : 어두운 파랑 */
    DARK_GREEN, /*  2 : 어두운 초록 */
    DARK_SKY_BLUE, /*  3 : 어두운 하늘 */
    DARK_RED, /*  4 : 어두운 빨강 */
    DARK_VIOLET, /*  5 : 어두운 보라 */
    DARK_YELLOW, /*  6 : 어두운 노랑 */
    GRAY, /*  7 : 회색 */
    DARK_GRAY, /*  8 : 어두운 회색 */
    BLUE, /*  9 : 파랑 */
    GREEN, /* 10 : 초록 */
    SKY_BLUE, /* 11 : 하늘 */
    RED, /* 12 : 빨강 */
    VIOLET, /* 13 : 보라 */
    YELLOW, /* 14 : 노랑 */
    WHITE, /* 15 : 하양 */
};