/*
 * File: build-number.h
 * Author: 1therealcloud
 * Last Update: 2026-05-29
 * Description: Automatically generates a build number based on the compilation date.
 */
#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>

inline int calculate_build_number() {
    const char* months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    const int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // 10th of May, 2006
    const int start_day = 10;
    const int start_month = 5;
    const int start_year = 2006;

    char month_str[4];
    int day, year;

    if (std::sscanf(__DATE__, "%3s %d %d", month_str, &day, &year) != 3) {
        return -1;
    }

    int month_idx = 0;
    for (int i = 0; i < 12; ++i) {
        if (std::strncmp(months[i], month_str, 3) == 0) {
            month_idx = i;
            break;
        }
    }

    int total_days = (year - start_year) * 365 + day;
    for (int i = 0; i < month_idx; ++i) total_days += days_in_month[i];

    int start_total = start_day;
    for (int i = 0; i < start_month - 1; ++i) start_total += days_in_month[i];

    return total_days - start_total;
}
