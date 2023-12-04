
#include <fstream>
#include <map>
#include <algorithm>

std::string findVectorIndex(std::vector<std::string> vector, std::string_view value);

std::vector<std::string> openFile(const char* filename)
{
	std::ifstream dataFromFile{ filename };

	std::string output{};
	std::vector<std::string> calibration{};

	if (!dataFromFile)
	{
		std::cerr <<filename << " file not found" << std::endl;
		return calibration;
	}

	while (dataFromFile >> output)
	{
		calibration.push_back(output);
	}

	return calibration;
}

void printInputData(const std::vector<std::string>& lines)
	{
		for (const auto& str : lines) {
			std::cout << str << "\n";
		}
	}


[[nodiscard]] std::vector<std::string> ExtractCalibrationValues(std::vector<std::string>input)
{
    std::vector<std::string> digits;


    for (auto& str : input) //
    {
        std::string line{}; //new string where we store all the digits

        for (const auto& x : str)
        {
            if (isdigit(x))
            {
                line.push_back(x);      //                
            }
        }

        digits.push_back(line);      

    }
    return digits;
}


int getCalibrationValue(std::vector<std::string> CalibrationDigits)
{
    int result{};

    for (const auto& x : CalibrationDigits)
    {
        std::cout << x << " | "<<result << "\n";
        if (x.length() == 0) { continue; }
        if (x.length() == 1)
        {
            int temp = std::stoi(x);
            result += temp + 10 * temp; // we add 10X to duplicate the digit, eg. 1 +10 = 11, 2+20 = 22

        }
        else if (x.length() == 2)
        {
            result += std::stoi(x);
        }
        else
        {
            result += (x.front() - '0') * 10 + (x.back() - '0'); // substracting - '0' yields the equivalent int            
        }        
    }

    return result;
}

[[nodiscard]] std::vector<std::string> replaceLetters(std::vector<std::string> input)
{
    std::vector<std::string> numbers{ "zero","one","two","three","four","five","six","seven","eight","nine" };

    for (auto& theString : input)
    {
        int index{ 0 };
        std::map<int, std::string> numbersFound;
        auto theStringSize = theString.length();

        for (auto& number : numbers)
        {
            std::string::size_type n;
            //std::vector<int> numbersFound;
            int positionInString = theString.find(number);            

            if (!(positionInString == (std::string::npos)))
            {
                numbersFound[positionInString]= number;                               
                //string.replace(positionInString, number.length(), std::to_string(index));
            }

            index++;
        }

  //      for (auto& number : numbers)
        
           
            if (numbersFound.empty())
            {
                continue;
            }
            else if (numbersFound.size() == 1)
            {
                theString.replace(numbersFound.begin()->first, numbersFound.begin()->second.length(), findVectorIndex(numbers, numbersFound.begin()->second));
            }
            else if (numbersFound.size() == 2)
            {
                auto a1 = numbersFound.begin()->second.length();
                auto a2 = (++numbersFound.begin())->first;
                if (((a1) < a2))
                {
                    auto a = findVectorIndex(numbers, numbersFound.begin()->second);
                    auto b = findVectorIndex(numbers, numbersFound.rbegin()->second);
                    theString.replace(numbersFound.rbegin()->first, numbersFound.rbegin()->second.length(), b);
                    theString.replace(numbersFound.begin()->first, numbersFound.begin()->second.length(),a );                    
                }
                else 
                {
                    auto a = findVectorIndex(numbers, numbersFound.begin()->second);
                    theString.replace(numbersFound.begin()->first, numbersFound.begin()->second.length(), a);
                }
            }
            else
            {
                if (((numbersFound.begin()->second.length() < (numbersFound.rbegin())->first)))
                {
                    theString.replace(numbersFound.rbegin()->first, numbersFound.rbegin()->second.length(), findVectorIndex(numbers, numbersFound.rbegin()->second));
                    theString.replace(numbersFound.begin()->first, numbersFound.begin()->second.length(), findVectorIndex(numbers, numbersFound.begin()->second));
                }
                else
                {
                    theString.replace(numbersFound.begin()->first, numbersFound.begin()->second.length(), findVectorIndex(numbers, numbersFound.begin()->second));
                }
            }            
            std::cout << theString << "\n";
        

    }
    return input;
}

std::string findVectorIndex(std::vector<std::string> vector, std::string_view value)
{
    auto it = std::find(vector.begin(), vector.end(), value);

    return std::to_string(std::distance(vector.begin(), it));
}
