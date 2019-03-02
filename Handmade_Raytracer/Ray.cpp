//setting up the bitmap header for displaying the ray traced images.
#include<stdio.h>
#include<stdint.h>
#include<cstdlib>
#include<fstream>
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

int main(int ArgCount, char **Args)
{
	//return material 0 to ray trace a color when the 
	//ray tracer hits nothing
	material Materials[2] = {};
	Materials[0].color = V3(0, 0, 0);//the error for no suitable constructor from int to v3. Solved by defining functions for v2,v3 and v4 in ray_math.h
	Materials[1].color = V3(1, 0, 0);

	//definin the plane for ray tracing the plane.
	//the plane here is pointing up towards z axis
	plane Plane = {};
	Plane.N = V3(0, 0, 1);
	Plane.d = 0;
	Plane.MatIndex = 1;

	world World = {};
	World.MaterialCount = 2;
	World.Materials = Materials;
	World.planeCount = 1;
	World.planes = &Plane;
	World.sphereCount = 0;
	World.spheres = 0;


	

	u32 OutputWidth = 1280;
	u32 OutputHeight = 720;
	//creating the image and allocating it
	image_32 Image = AllocateImage(1280, 720);




	//SETTING THE CAMERA POSITIONS AND RAY POINTS TO SHOOT RAYS FROM
	v3 CameraPos = V3(0, 10, 1);
	v3 CameraZ = NOZ(CameraPos);
	v3 CameraX = NOZ(Cross(CameraZ, V3(0, 0, 1)));
	v3 CameraY = NOZ(Cross(CameraZ, CameraX));


	u32 *Out = Image.Pixels;


	//setting the ray tracer for camera positions and ray tracing 
	//on the plane
	for (u32 y = 0; y < Image.Height; ++y)
	{
		f32 FilmY = -1.0f + 2.0f*((f32)y / (f32)Image.Height);
		for (u32 x = 0; x < Image.Width; ++x)
		{
			f32 FilmX = -1.0f + 2.0f*((f32)x / (f32)Image.Height);
			*Out++ = (y < 32) ? 0xFFFF0000 : 0xFF0000FF;//BITMAP FILES BY DEFAULT START FROM THE BOTTOM ROW and iterating those pixels denoted by *Out.
		}
	}

	WriteImage(Image, "test.bmp");//sets the allocated image to a bitmap file.
	

	


	

	



	return(0);
}
