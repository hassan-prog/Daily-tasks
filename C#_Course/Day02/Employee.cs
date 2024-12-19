using Day02_ClassLibrary;

namespace Day01
{
    public class Employee : IComparable<Employee>
    {
        private int id;
        private static int currentID = 0;
        private float salary;

        private HiringDate hiringDate;
        private SecurityLvl securityLvl;
        private Gender gender;

        public string name;
        public float age;
        public float target;
        public string genderText;

        public Employee(string _name, float _age, float _salary, int _target, HiringDate _hiringDate, SecurityLvl _securityLvl, Gender _gender)
        {
            id = ++currentID;
            name = _name;
            age = _age;
            target = _target;
            salary = _salary;
            hiringDate = _hiringDate;
            securityLvl = _securityLvl;
            gender = _gender;
            genderText = (gender == Gender.Male) ? "Male" : "Female";
        }

        #region Getters | Setters
        public int getID() { return id; }
        public string getName() { return name; }
        public void setName(string _name) { name = _name; }
        public float getAge() { return age; }
        public void setAge(float _age) { age = _age; }
        public float getTarget() { return target; }
        public void setTarget(float _target) { target = _target; }
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
        #endregion

        public override string ToString()
        {
            return $"ID: {id}, Name: {name}, Age: {age}, Target: {target}, Gender: {genderText}, Security Level: {securityLvl}," +
                $" Salary: {salary}, Hiring Date: {hiringDate.getDay()}/{hiringDate.getMonth()}/{hiringDate.getYear()}";
        }
        public int CompareTo(Employee other)
        {
            // Compare based on HiringDate
            return hiringDate.CompareTo(other.hiringDate);
        }

    }
}
