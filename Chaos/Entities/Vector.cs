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
    }
}
