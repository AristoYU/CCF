/*
 试题编号：    201509-2
 试题名称：    日期计算
 时间限制：    1.0s
 内存限制：    256.0MB
 问题描述：
 问题描述
 　　给定一个年份y和一个整数d，问这一年的第d天是几月几日？
 　　注意闰年的2月有29天。满足下面条件之一的是闰年：
 　　1） 年份是4的整数倍，而且不是100的整数倍；
 　　2） 年份是400的整数倍。
 输入格式
 　　输入的第一行包含一个整数y，表示年份，年份在1900到2015之间（包含1900和2015）。
 　　输入的第二行包含一个整数d，d在1至365之间。
 输出格式
 　　输出两行，每行一个整数，分别表示答案的月份和日期。
 样例输入
 2015
 80
 样例输出
 3
 21
 样例输入
 2000
 40
 样例输出
 2
 9
 */

#include <iostream>

using namespace std;

int LeapYearMonth[12] = {31, 29 , 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int LeapYearDay[13];
int NotLeapYearMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int NotLeapYearDay[13];

typedef struct date {
    int month;
    int day;
} date;

bool isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        return true;
    }
    return false;
}

int calMonth(int year, int day) {
    if (isLeapYear(year)) {
        for (int i = 0; i < 12; i++) {
            if (day > LeapYearDay[i] && day <= LeapYearDay[i + 1]) {
                return i + 1;
            }
        }
    }
    else {
        for (int i = 0; i < 12; i++) {
            if (day > NotLeapYearDay[i] && day <= NotLeapYearDay[i + 1]) {
                return i + 1;
            }
        }
    }
    return -1;
}

int calDay(int year, int month, int day) {
    if (isLeapYear(year)) {
        return day - LeapYearDay[month - 1];
    }
    else {
        return day - NotLeapYearDay[month - 1];
    }
}

date calDate(int year, int day) {
    date Date;
    int m = calMonth(year, day);
    int d = calDay(year, m, day);
    Date.month = m;
    Date.day = d;
    return Date;
}

void init() {
    int cal1 = 0, cal2 = 0;
    for (int i = -1; i < 12; i++) {
        if (i == -1) {
            LeapYearDay[i + 1] = 0;
            NotLeapYearDay[i + 1] = 0;
        }
        else {
            cal1 += LeapYearMonth[i];
            cal2 += NotLeapYearMonth[i];
            LeapYearDay[i + 1] = cal1;
            NotLeapYearDay[i + 1] = cal2;
        }
    }
}

int main() {
    init();
    int year, day;
    cin >> year >> day;
    date Date = calDate(year, day);
    cout << Date.month << endl;
    cout << Date.day << endl;
    return 0;
}
