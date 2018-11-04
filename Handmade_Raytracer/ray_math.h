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

