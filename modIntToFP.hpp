#ifndef modIntToFP_HPP
#define modIntToFP_HPP

#include <iostream>
#include <string.h>
#include <vector>
#include "stringNumber.hpp"

bool periodDetection;

class modLong
{
  public:
  inline modLong(unsigned long long input)
  {
    this->value = input;
  }
  inline modLong()
  {
    this->value = 0;
  }
  inline void setValueOnIndex(char index, bool value)
  {
    if(index >= 64)
    {
      std::cout << "error in memberfunction modLong::setValueOnIndex : the given index is too high\n";
    }
    else
    {
      if(value != this->operator[](index))
      {
        value ? this->value += modLong::numberOnIndex(index): this->value -= modLong::numberOnIndex(index);
      }
    }
  }
  inline bool operator[](char index)
  {
    if(index < 64)
    {
      unsigned long long numberOnGivenIndex = modLong::numberOnIndex(index);
      unsigned long long ANDresult = this->value & numberOnGivenIndex;
      return ANDresult == 0 ? false : true;
    }
    else
    {
      std::cerr << "error in memberfunction modLong::operator[] : the given index is too high\n";
    }
  }
  unsigned long long value;
  inline static unsigned long long numberOnIndex(char index)
  {
    char realIndex = (index - 63) * -1;
    if(index < 64 && index >= 0)
    {
      if(realIndex == 0)
      {
        return 1;
      }
      unsigned long long ret = 1;
      for(char i = 1; i <= realIndex; i++)
      {
        ret *= 2;
      }
      return ret;
    }
    else
    {
      std::cerr << "error in static function modLong::numberOnIndex : the given index is too high\n";
    }
  }
};

class modFP_64
{
  public:
    inline modFP_64(std::string inputValue="0")
    {
      //DEBUG std::cout << inputValue + "\n";
      /*if()
      std::string inputValue;
      int i0 = inputValue.length()-1;
      bool yetZero = true;
      while(i0 >= 0)
      {
        if(yetZero)
        {
          if(inputValue[i0] == '0')
          {
            continue;
          }
          yetZero = false;

        }
        i0--;
      }*/
      std::string modInputValue; // this variable is for the inputValue without a point
      int counter = 0; // this variable is for the pointPosition
      int i = 0; //this is the index with which we access to the indexes of modInputValue and inputValue
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
          //DEBUG std::cout << "modInputValue = " + modInputValue + " inputValue[" << i << "] = " << inputValue[i] << "\n";
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
      //DEBUG std::cout << "this->pointPosition = " << (short)this->pointPosition << "\n";
      //DEBUG std::cout << decStringtoBinString(modInputValue)+"\n";
      //DEBUG std::cout << "modInputValue = "+modInputValue+"\n";
      this->value = this->binStringToModLong(decStringtoBinString(modInputValue)); //this line is generating the modlong which contains the binary value and saves it
    }
    inline static std::string decStringtoBinString(std::string decString)
    {
      //DEBUG std::cout << "decString = " + decString + "\n";
      std::string ret;
      stringNumber decstringNumber(decString);
      std::string tempRet;
      std::string zerovalue;
      //DEBUG std::cout << decstringNumber.value << " hallo\n"; //DEBUG
      for(int i = 0; i < decString.length(); i++)
      {
        zerovalue += "0";
      }
      stringNumber zero(zerovalue);
      int counter = 0;
      bool overflow;
      while(decstringNumber.value != zero.value)
      {
        //DEBUG std::cout << "while!\n"; //DEBUG
        decstringNumber = decstringNumber.div2(&overflow);
        tempRet += "e";
        tempRet[counter] = overflow+'0';
        counter++;
      }
      //DEBUG std::cout << "tempRet = " << tempRet << "\n"; // DEBUG
      int i1 = 0;
      int i2 = tempRet.length()-1;
      while(i1 < tempRet.length())
      {
        ret+="0";
        //DEBUG std::cout << "ret = " << ret << "\n";
        ret[i1] = tempRet[i2];
        i1++;
        i2--;
      }
      return ret;
    }
    inline modLong binStringToModLong(std::string binString)
    {
      if (binString.length() > 64)
      {
        std::cerr << "error in memberfunction modFP_64::binStringToModLong : the length of binString is not lower or equal than 64\n";
      }

      //DEBUG std::cout << binString+"\n";

      modLong ret;
      for (int i = 0; i < binString.length(); i++)
      {
        /*if(i < (numOfBits-(binString.length())))
        {
          ret.setValueOnIndex(i, false);
          continue;
        }*/
        //DEBUG std::cout << "i = " << i << " binString[" << i << "] = " << binString[i] << "\n";
        ret.setValueOnIndex(i + 64 - binString.length(), (binString[i]-'0'));
      }
      //DEBUG std::cout << ret.value << "\n";
      return ret;
    }
    inline std::string getStringValue()
    {
      //DEBUG std::cout << this->value.value << " beginfunc\n";
      /*DEBUG for(int i = 0; i < this->numOfBits; i++)
      {
        std::cout << this->value[i] << "  " << i << "  " << this->numOfBits << "\n";
      }*/
      //DEBUG std::cout << "no error6\n";
      //DEBUG std::cout << "bitArray[4] = " << this->value[4] << "\n";
      unsigned counter = 0;
      bool* yetZero = new bool;
      *yetZero = true;
      std::string ret;
      if(!(this->value[0])) {
        //DEBUG std::cout << "if\n";
        //DEBUG std::cout << "no error7\n";
        //DEBUG std::cout << this->value.value << " irgfunc\n";
      }

      else {
        //DEBUG std::cout << this->value.value << " irgfunc\n";
        //DEBUG std::cout << "no error7\n";
        *yetZero = false;
        ret+="0";
        ret[counter] = (char)(this->value[0]+'0');
        counter++;
      }
      //DEBUG std::cout << this->value.value << " irgfunc\n";
      int i = 1;
      while(i < 64)
      {
        if(*yetZero)
        {
          if(this->value[i])
          {
            *yetZero = false;
            ret+="0";
            ret[counter] = (char)(this->value[i]+'0');
            //DEBUG std::cout << this->value.value << " whilefunc\n";
            counter++;
          }
          i++;
          //DEBUG std::cout << "if\n";
          continue;
        }
        else {
          ret+="0";
          ret[counter] = (char)(this->value[i]+'0');
          //DEBUG std::cout << this->value.value << " whilefunc\n";
          counter++;
          //DEBUG std::cout << this->value[i] << " = this->value[" << i << "]\n";
          i++;
        }
      }
      //DEBUG std::cout << "this->value.value = " << this->value.value << " irgfunc\n";
      delete yetZero;
      std::string binString = ret;
      //DEBUG std::cout << binString+"\n";//DEBUG
      stringNumber zero("0");
      stringNumber* tempRet = new stringNumber;
      if(binString[0] == '1')
      {
        //DEBUG std::cout << "true\n";
        *tempRet = zero.addOne();
        //DEBUG std::cout << "tempRet->value = " << tempRet->value << "\n"; //DEBUG
      }
      //DEBUG std::cout << "this->value.value = " << this->value.value << " irgfunc\n";
      for(int i2 = 1; i2 < binString.length(); i2++)
      {
        *tempRet = tempRet->mul2();
        //DEBUG std::cout << "tempRet->value = "+tempRet->value+"\n"; //DEBUG
        if(binString[i2] == '1')
        {
          //DEBUG std::cout << "binString[i] = '1'\n"; //DEBUG
          *tempRet = tempRet->addOne();
          //DEBUG std::cout << tempRet->value << "\n";
        }
        //DEBUG std::cout << "end of foriteration\n";
      }
      //DEBUG std::cout << "this->value.value = " << this->value.value << " irgfunc\n";
      //DEBUG std::cout << "tempRet->value = " << tempRet->value << "\n";
      stringNumber ret2 = *tempRet;
      delete tempRet;
      //DEBUG std::cout << "ret2->value = " << ret2.value << "\n";
      //DEBUG std::cout << "this->value.value = " << this->value.value << " irgfunc\n";
      if(this->value.value == 1)
      {
        for(int i = 0; i < this->pointPosition; i++)
        {
          ret2.value = "0" + ret2.value;
        }
      }

      //DEBUG std::cout << "this->value.value = " << this->value.value << " this->pointPosition = " << (int)this->pointPosition << " ret2 = " << ret2.value << "\n";

      if(this->pointPosition == 0)
      {
        //DEBUG std::cout << "this->value.value = " << this->value.value << " endfunc\n";
        return ret2.value;
      }
      std::string ret3;
      if(ret2.value.length() <= this->pointPosition || (ret2.value.length() <= this->pointPosition+1 && ret2[0] == '0'))
      {
        //DEBUG std::cout << "new if\n";
        ret3 = ret2.value;
        int i0 = this->pointPosition - ret2.value.length();
        while(i0 >= 0)
        {
          ret3 = "0" + ret3;
          i0--;
        }
        ret3[0] = '.';
        ret3 = "0" + ret3;
        return ret3;
      }
      int i3 = ret2.value.length()-1;
      //DEBUG std::cout << "no error 10\n";
      while(i3 >= 0)
      {
        if(i3 == ((ret2.value.length()-1) - this->pointPosition))
        {
          ret3 = "0" + ret3;
          ret3[0] = '.';
          //DEBUG std::cout << "if ret3 = " << ret3 << " i3 = " << i3 << "\n";
          break;
        }
        ret3 = "0" + ret3;
        ret3[0] = ret2[i3];
        //DEBUG std::cout << "ret3 = " << ret3 << " i3 = " << i3 << "\n";
        i3--;
      }
      //DEBUG std::cout << "no error 11\n";
      while(i3 >= 0)
      {
        //DEBUG std::cout << "no error 12\n";
        ret3 = "0" + ret3;
        ret3[0] = ret2[i3];
        //DEBUG std::cout << "ret3 = " << ret3 << " i3 = " << i3 << "\n";
        i3--;
      }
      //DEBUG std::cout << "no error 13\n";
      std::string ret4;
      bool yetZero2 = true;
      for(int i4 = 0; i4 < ret3.length(); i4++)
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
      //DEBUG std::cout << "this->value.value = " << this->value.value << " endfunc\n";
      return ret4;
    }
    inline modFP_64 pointConvert(unsigned char newPointPosition)
    {
      if(newPointPosition < this->pointPosition)
      {
        std::cerr << "error in memberfunction modFP_64::pointConvert : the new pointPosition is lower than the pointPosition of the current object (modFP_64* this)\n";
      }
      if(newPointPosition == this->pointPosition)
      {
        return *this;
      }
      char exp = newPointPosition - pointPosition;
      unsigned long long powOfTen = 1;
      for(unsigned char tempExp = 0; tempExp < exp; tempExp++)
      {
        powOfTen*=10;
      }
      modFP_64 ret;
      //DEBUG std::cout << this->value.value << "  " << powOfTen << "  " << this->value.value * powOfTen << "\n";
      ret.value.value = this->value.value * powOfTen;
      ret.pointPosition = newPointPosition;
      return ret;
    }
    inline void operator = (modFP_64 operand)
    {
      //DEBUG std::cout << /*"*this = " << this->getStringValue() << " operand = " << operand.getStringValue() << */" this->value.value = " << this->value.value << " operand.value.value = " << operand.value.value << "\n";
      //DEBUG std::cout << "this->value.value = " << this->value.value << " operand.value.value = " << operand.value.value << "\n";
      this->value.value = operand.value.value;
      //DEBUG std::cout << "this->value.value = " << this->value.value << " operand.value.value = " << operand.value.value << "\n";
      this->pointPosition = operand.pointPosition;
      //DEBUG std::cout << "*this = " << this->value.value << "\n";
    }
    inline modFP_64 operator + (modFP_64 operand)
    {
      unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      modFP_64 ret("1");
      ret.pointPosition = uniquePointPosition;
      ret.value.value = convertThis.value.value + convertOperand.value.value;
      if(ret.value.value < convertThis.value.value)
      {
        std::cerr << "error in memberfunction modFP_64::operator+ : the result of the addition of the two inputs doesn't fit in the 64bit\n";
      }
      return ret;
    }
    /*modFP_64 twoscomplement()
    {
      modFP_64 ret = *this;
      ret.value.value = ~this->value.value;
      ret.value.value = ret.value.value + 1;
      return ret;
    }*/
    inline modFP_64 operator - (modFP_64 operand)
    {
      unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      modFP_64 ret("1");
      ret.pointPosition = uniquePointPosition;
      //DEBUG std::cout << (int)uniquePointPosition << "  " << (int)ret.pointPosition << "\n";
      ret.value.value = convertThis.value.value - convertOperand.value.value;
      //DEBUG std::cout << ret.value.value << " ret = " << ret.getStringValue() << "\n";
      if(ret.value.value > convertThis.value.value)
      {
        std::cerr << "error in memberfunction modFP_64::operator- : the result will be not right because this datatype can't represent negative values\n";
      }
      return ret;
    }
    inline modFP_64 operator * (modFP_64 operand)
    {
      if(this->value.value == 0 || operand.value.value == 0)
      {
        return modFP_64("0");
      }
      unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      modFP_64 ret("1");
      ret.pointPosition = uniquePointPosition+uniquePointPosition;
      ret.value.value = convertThis.value.value * convertOperand.value.value;
      if(ret.value.value < convertThis.value.value)
      {
        std::cerr << "error in memberfunction modFP_64::operator* : the result of the multiplication of the two inputs doesn't fit in the 64bit\n";
      }
      return ret;
    }
    inline modFP_64 operator / (modFP_64 operand);
    inline modFP_64 pointLeftShift(unsigned char in)
    {
      modFP_64 ret = *this;
      if(255-this->pointPosition >= in)
      {
        ret.pointPosition += in;
        return ret;
      }
      else {
        std::cerr << "error in memberfunction modFP_64::pointLeftShift : Can't shift the point because there would be an overflow an the complete program would go wrong!\n";
      }
    }
    inline modFP_64 divisionWithoutPoint(modFP_64 operand)
    {
      if(operand == (*this))
      {
        return modFP_64("1");
      }
      else if(!((*this) > operand) || this->value.value == 0)
      {
        return modFP_64("0");
      }
      else if(operand.value.value == 0)
      {
        std::cerr << "error in memberfunction modFP_64::divisionWithoutPoint : you can't divide with zero\n";
      }
      else if(operand.value.value == 1 && operand.pointPosition == 0)
      {
        return *this;
      }
    	unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      modFP_64 oldConvertThis;
      modFP_64 ret("0");
      modFP_64 one("1");
      oldConvertThis = convertThis;
      convertThis = convertThis - convertOperand;
      while(convertThis < oldConvertThis/* && std::cout << "whilehead convertThis = " << convertThis.getStringValue() << " oldConvertThis = " << oldConvertThis.getStringValue() << "\n"*/)
      {
        //DEBUG std::cout << "0 oldConvertThis = " << oldConvertThis.getStringValue()
        //DEBUG << " convertThis = " << convertThis.getStringValue() << " ret = " << ret.getStringValue() << "\n";
        oldConvertThis = convertThis;
        /*DEBUG std::cout << "1 oldConvertThis = " << oldConvertThis.getStringValue()
        << " convertThis = " << convertThis.getStringValue() << " ret = " << ret.getStringValue() << "\n"; */
      	convertThis.value.value = convertThis.value.value - convertOperand.value.value;
      	ret = ret + one;
        /*DEBUG std::cout << "2 oldConvertThis = " << oldConvertThis.getStringValue()
        << " convertThis = " << convertThis.getStringValue() << " ret = " << ret.getStringValue() << "\n";*/
      }
      return ret;
    }
    inline modFP_64 pow(modFP_64 operand)
    {
      modFP_64 ret("1");
      modFP_64 one("1");
      modFP_64 zero("0");
      while (operand > zero)
      {
        ret = ret * (*this);
        operand = operand - one;
      }
      return ret;
    }
    inline modFP_64 operator % (modFP_64 operand)
    {
      modFP_64 ret = this->divisionWithoutPoint(operand);
      //DEBUG std::cout << "ret = " << ret.getStringValue() << " operand = " << operand.getStringValue() << "\n";
      ret = ret * operand;
      //DEBUG std::cout << "ret = " << ret.getStringValue() << " operand = " << operand.getStringValue() << "\n";
      ret = (*this) - ret;
      //DEBUG std::cout << "ret = " << ret.getStringValue() << " operand = " << operand.getStringValue() << "\n";
      return ret;
      //return (*this) - ((this->divisionWithoutPoint(operand))*operand);
    }
  	inline bool operator > (modFP_64 operand)
  	{
  		unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      return convertThis.value.value > convertOperand.value.value;
  	}
  	inline bool operator < (modFP_64 operand)
  	{
  		unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      return convertThis.value.value < convertOperand.value.value;
  	}
  	inline bool operator == (modFP_64 operand)
  	{
  		unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      return convertThis.value.value == convertOperand.value.value;
  	}
  	inline bool operator != (modFP_64 operand)
  	{
  		unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      return convertThis.value.value != convertOperand.value.value;
  	}
  	inline bool operator >= (modFP_64 operand)
  	{
  		unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      return convertThis.value.value >= convertOperand.value.value;
  	}
  	inline  bool operator <= (modFP_64 operand)
  	{
  		unsigned char uniquePointPosition = this->pointPosition > operand.pointPosition ? this->pointPosition : operand.pointPosition;
      modFP_64 convertThis = this->pointConvert(uniquePointPosition);
      modFP_64 convertOperand = operand.pointConvert(uniquePointPosition);
      return convertThis.value.value <= convertOperand.value.value;
  	}
    modLong value;
    unsigned char pointPosition;
};

class periodDivisionElement
{
  public:
    inline bool operator == (periodDivisionElement operand)
    {
      return (this->result == operand.result) && (this->remainder == operand.remainder);
    }
    modFP_64 result;
    modFP_64 remainder;
};

class periodDivisionVector
{
  public:
    inline periodDivisionElement operator [] (int index)
    {
      //DEBUG std::cout << "operator [] " << value[index].result.getStringValue() << "  " << value[index].remainder.getStringValue() << "\n"
      return value[index];
    }
    inline void append (periodDivisionElement operand)
    {
      this->value.push_back(operand);
      //DEBUG std::cout<< this->value[this->value.size()-1].result.getStringValue() << "        1\n";
    }
    inline bool is_in (periodDivisionElement operand)
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
    inline std::string getAllResults(periodDivisionElement OnThisIndex)
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
    std::vector<periodDivisionElement> value;
};

modFP_64 modFP_64::operator / (modFP_64 operand)
{
  if(periodDetection)
  {
    periodDivisionVector periodDetector;
    periodDivisionElement mem;
    modFP_64 ret = this->divisionWithoutPoint(operand);
    modFP_64 moduloResult = (*this) % operand;
    modFP_64 zero("0");
    modFP_64 ten("10");
    modFP_64 divisionMem;
    unsigned char tenExponent = 1;
    //DEBUG std::cout << "no error 1\n";
    while(moduloResult != zero)
    {
      divisionMem = moduloResult * ten;
      moduloResult = divisionMem % operand;
      mem.remainder = moduloResult;
      divisionMem = divisionMem.divisionWithoutPoint(operand);
      mem.result = divisionMem;
      if(periodDetector.is_in(mem))
      {
        std::cerr << "error in memberfunction modFP_64::operator/ : the program has detected a period which is produced by an operation the current return value which won't be returned is: " << ret.getStringValue() << " and the period is: " << periodDetector.getAllResults(mem) << "\n";
        break;
      }
      periodDetector.append(mem);
      //DEBUG std::cout << mem.result.getStringValue() << "  " << mem.remainder.getStringValue() << "\n"; //DEBUG
      divisionMem = divisionMem.pointLeftShift(tenExponent);
      ret = ret + divisionMem;
      //DEBUG std::cout << "no error " << (int)tenExponent << "\n";
      //DEBUG std::cout << ret.getStringValue() << "\n";
      tenExponent++;
    }
    return ret;
  }
  else
  {
    modFP_64 ret = this->divisionWithoutPoint(operand);
    modFP_64 moduloResult = (*this) % operand;
    modFP_64 zero("0");
    modFP_64 ten("10");
    modFP_64 divisionMem;
    unsigned char tenExponent = 1;
    //DEBUG std::cout << "no error 1\n";
    while(moduloResult != zero)
    {
      divisionMem = moduloResult * ten;
      moduloResult = divisionMem % operand;
      divisionMem = divisionMem.divisionWithoutPoint(operand);
      divisionMem = divisionMem.pointLeftShift(tenExponent);
      ret = ret + divisionMem;
      //DEBUG std::cout << "no error " << (int)tenExponent << "\n";
      //DEBUG std::cout << ret.getStringValue() << "\n";
      tenExponent++;
    }
    return ret;
  }
}

#endif
