#pragma once
#include <iostream>
using namespace std;


class Date
{
    int mo, da, yr;
    
    bool is_leap(int y) const;
    int get_month_days(int y, int m) const;
    long long total_days() const;
    bool is_valid() const;
public:
    Date(int y, int m, int d)
    {
        mo = m; da = d; yr = y;
    }
    Date()
    {
        mo=1; da = 1;yr =1;
    }


    friend ostream& operator<<(ostream& os, const Date& dt);
    friend istream& operator>> (istream& is, Date& dt);
    Date& operator+=(int days);
    Date& operator-=(int days);
    

    friend Date operator+(Date lhs, int days);
    friend Date operator+(int days, Date rhs);
    friend Date operator-(Date lhs, int days);
    
    friend long long operator-(const Date& lhs, const Date& rhs);
    
    friend bool operator==(const Date& lhs, const Date& rhs)
    {
        return lhs.yr == rhs.yr && lhs.mo == rhs.mo && lhs.da == rhs.da;
    }
    friend bool operator!=(const Date& lhs, const Date& rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const Date& lhs, const Date& rhs)
    {
        return lhs.total_days() < rhs.total_days();
    }
    friend bool operator>(const Date& lhs, const Date& rhs)
    {
        return rhs < lhs;
    }
    friend bool operator<=(const Date& lhs, const Date& rhs)
    {
        return !(rhs < lhs);
    }
    friend bool operator>=(const Date& lhs, const Date& rhs)
    {
        return !(lhs < rhs);
    }
    
    bool operator!() const
    {
        return !is_valid();
    }
    
    Date& operator++()
    {
        *this += 1;
        return *this;
    }
    
    Date operator++(int)
    {
        Date tmp = *this;
        *this += 1;
        return tmp;
    }
    
    Date& operator--()
    {
        *this -= 1;
        return *this;
    }
    
    Date operator--(int)
    {
        Date tmp = *this;
        *this -= 1;
        return tmp;
    }

    Date& operator=(const Date& rhs)
    {
        if(this == &rhs)
            return *this;
        yr = rhs.yr;
        mo = rhs.mo;
        da = rhs.da;
        return *this;
    }
};


inline ostream& operator<<(ostream& os, const Date& dt)
{
    os << dt.mo << '/' << dt.da << '/' << dt.yr;
    return os;
}

inline istream& operator>> (istream& is, Date& dt)
{
    is>> dt.mo>> dt.da>> dt.yr;
    return is;
}

inline Date operator+(Date lhs, int days)
{
    lhs += days;
    return lhs;
}

inline Date operator+(int days, Date rhs)
{
    rhs += days;
    return rhs;
}

inline Date operator-(Date lhs, int days)
{
    lhs -= days;
    return lhs;
}

inline long long operator-(const Date& lhs, const Date& rhs)
{
    return lhs.total_days() - rhs.total_days();
}