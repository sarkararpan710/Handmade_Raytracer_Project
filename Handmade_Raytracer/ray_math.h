#include<math.h>


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


inline u32 RoundReal32ToUInt32(f32 F)
{
	u32 Result = (u32)(F + 0.5f);
	return Result;
}



//Compression oriented Programming. Defining constructors in C-style for each Vector type. Vector2 and Vector3 and Vector4.
//V2 Constructor definition
inline v2
V2(f32 X, f32 Y)
{
	v2 Result;

	Result.x = X;
	Result.y = Y;

	return(Result);
}

//V3 Constructor Definition
inline v3
V3(f32 X, f32 Y, f32 Z)
{
	v3 Result;

	Result.x = X;
	Result.y = Y;
	Result.z = Z;

	return(Result);
}

inline v3
V3(v2 XY, f32 Z)
{
	v3 Result;

	Result.x = XY.x;
	Result.y = XY.y;
	Result.z = Z;

	return(Result);
}


//V4 constructor definition
inline v4
V4(f32 X, f32 Y, f32 Z, f32 W)
{
	v4 Result;

	Result.x = X;
	Result.y = Y;
	Result.z = Z;
	Result.w = W;

	return(Result);
}

inline v4
V4(v3 XYZ, f32 W)
{
	v4 Result;

	Result.xyz = XYZ;
	Result.w = W;

	return(Result);
}

//
// NOTE(casey): Scalar operations
//

inline f32
Square(f32 A)
{
	f32 Result = A * A;

	return(Result);
}



//
// NOTE(casey): v2 operations
//


inline v2
operator*(f32 A, v2 B)
{
	v2 Result;

	Result.x = A * B.x;
	Result.y = A * B.y;

	return(Result);
}

inline v2
operator*(v2 B, f32 A)
{
	v2 Result = A * B;

	return(Result);
}

inline v2 &
operator*=(v2 &B, f32 A)
{
	B = A * B;

	return(B);
}

inline v2
operator-(v2 A)
{
	v2 Result;

	Result.x = -A.x;
	Result.y = -A.y;

	return(Result);
}

inline v2
operator+(v2 A, v2 B)
{
	v2 Result;

	Result.x = A.x + B.x;
	Result.y = A.y + B.y;

	return(Result);
}

inline v2 &
operator+=(v2 &A, v2 B)
{
	A = A + B;

	return(A);
}

inline v2
operator-(v2 A, v2 B)
{
	v2 Result;

	Result.x = A.x - B.x;
	Result.y = A.y - B.y;

	return(Result);
}

inline v2 &
operator-=(v2 &A, v2 B)
{
	A = A - B;

	return(A);
}

inline v2
Hadamard(v2 A, v2 B)
{
	v2 Result = { A.x*B.x, A.y*B.y };

	return(Result);
}

inline f32
Inner(v2 A, v2 B)
{
	f32 Result = A.x*B.x + A.y*B.y;

	return(Result);
}

inline f32
LengthSq(v2 A)
{
	f32 Result = Inner(A, A);

	return(Result);
}

inline f32
Length(v2 A)
{
	f32 Result = sqrt(LengthSq(A));
	return(Result);
}



//
// NOTE(casey): v3 operations
//

inline v3
operator*(f32 A, v3 B)
{
	v3 Result;

	Result.x = A * B.x;
	Result.y = A * B.y;
	Result.z = A * B.z;

	return(Result);
}

inline v3
operator*(v3 B, f32 A)
{
	v3 Result = A * B;

	return(Result);
}

inline v3 &
operator*=(v3 &B, f32 A)
{
	B = A * B;

	return(B);
}

inline v3
operator/(v3 B, f32 A)
{
	v3 Result = (1.0f / A)*B;

	return(Result);
}

inline v3 &
operator/=(v3 &B, f32 A)
{
	B = B / A;

	return(B);
}

inline v3
operator-(v3 A)
{
	v3 Result;

	Result.x = -A.x;
	Result.y = -A.y;
	Result.z = -A.z;

	return(Result);
}

inline v3
operator+(v3 A, v3 B)
{
	v3 Result;

	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	Result.z = A.z + B.z;

	return(Result);
}

inline v3 &
operator+=(v3 &A, v3 B)
{
	A = A + B;

	return(A);
}

inline v3
operator-(v3 A, v3 B)
{
	v3 Result;

	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	Result.z = A.z - B.z;

	return(Result);
}

inline v3 &
operator-=(v3 &A, v3 B)
{
	A = A - B;

	return(A);
}

inline v3
Hadamard(v3 A, v3 B)
{
	v3 Result = { A.x*B.x, A.y*B.y, A.z*B.z };

	return(Result);
}

inline f32
Inner(v3 A, v3 B)
{
	f32 Result = A.x*B.x + A.y*B.y + A.z*B.z;

	return(Result);
}

inline v3
Cross(v3 A, v3 B)
{
	v3 Result;

	Result.x = A.y*B.z - A.z*B.y;
	Result.y = A.z*B.x - A.x*B.z;
	Result.z = A.x*B.y - A.y*B.x;

	return(Result);
}

inline f32
LengthSq(v3 A)
{
	f32 Result = Inner(A, A);

	return(Result);
}

inline f32
Length(v3 A)
{
	f32 Result = sqrt(LengthSq(A));
	return(Result);
}

inline v3
Normalize(v3 A)
{
	v3 Result = A * (1.0f / Length(A));

	return(Result);
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

	return(Result);
}


//
// NOTE(casey): v4 operations
//

inline v4
operator*(f32 A, v4 B)
{
	v4 Result;

	Result.x = A * B.x;
	Result.y = A * B.y;
	Result.z = A * B.z;
	Result.w = A * B.w;

	return(Result);
}

inline v4
operator*(v4 B, f32 A)
{
	v4 Result = A * B;

	return(Result);
}

inline v4 &
operator*=(v4 &B, f32 A)
{
	B = A * B;

	return(B);
}

inline v4
operator-(v4 A)
{
	v4 Result;

	Result.x = -A.x;
	Result.y = -A.y;
	Result.z = -A.z;
	Result.w = -A.w;

	return(Result);
}

inline v4
operator+(v4 A, v4 B)
{
	v4 Result;

	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	Result.z = A.z + B.z;
	Result.w = A.w + B.w;

	return(Result);
}

inline v4 &
operator+=(v4 &A, v4 B)
{
	A = A + B;

	return(A);
}

inline v4
operator-(v4 A, v4 B)
{
	v4 Result;

	Result.x = A.x - B.x;
	Result.y = A.y - B.y;
	Result.z = A.z - B.z;
	Result.w = A.w - B.w;

	return(Result);
}

inline v4 &
operator-=(v4 &A, v4 B)
{
	A = A - B;

	return(A);
}

inline v4
Hadamard(v4 A, v4 B)
{
	v4 Result = { A.x*B.x, A.y*B.y, A.z*B.z, A.w*B.w };

	return(Result);
}

inline f32
Inner(v4 A, v4 B)
{
	f32 Result = A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;

	return(Result);
}

inline f32
LengthSq(v4 A)
{
	f32 Result = Inner(A, A);

	return(Result);
}

inline f32
Length(v4 A)
{
	f32 Result = sqrt(LengthSq(A));
	return(Result);
}







inline v4
BGRAUnpack4x8(u32 Packed)
{
	v4 Result = { (f32)((Packed >> 16) & 0xFF),
		(f32)((Packed >> 8) & 0xFF),
		(f32)((Packed >> 0) & 0xFF),
		(f32)((Packed >> 24) & 0xFF) };

	return(Result);
}

inline u32
BGRAPack4x8(v4 Unpacked)
{
	u32 Result = ((RoundReal32ToUInt32(Unpacked.a) << 24) |
		(RoundReal32ToUInt32(Unpacked.r) << 16) |
		(RoundReal32ToUInt32(Unpacked.g) << 8) |
		(RoundReal32ToUInt32(Unpacked.b) << 0));

	return(Result);
}

inline v4
RGBAUnpack4x8(u32 Packed)
{
	v4 Result = { (f32)((Packed >> 0) & 0xFF),
		(f32)((Packed >> 8) & 0xFF),
		(f32)((Packed >> 16) & 0xFF),
		(f32)((Packed >> 24) & 0xFF) };

	return(Result);
}

inline u32
RGBAPack4x8(v4 Unpacked)
{
	u32 Result = ((RoundReal32ToUInt32(Unpacked.a) << 24) |
		(RoundReal32ToUInt32(Unpacked.b) << 16) |
		(RoundReal32ToUInt32(Unpacked.g) << 8) |
		(RoundReal32ToUInt32(Unpacked.r) << 0));

	return(Result);
}



