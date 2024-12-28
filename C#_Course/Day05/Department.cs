namespace Day05
{
    internal class Department
    {
        public int DeptID { get; set; }
        public string DeptName { get; set; }
        private List<Employee> Staff;
        public void AddStaff(Employee E)
        {
            Staff.Add(E);
            E.EmployeeLayOff += RemoveStaff;
        }
        ///CallBackMethod
        public void RemoveStaff(object sender, EmployeeLayOffEventArgs e)
        {
            Employee? employee = sender as Employee;
            if (employee != null && (e.Cause == LayOffCause.VacationStockNegative || e.Cause == LayOffCause.AgeLimitExceeded))
            {
                Staff.Remove(employee);
                Console.WriteLine($"Employee {employee.EmployeeID} removed from Department due to {e.Cause}");
            }
        }
    }
}
