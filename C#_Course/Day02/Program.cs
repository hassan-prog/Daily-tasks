using Day01;
using Day02_ClassLibrary;


internal class Program
{
    private static void Main(string[] args)
    {
        Employee[] empArr = new Employee[3];
        float age;
        int target;
        float salary;
        string gender;
        string name;
        string securityLvl;

        for (int i = 0; i < empArr.Length; i++)
        {
            do
            {
                Console.Write($"Employee {i + 1} Name: ");
                name = Console.ReadLine();
            } while (name == null);

            Console.WriteLine("The age must be between 18 and 45");
            do
            {
                Console.Write("Age: ");
                age = float.Parse(Console.ReadLine());
            } while (age < 18 || age > 45);

            Console.WriteLine("The target must be greater than 300");
            do
            {
                Console.Write("Target: ");
                target = int.Parse(Console.ReadLine());
            } while (target < 300);

            Console.WriteLine("The salary range must be between 6000 and 20000");
            do
            {
                Console.Write("Salary: ");
                salary = float.Parse(Console.ReadLine());
            } while (salary < 6000 || salary > 20000);

            do
            {
                Console.Write("Security level Admin/HR/Officer: ");
                securityLvl = Console.ReadLine().ToUpper();
            } while (securityLvl != "ADMIN" && securityLvl != "HR" && securityLvl != "OFFICER");

            SecurityLvl securityLevel = new SecurityLvl();
            switch (securityLvl)
            {
                case "ADMIN":
                    securityLevel = SecurityLvl.Admin;
                    break;
                case "HR":
                    securityLevel = SecurityLvl.HR;
                    break;
                case "OFFICER":
                    securityLevel = SecurityLvl.Officer;
                    break;
            }

            do
            {
                Console.Write("Gender M/F: ");
                gender = Console.ReadLine().ToUpper();
            } while (gender != "M" && gender != "F");

            Gender empGender = new Gender();
            switch (gender)
            {
                case "M":
                    empGender = Gender.Male;
                    break;
                case "F":
                    empGender = Gender.Female;
                    break;
            }

            Console.WriteLine("Please enter your hiring date in the format of dd/mm/yyyy");

            Console.Write("Day: ");
            int day = int.Parse(Console.ReadLine());

            Console.Write("Month: ");
            int month = int.Parse(Console.ReadLine());

            Console.Write("Year: ");
            int year = int.Parse(Console.ReadLine());

            HiringDate hiringDate = new HiringDate(day, month, year);

            empArr[i] = new Employee(name, age, salary, target, hiringDate, securityLevel, empGender);
        }

        for (int i = 0; i < empArr.Length; i++)
            Console.WriteLine(empArr[i].ToString());

        for (int i = 0; i < empArr.Length; i++)
        {
            Array.Sort(empArr);
            Console.WriteLine(empArr[i].ToString());
        }

    }
}