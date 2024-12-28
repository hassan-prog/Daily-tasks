namespace Day05
{
    internal class SalesPerson : Employee
    {
        public SalesPerson()
        {
            EmployeeLayOff += (sender, e) => Console.WriteLine($"Sales Person laid off. Cause: {e.Cause}");
        }
        public int AchievedTarget { get; set; }

        public bool CheckTarget(int Quota)
        {
            if (AchievedTarget < Quota)
            {
                OnEmployeeLayOff(new EmployeeLayOffEventArgs(LayOffCause.SalesTargetNotAchieved));
                return false;
            }
            return true;
        }

        public new void EndOfYearOperation()
        {
            if ((DateTime.Now.Year - BirthDate.Year) > 60)
            {
                OnEmployeeLayOff(new EmployeeLayOffEventArgs(LayOffCause.AgeLimitExceeded));
            }
        }
        public override string ToString()
        {
            return $"Sales Person ID: {EmployeeID}\nBirthday: {BirthDate.Date.ToString("D")}\nTarget: {AchievedTarget}\n";
        }
    }
}
