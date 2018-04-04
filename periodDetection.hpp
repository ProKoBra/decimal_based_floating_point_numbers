#ifndef periodDetection_HPP
#define periodDetection_HPP

#include <iostream>
#include <string.h>
#include <vector>

bool periodDetection;

template<class data>
class periodDivisionElement
{
  public:
    inline bool operator == (periodDivisionElement operand)
    {
      return (this->result == operand.result) && (this->remainder == operand.remainder);
    }
    data result;
    data remainder;
};

template<class data>
class periodDivisionVector
{
  public:
    inline periodDivisionElement<data> operator [] (int index)
    {
      //DEBUG std::cout << "operator [] " << value[index].result.getStringValue() << "  " << value[index].remainder.getStringValue() << "\n"
      return value[index];
    }
    inline void append (periodDivisionElement<data> operand)
    {
      this->value.push_back(operand);
      //DEBUG std::cout<< this->value[this->value.size()-1].result.getStringValue() << "        1\n";
    }
    inline bool is_in (periodDivisionElement<data> operand)
    {
      bool ret = false;
      for(int i = 0; i < this->value.size(); i++)
      {
        if(value[i] == operand)
        {
          ret = true;
          break;
        }
      }
      return ret;
    }
    inline std::string getAllResults(periodDivisionElement<data> OnThisIndex)
    {
      std::string ret;
      int i = 0;
      while((i < value.size()) && !(value[i] == OnThisIndex))
      {
        i++;
      }
      //DEBUGstd::cout << i << "\n";
      for(int i2 = i; i2 < value.size(); i2++)
      {
        //DEBUG std::cout << value[i].result.getStringValue() << "  " << i << "  " << i2<<  "\n";
        ret += value[i2].result.getStringValue();
      }
      return ret;
    }
    std::vector<periodDivisionElement<data> > value;
};
#endif
