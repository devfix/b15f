#ifndef PLOTTYFILE_H
#define PLOTTYFILE_H

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include "dot.h"

enum FunctionType
{
	CurveFamily = 'S',
	Curve = 'C',
	Level = 'P'
};	

class PlottyFile
{
public:
	void addDot(Dot& dot);
	void addDot(Dot dot);
	
	void setFunctionType(FunctionType);
	void setQuadrant(uint8_t);
	void setRefX(uint16_t);
	void setRefY(uint16_t);
	void setParaFirstCurve(uint16_t);
	void setParaStepWidth(uint16_t);
	void setUnitX(std::string);
	void setDescX(std::string);
	void setUnitY(std::string);
	void setDescY(std::string);
	void setUnitPara(std::string);
	void setDescPara(std::string);
	
	FunctionType getFunctionType(void) const;
	uint8_t getQuadrant(void) const;
	uint16_t getRefX(void) const;
	uint16_t getRefY(void) const;
	uint16_t getParaFirstCurve(void) const;
	uint16_t getParaStepWidth(void) const;
	std::string getUnitX(void) const;
	std::string getDescX(void) const;
	std::string getUnitY(void) const;
	std::string getDescY(void) const;
	std::string getUnitPara(void) const;
	std::string getDescPara(void) const;
	
	void writeToFile(std::string filename);
private:
	void prepStr(std::string& str, uint8_t len);

	std::vector<Dot> dots;

	int8_t command = 0x1D;
	const std::string head = "HTWK-HWLab";
	const std::string filetype = "MD";
	int16_t version = 1;
	int16_t subversion = 0;
	FunctionType function_type = FunctionType::Curve;
	uint8_t quadrant = 1;
	uint16_t ref_x = 1023;
	uint16_t ref_y = 1023;
	uint16_t para_first = 1;
	uint16_t para_stepwidth = 1;
	std::string unit_x;
	std::string desc_x;
	std::string unit_y;
	std::string desc_y;
	std::string unit_para;
	std::string desc_para;
	const uint8_t eof = 0xD;
	
	constexpr static uint8_t STR_LEN_SHORT = 10;
	constexpr static uint8_t STR_LEN_LARGE = 20;
};

#endif // PLOTTYFILE_H
