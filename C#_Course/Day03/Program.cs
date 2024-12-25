using Day03;

internal class Program
{
    private static void Main(string[] args)
    {
        Console.WriteLine($"Dividing 10/5 using Maths class: {Maths.Divide(10, 5)}\n");

        int pointCounter = 0;
        Point3D[] arrayOfPoint3D = new Point3D[2];
        Console.Write($"Please enter the coordenates for 2 points\n");
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
        Console.WriteLine();

        Duration D1 = new Duration(1, 10, 15);
        Console.WriteLine("D1" + D1.ToString());

        Duration D2 = new Duration(3600);
        Console.WriteLine("D2: " + D2.ToString());

        Duration D3 = new Duration(7800);
        Console.WriteLine("D3: " + D3.ToString());

        Duration D4 = new Duration(666);
        Console.WriteLine("D4: " + D4.ToString());

        D3 = D1 + D2;
        Console.WriteLine("addition D3: " + D3.ToString());
        D3 = D1 + 7800;
        Console.WriteLine("addition v2.0 D3: " + D3.ToString());
        D3 = 666 + D3;
        Console.WriteLine("addition v3.0 D3: " + D3.ToString());
        D3 = D1++;
        Console.WriteLine("postfix increment D3: " + D3.ToString());
        D3 = --D2;
        Console.WriteLine("prefix decrement D3: " + D3.ToString());
        D1 = -D2;
        Console.WriteLine("D1: " + D1.ToString());
        if (D1 > D2) { Console.WriteLine("D1 > D2"); } else { Console.WriteLine("D1 is not bigger than D2"); };
        if (D1 <= D2) Console.WriteLine("D1 <= D2");
        if (D1) Console.WriteLine("D1 exists"); ;
        DateTime Obj = (DateTime)D1;
        Console.WriteLine(Obj);

    }
}