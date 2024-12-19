using Day01;
internal class Program
{
    private static void Main(string[] args)
    {
        Employee[] empArr = new Employee[3];
        for (int i = 0; i < empArr.Length; i++)
        {
            Console.WriteLine($"Employee {i + 1}");
            Console.Write("How much is your salary? ");
            float salary = float.Parse(Console.ReadLine());

            Console.WriteLine("Please enter your hiring date in the format of dd/mm/yyyy");

            Console.Write("Day: ");
            int day = int.Parse(Console.ReadLine());

            Console.Write("Month: ");
            int month = int.Parse(Console.ReadLine());

            Console.Write("Year: ");
            int year = int.Parse(Console.ReadLine());

            Console.WriteLine("M / F");
            string gender = Console.ReadLine();

            Gender empGender = new Gender();
            switch (gender.ToUpper())
            {
                case "M":
                    empGender = Gender.Male;
                    break;
                case "F":
                    empGender = Gender.Female;
                    break;
            }


            HiringDate hiringDate = new HiringDate();
            hiringDate.setDay(day);
            hiringDate.setMonth(month);
            hiringDate.setYear(year);

            empArr[i] = new Employee(salary, hiringDate, empGender);
        }

        for (int i = 0; i < empArr.Length; i++)
            empArr[i].printEmpDetails();
    }
}