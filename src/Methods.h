#ifndef METHODS_H_INCLUDED
#define METHODS_H_INCLUDED
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <ctime>
#include <string>
#include <climits>
#include <SDL/SDL.h>
#include <SDL/SDL_Image.h>
#include <iostream>
using namespace std;

const char* fileRead(string filename);
string getSection(string name, string dat);
int count(string data, string ch);
Sint32 getNumber(string dat,string name);
string getString(string dat,string name);
SDL_Surface* loadImage(string);
double smoothNoise(int x, int y, int prime1, int prime2, int prime3);
double noise(int x, int y, int prime1, int prime2, int prime3);
double interpolate(double a, double b, double x);
double interpolatedNoise(double x, double y, int prime1, int prime2, int prime3);
double perlinNoise(double x, double y, int prime1, int prime2, int prime3, int zoom, int xOffset, int yOffset);
void createNoise(Uint32 *pix,int width, int height, int prime1, int prime2, int prime3, int zoom, int xOffset, int yOffset);
void makeMap(Uint32 *noise, Uint32 *des, int width, int height, Uint32 threshold);
Uint32 LCM(int f, int s);
void halt(float);
Uint64 getBit(Uint32 pos);
Uint64 getBitRange(Uint32 beg, Uint32 end);
uint64_t CRC32(const char *buf, unsigned long len);

#endif // METHODS_H_INCLUDED
