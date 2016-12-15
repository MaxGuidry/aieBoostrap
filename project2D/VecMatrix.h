#pragma once
#include<iostream>
#include<time.h>
#include<Windows.h>
#include<fstream>
class Vector2
{
public:
	Vector2();
	Vector2(float xx, float yy);
	//NAME: operator==
	//ARGUMENTS: one argument of a const 2d vector
	//DESCRIPTION: checks each value in the vector and returns true if they are equal and false if they are not
	bool operator == (const Vector2 &A);
	
	friend std::ostream& operator<<(std::ostream& os, const Vector2 vec);
	
	//NAME:operator +
	//ARGUMENTS: one argument of type const 2d vector
	//DESCRIPTION: adds the current vector to the one passed in and returns the result
	Vector2 operator +(const Vector2 &A);

	//NAME: operator -
	//ARGUMENTS: one argument of a const 3d vector
	//DESCRIPTION: subtracts each of the values in the vector and returns the result
	Vector2 operator -(const Vector2 &A);
	
	//NAME: operator *
	//ARGUMENTS: one argument of a float
	//DESCRIPTION: multiplies each value in the vector by a scalar value and returns the resultant vector
	Vector2 operator *(float Mult);
	
	//NAME: Magnitude
	//ARGUMENTS: no arguments
	//DESCRIPTION: returns the value that is the length of the vector
	float Magnitude();
	
	//NAME: Normalize
	//ARGUMENTS: no arguments
	//DESCRIPTION: creates a temporary 3d vector and sets its values to the normalized values of the current vector by dividing each value by the magnitude
	Vector2 Normalize();
	
	//NAME: DotProduct
	//ARGUMENTS: one arguments of const 3d vector
	//DESCRIPTION: returns the result of the dot product of the current vector and the vector passed in and returns the result
	float DotProduct(const Vector2 &A);
	
	float x, y;
};

class Vector3
{
public:
	Vector3();
	//constructor that takes in 3 float values for each part in the vector 
	Vector3(float xpos, float ypos, float zpos);
	friend std::ostream& operator<<(std::ostream& os, const Vector3 vec);
	
	//NAME: operator *
	//ARGUMENTS: one argument of a float
	//DESCRIPTION: multiplies each value in the vector by a scalar value and returns the resultant vector
	Vector3 operator *(float Scalar);
	
	//NAME: Magnitude
	//ARGUMENTS: no arguments
	//DESCRIPTION: returns the value that is the length of the vector
	float Magnitude();
	
	//NAME: Normalize
	//ARGUMENTS: no arguments
	//DESCRIPTION: creates a temporary 3d vector and sets its values to the normalized values of the current vector by dividing each value by the magnitude
	Vector3 Normalize();
	
	//NAME: DotProduct
	//ARGUMENTS: one arguments of const 3d vector
	//DESCRIPTION: returns the result of the dot product of the current vector and the vector passed in and returns the result
	float DotProduct(const Vector3 &B);
	
	//NAME: CrossProduct
	//ARGUMENTS: one argument of type const 3d vector
	//DESCRIPTION: creates a new 3d vector whos values are given by the cross product of the current vector and the one passed in using the cross product formula
	Vector3 CrossProduct(const Vector3 &B);
	
	//NAME:operator +
	//ARGUMENTS: one argument of type const 3d vector
	//DESCRIPTION: adds the current vector to the one passed in and returns the result
	Vector3 operator +(const Vector3 &B);
	
	//NAME: operator -
	//ARGUMENTS: one argument of a const 3d vector
	//DESCRIPTION: subtracts each of the values in the vector and returns the result
	Vector3 operator -(const Vector3 &B);
	
	//NAME: operator==
	//ARGUMENTS: one argument of a const 3d vector
	//DESCRIPTION: checks each value in the vector and returns true if they are equal and false if they are not
	bool operator==(const Vector3 &B);
	
	float VecArray[3];
	float x, y, z;
};

class Vector4
{
public:
	Vector4();
	//constructor that takes in 4 float values for each part in the vector 
	Vector4(float xpos, float ypos, float zpos, float wpos);

	friend std::ostream& operator<<(std::ostream& os, const Vector4 vec);
	
	//NAME: operator *
	//ARGUMENTS: one argument of a float
	//DESCRIPTION: multiplies each value in the vector by a scalar value and returns the resultant vector
	Vector4 operator*(float scalar);
	
	//NAME: Magnitude
	//ARGUMENTS: no arguments
	//DESCRIPTION: returns the value that is the length of the vector
	float Magnitude();
	
	//NAME: Normalize
	//ARGUMENTS: no arguments
	//DESCRIPTION: creates a temporary 4d vector and sets its values to the normalized values of the current vector by dividing each value by the magnitude
	Vector4 Normalize();
	
	//NAME: DotProduct
	//ARGUMENTS: one arguments of const 4d vector
	//DESCRIPTION: returns the result of the dot product of the current vector and the vector passed in and returns the result
	float DotProduct(const Vector4 &B);
	
	//NAME:operator +
	//ARGUMENTS: one argument of type const 4d vector
	//DESCRIPTION: adds the current vector to the one passed in and returns the result
	Vector4 operator +(const Vector4 &B);
	
	//NAME: operator -
	//ARGUMENTS: one argument of a const 4d vector
	//DESCRIPTION: subtracts each of the values in the vector and returns the result
	Vector4 operator -(const Vector4 &B);
	
	//NAME: operator==
	//ARGUMENTS: one argument of a const 4d vector
	//DESCRIPTION: checks each value in the vector and returns true if they are equal and false if they are not
	bool operator==(const Vector4 &B);
	
	float VecArray[4];
	float x, y, z, w;
};

class Mat2
{
public:
	Mat2(float a[2][2]);
	
	//
	Mat2(float a, float b, float c, float d);
	
	friend std::ostream& operator<<(std::ostream& os, const Mat2 mat);
	
	//NAME: print	
	//ARGUMENTS: no arguments
	//DESCRIPTION: 
	void print();
	
	//NAME: operator *
	//ARGUMENTS: one argument of a const 2d vector
	//DESCRIPTION: multiplies the current matrix by the vector that is passed in and returns the result
	Vector2 operator *(const Vector2 &vec)const;
	
	//NAME: operator *
	//ARGUMENTS: one argument of a const 2x2 matrix
	//DESCRIPTION: multiplies current matrix by the passed in matrix and returns the result
	Mat2 operator *(const Mat2 &mat)const;
	
private:
	float matrix[2][2];
};

class Mat3
{
public:
	Mat3();
	//constructor taking in an array and initializing the matrix
	Mat3(float a[3][3]);
	
	//constructor for 9 float values to initialize the matrix
	Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
	
	friend std::ostream& operator<<(std::ostream& os, const Mat3 mat);
	
	//NAME: print
	//ARGUMENTS: none
	//DESCRIPTION: loops through the matrix and prints the number at each index
	void print();
	
	//NAME: operator *
	//ARGUMENTS: one argument of a 3x3 matrix
	//DESCRIPTION: creates matrix temp of all zeros then sets this temp equal to the two matrices multiplied together
	Vector3 operator *(const Vector3 &vec);

	//NAME: operator *
	//ARGUMENTS: one argument of a 3d vector
	//DESCRIPTION: creates a vector temp of all zeros then loops through the multiplication of the vector and matrix
	//setting the temp equal to the product and returns the temp vector
	Mat3 operator *(const Mat3 &mat);
	
	//NAME: setRotateX
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the X axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat3 setRotateX(float angle);
	
	//NAME: setRotateY
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the Y axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat3 setRotateY(float angle);
	
	//NAME: setRotateZ
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the Z axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat3 setRotateZ(float angle);
	
private:
	float matrix[3][3];
};

class Mat4
{
public:
	//Two constructors 
	//Constructor that takes in a 2x2 array to initialize the matrix
	Mat4(float a[4][4]);
	
	//Constructor that takes in 16 float values to initialize the matrix
	Mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);
	
	friend std::ostream& operator<<(std::ostream& os, const Mat4 mat);
	
	void print();
	
	//NAME: operator *
	//ARGUMENTS: one argument of a 4x4 matrix
	//DESCRIPTION: creates matrix temp of all zeros then sets this temp equal to the two matrices multiplied together
	Mat4 operator *(const Mat4 &mat) const;
	
	//NAME: operator *
	//ARGUMENTS: one argument of a 4d vector
	//DESCRIPTION: creates a vector temp of all zeros then loops through the multiplication of the vector and matrix
	//setting the temp equal to the product and returns the temp vector
	Vector4 operator *(const Vector4 &vec)const;
	
	//NAME: setRotateX
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the x axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat4 setRotateX(float angle);

	//NAME: setRotateY
	//ARGUMENTS: one argument of type float
	//DESCRIPTION: function for rotation around the y axis using the overloaded multiplication operators and returns
	//the current instance of the matrix
	Mat4 setRotateY(float angle);
	
	//NAME: setRotateZ
	//ARGUMENTS: one arguments of type float
	//DESCRIPTION: function for rotation around the z axis using the overloaded multipication operators and returns
	//the current instance of the matrix
	Mat4 setRotateZ(float angle);
	
private:
	float matrix[4][4];

};	