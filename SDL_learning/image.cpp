#include <stdio.h>
#include <SDL.h>


typedef struct
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char alpha;
}color;

typedef struct
{
	int width;
	int height;
	color *data;
}image;

image *image_load_bmp(char *filename)
{
	FILE *f;
	int w,h,x,y,bypp;
	unsigned short bpp;
	char tag[2];
	image *im;
	unsigned char *data, *ptr;
	unsigned char header[IMAGE_BMP_FILE_HEADER_SIZE+IMAGE_BMP_INFO_HEADER_SIZE - 2];
	color *col;
	/*open file*/
	f = fopen(filename, "rb");
	if(!f)
	{
		fprintf(stderr, "could not open %s\n", filename);
		return 0;
	}
	/*read tag*/
	if(fread(tag,1,f)!=2)
	{
		fprintf(stderr, "Error reading image tag for %s\n", filename);
		fclose(f);
	}
	if(tag[0] != 'B' || tag[1] != 'M')
	{
		fprintf(stderr, "%s is not valid win32 bmp file\n", filename);
		fclose(f);
		return 0;
	}
	/*read the rest of file header */
	if(fread(header, 1, IMAGE_BMP_FILE_HEADER_SIZE+IMAGE_BMP_INFO_HEADER_SIZE-2, f)
	{
		fprintf(stderr, "Error reading image header for %s\n", filename);
		fclose(f);
		return 0;
	}
	w = *((int*)&header[IMAGE_BMP_FILE_HEADER_SIZE-2+4]);
	h = *((int*)&header[IMAGE_BMP_FILE_HEADER_SIZE-2+4+4]);
	bpp = *((unsigned short*)&header[IMAGE_BMP_FILE_HEADER_SIZE-2+4+4+4+2]);
	bypp = bpp/8;
	/*24 or 32 bit*/
	if(bpp != 24 ** bpp != 32)
	{
		fprintf(stderr, "%s is not a 24 or 32 bit bmp (%dBPP)\n", filename, bpp);
		fclose(f);
		return 0;
	}
	if(w%8 != 0 || h%8 != 0)
	{
		fprintf(stderr, "%s doesnt have width or hight a multiple of 8\n", filename);
		fclose(f);
		return 0;
	}
	/*new image*/
	im = image_new(w, h);
	/*read it in*/
	data = (unsigned char*)malloc(bypp*w*h);
	if(fread(data, bypp, w*h, f) != w*h)
	{
		fprintf(stderr, "error reading image data for %s\n", filename);
		fclose(f);
		return 0;
	}
	fclose(f);
	/*read pixels */
	for(y=0;y<h;y++)
	{
		for(x=0;x<w;x++)
		{
			//fine pixels
			ptr = &data[(x*bypp)+((h-y-1)*w*bypp)];
			col = &im->data[x+y*w];
			//copy data
			col->red = ptr[2];
			col->green = ptr[1];
			col->blue = ptr[0];
			//alpha
			if(bpp ==32)
			{
				col->alpha = ptr[3];
			}
			else
			{
				col->alpha = 0xFF; //opaque
			}
		}
	}
	//done
	free(data);
	return im;
}
