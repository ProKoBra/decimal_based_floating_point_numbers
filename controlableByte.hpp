#include<iostream>
#ifndef CONTROLABLEBYTE_H
#define CONTROLABLEBYTE_H

class controlableByte
{
public:
  controlableByte()
  {
    this->value = 0;
  }
  void setValueOnIndex(char index, bool inputvalue)
  {
    if(this->operator[](index) != inputvalue)
    {
      if(inputvalue==true)
      {
        this->value += numberOnIndex(index);
      }
      else {
        this->value -= numberOnIndex(index);
      }
    }
  }
  void operator = (unsigned char inputvalue)
  {
  this->value = inputvalue;
  }
  bool operator [](char index)
  {
    if (index>7) 
    {
      std::cerr << "The given Index is greater than 7\n";
    }
    unsigned char tempValue = 0;
    switch (index)
    {
      case 0:
        tempValue = this->value -128;
        if (tempValue > 127)
        {
          return false;
        }
        else {
          return true;
        }
      case 1:
        tempValue = this->value -128;
        if (tempValue > 127)
        {
          tempValue += 128;
        }
        tempValue -= 64;
        if (tempValue > 63)
        {
          return false;
        }
        else {
          return true;
        }

      case 2:
        tempValue = this->value -128;
        if (tempValue > 127)
        {
          tempValue += 128;
        }
        tempValue -= 64;
        if (tempValue > 63)
        {
          tempValue += 64;
        }
        tempValue -= 32;
        if (tempValue > 31)
        {
          return false;
        }
        else {
          return true;
        }
      case 3:
        tempValue = this->value -128;
        if (tempValue > 127)
        {
          tempValue += 128;
        }
        tempValue -= 64;
        if (tempValue > 63)
        {
          tempValue += 64;
        }
        tempValue -= 32;
        if (tempValue > 31)
        {
          tempValue += 32;
        }
        tempValue -= 16;
        if (tempValue > 15)
        {
          return false;
        }
        else {
          return true;
        }
      case 4:
        tempValue = this->value;
        if (this->value % 2 == 1)
        {
          tempValue -= 1;
        }
        tempValue -= 2;
        if(!(tempValue % 4 == 0))
        {
          tempValue += 2;
        }
        tempValue-=4;
        if(!(tempValue % 8 == 0))
        {
          tempValue+=4;
        }
        tempValue-=8;
        if(!(tempValue%16 == 0))
        {
          return false;
        }
        else {
          return true;
        }
      case 5:
        tempValue = this->value;
        if (this->value % 2 == 1)
        {
          tempValue -= 1;
        }
        tempValue -= 2;
        if(!(tempValue % 4 == 0))
        {
          tempValue += 2;
        }
        tempValue-=4;
        if(!(tempValue % 8 == 0))
        {
          return false;
        }
        else {
          return true;
        }
      case 6:
        tempValue = this->value;
        if (this->value % 2 == 1)
        {
          tempValue -= 1;
        }
        tempValue-=2;
        if(tempValue % 4 == 0)
        {
          return true;
        }
        else {
          return false;
        }
      case 7:
        if (this->value % 2 == 1)
        {
          return true;
        }
        else {
          return false;
        }
      default:
        return false;
    }
  }

protected:
  unsigned char numberOnIndex(char index)
  {
    switch (index)
    {
      case 0:
        return 128;
      case 1:
        return 64;
      case 2:
        return 32;
      case 3:
        return 16;
      case 4:
        return 8;
      case 5:
        return 4;
      case 6:
        return 2;
      case 7:
        return 1;
      default:
        std::cerr << "The given Index is greater than 7\n";
        return 0;
    }
  }
  unsigned char value;
};
#endif