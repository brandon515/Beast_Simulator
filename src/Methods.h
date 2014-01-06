#ifndef METHODS_H_INCLUDED
#define METHODS_H_INCLUDED
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <stdint.h>
#include <string>
#include <climits>
#include <iostream>
using namespace std;

const char* fileRead(string filename);
string getSection(string name, string dat);
int count(string data, string ch);
int getNumber(string dat,string name);
string getString(string dat,string name);
//SDL_Surface* loadImage(string);
double smoothNoise(int x, int y, int prime1, int prime2, int prime3);
double noise(int x, int y, int prime1, int prime2, int prime3);
double interpolate(double a, double b, double x);
double interpolatedNoise(double x, double y, int prime1, int prime2, int prime3);
double perlinNoise(double x, double y, int prime1, int prime2, int prime3, int zoom, int xOffset, int yOffset);
uint32_t LCM(int f, int s);
void halt(float);
uint32_t CRC32(const char *buf, unsigned long len);

#endif // METHODS_H_INCLUDED
