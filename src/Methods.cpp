#include "Methods.h"

const char* fileRead(string filename)
{
    FILE* file;
    int len;
    file = fopen(filename.c_str(), "r+");
    if(file == NULL)
    {
        cerr << "file " << filename << " failed to load, does it exsist?\n";
        return "nope.avi";
    }
    fseek(file, 0, SEEK_END);
    len = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* filedat;
    filedat = (char*)malloc(sizeof(char)*len);
    fread(filedat, 1, len, file);
    fclose(file);
    return filedat;
    /*ifstream file;
    file.open(filename.c_str());
    string filedat, fileline;
    while(file>>fileline)
    {
        filedat+=fileline;
    }
    return filedat;*/
}

string getSection(string name, string dat)
{
    string::size_type pos, pos2;
    pos = dat.find(name);
    if(pos == string::npos)
        return "no variable by that name";
    pos2 = dat.find("}", pos+1);
    if(pos2 == string::npos)
        return "no end curly in the rest of file";
    string temp = dat.substr(pos+name.size()+3, (pos2-pos)-name.size()-3);
    return temp;
}

int count(string data, string ch)
{
    int count=0;
    string::size_type pos = 0, sol=0;
    pos = data.find(ch,sol);
    while(pos != string::npos)
    {
        count++;
        sol=pos+1;
        pos = data.find(ch,sol);
    }
    return count;
}

Sint32 getNumber(string dat, string name)
{
    string::size_type pos, pos2, pos3;
    string num;
    pos = dat.find(name.c_str());
    if(pos == string::npos)
        return LONG_MAX;
    pos2 = dat.find('=', pos);
    if(pos2 == string::npos)
        return LONG_MAX;
    pos3 = dat.find(';',pos);
    if(pos3 == string::npos)
        return LONG_MAX;
    if(pos3-pos2>1)
        num = dat.substr(pos2+1,(pos3-(pos2+1)));
    else
        num = dat[pos2+1];
    return atoi(num.c_str());
}

string getString(string dat, string name)
{
    string::size_type pos, pos2, pos3;
    string num;
    pos = dat.find(name.c_str());
    if(pos == string::npos)
        return "nope";
    pos2 = dat.find('=', pos);
    if(pos2 == string::npos)
        return "nope";
    pos3 = dat.find(';',pos);
    if(pos3 == string::npos)
        return "nope";
    if(pos3-pos2>1)
        num = dat.substr(pos2+1,(pos3-(pos2+1)));
    else
        num = dat[pos2+1];
    return num;
}

SDL_Surface* loadImage(string file)
{
    SDL_Surface* temp = NULL;
    SDL_Surface* opt = NULL;
    temp = IMG_Load(file.c_str());
    if(temp != NULL)
    {
        opt = SDL_DisplayFormat(temp);
        SDL_FreeSurface(temp);
    }
    else
    {
        cerr << "image: " << file << " failed to load\n";
        return NULL;
    }
    if(opt != NULL)
    {
        Uint32 colorkey = SDL_MapRGB(opt->format,0xFF,0,0xFF);
        SDL_SetColorKey(opt, SDL_SRCCOLORKEY, colorkey);
    }
    else
    {
        cerr << "image format change for " << file << " failed\n";
    }
    return opt;
}
Uint32 LCM(int f, int s)
{
    for(int i = 1; i <= s; i++)
    {
        int h = f*i;
        for(int j = 1; j <= f; j++)
        {
            if(h==s*j)
            {
                return s*j;
            }
        }
    }
    return 0;
}
double noise(int x, int y, int prime1, int prime2, int prime3)
{
    int n=(int)x+(int)y*57;
    n=(n<<13)^n;
    int nn=(n*(n*n*prime1+prime2)+prime3)&0x7fffffff;
    return 1.0-((double)nn/1073741824.0);
}

double interpolate(double a, double b, double x)
{
	double f = x * 3.1415926;
	f = (1 - cos(f)) * .5;
	return a*(1-f)+b*f;
}

double smoothNoise(int x, int y, int prime1, int prime2, int prime3)
{
    double corners = (noise(x+1,y+1, prime1, prime2, prime3) + noise(x+1,y-1, prime1, prime2, prime3) + noise(x-1,y+1, prime1, prime2, prime3) + noise(x-1,y-1, prime1, prime2, prime3)) / 16;
    double sides = (noise(x,y+1, prime1, prime2, prime3) + noise(x,y-1, prime1, prime2, prime3) + noise(x+1,y, prime1, prime2, prime3) + noise(x-1,y, prime1, prime2, prime3)) / 8;
    double center = noise(x,y, prime1, prime2, prime3)/4;
    return corners+sides+center;
}
double interpolatedNoise(double x, double y, int prime1, int prime2, int prime3)
{
    int i_x(x);
    double dec_x = x-i_x;
    int i_y(y);
    double dec_y = y-i_y;

    double v1 = smoothNoise(i_x,i_y, prime1, prime2, prime3);
    double v2 = smoothNoise(i_x+1,i_y, prime1, prime2, prime3);
    double v3 = smoothNoise(i_x,i_y+1, prime1, prime2, prime3);
    double v4 = smoothNoise(i_x+1,i_y+1, prime1, prime2, prime3);

    double i1 = interpolate(v1, v2, dec_x);
    double i2 = interpolate(v3, v4, dec_x);

    return interpolate(i1, i2, dec_y);
}

double perlinNoise(double x, double y, int prime1, int prime2, int prime3, int zoom, int xOffset, int yOffset)
{
    double total = 0, p = .5, n = 8;
    double frequency, amplitude;
    for(int i = 0; i <= n; i++)
    {
        frequency = pow(2,i);
        amplitude = pow(p,i);
        total += interpolatedNoise((x+xOffset)*frequency/zoom, (y+yOffset)*frequency/zoom, prime1, prime2, prime3) * amplitude;
    }
    return total;
}

void createNoise(Uint32 *pix,int width, int height, int prime1, int prime2, int prime3, int zoom, int xOffset, int yOffset)
{
    for(int y = 0; y <= (height-1); y++)
    {
        for(int x = 0; x <= (width-1); x++)
        {
            int num = (int)(perlinNoise(x+1,y+1,prime1,prime2,prime3,zoom,xOffset,yOffset)*128+128);
            if(num >255)
                num = 255;
            if(num < 0)
                num = 0;
            //cout << "value(" << x+1 << "," << y+1 << ") = " << num << "\n";
            Uint32 val = (0x010000*num)+(0x000100*num)+num;
            pix[y*width+x] = val;
        }
    }
}

void makeMap(Uint32 *noise, Uint32 *des, int width, int height, Uint32 threshold)
{
    for(int y = 0; y <= (height-1); y++)
    {
        for(int x = 0; x <= (width-1); x++)
        {
            Uint32 pixel = noise[y*width+x]%0x000100;
            if(pixel > threshold)
                des[y*width+x] = pixel * 0x000100;
            else
                des[y*width+x] = (0x0000ff-threshold) + pixel;
        }
    }
}

void halt(float ms)
{
    double start = clock();
    while (clock()-start < ms);
}

Uint64 getBit(Uint32 pos)
{
    Uint64 beg = 1;
    if(pos > 64 || pos < 1)
    {
        std::cerr << "out of range";
        return 0;
    }
    return beg << (pos-1);
}

Uint64 getBitRange(Uint32 beg, Uint32 end)
{
    Uint64 num = 1, total = 0;
    total += num << (beg-1);
    if(end < beg)
    {
        std::cerr << "Error: ending bit is less than beginning bit\n";
        return 0;
    }
    else if(end > 64 || end < 1)
    {
        std::cerr << "Error: ending bit is out of range";
        return 0;
    }
    else if(beg >64 || beg < 1)
    {
        std::cerr << "Error: beginning bit is out of range";
        return 0;
    }
    for(Uint32 i = beg; i < end; i++)
    {
        total += num << i;
    }
    return total;
}

uint64_t CRC32(const char *buf, unsigned long len)
{
    uint64_t crc_table[256];
    uint64_t crc;
    for (int i = 0; i < 256; i++) {
        crc = i;
        for (int j = 0; j < 8; j++) {
            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
        }
        crc_table[i] = crc;
    }
    crc = 0xFFFFFFFFUL;
    while (len--) {
        crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ 0xFFFFFFFFUL;
}
