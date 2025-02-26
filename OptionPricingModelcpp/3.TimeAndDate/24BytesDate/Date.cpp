#include "Date.hpp"
#include<string>
#include<iostream>
#include<algorithm>

using std::cout;
using std::endl;
using std::string;

Date::Date(int year, int month, int day):
    m_year(year),
    m_month(month),
    m_day(day),
    m_weekDay(DayOfTheWeek_UNKOWN)
{}

Date::Date(const Date &p):
    m_year(p.m_year),
    m_month(p.m_month),
    m_day(p.m_day),
    m_weekDay(p.m_weekDay),
    m_holidays(p.m_holidays)
{}

Date::~Date()
{}

Date &Date::operator=(const Date &p){
    if(&p != this){ //the object is not being assigned to itself 
        m_day     = p.m_day;
        m_month   = p.m_month;
        m_year    = p.m_year;
        m_weekDay = p.m_weekDay;
        m_holidays= p.m_holidays;
    }
    return *this; //returns the current object (*this) by reference
}

///emuration values
std::string Date::month(){
    switch(m_month){
        case Month_January:  return "January";
        case Month_February: return "February";
        case Month_March:    return "March";
        case Month_April:    return "April";
        case Month_May:      return "May";
        case Month_June:     return "June";
        case Month_July:     return "July";
        case Month_August:   return "August";
        case Month_September:return "Septembar";
        case Month_October:  return "October";
        case Month_November: return "November";
        case Month_December: return "December";
        default: throw std::runtime_error("unknown month");
    }
    return "";
}

std::string Date::dayOfWeek(){
    switch(this->dayOfTheWeek()){
        case DayOfTheWeek_Sunday: return "Sunday";
        case DayOfTheWeek_Monday: return "Monday";
        case DayOfTheWeek_Tuesday: return "Tuesday";
        case DayOfTheWeek_Wednesday: return "Wednesday";
        case DayOfTheWeek_Thursday: return "Thursday";
        case DayOfTheWeek_Friday: return "Friday";
        case DayOfTheWeek_Saturday: return "Saturday";
        default: throw std::runtime_error("unknown day of week");
    }
}

bool Date::operator<(const Date &d) const{
    if(m_year < d.m_year) return true;
    if(m_year == d.m_year && m_month < d.m_month) return true;
    if(m_year == d.m_year && m_month == d.m_month && m_day < d.m_day) return true;

    return false;
}

bool Date::operator==(const Date &d){
    return d.m_day == m_day && d.m_month == m_month && d.m_year == m_year;
}


void Date::setHolidays(const std::vector<Date> &days){
    m_holidays = days;
}

bool Date::isHoliday(){
    return std::find(m_holidays.begin(), m_holidays.end(), *this) != m_holidays.end();
}


// Add a certain number of days to the current date.
void Date::add(int numDays){
    for(int i=0; i<numDays; i++){
        ++*this;
    }
}

//Add a number of trading days to the current date.
void Date::addTradingDays(int numDays){
    while(!isTradingDay()){
        ++*this;
    }
    for(int i=0; i<numDays; i++){
        ++*this;
        while(!isTradingDay()){
            ++*this;
        }
    }
}

// Subtract a certain number of days from the current date.
void Date::subtract(int numDays){
    for(int i=0; i<numDays; i++){
        --*this;
    }
}

// Subtract a number of trading days from the current date.
void Date::subtractTradingDays(int numDays){
    while(!isTradingDay()){
        --*this;
    }
    for(int i=0; i<numDays; i++){
        --*this;
        while(!isTradingDay()){
            --*this;
        }
    }
}

// Return the difference in days from the current date.
int Date::dateDifference(const Date &date){
    Date d = *this;
    if(d < date){
        int diff = 0;
        while(d<date){
            ++d;
            ++diff;
        }
        return diff;
    }
    int diff=0;
    while(date < d){
        --d;
        --diff;
    }
    return diff;
}

// Return the difference in trading days between two dates.
int Date::tradingDateDifference(const Date &date){
    Date d = *this;
    if(d < date){
        int diff=0;
        while(!d.isTradingDay()) ++d;
        while(d < date){
            ++d;
            ++diff;
            while(!d.isTradingDay()) ++d;
        }
        return diff;
    }

    int diff=0;
    while(!d.isTradingDay()) --d;
    while(date < d){
        --d;
        --diff;
        while(!d.isTradingDay()) --d;
    }
    return diff;
}

//Return the day of the week corresponding to the given date.
DayOfTheWeek Date::dayOfTheWeek(){
    if(m_weekDay != DayOfTheWeek_UNKOWN) return m_weekDay;

    int day = 1;
    Date d(1900, 1, 1);
    for(; d<*this; ++d){
        if(day == 6) day = 0;
        else day++;
    }
    m_weekDay = static_cast<DayOfTheWeek>(day);
    return m_weekDay;
}

// True if the date is a weekday.
bool Date::isWeekDay(){
    DayOfTheWeek dayOfWeek = dayOfTheWeek();
    if(dayOfWeek == DayOfTheWeek_Sunday || dayOfWeek == DayOfTheWeek_Saturday) return false;
    return true;
}

// True if the date is a trading day.
bool Date::isTradingDay(){
    if(!isWeekDay()) return false;
    if(m_holidays.size()==0) return true;
    if(isHoliday()) return false;
    return true;
}

// increment the current date to the next valid trading day.
Date Date::nextTradingDay(){
    Date d = *this;
    if(d.isTradingDay()){
        return ++d;
    }
    while(!d.isTradingDay()){
        ++d;
    }
    return d;
}

// True if the year is a leap year (i.e., it has 366 days).
bool Date::isLeapYear(){
    if(m_year%4 != 0) return false;
    if(m_year%100 != 0) return true;
    if(m_year%400 != 0) return false;
    return true;
}



Date &Date::operator--(){
    //update weekday
    if(m_weekDay != DayOfTheWeek_UNKOWN){
        if(m_weekDay == DayOfTheWeek_Sunday){
            m_weekDay == DayOfTheWeek_Saturday;
        }else{
            m_weekDay == static_cast<DayOfTheWeek>(m_weekDay-1);
        }
    }

    if(m_day > 1){
        m_day--;
        return *this;
    }
    if(m_month == Month_January){
        m_month = Month_December;
        m_day = 31;
        m_year--;
        return *this;
    }
    m_month--;
    if(m_month == Month_February){
        m_day = isLeapYear() ? 29 : 28;
        return *this;
    }
    // List of months with 31 days
    std::vector<int> monthsWithThirtyOneDays = {1, 3, 5, 7, 8, 10, 12};
    if (std::find(monthsWithThirtyOneDays.begin(),monthsWithThirtyOneDays.end(), m_month)!= monthsWithThirtyOneDays.end()){
        m_day = 31;
    }else{
        m_day = 30;
    }
    return *this;
}

Date &Date::operator++(){
    //31 days month
    std::vector<int> monthsWithThirtyOneDays = {
        1,3,5,7,8,10,12
    };
    if(m_day == 31){
        m_day = 1;
        m_month++;
    }else if(m_day == 30 && std::find(monthsWithThirtyOneDays.begin(),monthsWithThirtyOneDays.end(),m_month) == monthsWithThirtyOneDays.end()){
        m_day = 1;
        m_month++;
    }else if(m_day == 29 && m_month == 2){
        m_day = 1;
        m_month++;
    }else if(m_day == 28 && m_month == 2 && !isLeapYear()){
        m_day = 1;
        m_month++;
    }else{
        m_day++;
    }
    if(m_month > 12){
        m_month = 1;
        m_year++;
    }
    if(m_weekDay != DayOfTheWeek_UNKOWN){
        if(m_weekDay == DayOfTheWeek_Saturday){
            m_weekDay == DayOfTheWeek_Sunday;
        }else{
            m_weekDay = static_cast<DayOfTheWeek>(m_weekDay+1);
        }
        return *this;
    }
}

void Date::print(){
    cout<<m_year<<"/"<<m_month<<"/"<<m_day<<endl;
}

int main(){
    Date d(2015, 9, 12);
    DayOfTheWeek wd = d.dayOfTheWeek();
    cout<<"day of the week:"<<wd <<" " << d.dayOfWeek()<<endl;
    d.print();
    d.add(25);
    d.print();
    d.addTradingDays(120);
    d.print();

    cout<<"day of the week: "<<d.dayOfTheWeek()<<" "<<d.dayOfWeek()<<endl;
    return 0;
}