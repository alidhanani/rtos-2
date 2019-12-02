/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alidhanani
 *
 * Created on November 19, 2019, 12:00 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

void GameMaster();
/*
 * 
 */

void GameMaster() {
    int ArrayOfGameMaster[4] = {0};
    int actualCount[9] = {0};
    int counterPerfect  =  0;
    int counterGuess = 0;
    for(int i = 0; i < 4; i++) {
        int color = rand()  % 9;
        ArrayOfGameMaster[i] = color;
        actualCount[color]++;
    }
    for(int i = 0; i < 4; i++) {
        printf("%d ", ArrayOfGameMaster[i]);
    }
    
    while(counterPerfect != 4) {
        counterPerfect  =  0;
        counterGuess = 0;
        int ArrayOfGameUser[4] = {0};
        for(int i = 0; i < 4; i++) {
            ArrayOfGameUser[i] = rand()  % 9;
        }
        int guessCount[9] = {0};  
        for(int i = 0; i < 4; i++) {
            if(ArrayOfGameMaster[i] == ArrayOfGameUser[i]) {
                counterPerfect++;
            }
            int color = ArrayOfGameUser[i];
            guessCount[color]++;
        }
        for(int i = 0; i < 9; i++) {
            counterGuess += std::min(actualCount[i], guessCount[i]);
        }
        counterGuess -= counterPerfect;
        printf("\nPerfect: %d Colour Only: %d", counterPerfect, counterGuess);
    }
    
}

int main(int argc, char** argv) {
    GameMaster();
    return 0;
}

