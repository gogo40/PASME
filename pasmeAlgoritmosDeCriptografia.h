#ifndef PASMEALGORITMOSDECRIPTOGRAFIA_H
#define PASMEALGORITMOSDECRIPTOGRAFIA_H

#include <QMainWindow>
#include <QString>

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <zlib.h>
#include <string>
#include <QWidget>
#include <gmp.h>
#include <gmpxx.h>

#include "pasmeConfig.h"

/*
 Encripta usando algoritmo PASME
*/
void encripta_PASME(std::vector<char>& key, const char* fin, const char* fout, const pasmeConfig* pc,QWidget * p);

/*
 Desencripta usando algoritmo PASME
*/
void desencripta_PASME(std::vector<char>& key, const char* fin, const char* fout, const pasmeConfig* pc,QWidget * p);

/*
 Encripta usando algoritmo XOR
*/
void encripta_XOR(std::vector<char>& key, const char* fin, const char* fout, const pasmeConfig* pc,QWidget * p);

/*
 Desencripta usando algoritmo XOR
*/
void desencripta_XOR(std::vector<char>& key, const char* fin, const char* fout, const pasmeConfig* pc,QWidget * p);


#endif // PASMEALGORITMOSDECRIPTOGRAFIA_H
