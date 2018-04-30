#ifndef concept234_HPP
#define concept234_HPP

#include <iostream>
#include <string.h>
#include "concept4.hpp"
#include "periodDetection.hpp"
#include <exception>
#include "definitions.hpp"

template<class data>
class infinitFP
{
public:
  inline infinitFP(std::string inputValue)
  {
    std::string modInputValue; // this variable is for the inputValue without a point
    unsigned long long counter = 0; // this variable is for the pointPosition
    unsigned long long i = 0; //this is the index with which we access to the indexes of modInputValue and inputValue
    while(i < inputValue.length())
    {
      if(inputValue[i]=='.')
      {
        i++;
        break;
      }
      else
      {
        modInputValue += "0";
        modInputValue[modInputValue.length()-1] = inputValue[i];
      }
      i++;
      counter++;
    }
    while(i < inputValue.length())
    {
      modInputValue += "0";
      modInputValue[i-1] = inputValue[i];
      //DEBUG std::cout << "modInputValue = "+modInputValue << " i = " << i << "\n";
      i++;
    }
    // these while loops are removing the point from the input string and preparing it for saving the position of the point in pointPosition
    this->pointPosition = (counter != inputValue.length()) ? inputValue.length()-counter-1 : 0; //this line is saving the point position into the pointPosition variable
    this->value = data(modInputValue);
  }
  inline infinitFP()
  {
    this->pointPosition = 0;
    this->value = data("0");
  }
  inline std::string getStringValue()
  {
    std::string ret2 = this->value.getStringValue();
    if(this->pointPosition == 0)
    {
      return ret2;
    }
    //DEBUG std::cout << "no error0\n";
    std::string ret3;
    //DEBUG std::cout << "no error1\n";
    if(ret2.length() <= this->pointPosition || ((ret2.length() <= (unsigned long long)this->pointPosition+1) && ret2[0] == '0'))
    {
      ret3 = ret2;
      int i0 = this->pointPosition - ret2.length();
      while(i0 >= 0)
      {
        ret3 = "0" + ret3;
        i0--;
      }
      ret3[0] = '.';
      ret3 = "0" + ret3;
      return ret3;
    }
    //DEBUG std::cout << "no error2\n";
    int i3 = ret2.length()-1;
    while(i3 >= 0)
    {
      if(i3 == ((ret2.length()-1) - this->pointPosition))
      {
        ret3 = "0" + ret3;
        ret3[0] = '.';
        break;
      }
      ret3 = "0" + ret3;
      ret3[0] = ret2[i3];
      i3--;
    }
    //DEBUG std::cout << "no error3\n";
    while(i3 >= 0)
    {
      ret3 = "0" + ret3;
      ret3[0] = ret2[i3];
      i3--;
      //DEBUG std::cout << "no error4 "<< i3 << "  " << ret3 << "\n";
    }
    std::string ret4;
    bool yetZero2 = true;
    //DEBUG std::cout << "no error5\n";
    for(unsigned int i4 = 0; i4 < ret3.length(); i4++)
    {
      if(yetZero2)
      {
        if(ret3[i4] == '0')
        {
          continue;
        }
        ret4 += "0";
        ret4[ret4.length()-1] = ret3[i4];
        yetZero2 = false;
        continue;
      }
      ret4 += "0";
      ret4[ret4.length()-1] = ret3[i4];

    }
    return ret4;
  }
  /*inline infinitFP<data> pointConvert(unsigned int newPointPosition)
  {
    if(newPointPosition < this->pointPosition)
    {
      std::cerr << "error in memberfunction infinitFP::pointConvert :" <<
      "the new pointPosition is lower than the pointPosition of the current"
      <<" object (infinitFP<data>* this)\n";
    }
    if(newPointPosition == this->pointPosition)
    {
      return *this;
    }
    unsigned long long exp = newPointPosition - pointPosition;
    infinitFP<data> ten("10");
    infinitFP<data> ret("0");
    ret = *this;
    ret.pointPosition = newPointPosition;
    ret = ret * ten;
    std::cout << "no error1\n";
    std::cout << "pointConvert1  this = " << this->getStringValue() << "\n";
    //DEBUG std::cout << "no error2\n";
    std::cout << "                ret = " << ret.getStringValue() << "\n";
    //DEBUG std::cout << "no error3\n";
    std::cout << "                ten = " << ten.getStringValue() << "\n";
    std::cout << "                exp = " << ten.getStringValue() << "\n";
    std::cout << " this.pointPosition = " << this->pointPosition << "\n";
    std::cout << "  ret.pointPosition = " << ret.pointPosition << "\n";
    std::cout << "   newPointPosition = " << newPointPosition << "\n";
    //DEBUG std::cout << "no error8\n";
    for(unsigned long long tempExp = 1; tempExp < exp; tempExp++)
    {
      ret = ret * ten;
      std::cout << "                ret = " << ret.getStringValue() << "\n";
    }
    //DEBUG std::cout << "no error9\n";
    std::cout << "                ret = " << ret.getStringValue() << "\n";
    //std::cout << "pointConvert1 ret = "<< ret.getStringValue() << " this = " <<
    //this->getStringValue() << " exp = " << exp << " powOfTen = " << powOfTen.getStringValue() << "\n";
    return ret;
  }*/
  inline infinitFP<data> pointConvert(unsigned int newPointPosition)
  {
    if(newPointPosition < this->pointPosition)
    {
      std::cerr << "the new pointPosition is lesser than the current pointPosition\n";
      throw std::exception();
    }
    if(this->pointPosition == newPointPosition){return *this;}
    infinitFP<data> ten("10");
    infinitFP<data> ret = *this;
    ret.pointPosition = newPointPosition;
    unsigned exp = newPointPosition - this->pointPosition;
    //DEBUG std::cout << "pointConvert1 exp = " << exp << " this.pointPosition = " << this->pointPosition << " newPointPosition = " << newPointPosition << "\n";
    while (exp > 0) {
      //DEBUG std::cout << "              exp = " << exp << "\n";
      //DEBUG std::cout << "no error0\n";
      //DEBUG std::cout << "before mul\n";
      ret = ret * ten;
      //DEBUG std::cout << "after mul\n";
      //DEBUG std::cout << "no error1\n";
      exp--;
    }
    /*if(error)
    {
      std::cerr << "the pointconvertion is impossible because there are not enough bits available\n";
      error = false;
      throw std::exception();
    }*/
    return ret;
  }
  inline void operator = (infinitFP<data> equal)
  {
    this->pointPosition = equal.pointPosition;
    this->value = equal.value;
  }
  inline infinitFP<data> operator + (infinitFP<data> operand)
  {
    unsigned short uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    /*if(convertThis != *this)
    {
      std::cerr << "pointconvertion failed\n";
    }*/
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    infinitFP<data> ret("1");
    ret.pointPosition = uniquePointPosition;
    //DEBUG std::cout << "add1 ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " convertThis = " << convertThis.getStringValue() << " operand = "
    //DEBUG << operand.getStringValue() << " convertOperand = " << convertOperand.getStringValue() << '\n';
    ret.value = convertThis.value + convertOperand.value;
    //DEBUG std::cout << "add2 ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " convertThis = " << convertThis.getStringValue() << " operand = "
    //DEBUG << operand.getStringValue() << " convertOperand = " << convertOperand.getStringValue() << '\n';
    //DEBUG std::cout << "add1ret = " << ret.getStringValue() << "\n";
    //DEBUG std::cout << " convertThis = " << convertThis.getStringValue() << "\n";
    //DEBUG std::cout << " convertOperand = " << convertOperand.getStringValue() << "\n";
    //DEBUG std::cout << " this = " << this->getStringValue() << "\n";
    //DEBUG std::cout << " operand = " << operand.getStringValue() << "\n";
    if(error)
    {
      std::cerr << "error in memberfunction infinitFP::operator+ : the result of the addition of the two inputs doesn't fit in the num of bits\n";
      error = false;
      throw std::exception();
    }
    return ret;
  }
  inline infinitFP<data> operator - (infinitFP<data> operand)
  {
    unsigned short uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    infinitFP<data> ret("1");
    ret.pointPosition = uniquePointPosition;
    //DEBUG std::cout << (int)uniquePointPosition << "  " << (int)ret.pointPosition << "\n";
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << "\n";
    ret.value = convertThis.value - convertOperand.value;
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << "\n";
    //DEBUG std::cout << ret.value.value << " ret = " << ret.getStringValue() << "\n";
    //DEBUG std::cout << "sub1 ret = " << ret.getStringValue() << "\n";
    if(error)
    {
      std::cerr << "error in memberfunction infinitFP::operator- : the result will be not right because this datatype can't represent negative values\n";
      error = false;
      throw std::exception();
    }
    return ret;
  }
  inline infinitFP<data> operator * (infinitFP<data> operand)
  {
    data zero("0");
    if(this->value == zero || operand.value == zero)
    {
      return infinitFP<data>();
    }
    infinitFP<data> ret;
    ret.pointPosition = this->pointPosition + operand.pointPosition;
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << "\n";
    ret.value = this->value * operand.value;
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << "\n";
    //DEBUG std::cout << "mul1 ret = " << ret.getStringValue() << "\n";
    //DEBUG std::cout << "    this = " << this->getStringValue() << "\n";
    //DEBUG std::cout << " operand = " << operand.getStringValue() << "\n";
    if(error)
    {
      std::cerr << "error in memberfunction infinitFP::operator* : the result of the multiplication of the two inputs doesn't fit in the " << value.getSize() << "bit\n";
      error = false;
      throw std::exception();
    }
    return ret;
  }
  inline infinitFP<data> pointLeftShift(unsigned short in)
  {
    infinitFP<data> ret = *this;
    if(((unsigned short)(0-1)-this->pointPosition) >= in)
    {
      ret.pointPosition += in;
      return ret;
    }
    else {
      std::cerr << "error in memberfunction infinitFP::pointLeftShift : Can't shift the point because there would be an overflow an the complete program would go wrong!\n";
      return ret;
    }
  }
  inline infinitFP<data> divisionWithoutPoint(infinitFP<data> operand)
  {
    //DEBUG std::cout << "begin of ifs\n";
    if(operand == (*this))
    {
      return infinitFP<data>("1");
    }
    else if((*this) < operand || this->value.firstSignificantIndex() == this->value.getSize())
    {
      return infinitFP<data>();
    }
    else if(operand.value.firstSignificantIndex() == operand.value.getSize())
    {
      std::cerr << "error in memberfunction infinitFP::divisionWithoutPoint : you can't divide with zero\n";
      throw std::exception();
    }
    else if(operand.value == data("1") && operand.pointPosition == 0)
    {
      return *this;
    }
    //DEBUG std::cout << "begin of dwp\n";
    unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    infinitFP<data> ret("0");
    infinitFP<data> one("1");
    //DEBUG std::cout << "before sub\n";
    //DEBUG std::cout << "convertThis = " << convertThis.getStringValue() << " convertOperand = " << convertOperand.getStringValue() << "\n";
    convertThis.value = convertThis.value - convertOperand.value;
    //DEBUG std::cout << "after sub\n";
    bool whileError = error;
    bool localError;
    while(!whileError)
    {
      convertThis.value = convertThis.value - convertOperand.value;
      whileError = error;
      //DEBUG std::cout << "while" << error << whileError << "\n";
      ret = ret + one;
      localError = error;
    }
    if(localError)
    {
      std::cerr << "error in memberfunction infinitFP::divisionWithoutPoint : result is too high\n";
      throw std::exception();
    }
    error = false;
    //DEBUG std::cout << "end of dwp\n";
    return ret;
  }
  /*inline infinitFP<data> operator % (infinitFP<data> operand)
  {
    //DEBUG std::cout << "before div\n";
    infinitFP<data> ret = this->divisionWithoutPoint(operand);
    //DEBUG std::cout << "after div\n";
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " operand = " << operand.getStringValue() << "\n";
    ret = ret * operand;
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " operand = " << operand.getStringValue() << "\n";
    ret = (*this) - ret;
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " operand = " << operand.getStringValue() << "\n";
    return ret;
    //return (*this) - ((this->divisionWithoutPoint(operand))*operand);
  }*/
  inline infinitFP<data> operator % (infinitFP<data> operand)
  {
    if(operand == (*this) || this->value.firstSignificantIndex() == this->value.getSize() || (operand.value == data("1") && operand.pointPosition == 0))
    {
      return infinitFP<data>("0");
    }
    else if(operand.value.firstSignificantIndex() == operand.value.getSize())
    {
      std::cerr << "error in memberfunction infinitFP::divisionWithoutPoint : you can't divide with zero\n";
      throw std::exception();
    }
    unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    infinitFP<data> one("1");
    infinitFP<data> oldConvertThis("0");
    //DEBUG std::cout << "before sub\n";
    //DEBUG std::cout << "convertThis = " << convertThis.getStringValue() << " convertOperand = " << convertOperand.getStringValue() << "\n";
    oldConvertThis = convertThis;
    convertThis.value = convertThis.value - convertOperand.value;
    //DEBUG std::cout << "after sub\n";
    bool whileError = error;
    while(!whileError)
    {
      oldConvertThis = convertThis;
      convertThis.value = convertThis.value - convertOperand.value;
      whileError = error;
      //DEBUG std::cout << "while" << error << whileError << "\n";
    }
    convertThis = oldConvertThis;
    error = false;
    return convertThis;
  }
  inline infinitFP<data> pow(infinitFP<data> operand)
  {
    infinitFP<data> ret("1");
    infinitFP<data> one("1");
    infinitFP<data> zero("0");
    while (operand > zero)
    {
      ret = ret * (*this);
      operand = operand - one;
    }
    error = false;
    return ret;
  }
  inline infinitFP<data> factorial()
  {
    if(this->pointPosition != 0)
    {
      std::cerr << "error in meberfunction infinitFP::fakul : Cannot calculate the factorial of a number, which has a point!\n";
      throw std::exception();
    }
    infinitFP<data> one("1");
    if(this->value.firstSignificantIndex() == this->value.getSize() || *this == one)
    {
      return one;
    }
    error = false;
    return *this * ((*this - one).factorial());
  }
  inline bool operator > (infinitFP<data> operand)
  {
    unsigned short uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    return convertThis.value > convertOperand.value;
  }
  inline bool operator < (infinitFP<data> operand)
  {
    //DEBUG std::cout << "begin of cmp\n";
    unsigned short uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    bool ret = convertThis.value < convertOperand.value;
    //DEBUG std::cout << "end of cmp\n";
    return ret;
  }
  inline bool operator == (infinitFP<data> operand)
  {
    unsigned short uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    return convertThis.value == convertOperand.value;
  }
  inline bool operator != (infinitFP<data> operand)
  {
    unsigned short uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    return convertThis.value != convertOperand.value;
  }
  inline bool operator >= (infinitFP<data> operand)
  {
    unsigned short uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    return convertThis.value >= convertOperand.value;
  }
  inline bool operator <= (infinitFP<data> operand)
  {
    unsigned short uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
    infinitFP<data> convertThis = this->pointConvert(uniquePointPosition);
    infinitFP<data> convertOperand = operand.pointConvert(uniquePointPosition);
    return convertThis.value <= convertOperand.value;
  }
  infinitFP<data> operator / (infinitFP<data> operand)
  {
    if(periodDetection)
    {
      periodDivisionVector<infinitFP<data> > periodDetector;
      periodDivisionElement<infinitFP<data> > mem;
      //DEBUG std::cout << "before dwp\n";
      infinitFP<data> ret = this->divisionWithoutPoint(operand);
      //error = false;
      infinitFP<data> moduloResult = (*this) % operand;
      //DEBUG std::cout << "moduloResult = " << moduloResult.getStringValue() << "\n";
      //error = false;
      infinitFP<data> zero("0");
      infinitFP<data> ten("10");
      infinitFP<data> divisionMem;
      unsigned char tenExponent = 1;
      //DEBUG std::cout << "no error 1\n";
      while(moduloResult != zero)
      {
        //DEBUG std::cout << "no error0\n";
        divisionMem = moduloResult * ten;
        //error = false;
        //DEBUG std::cout << "no error1\n";
        moduloResult = divisionMem % operand;
        //error = false;
        //DEBUG std::cout << "no error2\n";
        mem.remainder = moduloResult;
        divisionMem = divisionMem.divisionWithoutPoint(operand);
        //error = false;
        mem.result = divisionMem;
        //DEBUG std::cout << "no error3\n";
        if(periodDetector.is_in(mem))
        {
          std::cerr << "error in memberfunction infinitFP::operator/ : the program has detected a period which is produced by an operation the current return value which won't be returned is: " << ret.getStringValue() << " and the period is: " << periodDetector.getAllResults(mem) << "\n";
          break;
        }
        periodDetector.append(mem);
        //DEBUG std::cout << mem.result.getStringValue() << "  " << mem.remainder.getStringValue() << "\n"; //DEBUG
        divisionMem = divisionMem.pointLeftShift(tenExponent);
        //DEBUG std::cout << "div1ret = " << ret.getStringValue() << " divisionMem = " << divisionMem.getStringValue() << "\n";
        ret = ret + divisionMem;
        //error = false;
        //DEBUG std::cout << "div2ret = " << ret.getStringValue() << " divisionMem = " << divisionMem.getStringValue() << "\n";
        tenExponent++;
      }
      error = false;
      return ret;
    }
    else
    {
      infinitFP<data> ret = this->divisionWithoutPoint(operand);
      //error = false;
      infinitFP<data> moduloResult = (*this) % operand;
      //error = false;
      infinitFP<data> zero("0");
      infinitFP<data> ten("10");
      infinitFP<data> divisionMem;
      unsigned char tenExponent = 1;
      //DEBUG std::cout << "no error 1\n";
      while(moduloResult != zero)
      {
        divisionMem = moduloResult * ten;
        //error = false;
        moduloResult = divisionMem % operand;
        //error = false;
        divisionMem = divisionMem.divisionWithoutPoint(operand);
        //error = false;
        divisionMem = divisionMem.pointLeftShift(tenExponent);
        ret = ret + divisionMem;
        //error = false;
        //DEBUG std::cout << "no error " << (int)tenExponent << "\n";
        //DEBUG std::cout << ret.getStringValue() << "\n";
        tenExponent++;
      }
      error = false;
      return ret;
    }
  }
  data value;
  unsigned short pointPosition;
};



#endif
