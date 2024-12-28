namespace Day05
{
    internal class BoardMember : Employee
    {
        public BoardMember()
        {
            EmployeeLayOff += (sender, e) => Console.WriteLine($"Board Member {e.Cause}");
        }

        public void Resign()
        {
            OnEmployeeLayOff(new EmployeeLayOffEventArgs(LayOffCause.Resigned));
        }
    }
}
