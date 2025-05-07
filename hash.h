#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0};

        for(int substring = 0; substring < 5; substring++){
          //calc starting position for substring
          int startPos = k.length() - 6 * (substring+1);
          if(startPos < 0){
            if(startPos+6 <= 0){
              break; //break after processing entire string
            }
            startPos = 0;
          }
          //current substring of <= 6 char
          unsigned long long val = 0;
          int substringLen = 6;
          if(startPos == 0){
            substringLen = k.length() - (6*substring);
          }
          for(int i=0; i<substringLen; i++){
            //base conversion
            val = val*36+letterDigitToNumber(k[startPos+i]);
          }
          //store in w array
          w[4-substring] = val;
        }

        //hash
        HASH_INDEX_T hash = 0;
        for(int i=0; i<5; i++){
          hash += rValues[i] * w[i];
        }

        return hash;
    }

//a likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T val = 0;
        if(letter >= 'a' && letter <= 'z'){
          val = letter - 'a';
        }
        else if(letter >= 'A' && letter <= 'Z'){
          val = letter - 'A';
        }
        else if(letter >= '0' && letter <= '9'){
          val = letter - '0' + 26;
        }
        return val;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
