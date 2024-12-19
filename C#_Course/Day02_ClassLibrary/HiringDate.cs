using System;

namespace Day01
{
    public struct HiringDate : IComparable<HiringDate>
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
        public HiringDate(int _day, int _month, int _year)
        {
            day = _day;
            month = _month;
            year = _year;
        }
        #region Getters | Setters
        public int getDay() { return day; }
        public void setDay(int _day) { day = _day; }
        public int getMonth() { return month; }
        public void setMonth(int _month) { month = _month; }
        public int getYear() { return year; }
        public void setYear(int _year) { year = _year; }
        #endregion
        public int CompareTo(HiringDate other)
        {
            if (year != other.year)
                return year.CompareTo(other.year);
            if (month != other.month)
                return month.CompareTo(other.month);
            return day.CompareTo(other.day);
        }
    }
}
