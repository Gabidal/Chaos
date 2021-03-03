using System;
using System.Collections.Generic;
using System.Text;

namespace Chaos
{
    class Vector
    {
        public double X;
        public double Y;
        public double Z;

        public double Length => Math.Sqrt(X * X + Y * Y + Z * Z);

        /// <summary>
        /// Sets the values of the components equal to the specified value.
        /// </summary>
        public Vector(double scalar = 0.0)
        {
            X = scalar;
            Y = scalar;
            Z = scalar;
        }

        /// <summary>
        /// Constructs a vector by specified component values.
        /// </summary>
        public Vector(double x, double y, double z = 0.0)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public static Vector operator+(Vector a, Vector b)
        {
            return new Vector(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
        }

        public static Vector operator -(Vector a, Vector b)
        {
            return new Vector(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
        }

        public Vector Normalized(double Lenght)
        {
            return new Vector(X / Length, Y / Length, Z / Length);
        }

        public static Vector operator *(Vector a, double b)
        {
            return new Vector(a.X * b, a.Y * b, a.Z * b);
        }
    }
}
