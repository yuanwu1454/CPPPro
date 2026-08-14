#include "Date.h"


bool Date::is_leap(int y) const
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Date::get_month_days(int y, int m) const
{
    int mon_days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && is_leap(y))
        return 29;
    return mon_days[m];
}

Date& Date::operator+=(int days)
{
    while (days > 0)
    {
        int cur_month_max = get_month_days(yr, mo);
        int remain = cur_month_max - da;
        
        if (remain >= days)
        {
            da += days;
            break;
        }
        else
        {
            days -= (remain + 1);
            da = 1;
            mo += 1;
            
            if (mo > 12)
            {
                mo = 1;
                yr += 1;
            }
        }
    }
    return *this;
}

Date& Date::operator-=(int days)
{
    while (days > 0)
    {
        if (da > days)
        {
            da -= days;
            break;
        }
        else
        {
            days -= da;
            mo -= 1;

            if (mo < 1)
            {
                mo = 12;
                yr -= 1;
            }
            da = get_month_days(yr, mo);
        }
    }
    return *this;
}

long long Date::total_days() const
{
    long long total = 0;
    for (int y = 1; y < yr; ++y)
    {
        total += is_leap(y) ? 366 : 365;
    }
    for (int m = 1; m < mo; ++m)
    {
        total += get_month_days(yr, m);
    }
    total += da;
    return total;
}

bool Date::is_valid() const
{
    if (mo < 1 || mo > 12)
        return false;
    int max_d = get_month_days(yr, mo);
    if (da < 1 || da > max_d)
        return false;
    return true;
}