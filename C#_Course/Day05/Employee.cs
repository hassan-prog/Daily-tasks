namespace Day05
{
    public enum LayOffCause
    {
        VacationStockNegative,
        AgeLimitExceeded,
        SalesTargetNotAchieved,
        Resigned
    }
    public class EmployeeLayOffEventArgs : EventArgs
    {
        public LayOffCause Cause { get; set; }
        public EmployeeLayOffEventArgs(LayOffCause cause)
        {
            Cause = cause;
        }
    }

    internal class Employee
    {
        public event EventHandler<EmployeeLayOffEventArgs> EmployeeLayOff;

        protected virtual void OnEmployeeLayOff(EmployeeLayOffEventArgs e)
        {
            EmployeeLayOff?.Invoke(this, e);
        }

        public int EmployeeID { get; set; }
        DateTime birthDate;
        public DateTime BirthDate
        {
            get { return birthDate; }
            set
            {
                birthDate = value;
                if ((DateTime.Now - birthDate).TotalDays / 365 >= 60)
                {
                    OnEmployeeLayOff(new EmployeeLayOffEventArgs(LayOffCause.AgeLimitExceeded));
                }
            }
        }
        public int VacationStock { get; set; }

        public bool RequestVacation(DateTime From, DateTime To)
        {
            int requestedDays = (To - From).Days;
            if (VacationStock >= requestedDays)
            {
                VacationStock -= requestedDays;
                return true;
            }
            return false;
        }

        public void EndOfYearOperation()
        {
            if (VacationStock < 0)
            {
                OnEmployeeLayOff(new EmployeeLayOffEventArgs(LayOffCause.VacationStockNegative));
            }
            if ((DateTime.Now.Year - birthDate.Year) > 60)
            {
                OnEmployeeLayOff(new EmployeeLayOffEventArgs(LayOffCause.AgeLimitExceeded));
            }
        }
        public override string ToString()
        {
            return $"Employee ID: {EmployeeID}\nBirthday: {birthDate.Date.ToString("D")}\nVacation Stock: {VacationStock}\n";
        }
    }
}


