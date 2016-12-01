#pragma once
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<fstream>
class Vector2
{
public:
	Vector2() {};
	Vector2(float xx, float yy) : x(xx), y(yy) {}
	//NAME: operator==
	//ARGUMENTS: one argument of a const 2d vector
	//DESCRIPTION: checks each value in the vector and returns true if they are equal and false if they are not
	bool operator == (const Vector2 &A)
	{
		return x == A.x && y == A.y;
	}
	friend std::ostream& operator<<(std::ostream& os, const Vector2 vec)
	{
		os << '<' << vec.x << ',' << vec.y << '>';
		return os;
	}
	//NAME:operator +
	//ARGUMENTS: one argument of type const 2d vector
	//DESCRIPTION: adds the current vector to the one passed in and returns the result
	Vector2 operator +(const Vector2 &A)
	{
		Vector2 temp = Vector2(x + A.x, y + A.y);
		return temp;
	}
	//NAME: operator -
	//ARGUMENTS: one argument of a const 3d vector
	//DESCRIPTION: subtracts each of the values in the vector and returns the result
	Vector2 operator -(const Vector2 &A)
	{
		Vector2 temp = Vector2(x - A.x, y - A.y);
		return temp;
	}
	//NAME: operator *
	//ARGUMENTS: one argument of a float
	//DESCRIPTION: multiplies each value in the vector by a scalar value and returns the resultant vector
	Vector2 operator *(float Mult)
	{
		Vector2 temp = Vector2(x * Mult, y * Mult);
		return temp;
	}
	//NAME: Magnitude
	//ARGUMENTS: no arguments
	//DESCRIPTION: returns the value that is the length of the vector
	float Magnitude()
	{
		return sqrt((x*x) + (y*y));
	}
	//NAME: Normalize
	//ARGUMENTS: no arguments
	//DESCRIPTION: creates a temporary 3d vector and sets its values to the normalized values of the current vector by dividing each value by the magnitude
	Vector2 Normalize()
	{
		Vector2 temp = Vector2(x / Magnitude(), y / Magnitude());
		return temp;
	}
	//NAME: DotProduct
	//ARGUMENTS: one arguments of const 3d vector
	//DESCRIPTION: returns the result of the dot product of the current vector and the vector passed in and returns the result
	float DotProduct(const Vector2 &A)
	{
		return (x * A.x) + (y * A.y);
	}
	float x, y;
};

class Vector3
{
public:
	Vector3() {}
	//constructor that takes in 3 float values for each part in the vector 
	Vector3(float xpos, float ypos, float zpos) : x(xpos), y(ypos), z(zpos)
	{
		VecArray[0] = xpos;
		VecArray[1] = ypos;
		VecArray[2] = zpos;
	}
	friend std::ostream& operator<<(std::ostream& os, const Vector3 vec)
	{
		os << '<' << vec.VecArray[0] << ',' << vec.VecArray[1] << ',' << vec.VecArray[2] << '>';
		return os;
	}
	//NAME: operator *
	//ARGUMENTS: one argument of a float
	//DESCRIPTION: multiplies each value in the vector by a scalar value and returns the resultant vector
	Vector3 operator *(float Scalar)
	{
		Vector3 temp = Vector3(x*Scalar, y*Scalar, z*Scalar);
		return temp;
	}
	//NAME: Magnitude
	//ARGUMENTS: no arguments
	//DESCRIPTION: returns the value that is the length of the vector
	float Magnitude()
	{
		return sqrt(x*x + y*y + z*z);
	}
	//NAME: Normalize
	//ARGUMENTS: no arguments
	//DESCRIPTION: creates a temporary 3d vector and sets its values to the normalized values of the current vector by dividing each value by the magnitude
	Vector3 Normalize()
	{
		Vector3 temp = Vector3(x / Magnitude(), y / Magnitude(), z / Magnitude());
		return temp;
	}
	//NAME: DotProduct
	//ARGUMENTS: one arguments of const 3d vector
	//DESCRIPTION: returns the result of the dot product of the current vector and the vector passed in and returns the result
	float DotProduct(const Vector3 &B)
	{
		return ((x*B.x) + (y*B.y) + (z*B.z));
	}
	//NAME: CrossProduct
	//ARGUMENTS: one argument of type const 3d vector
	//DESCRIPTION: creates a new 3d vector whos values are given by the cross product of the current vector and the one passed in using the cross product formula
	Vector3 CrossProduct(const Vector3 &B)
	{
		Vector3 temp = Vector3((y*B.z) - (z*B.y), (x*B.z) - (z*B.x), (x*B.y) - (y*B.x));
		return temp;
	}
	//NAME:operator +
	//ARGUMENTS: one argument of type const 3d vector
	//DESCRIPTION: adds the current vector to the one passed in and returns the result
	Vector3 operator +(const Vector3 &B)
	{
		Vector3 temp = Vector3(x + B.x, y + B.y, z + B.z);
		return temp;
	}
	//NAME: operator -
	//ARGUMENTS: one argument of a const 3d vector
	//DESCRIPTION: subtracts each of the values in the vector and returns the result
	Vector3 operator -(const Vector3 &B)
	{
		Vector3 temp = Vector3(x - B.x, y - B.y, z - B.z);
		return temp;
	}
	//NAME: operator==
	//ARGUMENTS: one argument of a const 3d vector
	//DESCRIPTION: checks each value in the vector and returns true if they are equal and false if they are not
	bool operator==(const Vector3 &B)
	{
		return x == B.x&&y == B.y&&z == B.z;
	}
	float VecArray[3];
	float x, y, z;
};

class Vector4
{
public:
	Vector4() {}
	//constructor that takes in 4 float values for each part in the vector 
	Vector4(float xpos, float ypos, float zpos, float wpos) :x(xpos), y(ypos), z(zpos), w(wpos)
	{
		VecArray[0] = xpos;
		VecArray[1] = ypos;
		VecArray[2] = zpos;
		VecArray[3] = wpos;
	}
	friend std::ostream& operator<<(std::ostream& os, const Vector4 vec)
	{
		os << '<' << vec.VecArray[0] << ',' << vec.VecArray[1] << ',' << vec.VecArray[2] <<','<<vec.VecArray[3]<< '>';
		return os;
	}
	//NAME: operator *
	//ARGUMENTS: one argument of a float
	//DESCRIPTION: multiplies each value in the vector by a scalar value and returns the resultant vector
	Vector4 operator*(float scalar)
	{
		Vector4 temp = Vector4(x*scalar, y*scalar, z*scalar, w*scalar);
		return temp;
	}
	//NAME: Magnitude
	//ARGUMENTS: no arguments
	//DESCRIPTION: returns the value that is the length of the vector
	float Magnitude()
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}
	//NAME: Normalize
	//ARGUMENTS: no arguments
	//DESCRIPTION: creates a temporary 4d vector and sets its values to the normalized values of the current vector by dividing each value by the magnitude
	Vector4 Normalize()
	{
		Vector4 temp = Vector4(x / Magnitude(), y / Magnitude(), z / Magnitude(), w / Magnitude());
		return temp;
	}
	//NAME: DotProduct
	//ARGUMENTS: one arguments of const 4d vector
	//DESCRIPTION: returns the result of the dot product of the current vector and the vector passed in and returns the result
	float DotProduct(const Vector4 &B)
	{
		return ((x*B.x) + (y*B.y) + (z*B.z) + (w*B.w));
	}
	//NAME:operator +
	//ARGUMENTS: one argument of type const 4d vector
	//DESCRIPTION: adds the current vector to the one passed in and returns the result
	Vector4 operator +(const Vector4 &B)
	{
		Vector4 temp = Vector4(x + B.x, y + B.y, z + B.z, w + B.w);
		return temp;
	}
	//NAME: operator -
	//ARGUMENTS: one argument of a const 4d vector
	//DESCRIPTION: subtracts each of the values in the vector and returns the result
	Vector4 operator -(const Vector4 &B)
	{
		Vector4 temp = Vector4(x - B.x, y - B.y, z - B.z, w - B.w);
		return temp;
	}
	//NAME: operator==
	//ARGUMENTS: one argument of a const 4d vector
	//DESCRIPTION: checks each value in the vector and returns true if they are equal and false if they are not
	bool operator==(const Vector4 &B)
	{
		return x == B.x&&y == B.y&&z == B.z&&w == B.w;
	}
	float VecArray[4];
	float x, y, z, w;
};

class Mat2
{
public:
	Mat2(float a[2][2])
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				matrix[i][j] = a[i][j];
			}
		}
	}
	//
	Mat2(float a, float b, float c, float d)
	{
		matrix[0][0] = a;
		matrix[0][1] = b;
		matrix[1][0] = c;
		matrix[1][1] = d;
	}
	friend std::ostream& operator<<(std::ostream& os, const Mat2 mat)
	{
		for (int i = 0; i < 4; i++)
		{
			if (i % 2 == 0)
				os << "\n";
			os << mat.matrix[i / 2][i % 2] << " ";
		}
		return os;
	}
	//NAME: print	
	//ARGUMENTS: no arguments
	//DESCRIPTION: 
	void print()
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				std::cout << matrix[i][j] << ", ";
			}
		}
	}
	//NAME: operator *
	//ARGUMENTS: one argument of a const 2d vector
	//DESCRIPTION: multiplies the current matrix by the vector that is passed in and returns the result
	Vector2 operator *(const Vector2 &vec)const
	{
		Vector2 temp = Vector2(vec.x*matrix[0][0] + vec.y*matrix[1][0], vec.x*matrix[0][1] + vec.y*matrix[1][1]);
		return temp;
	}
	//NAME: operator *
	//ARGUMENTS: one argument of a const 2x2 matrix
	//DESCRIPTION: multiplies current matrix by the passed in matrix and returns the result
	Mat2 operator *(const Mat2 &mat)const
	{
		Mat2 temp = Mat2(matrix[0][0] * mat.matrix[0][0] + matrix[0][1] * mat.matrix[1][0], matrix[0][0] * mat.matrix[0][1] + matrix[0][1] * mat.matrix[1][1], matrix[1][0] * mat.matrix[0][0] + matrix[1][1] * mat.matrix[1][0], matrix[1][0] * mat.matrix[0][1] + matrix[1][1] * mat.matrix[1][1]);
		return temp;
	}
private:
	float matrix[2][2];
};

class Mat3
{
public:
	Mat3() {}
	//constructor taking in an array and initializing the matrix
	Mat3(float a[3][3])
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				matrix[i][j] = a[i][j];
			}
		}
	}
	//constructor for 9 float values to initialize the matrix
	Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
	{
		matrix[0][0] = a;
		matrix[0][1] = b;
		matrix[0][2] = c;
		matrix[1][0] = d;
		matrix[1][1] = e;
		matrix[1][2] = f;
		matrix[2][0] = g;
		matrix[2][1] = h;
		matrix[2][2] = i;
	}
	friend std::ostream& operator<<(std::ostream& os, const Mat3 mat)
	{
		for (int i = 0; i < 9; i++)
		{
			if (i % 3 == 0)
				os << "\n";
			os << mat.matrix[i / 3][i % 3] << " ";
		}
		return os;
	}
	//NAME: print
	//ARGUMENTS: none
	//DESCRIPTION: loops through the matrix and prints the number at each index
	void print()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				std::cout << matrix[i][j] << ", ";
			}
		}
	}
	//NAME: operator *
	//ARGUMENTS: one argument of a 3x3 matrix
	//DESCRIPTION: creates matrix temp of all zeros then sets this temp equal to the two matrices multiplied together
	Vector3 operator *(const Vector3 &vec)
	{
		Vector3 temp = Vector3(0, 0, 0);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				temp.VecArray[i] += vec.VecArray[j] * matrix[j][i];

			}
		}
		return temp;
	}
	//NAME: operator *
	//ARGUMENTS: one argument of a 3d vector
	//DESCRIPTION: creates a vector temp of all zeros then loops through the multiplication of the vector and matrix
	//setting the temp equal to the product and returns the temp vector
	Mat3 operator *(const Mat3 &mat)
	{
		Mat3 temp = Mat3(0, 0, 0, 0, 0, 0, 0, 0, 0);

		//THIRD AND FINAL ATTEMPT(WORKS) 
		for (int i = 0; i < 27; i++)
		{
			temp.matrix[i / 9][(i % 9) / 3] += matrix[(i / 9)][i % 3] * mat.matrix[i % 3][(i % 9) / 3];
		}
		return temp;
	}
	//NAME: setRotateX
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the X axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat3 setRotateX(float angle)
	{
		Mat3 RotationalX = Mat3(1, 0, 0, 0, cos(angle), -sin(angle), 0, sin(angle), cos(angle));
		*this = RotationalX**this;
		//*this = *this*RotationalX;
		return *this;
	}
	//NAME: setRotateY
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the Y axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat3 setRotateY(float angle)
	{
		Mat3 RotationalY = Mat3(cos(angle), 0, sin(angle), 0, 1, 0, -sin(angle), 0, cos(angle));
		*this = RotationalY**this;
		return *this;
	}
	//NAME: setRotateZ
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the Z axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat3 setRotateZ(float angle)
	{
		Mat3 RotationalZ = Mat3(cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1);
		*this = RotationalZ**this;
		return *this;
	}
private:
	float matrix[3][3];
};

class Mat4
{
public:
	//Two constructors 
	//Constructor that takes in a 2x2 array to initialize the matrix
	Mat4(float a[4][4])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				matrix[i][j] = a[i][j];
			}
		}
	}
	//Constructor that takes in 16 float values to initialize the matrix
	Mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
	{
		matrix[0][0] = a;
		matrix[0][1] = b;
		matrix[0][2] = c;
		matrix[0][3] = d;
		matrix[1][0] = e;
		matrix[1][1] = f;
		matrix[1][2] = g;
		matrix[1][3] = h;
		matrix[2][0] = i;
		matrix[2][1] = j;
		matrix[2][2] = k;
		matrix[2][3] = l;
		matrix[3][0] = m;
		matrix[3][1] = n;
		matrix[3][2] = o;
		matrix[3][3] = p;
	}
	friend std::ostream& operator<<(std::ostream& os, const Mat4 mat)
	{
		for (int i = 0; i < 16; i++)
		{
			if (i % 4 == 0)
				os << "\n";
			os << mat.matrix[i / 4][i % 4] << " ";
		}
		return os;
	}
	void print()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				std::cout << matrix[i][j] << ", ";
			}
		}
	}
	//NAME: operator *
	//ARGUMENTS: one argument of a 4x4 matrix
	//DESCRIPTION: creates matrix temp of all zeros then sets this temp equal to the two matrices multiplied together
	Mat4 operator *(const Mat4 &mat) const
	{
		Mat4 temp = Mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		for (int i = 0; i < 64; i++)
		{
			temp.matrix[i / 16][(i % 16) / 4] += matrix[(i / 16)][i % 4] * mat.matrix[i % 4][(i % 16) / 4];
		}
		return temp;
	}
	//NAME: operator *
	//ARGUMENTS: one argument of a 4d vector
	//DESCRIPTION: creates a vector temp of all zeros then loops through the multiplication of the vector and matrix
	//setting the temp equal to the product and returns the temp vector
	Vector4 operator *(const Vector4 &vec)const
	{
		Vector4 temp = Vector4(0, 0, 0, 0);
		for (int i = 0; i < 16; i++)
		{
			temp.VecArray[i / 4] += matrix[i % 4][i / 4] * vec.VecArray[i % 4];
		}
		return temp;
	}
	//NAME: setRotateX
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the x axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat4 setRotateX(float angle)
	{
		Mat4 RotationalX = Mat4(1, 0, 0, 0, 0, cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1);
		*this = RotationalX**this;
		return *this;
	}
	//NAME: setRotateY
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the y axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat4 setRotateY(float angle)
	{
		Mat4 RotationalY = Mat4(cos(angle), 0, sin(angle), 0, 0, 1, 0, 0, -sin(angle), 0, cos(angle), 0, 0, 0, 0, 1);
		*this = RotationalY**this;
		return *this;
	}	
	//NAME: setRotateZ
	//ARGUMENTS: one arguments of type float
	//DESCRIPTION: function for rotation around the z axis using the overloaded multipication operators and returns
	//the current instance of the matrix
	Mat4 setRotateZ(float angle)
	{
		Mat4 RotationalZ = Mat4(cos(angle), -sin(angle), 0, 0, sin(angle), cos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
		*this = RotationalZ**this;
		return *this;
	}
private:
	float matrix[4][4];

};