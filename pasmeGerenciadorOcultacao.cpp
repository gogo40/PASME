#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pasmeGerenciadorOcultacao.h"

#include <vector>
#include <cstdio>
#include <cstdlib>

#include <QString>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QtCore>

using namespace std;

/**
Oculta o arquivo 'mens' no arquivo 'alvo'
*/
void oculta(const char* mens, const char* alvo, QWidget * p){

	QMessageBox::information(p,"Aviso!","Comprimindo mensagem...");

	QString tmp(mens); tmp+=".tmp";
	gzFile tmpF = gzopen(tmp.toAscii(),"wb9f");

	if(!tmpF){
		QMessageBox::information(p,"Aviso!","Falha ao abrir arquivo:"+tmp);
		return;
	}

	//Realizando compressão da mensagem
	FILE* fin=fopen(mens,"rb");

	if(!fin){
		QMessageBox::information(p,"Aviso!","Falha ao abrir arquivo:"+QString(mens));
		return;
	}


	while(!feof(fin)){
		char c;
		fread(&c,sizeof(char),1,fin);
		gzwrite(tmpF,&c,sizeof(char));
	}

	gzclose(tmpF);
	fclose(fin);

	//Realizando ocultação da mensagem
	QMessageBox::information(p,"Aviso!","Ocultando mensagem...");

	fin=fopen(tmp.toAscii(),"rb");
	if(!fin){
		QMessageBox::information(p,"Aviso!","Falha ao abrir arquivo:"+tmp);
		return;
	}

	FILE* fout=fopen(alvo,"ab");

	if(!fout){
		QMessageBox::information(p,"Aviso!","Falha ao abrir arquivo:"+QString(alvo));
		return;
	}

	int l=0;

	l=0;
	while(!feof(fin)){
		char c;
		fread(&c,sizeof(char),1,fin);
		fwrite(&c,sizeof(char),1,fout);
		l++;
	}
	fwrite(&l,sizeof(int),1,fout);

	fclose(fin);
	fclose(fout);

	QMessageBox::information(p,"Aviso!","Mensagem ocultada!");

}

/**
 Revela a mensagem oculta no arquivo 'fonte' e grava no arquivo 'dest'
*/
void revela(const char* fonte, const char* dest, QWidget * p){

	QMessageBox::information(p,"Aviso!","Recuperando mensagem...");

	FILE* fin=fopen(fonte,"rb");
	if(!fin){
		QMessageBox::information(p,"Aviso!",QString("Falha ao abrir arquivo:")+fonte);
		return;
	}

	QString tmp(fonte); tmp+=".tmp";
	FILE* tmpF=fopen(tmp.toAscii(),"wb");
	if(!tmpF){
		QMessageBox::information(p,"Aviso!",QString("Falha ao abrir arquivo:")+tmp);
		return;
	}

	int l=0, i=0;

	//Recupera tamanho do arquivo ocultado e posiciona iterador de arquivo
	fseek(fin,-sizeof(int),SEEK_END);
	fread(&l,sizeof(int),1,fin);

	fseek(fin,-l*sizeof(char)-sizeof(int),SEEK_END);

	//Recupera mensagem comprimida
	QMessageBox::information(p,"Aviso!","Recuperando mensagem comprimida...");

	i=0;
	while(i<l){
		char c;
		fread(&c,sizeof(char),1,fin);
		fwrite(&c,sizeof(char),1,tmpF);
		i++;
	}

	fclose(fin);
	fclose(tmpF);

	//Grava mensagem no arquivo destino
	QMessageBox::information(p,"Aviso!","Gravando mensagem recuperada...");

	gzFile gtmpF=gzopen(tmp.toAscii(),"rb9f");
	if(!gtmpF){
		QMessageBox::information(p,"Aviso!",QString("Falha ao abrir arquivo:")+tmp);
		return;
	}

	FILE* fout=fopen(dest,"wb");
	if(!fout){
		QMessageBox::information(p,"Aviso!",QString("Falha ao abrir arquivo:")+dest);
		return;
	}

	while(!gzeof(gtmpF)){
		char c;
		gzread(gtmpF,&c,sizeof(char));
		fwrite(&c,sizeof(char),1,fout);
	}
	fclose(fout);
	gzclose(gtmpF);

	QMessageBox::information(p,"Aviso!","Recuperação de mensagem concluida!");

}

//Estenografia
void initPosColors(Magick::Image& image, PosColors& vp, int WORDSIZE) {
    size_t c = image.rows();
    size_t r = image.columns();

    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            Magick::Color mc = image.pixelColor(i, j);

            Magick::Quantum red = mc.redQuantum();
            Magick::Quantum green = mc.greenQuantum();
            Magick::Quantum blue = mc.blueQuantum();

            if (okColor(red, WORDSIZE))
                vp.push_back(PosColor(i, j, red, 0));

            if (okColor(green, WORDSIZE))
                vp.push_back(PosColor(i, j, green, 1));

            if (okColor(blue, WORDSIZE))
                vp.push_back(PosColor(i, j, blue, 2));
        }
    }
}

void saveByte(PosColors& vpc, uchar mc, int& ip, int WORDSIZE) {
    int ni = (1 << 8) / WORDSIZE;
    int c = mc;

    for (int k = 0; k < ni && ip < vpc.size(); ++k) {
        int w = c % WORDSIZE;

        c /= WORDSIZE;

        int v = vpc[ip].c % WORDSIZE;
        int p = (WORDSIZE + w - v) % WORDSIZE;

        vpc[ip].c += p;

        ip++;
    }
}

uchar loadByte(PosColors& vpc, int& ip, int WORDSIZE) {
    int ni = (1 << 8) / WORDSIZE;
    int c = 0;
    int wa = 1;


    for (int k = 0; k < ni && ip < vpc.size(); ++k) {
        int w = vpc[ip].c % WORDSIZE;

        c = wa * w + c;

        ip++;

        wa *= WORDSIZE;
    }

    return (uchar)(c);
}

void merge(const char* fname, const char* image, std::vector<uchar>& msg, int len, int WORDSIZE) {
    Magick::Image inImage(image);
    PosColors vpc;

    size_t c = inImage.rows();
    size_t r = inImage.columns();
    int ip;

    Magick::Image outImage(Magick::Geometry(r, c), Magick::Color(0, 0, 0, 0));

    initPosColors(inImage, vpc, WORDSIZE);

    ip = 0;
    for (size_t i = 0; i < len; ++i) {
        saveByte(vpc, msg[i], ip, WORDSIZE);
    }

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            Magick::Color mc = inImage.pixelColor(i, j);
            outImage.pixelColor(i, j, mc);
        }
    }

    for (int i = 0; i < vpc.size(); ++i) {
        int ix = vpc[i].x;
        int iy = vpc[i].y;
        int c = vpc[i].c;
        int type = vpc[i].type;
        Magick::Color mc = outImage.pixelColor(ix, iy);

        Magick::Quantum red = mc.redQuantum();
        Magick::Quantum green = mc.greenQuantum();
        Magick::Quantum blue = mc.blueQuantum();

        switch (type) {
            case 0:
                mc.redQuantum(c);
            break;

            case 1:
                mc.greenQuantum(c);
            break;

            case 2:
                mc.blueQuantum(c);
            break;
        }

        outImage.pixelColor(ix, iy, mc);
    }

    outImage.write(fname);
}

void recover(const char* fout, const char* fin, int len, int WORDSIZE) {
    FILE* fOut = fopen(fout, "wb");
    Magick::Image inImage(fin);
    PosColors vpc;

    int ip;

    initPosColors(inImage, vpc, WORDSIZE);

    ip = 0;
    for (int i = 0; i < len; ++i) {
        uchar c = loadByte(vpc, ip, WORDSIZE);
        fwrite(&c, 1, sizeof(c), fOut);
    }
    fclose(fOut);
}

