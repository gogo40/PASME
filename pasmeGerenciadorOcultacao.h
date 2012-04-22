#ifndef PASMEGERENCIADOROCULTACAO_H
#define PASMEGERENCIADOROCULTACAO_H

#include <QMainWindow>
#include <QString>

#include <cstdio>
#include <cstdlib>
#include <zlib.h>
#include <string>
#include <QWidget>

/**
Oculta o arquivo 'mens' no arquivo 'alvo'
*/
void oculta(const char* mens, const char* alvo, QWidget * p);

/**
 Revela a mensagem oculta no arquivo 'fonte' e grava no arquivo 'dest'
*/
void revela(const char* fonte, const char* dest, QWidget * p);

#endif // PASMEGERENCIADOROCULTACAO_H
