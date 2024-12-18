using System;

namespace Day01
{
    internal struct HiringDate
    {
        private int day;
        private int month;
        private int year;

        public HiringDate()
        {
            day = 0;
            month = 0;
            year = 0;
        }

        // getters and setters
        public int getDay() { return day; }
        public void setDay(int _day) { day = _day; }
        public int getMonth() { return month; }
        public void setMonth(int _month) { month = _month; }
        public int getYear() { return year; }
        public void setYear(int _year) { year = _year; }
    }
}
