//
// Created by LEGION on 3/13/2021.
//

#ifndef MAIN_CPP_DICTIONARY_H
#define MAIN_CPP_DICTIONARY_H

#include <iostream>

class Dictionary {
public:

    void InitDictionary();


     std::vector<std::string> dictionary;
     std::vector<std::string> wordlength[10];

     std::string WordLength(int u, int v);
     std::string LetterWordLength(int letter, int u, int v);
};
extern Dictionary dict;


#endif //MAIN_CPP_DICTIONARY_H
