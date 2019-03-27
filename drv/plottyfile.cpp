#include "plottyfile.h"

void PlottyFile::prepStr(std::string& str, uint8_t len)
{
	if(str.length() > len)
		throw std::runtime_error("Zu grosser String.");
		
	if(str.length() != len)
		str += '\n';
	
	while(str.length() < len)
		str += '\0';
}

void PlottyFile::writeToFile(std::string filename)
{
	
	command = 0x1D;
	title = "HTWK-HWLab";
	filetype = "MD";
	version = 1;
	subversion = 0;
	function_type = 'C';
	quadrant = 1;
	ref_x = 5000;
	ref_y = 50;
	para_first = 1;
	para_stepwidth = 1;
	unit_x = "Unit X";
	desc_x = "Desc X";
	unit_y = "Unit Y";
	desc_y = "Desc Y";
	unit_para = "Unit P";
	desc_para = "Desc P";
	
	prepStr(title, 10);
	prepStr(unit_x, 10);
	prepStr(desc_x, 20);
	prepStr(unit_y, 10);
	prepStr(desc_y, 20);
	prepStr(unit_para, 10);
	prepStr(desc_para, 20);
	
	std::ofstream file(filename);
	file.write(reinterpret_cast<char*>(&command), 1);
	file.write(title.c_str(), title.length());
	file.write(filetype.c_str(), 2);
	file.write(reinterpret_cast<char*>(&version), 2);
	file.write(reinterpret_cast<char*>(&subversion), 2);
	file.write(reinterpret_cast<char*>(&function_type), 1);
	file.write(reinterpret_cast<char*>(&quadrant), 1);
	file.write(reinterpret_cast<char*>(&ref_x), 2);
	file.write(reinterpret_cast<char*>(&ref_y), 2);
	file.write(reinterpret_cast<char*>(&para_first), 2);
	file.write(reinterpret_cast<char*>(&para_stepwidth), 2);
	file.write(unit_x.c_str(), unit_x.length());
	file.write(desc_x.c_str(), desc_x.length());
	file.write(unit_y.c_str(), unit_y.length());
	file.write(desc_y.c_str(), desc_y.length());
	file.write(unit_para.c_str(), unit_para.length());
	file.write(desc_para.c_str(), desc_para.length());
	file.write(reinterpret_cast<const char*>(&eof), 1);
	
	while(file.tellp() < 256)
		file.put(0);
		
	for(uint16_t i = 0; i < 1023; i++)
	{
		file.put(i >> 8);
		file.put(i & 0xFF);
		file.put(1);
		file.put(0);
	}
		
	for(uint16_t i = 0; i < 1023; i++)
	{
		file.put((i >> 8) | 128);
		file.put(i & 0xFF);
		file.put(2);
		file.put(0);
	}
	
	file.close();
}
