// PeIL.cxx
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
#include <string>
#include <SOIL/SOIL.h>

// USE : PeIL <img file> <output C file>

// TO DO : Zlib that shit.

int main(int argc, char **argv)
{
	std::string name(argv[1]);
	std::string trueName;
	for(unsigned int i=0; i < name.size(); i++)
	{
		if(name[i] == '.')
			break;
		else
			trueName.push_back(name[i]);
	}
	// Juste pour récupérer le nom sans l'extension de fichier ( tout ce qui est après un point n'est pas conservé ).
	std::cout << trueName << std::endl;
		
	int width, height, channels;
	// On charge l'image.
	unsigned char* image = SOIL_load_image(argv[1], &width, &height, &channels, SOIL_LOAD_AUTO);
	
	std::ofstream output(argv[2], std::ios::out | std::ios::ate);
	if(output)
	{
		output << "// Image : " << name << ", wdith : " << width << ", height : " << height << ", depth : " << channels << std::endl;
		output << "// Name : " << trueName << std::endl;
		output << "unsigned char " << trueName << "[] = {" << std::endl;
		
		for(unsigned int i=0; i < width*height*channels; i++)
		{
			output << (int)image[i] << ","; // On écrit peu à peu chaque composante de chaque pixel.
			if(((i+1) % channels) == 0) // Si on à écrit tout les données d'un pixel, on reviens à la ligne.
				output << std::endl;
		}
		
		output << "};" << std::endl; // C'est un fichier C, il faut donc ne pas oublier de rajouter le retour à la ligne en fin de fichier.
		
		output.close();
	}
	else
		std::cerr << "Unable to create file " << argv[2] << std::endl;
	
	return 0;
}

