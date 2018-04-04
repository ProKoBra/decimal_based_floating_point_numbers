#ifndef modData_HPP
#define modData_HPP

#include <iostream>
#include <string.h>
#include "stringNumber.hpp"
#include "definitions.hpp"

template <typename data> //data has to be an atomic, unsigned and numeric datatype(char, short, int, long long) and no class
class modData
{
  public:
    inline modData(std::string inputValue="0")
    {
      this->value = 0;
      this->binStringToBitStructure(stringNumber::decStringtoBinString(inputValue));
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
      if(!((*this)[0])) {
        //DEBUG std::cout << "if\n";
        //DEBUG std::cout << "no error7\n";
        //DEBUG std::cout << this->value.value << " irgfunc\n";
      }

      else {
        //DEBUG std::cout << this->value.value << " irgfunc\n";
        //DEBUG std::cout << "no error7\n";
        *yetZero = false;
        ret+="0";
        ret[counter] = (char)((*this)[0]+'0');
        counter++;
      }
      //DEBUG std::cout << this->value.value << " irgfunc\n";
      int i = 1;
      while(i < this->getSize())
      {
        if(*yetZero)
        {
          if((*this)[i])
          {
            *yetZero = false;
            ret+="0";
            ret[counter] = (char)((*this)[i]+'0');
            //DEBUG std::cout << this->value.value << " whilefunc\n";
            counter++;
          }
          i++;
          //DEBUG std::cout << "if\n";
          continue;
        }
        else {
          ret+="0";
          ret[counter] = (char)((*this)[i]+'0');
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
      return ret2.value;
    }
    inline void binStringToBitStructure(std::string binString)
    {
      if (binString.length() > this->getSize())
      {
        std::cerr << "error in memberfunction modData::binStringToBitStructure : the length of binString is not lower or equal than " << this->getSize() << "\n";
      }
      else
      {
        for (int i = 0; i < binString.length(); i++)
        {
          this->setValueOnIndex(i + this->getSize() - binString.length(), (binString[i]-'0'));
        }
      }
    }
    inline unsigned int getSize()
    {
      return 8 * (sizeof(data));
    }
    inline unsigned long long firstSignificantIndex()
    {
      for(unsigned long long i = 0; i < 8 * (sizeof(data)); i++)
      {
        if((*this)[i])
        {
          return i;
        }
      }
      return this->getSize();
    }
    inline void operator =(modData<data> operand)
    {
      this->value = operand.value;
    }
    inline void operator =(data operand)
    {
      this->value = operand;
    }
    inline modData<data> operator +(modData<data> operand)
    {
      modData<data> ret;
      ret.value = this->value + operand.value;
      if (ret.value < this->value || ret.value < operand.value) {
        error = true;
      } else {
        error = false;
      }
      return ret;
    }
    inline modData<data> operator -(modData<data> operand)
    {
      modData<data> ret;
      ret.value = this->value - operand.value;
      if (ret.value > this->value) {
        error = true;
      } else {
        error = false;
      }
      return ret;
    }
    inline modData<data> operator *(modData<data> operand)
    {
      modData<data> ret;
      ret.value = this->value * operand.value;
      if (ret.value < this->value || ret.value < operand.value) {
        error = true;
      } else {
        error = false;
      }
      return ret;
    }
    inline modData<data> operator %(modData<data> operand)
    {
      return modData<data>(this->value % operand.value);
    }
    inline modData<data> operator /(modData<data> operand)
    {
      return modData<data>(this->value / operand.value);
    }
    inline modData<data> operator ~()
    {
      modData<data> ret;
      for(int i = 0; i < ret.getSize(); i++)
      {
        ret.setValueOnIndex(i, !(*this)[i]);
      }
      return ret;
    }
    inline modData<data> twoscomplement()
    {
      return ~(*this) + 1;
    }
    inline bool operator ==(modData<data> operand)
    {
      return this->value == operand.value;
    }
    inline bool operator ==(data operand)
    {
      return this->value == operand;
    }
    inline bool operator !=(modData<data> operand)
    {
      return this->value != operand.value;
    }
    inline bool operator >=(modData<data> operand)
    {
      return this->value >= operand.value;
    }
    inline bool operator <=(modData<data> operand)
    {
      return this->value <= operand.value;
    }
    inline bool operator <(modData<data> operand)
    {
      return this->value < operand.value;
    }
    inline bool operator >(modData<data> operand)
    {
      return this->value > operand.value;
    }
    inline bool operator [](unsigned int index)
    {
      if(index < ((sizeof(data)) * 8))
      {
        data numberOnGivenIndex = this->numberOnIndex(index);
        data ANDresult = this->value & numberOnGivenIndex;
        return ANDresult == 0 ? false : true;
      }
      else
      {
        std::cerr << "error in memberfunction modData::operator[] : the given index is too high\n";
      }
    }
    inline data numberOnIndex(unsigned int index)
    {
      char realIndex = (((sizeof(data))*8)-1)-index;
      if(realIndex == 0)
      {
        return 1;
      }
      data ret = 1;
      for(char i = 1; i <= realIndex; i++)
      {
        ret *= 2;
      }
      return ret;
    }
    inline void setValueOnIndex(unsigned int index, bool value)
    {
      if(index >= ((sizeof(data)) * 8))
      {
        std::cout << "error in memberfunction modData::setValueOnIndex : the given index is too high\n";
      }
      else
      {
        if(value != this->operator[](index))
        {
          value ? this->value += modData::numberOnIndex(index): this->value -= modData::numberOnIndex(index);
        }
      }
    }
    data value;
};

#endif
