// sans titre.cxx
// 
// Copyright 2012 Mael N. <contact@maeln.com>
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.


#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>

using namespace std;

typedef struct
{
	char sign[3];
	int width;
	int height;
	int channels;
	unsigned char* data;
} Image;

int main(int argc, char **argv)
{
	Image img;
	img.sign[0] = 'P';
	img.sign[1] = 'A';
	img.sign[2] = 'K';
	img.data = SOIL_load_image(argv[1], &img.width, &img.height, &img.channels, SOIL_LOAD_AUTO);
	
	ofstream file("test", ofstream::binary);
	if(file.is_open())
	{
		file.write(img.sign, sizeof(img.sign));
		file.write((char*)&img.width, sizeof(img.width));
		file.write((char*)&img.height, sizeof(img.height));
		file.write((char*)&img.channels, sizeof(img.channels));
		file.write((char*)&img.data, sizeof(img.data));
		
		file.close();
	}
	
	return 0;
}

