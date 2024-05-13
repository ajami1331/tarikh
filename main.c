#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>

wchar_t *bengali_months[] = {
    L"পৌষ",
    L"মাঘ",
    L"ফাল্গুন",
    L"চৈত্র",
    L"বৈশাখ",
    L"জ্যৈষ্ঠ",
    L"আষাড়",
    L"শ্রাবণ",
    L"ভাদ্র",
    L"আশ্বিন",
    L"কার্তিক",
    L"অগ্রহায়ণ",
};

wchar_t *bengali_days[] = {
    L"রবিবার",
    L"সোমবার",
    L"মঙ্গলবার",
    L"বুধবার",
    L"বৃহস্পতিবার",
    L"শুক্রবার",
    L"শনিবার"};

wchar_t *bengali_numbers = L"০১২৩৪৫৬৭৮৯";

int start_of_bengali_year = 594;

int month_start_date[] = {13, 12, 14, 13, 14, 14, 15, 15, 15, 15, 14, 14};

int month_days[] = {30, 30, 30, 30, 31, 31, 31, 31, 31, 30, 30, 30};

int leap_month_index = 2;

int last_month_index = 3;

int is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

wchar_t *bengali_number(int number)
{
    wchar_t *bengali_number = (wchar_t *)malloc(10 * sizeof(wchar_t));
    int i = 0;
    while (number > 0)
    {
        bengali_number[i++] = bengali_numbers[number % 10];
        number /= 10;
    }
    bengali_number[i] = L'\0';
    for (int j = 0; j < i / 2; j++)
    {
        wchar_t temp = bengali_number[j];
        bengali_number[j] = bengali_number[i - j - 1];
        bengali_number[i - j - 1] = temp;
    }
    return bengali_number;
}

int main()
{
    setlocale(LC_ALL, "");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int year = tm.tm_year + 1900;
    int month = tm.tm_mon;
    int date = tm.tm_mday;
    int day = tm.tm_wday;
    int bengali_year = year - start_of_bengali_year;
    if (month > last_month_index || (month == last_month_index && date >= month_start_date[last_month_index]))
    {
        bengali_year++;
    }
    int days_in_current_month = month_days[month];
    if (month == leap_month_index && is_leap_year(bengali_year))
    {
        days_in_current_month++;
    }

    int bengali_date = date;
    int bengali_month = month;
    if (date > month_start_date[month])
    {
        bengali_date = date - month_start_date[month];
        bengali_month = (bengali_month + 1) % 12;
    }
    else
    {
        bengali_date = days_in_current_month + date - month_start_date[bengali_month];
    }

    wchar_t *bengali_date_str = bengali_number(bengali_date);
    wchar_t *bengali_year_str = bengali_number(bengali_year);

    wprintf(L"%ls %ls %ls রোজ %ls\n", bengali_date_str, bengali_months[bengali_month], bengali_year_str, bengali_days[day]);

    free(bengali_date_str);
    free(bengali_year_str);
    return 0;
}