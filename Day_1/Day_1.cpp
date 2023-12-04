

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

#include "filehandlers.hpp"


//std::vector<std::string> ExtractCalibrationValues(std::vector<std::string> input);
//int getCalibrationValue(std::vector<std::string> CalibrationDigits);

int main()
{

    std::vector<std::string> inputData = openFile("Calibration.txt");
    
   // printInputData(inputData);
    std::vector<std::string> test{ "57eight9fivefiveeight" };
    auto noLetters = replaceLetters(test);

   printInputData(noLetters);
   auto values = ExtractCalibrationValues(noLetters);
    printInputData(values);
   std::cout << getCalibrationValue(values)      << std::endl;
    //std::cout << std::isalnum('1') << "\n";


}

