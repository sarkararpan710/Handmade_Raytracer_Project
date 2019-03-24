//setting up the bitmap header for displaying the ray traced images.
#include<stdio.h>
#include<stdint.h>
#include<cstdlib>
#include<fstream>
#include<float.h>
#include "ray.h"

internal u32 GetTotalPixelSize(image_32 Image)//take image_32 Image
{
	u32 Result = Image.Width*Image.Height * sizeof(u32);
	return(Result);
}

internal image_32 AllocateImage(u32 width, u32 height)
{
	image_32 Image = {};//create the image object and initialize it.
	Image.Height = height;
	Image.Width = width;
	u32 OutputPixelSize = GetTotalPixelSize(Image);//old version of the code does this line->sizeof(u32)*image.Width*image.Height;
	Image.Pixels = (u32*)malloc(OutputPixelSize);//main source of the initial nullpointer at main *Out.
	return(Image);
}

internal void WriteImage(image_32 Image, const char* OutputFileName)
{
	u32 OutputPixelSize = GetTotalPixelSize(Image);
	bitmap_header Header = {};

	Header.FileType = 0x4D42;
	Header.FileSize = sizeof(Header) + OutputPixelSize;//Need to set it later
													   //Header.Reserved1;//These are reserved and set by the header itself
													   //Header.Reserved2;//These are reserved and set by the header itself
	Header.BitmapOffset = sizeof(Header);
	Header.Size = sizeof(Header) - 14;//also need to set the size of the pixels. Since the header is 50 bytes check wikipedia.
	Header.Width = Image.Width;
	Header.Height = Image.Height;
	Header.Planes = 1;
	Header.BitsPerPixel = 32;
	Header.Compression = 0;
	Header.SizeOfBitmap = OutputPixelSize;//writing bottom part first. Very Important.
	Header.HorzResolution = 0;
	Header.VertResolution = 0;
	Header.ColorsUsed = 0;
	Header.ColorsImportant = 0;

	//Header.RedMask = 0x00FF0000;//LITTLE ENDIAN MACHINES TO SET UP THE COLOR OF THE BUFFER 
	//Header.GreenMask  = 0x0000FF00;
	//Header.BlueMask = 0x000000FF;

	/* Checking the reference image to check the values of the header.
	#if 0
	FILE *InFile = fopen("reference.bmp", "rb");
	bitmap_header RefHeader = {};
	fread(&RefHeader, sizeof(RefHeader), 1, InFile);
	fclose(InFile);
	#endif
	*/
	//performing the standard file procedures to set the output file on the bitmap image set by the structure header to 
	//const char *OutputFileName = "test.bmp";
	FILE *OutFile = fopen(OutputFileName, "wb");

	if (OutFile)
	{
		fwrite(&Header, sizeof(Header), 1, OutFile);//we write it into the header
		fwrite(Image.Pixels, OutputPixelSize, 1, OutFile);
		fclose(OutFile);
	}

	else
	{
		fprintf(stderr, "[Error]Unable to write output file %s. \n", OutputFileName);
	}
}

internal v3
RayCast(world *World, v3 RayOrigin, v3 RayDirection)
{
	//setting the material if the ray hits nothing
	//this should get packed properly
										  //starting to implement the raycast algorithm for ray plane intersection
	
	f32 MinHitDistance = 0.001f;
	f32 tolerance = 0.00001f; //putting it outside the for loop because of variable scope

	v3 Result = {};
	v3 Attenuation = V3(1,1,1); //Initial Attenuation factor to be black when
	//we hit nothing... means no attenuation for the ray

	//Shooting out multiple rays
	for(u32 RayCount = 0; RayCount<8; ++RayCount)
	{

	b32 hitSomething = false;
    f32 hitdistance = F32Max;
	v3 NextOrigin = {};
	v3 NextNormal  = {};
	u32 HitMatIndex = 0; //to have a notion of what color values the ray hits 
	//This function implements the minimum distance between the ray's first hit and the plane
	for (u32 PlaneIndex = 0; PlaneIndex<World->planeCount; ++PlaneIndex)
	{

		//loop through all the planes in the world
		plane Plane = World->planes[PlaneIndex];
		f32 denom = Inner(Plane.N, RayDirection);
		if ((denom < -tolerance) >(denom > tolerance))
		{
			f32 thisDistance = (-Plane.d - Inner(Plane.N, RayOrigin)) / denom;
			if (thisDistance > MinHitDistance && thisDistance<hitdistance)
			{
				hitdistance = thisDistance;

				//after checking for the closest Ray plane intersection, set the material of the hit
				//plane as red
				HitMatIndex = Plane.MatIndex;
				NextOrigin = RayOrigin + thisDistance*RayDirection;
				NextNormal = Plane.N;
			}
		}

	}



	//This loop performs ray casting for all the spheres in the World.
	for (u32 SphereIndex = 0; SphereIndex<World->sphereCount; ++SphereIndex)
	{

		//loop through all the spheres in the world
		sphere Sphere = World->spheres[SphereIndex];
		
		v3 SphereRelativeRayOrigin = RayOrigin - Sphere.P;
		f32 a = Inner(RayDirection,RayDirection);//getting the values for our Ray sphere intersection
		f32 b = 2*Inner(RayDirection, SphereRelativeRayOrigin);
		f32 c = Inner(SphereRelativeRayOrigin, SphereRelativeRayOrigin) - (Sphere.r*Sphere.r);
		
		
		f32 denom = 2*a;//parts of our quadratic eqn solution for the ray sphere intersection math.
		f32 RootTerm = sqrt((b*b) - (4 *(a*c)));

		if (RootTerm > tolerance)//doing a check with tolerance values to check for exceptions when either the root term is negative or when denom is 0.
		{
			f32 tp = (-b + RootTerm) / denom;
			f32 tn = (-b - RootTerm) / denom;

			f32 thisDistance = tp;
			if ((tn > MinHitDistance) && (tn < tp))
			{
				thisDistance = tn;
			}

			if ((thisDistance > 0) && (thisDistance < hitdistance))
			{
				hitdistance = thisDistance;
				HitMatIndex = Sphere.MatIndex;
				NextOrigin = RayOrigin + thisDistance*RayDirection;
				NextNormal = NOZ(NextOrigin - Sphere.P);
					}
			}

			//If I hit something then I may keep casting over the scene
			if(HitMatIndex)
			{
				//As we hit the objects in the scene we store these attenuation values
				material Mat = World->Materials[HitMatIndex];

				//For the emission color we propagate the attenuatiion factor 
				//of the Emission color back to the camera.
				Result += Hadamard(Attenuation,Mat.EmitColor);
				Mat.RefColor = Hadamard(Attenuation, Mat.RefColor);


				RayOrigin = NextOrigin;
				RayDirection = NextNormal;

				
			}

			//Display the color that has we got at the last hit.
			else
			{
				material Mat = World->Materials[HitMatIndex];

				//Here we propagate the attenuation of the null material.
				Result += Hadamard(Attenuation,Mat.EmitColor);
				break;
			}
			}
	}
	return Result;

	}


	


int main(int ArgCount, char **Args)
{
	printf("Raycasting... ");
	//return material 0 to ray trace a color when the 
	//ray tracer hits nothing
	material Materials[3] = {};

	//Want the sky to emit colo so we are assigning an emit color reference
	//for the sky.
	Materials[0].EmitColor = V3(0.3f, 0.4f, 0.5f);//the error for no suitable constructor from int to v3. Solved by defining functions for v2,v3 and v4 in ray_math.h
	Materials[1].RefColor = V3(0.5, 0.5, 0.5);//The Plane is Red color
	Materials[2].RefColor = V3(0.7f, 0.5f, 0.3f);//The Sphere is Green color
	

	//definin the plane for ray tracing the plane.
	//the plane here is pointing up towards z axis
	plane Plane = {};
	Plane.N = V3(0, 0, 1);
	Plane.d = 0;
	Plane.MatIndex = 1;


	//defining the sphere for ray tracing the sphere.
	sphere Sphere = {};
	Sphere.P = V3(2,0,1);
	Sphere.r = 1.0f;
	Sphere.MatIndex = 2;




	world World = {};
	World.MaterialCount = 4;
	World.Materials = Materials;
	World.planeCount = 1;
	World.planes = &Plane;
	World.sphereCount = 2;
	World.spheres = &Sphere;


	

	
	//creating the image and allocating it
	image_32 Image = AllocateImage(1280, 720);




	//SETTING THE CAMERA POSITIONS AND RAY POINTS TO SHOOT RAYS FROM
	v3 CameraPos = V3(0, 10, 1);
	v3 CameraZ = NOZ(CameraPos);
	v3 CameraX = NOZ(Cross(V3(0, 0, 1), CameraZ));//Changed the cross product the orientation of the bitmap changed because of this.
	v3 CameraY = NOZ(Cross(CameraZ, CameraX));


	f32 FilmDist = 1.0f;
	f32 FilmWidth = 1.0f;
	f32 FilmHeight = 1.0f;
	//Implementing Aspect Ratio to address the problem of ray casting in a specific square plane and
	//adjust the height and width ration accordingly.
	if (Image.Width > Image.Height)
	{
		FilmHeight = FilmWidth * ((f32)Image.Height / (f32)Image.Width);
	}
	else if (Image.Height > Image.Width)
	{
		FilmWidth = FilmHeight * ((f32)Image.Width / (f32)Image.Height);
	}

	f32 HalfFilmWidth = 0.5*FilmWidth;
	f32 HalfFilmHeight = 0.5*FilmHeight;
	v3 FilmCenter = CameraPos - (FilmDist*CameraZ);
	
	
	u32 *Out = Image.Pixels;


	//setting the ray tracer for camera positions and ray tracing 
	//on the plane
	for (u32 y = 0; y < Image.Height; ++y)
	{
		f32 FilmY = -1.0f + 2.0f*((f32)y / (f32)Image.Height);
		for (u32 x = 0; x < Image.Width; ++x)
		{
			f32 FilmX = -1.0f + 2.0f*((f32)x / (f32)Image.Width);
			
			v3 FilmPos = FilmCenter + (FilmX * HalfFilmWidth*CameraX + FilmY * HalfFilmHeight*CameraY);
			//shoot the rays now
			v3 RayOrigin = CameraPos;//rays start at the camera location
			v3 RayDirection = NOZ(FilmPos - CameraPos);
			
			v3 Color = RayCast(&World, RayOrigin, RayDirection);
			//also need to pack the color we receive back. Color comeback
			//so we have to convert the color back.
			v4 BMPColor = V4(255.0f*Color, 255.0f);//Passing RGBA values to the BMPColor
			u32 BMPValue = BGRAPack4x8(BMPColor);//Getting BMP values after packing them into RGBA
												 //Bitmap values were opposite because of Endianess.
												//So I changed them to BGRApack because of this.

			
			*Out++ = BMPValue; //Previously it was a default image value now. We are now passing the actual BITMAP COLOR VALUES
		}
		if((y%64) ==0)
		{
			printf("\rRaycasting row %d%%....",100*y / Image.Height);
			fflush(stdout);
		}
		
	}

	WriteImage(Image, "test.bmp");//getting the raytraced image plane on test.bmp.
	
	printf("\nDone.....\n");

	return(0);
}

