namespace Day05
{
    internal class Club
    {
        public int ClubID { get; set; }
        public string ClubName { get; set; }
        private List<Employee> Members = new List<Employee>();
        public void AddMember(Employee E)
        {
            Members.Add(E);
            E.EmployeeLayOff += RemoveMember;
        }
        public void RemoveMember(object sender, EmployeeLayOffEventArgs e)
        {
            Employee? employee = sender as Employee;
            if (employee != null && e.Cause == LayOffCause.VacationStockNegative)
            {
                Members.Remove(employee);
                Console.WriteLine($"Employee {employee.EmployeeID} removed from Club due to {e.Cause}");
            }
            else if (employee != null && e.Cause == LayOffCause.AgeLimitExceeded)
            {
                Console.WriteLine($"Employee {employee.EmployeeID} is still a member of Club despite being older than 60");
            }
        }
        public override string ToString()
        {
            string str = $"Club ID : {ClubID}\nname :{ClubName}";
            foreach (Employee e in Members)
            {
                str += "\n@@@@@@@@@@@@@@@\n" + e.ToString();
            }
            return str;
        }
    }
}
