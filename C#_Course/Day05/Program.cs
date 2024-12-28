using Day05;

internal class Program
{
    static void Main(string[] args)
    {
        Department dept = new Department();
        Club club = new Club();

        Employee oldEmployee = new Employee
        {
            EmployeeID = 1,
            BirthDate = new DateTime(1995, 4, 5),
            VacationStock = 6
        };
        
        Employee oldEmployee2 = new Employee
        {
            EmployeeID = 6,
            BirthDate = new DateTime(1968, 12, 3),
            VacationStock = -1
        };

        Employee youngEmployee = new Employee
        {
            EmployeeID = 2,
            BirthDate = new DateTime(1938, 1, 17),
            VacationStock = 3
        };

        SalesPerson lowPerformer = new SalesPerson
        {
            EmployeeID = 3,
            AchievedTarget = 100,
            BirthDate = new DateTime(1972, 12, 11)
        };

        SalesPerson highPerformer = new SalesPerson
        {
            EmployeeID = 4,
            AchievedTarget = 70,
            BirthDate = new DateTime(1987, 11, 26)
        };

        BoardMember resigningBoard = new BoardMember
        {
            EmployeeID = 5,
            BirthDate = new DateTime(1975, 8, 13)
        };

        dept.AddStaff(oldEmployee);
        club.AddMember(oldEmployee);

        dept.AddStaff(oldEmployee2);
        club.AddMember(oldEmployee2);

        dept.AddStaff(youngEmployee);
        club.AddMember(youngEmployee);

        dept.AddStaff(lowPerformer);
        club.AddMember(lowPerformer);

        dept.AddStaff(highPerformer);
        club.AddMember(highPerformer);

        dept.AddStaff(resigningBoard);
        club.AddMember(resigningBoard);



        Console.WriteLine(oldEmployee.ToString());
        Console.WriteLine(oldEmployee2.ToString());
        Console.WriteLine(youngEmployee.ToString());
        Console.WriteLine(lowPerformer.ToString());
        Console.WriteLine(highPerformer.ToString());
        Console.WriteLine(resigningBoard.ToString());

        Console.WriteLine("Running end of year operations...\n");
        oldEmployee.EndOfYearOperation();
        oldEmployee2.EndOfYearOperation();
        youngEmployee.EndOfYearOperation();
        lowPerformer.CheckTarget(80);
        highPerformer.CheckTarget(80);
        resigningBoard.Resign();

        Console.WriteLine("\nEnd of operations.");
    }
}