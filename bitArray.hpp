#ifndef BITARRAY_H
#define BITARRAY_H
#include "controlableByte.hpp"
#include <iostream>

class bitArray
{
  public:
    bitArray(int inputBits=64)
    {
      //DEBUG std::cout << "inputBits = " << inputBits << "\n";
      this->bits = inputBits;
      //DEBUG std::cout << "this->bits = " << this->bits << "\n";
      this->value = new controlableByte[((int)bits/8)+ (bits/8 - ((int)bits/8) == 0 ? 0 : 1)];
    }
    ~bitArray()
    {
      delete this->value;
    }
    bool operator [](signed int index)
    {
      if(index > this->bits)
      {
        std::cerr << "the given index("<< index << ") is bigger than the num of bits of the current object(" << this->bits << "). The result will usually be wrong because you've tried to acces random values in the RAM\n";
      }
      unsigned outIndex = index/8;
      unsigned innerIndex = index%8;
      return this->value[outIndex][innerIndex];
    }
    void setValueOnIndex(int index, bool value)
    {
      unsigned outIndex = index/8;
      unsigned innerIndex = index%8;
      //DEBUG std::cout << "no error\n";
      this->value[outIndex].setValueOnIndex(innerIndex, value);
    }
    void operator=(bitArray operand)
    {
      if(operand.bits > this->bits)
      {
        std::cerr << "the num of bits of the operand(" << operand.bits << ") has to be lower or equal than the num of bits of the current object(" << this->bits << ")(bitArray<bits>* this)\n ";
      }
      else {
        for(int i = 0; i < operand.bits; i++)
        {
          this->setValueOnIndex(i, operand[i]);
        }
      }
    }
    int bits;
    controlableByte* value;
};
#endif