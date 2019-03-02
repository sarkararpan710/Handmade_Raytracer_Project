#include<math.h>
typedef float f32;

union v2
{
	struct
	{
		f32 x, y;
	};
	struct
	{
		f32 u, v;
	};
	f32 E[2];
};

union v3
{
	struct
	{
		f32 x, y, z;
	};
	struct
	{
		f32 u, v, w;
	};
	struct
	{
		f32 r, g, b;
	};
	struct
	{
		v2 xy;
		f32 Ignored0_;
	};
	struct
	{
		f32 Ignored1_;
		v2 yz;
	};
	struct
	{
		v2 uv;
		f32 Ignored2_;
	};
	struct
	{
		f32 Ignored3_;
		v2 vw;
	};
	f32 E[3];
};

union v4
{
	struct
	{
		union
		{
			v3 xyz;
			struct
			{
				f32 x, y, z;
			};
		};

		f32 w;
	};
	struct
	{
		union
		{
			v3 rgb;
			struct
			{
				f32 r, g, b;
			};
		};

		f32 a;
	};
	
	struct
	{
		v2 xy;
		f32 Ignored0_;
		f32 Ignored1_;
	};
	
	struct
	{
		f32 Ignored2_;
		v2 yz;
		f32 Ignored3_;
	};
	
	struct
	{
		f32 Ignored4_;
		f32 Ignored5_;
		v2 zw;
	};
	f32 E[4];
};


inline v2
V2(f32 X, f32 Y)
{
	v2 Result;
	Result.x = X;
	Result.y = Y;
}

inline v3
V3(f32 X, f32 Y, f32 Z)
{
	v3 Result;
	Result.x = X;
	Result.y = Y;
	Result.z = Z;
}

//operator overloading for v2 operations in C style structs
inline v2 operator*(f32 A, v2 B)
{
	v2 Result;
	Result.x = A * B.x;
	Result.y = A * B.y;
	return Result;
}

inline v2 operator+(f32 A, v2 B)
{
	v2 Result;
	Result.x = A * B.x;
	Result.y = A * B.y;
	return Result;
}


inline v3 operator*(f32 A, v3 B)
{
	v3 Result;
	Result.x = A * B.x;
	Result.y = A * B.y;
	Result.z = A * B.z;
	return Result;
}

inline v3 operator*(v3 B, f32 A)
{
	v3 Result;
	Result.x = B.x * A;
	Result.y = B.y * A;
	Result.z = B.z * A;
}


//modularized this function to use square.
inline f32 LengthSq(v3 A)
{
	f32 Result;
	Result = Square(A.x) + Square(A.y) + Square(A.z);
	return Result;
}

//modularized this function to use LengthSq
inline v3
Normalize(v3 A)
{
	v3 Result;
	Result = A * (1.0f / LengthSq(A));
	return Result;
}

inline f32
Square(f32 A)
{
	f32 Result = A * A;
	return Result;
}

inline v3
NOZ(v3 A)
{
	v3 Result = {};
	f32 LenSq = LengthSq(A);
	if (LenSq > Square(0.0001f))
	{
		Result = A * (1.0f / sqrt(LenSq));
	}
	return Result;
}

inline v3
Cross(v3 A, v3 B)
{
	v3 Result;
	Result.x = A.y*B.z - A.z*B.y;
	Result.y = A.z*B.x - A.x*B.z;
	Result.z = A.x*B.y - A.y*B.x;
}


