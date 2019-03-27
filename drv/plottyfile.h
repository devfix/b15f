#ifndef PLOTTYFILE_H
#define PLOTTYFILE_H

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include "dot.h"

class PlottyFile
{
public:
	void addDot(Dot& dot);
	void writeToFile(std::string filename);
private:
	void prepStr(std::string& str, uint8_t len);

	std::vector<Dot> dots;

	int8_t command;
	std::string title;
	std::string filetype;
	int16_t version;
	int16_t subversion;
	uint8_t function_type;
	uint8_t quadrant;
	uint16_t ref_x;
	uint16_t ref_y;
	uint16_t para_first;
	uint16_t para_stepwidth;
	std::string unit_x;
	std::string desc_x;
	std::string unit_y;
	std::string desc_y;
	std::string unit_para;
	std::string desc_para;
	const uint8_t eof = 0xD;
};

#endif // PLOTTYFILE_H
