#ifndef concept4_HPP
#define concept4_HPP

#include <iostream>
#include <string.h>
#include "stringNumber.hpp"
#include "definitions.hpp"

template <typename data>
class dataMul2
{
public:
  inline dataMul2(std::string inputValue="0")
  {
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
    //DEBUG std::cout << "no error 1\n";
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
    //DEBUG std::cout << "no error 2\n";
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
  inline unsigned long long getSize()
  {
    return lowerValue.getSize() * 2;
  }
  inline dataMul2<dataMul2<data> > convert()
  {
    dataMul2<dataMul2<data> > ret;
    ret.lowerValue = *this;
    return ret;
  }
  inline bool operator [](unsigned long long index)
  {
    if(index < lowerValue.getSize())
    {
      return higherValue[index];
    }
    return lowerValue[index - lowerValue.getSize()];
  }
  inline void setValueOnIndex(unsigned index, bool value)
  {
    if(index >= this->getSize())
    {
      std::cout << "error in memberfunction dataMul2::setValueOnIndex : the given index is too high\n";
    }
    else
    {
      if(index < lowerValue.getSize())
      {
        higherValue.setValueOnIndex(index, value);
      }
      else
      {
        lowerValue.setValueOnIndex(index - lowerValue.getSize(), value);
      }
    }
  }
  inline unsigned long long firstSignificantIndex()
  {
    for(unsigned long long i = 0; i < this->getSize(); i++)
    {
      if((*this)[i])
      {
        return i;
      }
    }
    return this->getSize();
  }
  inline dataMul2<data> operator ~ ()
  {
    dataMul2<data> ret;
    ret.higherValue = ~this->higherValue;
    ret.lowerValue = ~this->lowerValue;
    return ret;
  }
  inline dataMul2<data> twoscomplement()
  {
    return (~(*this)) + dataMul2<data>("1");
  }
  inline void operator = (dataMul2<data> equal)
  {
    this->lowerValue = equal.lowerValue;
    this->higherValue = equal.higherValue;
  }
  inline bool operator == (dataMul2<data> operand)
  {
    return (this->lowerValue == operand.lowerValue) && (this->higherValue == operand.higherValue);
  }
  inline bool operator != (dataMul2<data> operand)
  {
    return (this->lowerValue != operand.lowerValue) || (this->higherValue != operand.higherValue);
  }
  inline bool operator > (dataMul2<data> operand)
  {
    return this->higherValue == operand.higherValue ? this->lowerValue > operand.lowerValue : this->higherValue > operand.higherValue;
  }
  inline bool operator < (dataMul2<data> operand)
  {
    return this->higherValue == operand.higherValue ? this->lowerValue < operand.lowerValue : this->higherValue < operand.higherValue;
  }
  inline bool operator <= (dataMul2<data> operand)
  {
    return *this < operand || *this == operand;
  }
  inline bool operator >= (dataMul2<data> operand)
  {
    return *this > operand || *this == operand;
  }
  inline dataMul2<data> operator + (dataMul2<data> operand)
  {
    dataMul2<data> ret("0");
    data carry("0");
    ret.lowerValue = this->lowerValue + operand.lowerValue;
    //DEBUG std::cout << this->lowerValue.getStringValue() << '\n';
    //DEBUG std::cout << operand.lowerValue.getStringValue() << '\n';
    //DEBUG std::cout << ret.lowerValue.getStringValue() << '\n';
    if(error)
    {
      //DEBUG std::cout << "if\n";
      carry = data("1");
      error = false;
    }
    ret.higherValue = this->higherValue + operand.higherValue;
    bool localError = error;
    ret.higherValue = ret.higherValue + carry;
    error = localError || error;
    return ret;
  }
  inline dataMul2<data> operator * (dataMul2<data> operand)
  {
    dataMul2<data> ret("0");
    dataMul2<data> zero("0");
    dataMul2<data> one("1");
    bool localError;
    if(operand == zero || (*this) == zero)
    {
      return ret;
    }
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << " one = " << one.getStringValue() << "\n";
    while(operand !=zero)
    {
      //DEBUG std::cout << "ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << " one = " << one.getStringValue() << "\n";
      operand = operand - one;
      //DEBUG std::cout << "ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << " one = " << one.getStringValue() << "\n";
      ret = ret + (*this);
      //DEBUG std::cout << "ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << " one = " << one.getStringValue() << "\n";
      if(error)
      {
        localError = true;
      }
    }
    error = localError;
    return ret;
  }
  /*old subtraction inline dataMul2<data> operator - (dataMul2<data> operand)
  {
    if(operand.firstSignificantIndex() == operand.getSize())
    {
      return *this;
    }
    unsigned long long originalFirstSignificantIndex = this->firstSignificantIndex();
    //DEBUG std::cout << "no error 3\n";
    dataMul2<data> subtrahend = operand.twoscomplement();
    //DEBUG std::cout << "no error 4\n";
    dataMul2<data> ret;
    std::cout << " ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << " subtrahend = " << subtrahend.getStringValue() << "\n";
    originalFirstSignificantIndex = subtrahend.firstSignificantIndex() > originalFirstSignificantIndex ? subtrahend.firstSignificantIndex() : originalFirstSignificantIndex;
    //DEBUG std::cout << "no error 5\n";
    ret = *this + subtrahend;
    std::cout << " ret = " << ret.getStringValue() << " this = " << this->getStringValue() << " operand = " << operand.getStringValue() << " subtrahend = " << subtrahend.getStringValue() << "\n";
    error = false;
    //DEBUG std::cout << "add\n";
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " error = " << error << "\n";
    //DEBUG std::cout << "no error 6 " << originalFirstSignificantIndex << "\n";
    if(originalFirstSignificantIndex != 0 && ret.firstSignificantIndex() > originalFirstSignificantIndex && ret.firstSignificantIndex() != ret.getSize())
    {
      ret.setValueOnIndex(ret.firstSignificantIndex(), 0);
    }
    if(ret > *this) {error = true;}
    //DEBUG std::cout << "ret = " << ret.getStringValue() << " error = " << error << "\n";
    //DEBUG std::cout << "no error 7\n";
    return ret;
  }*/
  inline dataMul2<data> operator - (dataMul2<data> operand)
  {
    bool localError;
    if(operand.firstSignificantIndex() == operand.getSize())
    {
      return *this;
    }
    dataMul2<data> ret;
    ret.lowerValue = this->lowerValue - operand.lowerValue;
    if(error)
    {
      error = false;
      operand.higherValue = operand.higherValue + data("1");
      localError = error;
    }
    ret.higherValue = this->higherValue - operand.higherValue;
    error = error || localError;
    return ret;
  }
  inline dataMul2<data> operator / (dataMul2<data> operand)
  {
    if(operand.firstSignificantIndex() == operand.getSize())
    {
      std::cerr << "error in memeberfunction dataMul2<data>::operator/ : cannot divide by zero\n";
      return *this;
    }
    dataMul2<data> ret;
    dataMul2<data> one("1");
    dataMul2<data> copyOfThis = *this;
    //DEBUG std::cout << "no error 0\n";
    bool localError;
    while(true)
    {
      //DEBUG std::cout << "copyOfThis = " << copyOfThis.getStringValue() << " operand = " << operand.getStringValue() << " copyOfThis < operand = " << (copyOfThis < operand) << "\n";
      if(copyOfThis < operand)
      {
        //DEBUG std::cout << "if\n";
        break;
      }
      else
      {
        //DEBUG std::cout << "no error 1 " << copyOfThis.getStringValue() << "\n";
        copyOfThis = copyOfThis - operand;
        if(error){localError=true;}
        //DEBUG std::cout << "no error 2 " << copyOfThis.getStringValue() << "\n";
        ret = ret + one;
        if(error){localError=true;}
      }
    }
    error = localError || error;
    return ret;
  }
  inline dataMul2<data> operator % (dataMul2<data> operand)
  {
    if(operand.firstSignificantIndex() == operand.getSize())
    {
      std::cerr << "error in memeberfunction dataMul2<data>::operator% : cannot divide by zero\n";
      return *this;
    }
    dataMul2<data> one("1");
    dataMul2<data> copyOfThis = *this;
    //DEBUG std::cout << "no error 0\n";
    bool localError;
    while(true)
    {
      //DEBUG std::cout << "copyOfThis = " << copyOfThis.getStringValue() << " operand = " << operand.getStringValue() << " copyOfThis < operand = " << (copyOfThis < operand) << "\n";
      if(copyOfThis < operand)
      {
        //DEBUG std::cout << "if\n";
        break;
      }
      else
      {
        //DEBUG std::cout << "no error 1 " << copyOfThis.getStringValue() << "\n";
        copyOfThis = copyOfThis - operand;
        if(error){localError=true;}
        //DEBUG std::cout << "no error 2 " << copyOfThis.getStringValue() << "\n";
      }
    }
    error = localError;
    return copyOfThis;
  }
  inline dataMul2<data> pow(dataMul2<data> operand)
  {
    dataMul2<data> ret("1");
    dataMul2<data> one = ret;
    dataMul2<data> zero = one - one;
    bool localError;
    while (operand > zero)
    {
      ret = ret * (*this);
      if(error&&!localError){localError=true;}
      operand = operand - one;
      if(error&&!localError){localError=true;}
    }
    error = localError || error;
    return ret;
  }
  inline void operator += (dataMul2<data> operand)
  {
    *this = *this + operand;
  }
  inline void operator *= (dataMul2<data> operand)
  {
    *this = *this * operand;
  }
  data higherValue;
  data lowerValue;
};

#endif
