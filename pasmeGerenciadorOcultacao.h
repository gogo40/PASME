#ifndef PASMEGERENCIADOROCULTACAO_H
#define PASMEGERENCIADOROCULTACAO_H

#include <QMainWindow>
#include <QString>

#include <cstdio>
#include <cstdlib>
#include <zlib.h>
#include <string>
#include <QWidget>
#include <vector>

#include <Magick++.h>


typedef unsigned char uchar;

using namespace MagickCore;

inline int newColor(int color, int inc, int WORDSIZE) {
    if (color + inc >= MaxRGB - WORDSIZE ) return color;
    return color + inc;
}

inline bool okColor(int color, int WORDSIZE) {
    return color + WORDSIZE < MaxRGB;
}

struct PosColor {
    int x, y;
    //type: 0 -> red; 1 -> green; 2 -> blue;
    int c, type;

    PosColor(int x = 0, int y = 0, int c = 0, int type = 0):
    x(x), y(y), c(c), type(type){}
};

typedef std::vector<PosColor> PosColors;

void initPosColors(Magick::Image& image, PosColors& vp, int WORDSIZE);
void saveByte(PosColors& vpc, uchar mc, int& ip, int WORDSIZE);
uchar loadByte(PosColors& vpc, int& ip, int WORDSIZE);
void merge(const char* fname, const char* image, std::vector<uchar>& msg, int len, int WORDSIZE);
void recover(const char* fout, const char* fin, int len, int WORDSIZE);

/**
Oculta o arquivo 'mens' no arquivo 'alvo'
*/
void oculta(const char* mens, const char* alvo, QWidget * p);

/**
 Revela a mensagem oculta no arquivo 'fonte' e grava no arquivo 'dest'
*/
void revela(const char* fonte, const char* dest, QWidget * p);

#endif // PASMEGERENCIADOROCULTACAO_H
