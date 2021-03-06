#ifndef PLOTTYFILE_H
#define PLOTTYFILE_H

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <stdexcept>
#include "dot.h"

enum FunctionType
{
    CurveFamily = 'S',
    Curve = 'C',
    Level = 'P'
};

/*! Wrapper class for convenient plot file creation, needed to display graphs using plotty. */

class PlottyFile
{
public:
    /**
     * Adds a dot to the plotty file.
     * \param dot the dot
     */
    void addDot(Dot& dot);

    /**
     * Adds a dot by reference to the plotty file.
     * \param dot the dot
     */
    void addDot(Dot dot);

    /**
     * Sets the FunctionType of this plotty file.
     * \param function_type enum value
     */
    void setFunctionType(FunctionType function_type);

    /**
     * Sets the quadrant of this plot.
     * \param quadrant quadrant number (1..4)
     */
    void setQuadrant(uint8_t quadrant);

    /**
     * Sets reference (max) value of the x axis
     * \param ref_x reference value
     */
    void setRefX(uint16_t ref_x);

    /**
     * Sets reference (max) value of the y axis
     * \param ref_y reference value
     */
    void setRefY(uint16_t ref_y);

    /**
     * Sets initial value of the parameter.
     * Gets used together with the stepwith to label the curves.
     * \param para_first initial parameter value
     */
    void setParaFirstCurve(uint16_t para_first);

    /**
     * Sets the stepwith the parameter got increased with each curve.
     * \param para_stepwidth parameter stepwith
     */
    void setParaStepWidth(uint16_t para_stepwidth);

    /**
     * Sets the unit of the x axis.
     * \param unit_x unit identifier
     */
    void setUnitX(std::string unit_x);

    /**
     * Sets the description of the x axis.
     * \param desc_x description
     */
    void setDescX(std::string desc_x);

    /**
     * Sets the unit of the y axis.
     * \param unit_y unit identifier
     */
    void setUnitY(std::string unit_y);

    /**
     * Sets the description of the y axis.
     * \param desc_y description
     */
    void setDescY(std::string desc_y);

    /**
     * Sets the unit of the parameter.
     * \param unit_para unit identifier
     */
    void setUnitPara(std::string unit_para);

    /**
     * Sets the description of the parameter.
     * \param desc_para description
     */
    void setDescPara(std::string desc_para);



    /**
     * \return the FunctionType
     */
    FunctionType getFunctionType(void) const;

    /**
     * \return the quadrant number
     */
    uint8_t getQuadrant(void) const;

    /**
     * \return x reference (max) value
     */
    uint16_t getRefX(void) const;

    /**
     * \return y reference (max) value
     */
    uint16_t getRefY(void) const;

    /**
     * \return initial parameter value
     */
    uint16_t getParaFirstCurve(void) const;

    /**
     * \return parameter stepwith
     */
    uint16_t getParaStepWidth(void) const;

    /**
     * \return unit of x axis
     */
    std::string getUnitX(void) const;

    /**
     * \return description of x axis
     */
    std::string getDescX(void) const;

    /**
     * \return unit of y axis
     */
    std::string getUnitY(void) const;

    /**
     * \return description of y axis
     */
    std::string getDescY(void) const;

    /**
     * \return unit of parameter
     */
    std::string getUnitPara(void) const;

    /**
     * \return description of parameter
     */
    std::string getDescPara(void) const;


    /**
     * Saves the PlottyFile in a binary format, ready to open with plotty.
     * \param filename desired plot path
     */
    void writeToFile(std::string filename);

    /**
     * Starts plotty with a plot file.
     * \param filename plot path
     */
    void startPlotty(std::string filename);
private:
    void prepStr(std::string& str, uint8_t len);

    std::vector<Dot> dots;

    int8_t command = 0x1D; //!< command for file header
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
    std::string unit_x; //!< unit name for x-axis
    std::string desc_x; //!< description for x-axis
    std::string unit_y; //!< unit name for y-axis
    std::string desc_y; //!< description for y-axis
    std::string unit_para; //!< unit name for parameter
    std::string desc_para; //!< description for parameter
    const uint8_t eof = 0xD; //!< end of file, but only marks end of header

    constexpr static uint8_t STR_LEN_SHORT = 10; //!< string length for short string in header
    constexpr static uint8_t STR_LEN_LARGE = 20; //!< string length for large string in header
};

#endif // PLOTTYFILE_H
