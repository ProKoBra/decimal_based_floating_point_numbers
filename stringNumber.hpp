#ifndef stringNumber_HPP
#define stringNumber_HPP

#include <iostream>
#include <string.h>

class stringNumber
{
  public:
      inline stringNumber(std::string inputValue)
      {
        this->value = inputValue;
      }
      inline stringNumber()
      {
        this->value = "0";
      }
      std::string value;
      inline static char digitAdd(char inputValue1, char inputValue2)
      {
        if(inputValue1 > '5' || inputValue2 > '5' || (inputValue1 == '5' && inputValue2 == '5'))
        {
          std::cerr << "The given input is to high! This function will return a";
          return 'a';
        }
        return (inputValue1 + inputValue2 - '0');
      }
      inline static char digitAddOne(char number, char &overflow)
      {
        overflow = '0';
        switch(number)
        {
          case '0':
            return '1';
          case '1':
            return '2';
          case '2':
            return '3';
          case '3':
            return '4';
          case '4':
            return '5';
          case '5':
            return '6';
          case '6':
            return '7';
          case '7':
            return '8';
          case '8':
            return '9';
          case '9':
            overflow = '1';
            return '0';
          default:
            std::cerr << "The given character isn't a digit, but it has to be a digit and not a letter or something else in the ASCII-Code\n";
        }
      }
      inline stringNumber addOne()
      {
        stringNumber* ret = new stringNumber;
        //DEBUG std::cout << this->value+" this->value\n";
        char overflow = '0';
        stringNumber* tempRet = new stringNumber;
        *tempRet = *this;
        int i = this->value.length()-1;
        //DEBUG std::cout << digitAddOne(this->value[i], overflow) << "\n";
        tempRet->value[i] = digitAddOne(this->value[i], overflow);
        i--;
        while(i >= 0 && overflow == '1')
        {
          tempRet->value[i] = digitAddOne(this->value[i], overflow);
          i--;
        }
        //DEBUG std::cout << "no error\n";
        if(overflow == '1')
        {
          ret->value[0] = '1';
          for(int i = 0; i < tempRet->value.length(); i++)
          {
            ret->value += "0";
            ret->value[i+1] = tempRet->value[i];
          }
          stringNumber realRet = *ret;
          delete ret, tempRet;
          return realRet;
        }
        //DEBUG std::cout << tempRet->value << "\n";
        ret->value = tempRet->value;
        stringNumber realRet = *ret;
        delete ret, tempRet;
        return realRet;
      }
      inline static char digitMul2(char number, char &overflow)
      {
        switch(number)
        {
          case '0':
            overflow = '0';
            return '0';
          case '1':
            overflow = '0';
            return '2';
          case '2':
            overflow = '0';
            return '4';
          case '3':
            overflow = '0';
            return '6';
          case '4':
            overflow = '0';
            return '8';
          case '5':
            overflow = '1';
            return '0';
          case '6':
            overflow = '1';
            return '2';
          case '7':
            overflow = '1';
            return '4';
          case '8':
            overflow = '1';
            return '6';
          case '9':
            overflow = '1';
            return '8';
          default:
            std::cerr << "The parameter Number has to contain a digit! The given parameter isn't a digit!\n";
        }
      }
      inline stringNumber mul2()
      {
        stringNumber* tempRet = new stringNumber;
        stringNumber* ret = new stringNumber;
        char hasNoSensOverflow = '0';
        char overflow = '0';
        char oldoverflow = '0';
        tempRet->value[0] = oldoverflow == '0' ? digitMul2(this->value[this->value.length() - 1], overflow) : oldoverflow == '1' ? digitAddOne(digitMul2(this->value[this->value.length() - 1], overflow), hasNoSensOverflow) : 'a';
        for(int i = this->value.length() - 2; i>=0; i--)
        {
          //DEBUG std::cout << tempRet->value + "\n";
          oldoverflow = overflow;

          tempRet->value = "0" + tempRet->value;
          tempRet->value[0] = oldoverflow == '0' ? digitMul2(this->value[i], overflow) : oldoverflow == '1' ? digitAddOne(digitMul2(this->value[i], overflow), hasNoSensOverflow) : 'a';
          //DEBUG std::cout << tempRet->value[i] << "  " << i << "  " << this->value[i] << "  " << tempRet->value << std::endl;
        }

        if(overflow == '1')
        {
          ret->value = "1" + tempRet->value;
        }
        else
        {
          *ret = *tempRet;
        }
        stringNumber realRet = *ret;
        delete tempRet, ret;
        return realRet;
      }
      inline static char digitDiv2(char number, char &point)
      {
        //DEBUG std::cout << number << "\n";
        switch(number)
        {
          case '0':
            point = '0';
            return '0';
          case '1':
            point = '5';
            return '0';
          case '2':
            point = '0';
            return '1';
          case '3':
            point = '5';
            return '1';
          case '4':
            point = '0';
            return '2';
          case '5':
            point = '5';
            return '2';
          case '6':
            point = '0';
            return '3';
          case '7':
            point = '5';
            return '3';
          case '8':
            point = '0';
            return '4';
          case '9':
            point = '5';
            return '4';
          default:
            std::cerr << "The parameter Number has to contain a digit! The given parameter isn't a digit!\n";
        }
      }
      inline stringNumber div2(bool* overflow)
      {
        char point = '0';
        char oldpoint = '0';
        stringNumber ret = *this;
        //DEBUG: std::cout << this->value[0] << "div2 \n";
        //DEBUG: std::cout << "this->value.length()=" << this->value.length() << "\n";
        ret.value[0] = digitDiv2(this->value[0], point);
        //DEBUG: std::cout << "ret[0] = " << ret.value[0] << "\n";
        for(int i = 1; i < this->value.length(); i++)
        {
          //DEBUG: std::cout << this->value[i] << "div2for \n"; //DEBUG
          oldpoint = point;
          ret.value[i] = digitAdd(oldpoint, digitDiv2(this->value[i], point));
          //DEBUG: std::cout << "ret[" << i << "]= " << ret.value[i] << "\n"; //DEBUG
        }
        *overflow = point-'0';
        //DEBUG: std::cout << "ret = " << ret.value << "and has the length" << ret.value.length() << "\n";
        return ret;
      }
      inline void operator = (stringNumber equal)
      {
        this->value = equal.value;
      }
      inline char operator [](int index)
      {
        return this->value[index];
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
};
#endif
