#include "estadodaencriptacao.h"
#include "ui_estadodaencriptacao.h"

estadoDaEncriptacao::estadoDaEncriptacao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::estadoDaEncriptacao)
{
    ui->setupUi(this);
}

estadoDaEncriptacao::~estadoDaEncriptacao()
{
    delete ui;
}

void estadoDaEncriptacao::reset(){
	ui->progresso->reset();
}

void estadoDaEncriptacao::setTotalSteps(int v){
	ui->progresso->setRange(0,v);
}

void estadoDaEncriptacao::setProgress(int v){
	ui->progresso->setValue(v);
}

void estadoDaEncriptacao::setStatus(const QString &s){
	ui->status->setText(s);
}

