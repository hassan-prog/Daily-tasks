namespace Day03
{
    internal class Duration
    {
        public int Hours { get; set; }
        public int Minutes { get; set; }
        public int Seconds { get; set; }

        #region CTOR
        public Duration()
        {
            Hours = 0;
            Minutes = 0;
            Seconds = 0;
        }
        public Duration(int _totalSeconds)
        {
            if (_totalSeconds >= 3600)
            {
                Hours = _totalSeconds / 3600;
                _totalSeconds %= 3600;
                Minutes = _totalSeconds / 60;
                _totalSeconds %= 60;
                Seconds = _totalSeconds;
            }
            else if (_totalSeconds >= 60)
            {
                Minutes = _totalSeconds / 60;
                _totalSeconds %= 60;
                Seconds = _totalSeconds;
            }
            else
            {
                Hours = 0;
                Minutes = 0;
                Seconds = _totalSeconds;
            }
        }
        public Duration(int _hours, int _minutes, int _seconds)
        {
            if (_seconds >= 60)
            {
                _minutes += _seconds / 60;
                _seconds %= 60;
            };

            if (_minutes >= 60)
            {
                _hours += _minutes / 60;
                _minutes %= 60;
            }
            Hours = _hours;
            Minutes = _minutes;
            Seconds = _seconds;
        }
        #endregion

        #region function override
        public override string ToString()
        {
            return $"Hours: {Hours}, Minutes: {Minutes}, Seconds: {Seconds}";
        }

        public override bool Equals(object? obj)
        {
            if (obj is Duration)
            {
                Duration p = (Duration)obj;

                return Hours == p.Hours && Minutes == p.Minutes && Seconds == p.Seconds;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return Hours + Minutes + Seconds;
        }
        #endregion

        #region function overloading
        // Arithmetic operators
        // Multiple conditions for the + operator
        public static Duration operator +(Duration left, Duration right)
        {
            return new Duration(left.Hours + right.Hours, left.Minutes + right.Minutes, left.Seconds + right.Seconds);
        }
        public static Duration operator +(int totalSeconds, Duration right)
        {
            Duration temp = new Duration(totalSeconds);
            return new Duration(temp.Hours + right.Hours, temp.Minutes + right.Minutes, temp.Seconds + right.Seconds);
        }
        public static Duration operator +(Duration left, int totalSeconds)
        {
            Duration temp = new Duration(totalSeconds);
            return new Duration(temp.Hours + left.Hours, temp.Minutes + left.Minutes, temp.Seconds + left.Seconds);
        }

        // To use as negative operator (D1 = -D2)
        public static Duration operator -(Duration duration)
        {
            return new Duration(-duration.Hours, -duration.Minutes, -duration.Seconds);
        }

        // Multiple conditions of the - operator
        public static Duration operator -(Duration left, Duration right)
        {
            return new Duration(left.Hours - right.Hours, left.Minutes - right.Minutes, left.Seconds - right.Seconds);
        }
        public static Duration operator -(int totalSeconds, Duration right)
        {
            Duration temp = new Duration(totalSeconds);
            return new Duration(temp.Hours - right.Hours, temp.Minutes - right.Minutes, temp.Seconds - right.Seconds);
        }
        public static Duration operator -(Duration left, int totalSeconds)
        {
            Duration temp = new Duration(totalSeconds);
            return new Duration(left.Hours - temp.Hours, left.Minutes - temp.Minutes, left.Seconds - temp.Seconds);
        }

        // Increment and Decrement operators
        public static Duration operator ++(Duration duration)
        {
            return new Duration(duration.toSeconds() + 60);
        }
        public static Duration operator --(Duration duration)
        {
            return new Duration(duration.toSeconds() - 60);
        }

        // Comparison operators
        public static bool operator >(Duration left, Duration right)
        {

            return left.toSeconds() > right.toSeconds();
        }

        public static bool operator <(Duration left, Duration right)
        {
            return left.toSeconds() < right.toSeconds();
        }

        public static bool operator >=(Duration left, Duration right)
        {

            return left.toSeconds() >= right.toSeconds();
        }

        public static bool operator <=(Duration left, Duration right)
        {
            return left.toSeconds() <= right.toSeconds();
        }

        public static implicit operator bool(Duration d)
        {
            return (d.Hours == 0 && d.Minutes == 0 && d.Seconds == 0) ? false : true;
        }
        public static explicit operator DateTime(Duration d)
        {
            int totalDays = d.Hours / 24;
            int hours = d.Hours % 24;

            int days = totalDays % 30;
            int months = (totalDays / 30) % 12;
            int years = totalDays / 360;

            return new DateTime(2000 + years, 1 + months, 1 + days, hours, d.Minutes, d.Seconds);
        }
        #endregion

        #region class functions
        private int toSeconds()
        {
            return Hours * 3600 + Minutes * 60 + Seconds;
        }
        #endregion
    }

}
