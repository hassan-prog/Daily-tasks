using Day03;

internal class Program
{
    private static void Main(string[] args)
    {
        Console.WriteLine($"Dividing 10/5 using Maths class: {Maths.Divide(10, 5)}");

        Duration test = new Duration(3800);

        Console.WriteLine(test);
        Console.WriteLine();
        int pointCounter = 0;
        Point3D[] arrayOfPoint3D = new Point3D[2];
        Console.Write($"Please enter the coordenates for 2 points");
        do
        {
            ++pointCounter;
            Console.Write($"Point #{pointCounter} X: ");
            float x, y, z;

            // Using TryParse
            while (!float.TryParse(Console.ReadLine(), out x))
            {
                Console.WriteLine("Invalid input. Please enter a valid number for X.");
                Console.Write($"Point #{pointCounter} X: ");
            }

            // Using Parse
            while (true)
            {
                Console.Write("Y: ");
                try
                {
                    y = float.Parse(Console.ReadLine());
                    break;
                }
                catch (FormatException)
                {
                    Console.WriteLine("Invalid input. Please enter a valid number for Y.");
                }
            }

            // Using Convert
            while (true)
            {
                Console.Write("Z: ");
                try
                {
                    z = Convert.ToSingle(Console.ReadLine());
                    break;
                }
                catch (FormatException)
                {
                    Console.WriteLine("Invalid input. Please enter a valid number for Z.");
                }
            }
            Point3D point = new Point3D(x, y, z);
            arrayOfPoint3D[pointCounter - 1] = point;
        } while (pointCounter < 2);

        if (arrayOfPoint3D[0] == arrayOfPoint3D[1])
        {
            Console.WriteLine("using == Operator: The two points are the same");
        }

        if (arrayOfPoint3D.Equals(arrayOfPoint3D[1]))
        {
            Console.WriteLine("using Equals(): The two points are the same");
        }

        Console.WriteLine($"Unsorted array: {arrayOfPoint3D[0]}, {arrayOfPoint3D[1]}");
        Array.Sort(arrayOfPoint3D);
        Console.WriteLine($"Sorted array: {arrayOfPoint3D[0]}, {arrayOfPoint3D[1]}");

        Point3D clonePoint = (Point3D)arrayOfPoint3D[0].Clone();
        Console.WriteLine($"Clone from first point: {clonePoint}");

    }
}