#include <iostream>

template <typename data> //data has to be an atomic, unsigned and numeric datatype(char, short, int, long long) and no class
class modData
{
public:
  inline modData(data inputValue)
  {
    value = inputValue;
  }
  inline unsigned int getSize()
  {
    return 8 * (sizeof(data));
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
    return modData<data>(this->value + operand.value);
  }
  inline modData<data> operator -(modData<data> operand)
  {
    return modData<data>(this->value - operand.value);
  }
  inline modData<data> operator *(modData<data> operand)
  {
    return modData<data>(this->value * operand.value);
  }
  inline modData<data> operator %(modData<data> operand)
  {
    return modData<data>(this->value % operand.value);
  }
  inline modData<data> operator /(modData<data> operand)
  {
    return modData<data>(this->value / operand.value);
  }
  inline bool operator ==(modData<data> operand)
  {
    return this->value == operand.value;
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
  inline void setValueOnIndex(unsigned index, bool value)
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
