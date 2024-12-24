namespace Day03
{
    internal class Point3D : Point2D, IComparable<Point3D>, ICloneable
    {
        public float Z { get; set; }

        #region CTOR
        public Point3D() : base()
        {
            Z = 0;
        }

        public Point3D(float _X, float _Y, float _Z) : base(_X, _Y)
        {
            Z = _Z;
        }
        #endregion

        #region function overriding
        public override string ToString()
        {
            return $"Point Coordinates: ({X}, {Y}, {Z})";
        }

        public override bool Equals(object? obj)
        {
            if (obj is Point3D)
            {
                Point3D p = (Point3D)obj;

                if (GetType() == p.GetType())
                    return X == p.X && Y == p.Y;
            }
            return false;
        }
        #endregion

        #region function overloading
        public static implicit operator string(Point3D p)
        {
            return $"Point Coordinates: ({p.X}, {p.Y}, {p.Z})";
        }

        public static bool operator ==(Point3D left, Point3D right)
        {
            return left.X == right.X && left.Y == right.Y && left.Z == right.Z;
        }

        public static bool operator !=(Point3D left, Point3D right)
        {
            return left.X == right.X || left.Y == right.Y || left.Z == right.Z;
        }
        #endregion

        #region Class functions
        public int CompareTo(Point3D other)
        {
            int xComparison = X.CompareTo(other.X);
            if (X.CompareTo(other.X) != 0)
                return xComparison;

            int yComparison = Y.CompareTo(other.Y);
            if (yComparison != 0)
                return yComparison;

            return Z.CompareTo(other.Z);
        }
        public object Clone()
        {
            // Return a new Point3D object with the same values
            return new Point3D(this.X, this.Y, this.Z);
        }
        #endregion
    }
}
