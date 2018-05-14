/* 
   Joseph Reidell
   CS 0449
   Project 1: Image Transformation 
*/

#pragma pack(1)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//This is the Bitmap Image File structure 
struct BMP {
   	short fileID;
	int filesize;
	short reserve1;
	short reserve2;
	int dataoffset;
} BMP;

//This is the Device-Independent Bitmap structure
struct DIB {
	int dibsize;
	int width;
	int height;
	short planes;
	short bitsperpixel;
	int compression;
	int bitmapsize;
	int horizontalres;
	int verticalres;
	int numcolors;
	int importantcolors;
} DIB;

//This is the pixel array structure
struct PIXEL {
	unsigned char b;
	unsigned char g;
	unsigned char r;
};

/*
  The main function takes in two command line arguments
  argc is the first argument that takes in the image transformation 
  argv is the second argument that takes in the filename 
*/

int main(int argc, char *argv[]) {
    	//Char pointers that will split into 8-bit parts
    	char *format[2];
   
    	//structure variable for the color pixels
    	struct PIXEL color;

	//for loop initializers
	int h;
	int w;

	int emptyPadding;
    
    	//Opens the file 
	FILE * bmpImage = fopen(argv[2], "rb+");
    
    	//Checks if the file actually exists
    	if(bmpImage == 0){
           printf("This file does not exist!\n");
           return 0;
    	}
    
   	//Reads in the BMP structure with 14 bytes
	fread(&BMP, 14, 1, bmpImage);
    
   	//Reads in the DIB structure with 40 bytes
	fread(&DIB, 40, 1, bmpImage);
	
	//Splits up into 8 bit parts
	format[0] = BMP.fileID;
	format[1] = BMP.fileID >> 8;
    
    	//Checks for formatting errors 
    	if(strcmp(format, "BM") != 0 || DIB.bitsperpixel != 24 || DIB.dibsize != 40){
           printf("The file is not formatted correctly\n");
           return 0;
    	}
    
	fseek(bmpImage, BMP.dataoffset, SEEK_SET);

	/*
 	  The empty padding equation checks for how many padding bytes 
	  are present.If the row of pixels present are a multiple of 4,
	  it forces the row of pixels to start an offset.
	*/

	emptyPadding = 4 - (DIB.width * 3 % 4);

	if(emptyPadding == 4){
	   emptyPadding = 0;
	}
    
    	//This will check if "-invert" was entered and invert the image
	if(strcmp(argv[1], "-invert") == 0) {
       
	printf("Inverting image\n");
	for(h = 0; h < DIB.height; h++){
		for(w = 0; w < DIB.width; w++){
		   fread(&color, 3, 1, bmpImage);
		   color.b = ~color.b;
		   color.g = ~color.g;
		   color.r = ~color.r;
               
                  fseek(bmpImage, -3, SEEK_CUR);
                  fwrite(&color, 3, 1, bmpImage);
           	}
		
		fseek(bmpImage, emptyPadding, SEEK_CUR);
	   }
	}
	
   	//This will check if "-grayscale" was entered and convert the image to grayscale
	else if(strcmp(argv[1], "-grayscale") == 0){
 
	printf("Grayscaling image\n");

	for(h = 0; h < DIB.height; h++){
		for(w = 0; w < DIB.width; w++){
		 fread(&color, 3, 1, bmpImage);
		 double bColor = ((double) color.b)/255.0;
		 double gColor = ((double) color.g)/255.0;
		 double rColor = ((double) color.r)/255.0;
               
		//This is the equation using the RGB pixels from the image
		 double yValue = .2126*rColor + .7152*gColor + .0722*bColor;
               
		//This starts the grayscaling process

		 if(yValue <= .0031308){
			bColor = 12.92 * yValue;
			gColor = 12.92 * yValue;
			rColor = 12.92 * yValue;
		 }
               
		 else{
			bColor = 1.055 * pow(yValue, 1.0/2.4) - .055;
			gColor = 1.055 * pow(yValue, 1.0/2.4) - .055;
			rColor = 1.055 * pow(yValue, 1.0/2.4) - .055;
                    
		 }
               
		color.b = (unsigned char) (bColor * 255.0);
		color.g = (unsigned char) (gColor * 255.0);
		color.r = (unsigned char) (rColor * 255.0);
               
		fseek(bmpImage, -3, SEEK_CUR);
		fwrite(&color, 3, 1, bmpImage);
               
		}

		 fseek(bmpImage, emptyPadding, SEEK_CUR);
	   }
	}
    
	//If no image transformation is entered, then the program will let you know
    
	else{
	  printf("-invert or -grayscale was not entered into the first command line argument\n");
	  return 0;
	}
    
	//The process is finished and the program terminates
   
	printf("\nImage transformation completed\n");
    

	return 0;
}
