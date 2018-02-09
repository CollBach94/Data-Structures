/**
* @ProgramName: Program-1
* @Author: Collin Bachman
* @Description:
*     This program reads in images stored as rgb values in a
*     space defined file format. Once read in, the program is 
*     capable of flipping the image vertically or horizontally or
*     turning the image grayscale before 
* @Course: 1063 Data Structures
* @Semester: Spring 2018
* @Date: 09 02 2018
*/
/**
* TXT Image Manipulation Starter
*
* This code is a simple way to read in color information stored in a space
* delimited txt format. The expected file format is:
*                ---------------------------
*                | width height            |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                ---------------------------
* So a 10x10 img would have 11 total rows, 10 rows of data, with 30 values in row.
*/

#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

/**
Structure to hold an rgb value
*/
struct rgb {
	int r;
	int g;
	int b;
};

/**
* @FunctionName: flipVert
* @Description:
*     Loops through a 2D array, copying values from bottom to
	  top into a new array, flipping the data vertically.
	  The values in the new array are then copied into the
	  old array, overwritting the old data.
* @Params:
*    rgb** image - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* @Returns:
*    void
*/
void flipVert(rgb** image, int width, int height) {
	//Creating an array (ArrayVert) to copy image into
	rgb **ArrayVert;
	ArrayVert = new rgb*[height];
	for (int i = 0; i < height; i++) {
		ArrayVert[i] = new rgb[width];
	}
	//Copying values from image to ArrayVert
	//reding in data from bottom to top
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			ArrayVert[height - 1 - i][j].r = image[i][j].r;
			ArrayVert[height - 1 - i][j].g = image[i][j].g;
			ArrayVert[height - 1 - i][j].b = image[i][j].b;
		}
	}
	//Overwriting the image array with ArrayVert data
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			image[i][j].r = ArrayVert[i][j].r;
			image[i][j].g = ArrayVert[i][j].g;
			image[i][j].b = ArrayVert[i][j].b;
		}
	}
}

/**
* @FunctionName: flipHoriz
* @Description:
*     Loops through a 2D array, copying values from right to
	  left into a new array, flipping the data horizontally.
	  The values in the new array are then copied into the 
	  old array, overwritting the old data.
* @Params:
*    rgb** image - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* @Returns:
*    void
*/
void flipHoriz(rgb** image, int width, int height) {
	//Creating an array (ArrayHiriz) to copy imgage into
	rgb **ArrayHoriz;
	ArrayHoriz = new rgb*[height];
	for (int i = 0; i < height; i++) {
		ArrayHoriz[i] = new rgb[width];
	}
	//Copying values from image to ArrayVert
	//Reading in data from right to left
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			ArrayHoriz[i][width - 1 - j].r = image[i][j].r;
			ArrayHoriz[i][width - 1 - j].g = image[i][j].g;
			ArrayHoriz[i][width - 1 - j].b = image[i][j].b;
		}
	}
	//Overwritting data in image with ArrayHoriz data
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			image[i][j].r = ArrayHoriz[i][j].r;
			image[i][j].g = ArrayHoriz[i][j].g;
			image[i][j].b = ArrayHoriz[i][j].b;
		}
	}
}

/**
* @FunctionName: grayScale
* @Description:
*     Loops through a 2D array and 
*	  turns every RGB value into its grayscale equivalent.
* @Params:
*    rgb** image - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* @Returns:
*    void
*/
void grayScale(rgb** image, int width, int height) {
	//Value for temporarily storing Gray calc
	int Gray;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//Gray is determined by adding .r, .g, .b of each location
			//before dividing by three.
			Gray = (image[i][j].r + image[i][j].g + image[i][j].b)/3;
			//Setting .r, .g, .b to equal gray.
			image[i][j].r = Gray;
			image[i][j].g = Gray;
			image[i][j].b = Gray;
		}
	}
}

int main() {
	ifstream ifile;          //Input / output files
	ofstream ofile;
	ifile.open("bot.txt");
	ofile.open("bot2.txt");

	int width;               //width of image
	int height;              //height of image

	rgb **imgArray;         //Pointer var for our 2D array because we         
							//don't know how big the image will be!

	ifile >> width >> height;   //Read in width and height from top of input 
								//file. We need this so we can make the array
								//the right size. After we get these two values
								//we can now allocate memory for our 2D array.

	imgArray = new rgb*[height];    //This array points to every row

	for (int i = 0; i<height; i++) {
		imgArray[i] = new rgb[width]; //Now allocate each row of rgb's
	}

	//Read the color data in from our txt file
	for (int i = 0; i<height; i++) {
		for (int j = 0; j<width; j++) {
			ifile >> imgArray[i][j].r >> imgArray[i][j].g >> imgArray[i][j].b;
		}
	}
	//We could make any changes we want to the color image here

	//Function call to grayScale (Makes image grayscale)
	grayScale(imgArray, width, height);
	//Function call to flipVert (Flips image Vertically)
	flipVert(imgArray, width, height);
	//Function call to flipHoriz (Flips image Horizontally)
	flipHoriz(imgArray, width, height);


	//Write out our color data to a new file
	ofile << width << " " << height << endl;
	for (int i = 0; i<height; i++) {
		for (int j = 0; j<width; j++) {
			//Output split into 2 lines to avoid column limit
			ofile << imgArray[i][j].r << " " << imgArray[i][j].g 
				<< " " << imgArray[i][j].b << " "; 
		}
		ofile << endl;
	}


	return 0;
}