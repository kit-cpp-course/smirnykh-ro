#include <sstream>
#pragma once
using namespace std;

const int W = 800; // ширина и высота окна
const int H = 600;

float DEGTORAD = 0.017453f;  // константа для перевода в радианы

int Score = 0; // счет игрока

std::ostringstream ssScore; // переменные для вывода текста
std::ostringstream ssGameover;