using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bento
{
    public struct Vector3
    {
        public float x, y, z;

        public static Vector3 zero => new Vector3(0.0f);
        public static Vector3 left => new Vector3(-1.0f, 0.0f, 0.0f);
        public static Vector3 right => new Vector3(1.0f, 0.0f, 0.0f);
        public static Vector3 up => new Vector3(0.0f, 1.0f, 0.0f);
        public static Vector3 down => new Vector3(0.0f, -1.0f, 0.0f);
        public static Vector3 forward => new Vector3(0.0f, 0.0f, 1.0f);
        public static Vector3 back => new Vector3(0.0f, 0.0f, -1.0f);

        public Vector3 normalized
        {
            get
            {
                Vector3 vec = this;

                if (vec == Vector3.zero)
                    return Vector3.zero;

                float scalar = (float)Math.Sqrt(Math.Pow(vec.x, 2) + Math.Pow(vec.y, 2) + Math.Pow(vec.z, 2));
                return vec /= scalar;
            }
        }

        public float magnitude
        {
            get
            {
                Vector3 vec = this;
                float scalar = (float)Math.Sqrt(Math.Pow(vec.x, 2) + Math.Pow(vec.y, 2) + Math.Pow(vec.z, 2));

                return scalar;
            }
        }

        public Vector3(float scalar)
        {
            x = scalar;
            y = scalar;
            z = scalar;
        }

        public void Normalize()
        {
            if (this == Vector3.zero)
                return;

            float scalar = (float)Math.Sqrt(Math.Pow(this.x, 2) + Math.Pow(this.y, 2) + Math.Pow(this.z, 2));
            this /= scalar;
        }

        public static float Dot(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
        }

        public static float Angle(Vector3 lhs, Vector3 rhs)
        {
            return (float)Math.Acos((Dot(lhs, rhs) / (lhs.magnitude * rhs.magnitude)));
        }

        public static Vector3 Lerp(Vector3 start, Vector3 end, float t)
        {
            return start + (end - start) * t;

        }

        public Vector3(float X, float Y, float Z)
        {
            x = X;
            y = Y;
            z = Z;
        }

        public static Vector3 operator *(Vector3 vector, float scalar)
        {
            return new Vector3(vector.x * scalar, vector.y * scalar, vector.z * scalar);
        }
        public static Vector3 operator /(Vector3 vector, float scalar)
        {
            return new Vector3(vector.x / scalar, vector.y / scalar, vector.z / scalar);
        }

        public static Vector3 operator +(Vector3 vectorL, Vector3 vectorR)
        {
            return new Vector3(vectorL.x + vectorR.x, vectorL.y + vectorR.y, vectorL.z + vectorR.z);
        }

        public static Vector3 operator -(Vector3 vectorL, Vector3 vectorR)
        {
            return new Vector3(vectorL.x - vectorR.x, vectorL.y - vectorR.y, vectorL.z - vectorR.z);
        }

        public static bool operator ==(Vector3 vectorL, Vector3 vectorR)
        {
            if (vectorL.x == vectorR.x && vectorL.y == vectorR.y && vectorL.z == vectorR.z)
                return true;
            else
                return false;
        }

        public static bool operator !=(Vector3 vectorL, Vector3 vectorR)
        {
            if (vectorL.x == vectorR.x && vectorL.y == vectorR.y && vectorL.z == vectorR.z)
                return false;
            else
                return true;
        }

    }
}
