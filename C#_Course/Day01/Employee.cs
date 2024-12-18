using System;

namespace Day01
{
    enum Gender
    {
        Male,
        Female
    }
    internal struct Employee
    {
        private static int currentID = 0;
        private int id;
        private float salary;
        private HiringDate hiringDate;
        private Gender gender;
        private string genderText;

        public Employee(float _salary, HiringDate _hiringDate, Gender _gender)
        {
            id = ++currentID;
            salary = _salary;
            hiringDate = _hiringDate;
            gender = _gender;
            genderText = (gender == Gender.Male) ? "Male" : "Female";
        }

        public int getID() { return id; }
        public float getSalary() { return salary; }
        public void setSalary(float _salary) { salary = _salary; }
        public HiringDate getHiringDate() { return hiringDate; }
        public void setHiringDate(HiringDate _hiringDate) { hiringDate = _hiringDate; }
        public Gender getGender() { return gender; }
        public void setGender(Gender _gender)
        {
            gender = _gender;
            genderText = (gender == Gender.Male) ? "Male" : "Female";

        }

        public void printEmpDetails()
        {
            Console.WriteLine($"ID: {id},Salary: {salary}, Hiring Date: {hiringDate.getDay()}/{hiringDate.getMonth()}/{hiringDate.getYear()}" +
                $"Gender: {genderText}");
        }

    }
}
