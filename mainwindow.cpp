#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pasmeGerenciadorOcultacao.h"
#include "pasmeAlgoritmosDeCriptografia.h"
#include "ajuda.h"
#include "sobre.h"
#include <vector>
#include <cstdio>
#include <cstdlib>

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QtCore>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow),
	pc(),
	tipoAlgoritmoCriptografia(PASME)
{
    ui->setupUi(this);

	this->usarArquivoChave=false;

	this->nomeArquivoAlvo="";
	this->nomeArquivoChave="";
	this->nomeArquivoComMensagemASerRecuperada="";
	this->nomeArquivoMensagemASerOcultada="";
	this->nomeArquivoOndeEsconderMensagem="";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chamarOcultarInformacaoImagem(){
    int WORDSIZE = ui->EstWordSize->value();
    //void merge(const char* fname, const char* image, const char* msg, int len, int WORDSIZE);
    FILE* f = fopen(this->nomeArquivoOcultarArquivoAlvo.toAscii(),"rb");
    int len = 0;
    string msg = "";
    QString Msg("");

    while (!feof(f)) {
        char c;
        fread(&c,1,sizeof(c),f);
        if (c == EOF) break;
        len++;
        msg+=c;
    }
    fclose(f);

    try {
        merge((this->nomeArquivoOcultarMensagemImagem+".pasme.png").toAscii(),
          this->nomeArquivoOcultarMensagemImagem.toAscii(),
          msg.c_str(), len, WORDSIZE);
        QString ls("");
        ls.setNum(len);
        Msg = QString(tr("Tamanho mensagem: ")) + ls + "\n";
        QMessageBox::information(this,tr("Aviso!"),Msg);
    } catch (Magick::Exception& error) {
        Msg = QString(tr("Erro: ")) + error.what()< + "\n";
        QMessageBox::information(this,tr("Aviso!"),Msg);
    }
}

void MainWindow::chamarRevelarInformacaoImagem(){
    int WORDSIZE = ui->EstWordSize->value();
    int lenMsg = ui->lenOcultaMensagem->value();
    QString Msg("");

    //void recover(const char* fout, const char* fin, int len, int WORDSIZE);
    try {
        recover(this->nomeArquivoRevelarArquivoDestino.toAscii(),
            this->nomeArquivoRevelarMensagemImagem.toAscii(),
            lenMsg,
            WORDSIZE);
        QString ls("");
        ls.setNum(lenMsg);
        Msg = QString(tr("Tamanho mensagem: ")) + ls + "\n";
        QMessageBox::information(this,tr("Aviso!"),Msg);
    } catch (Magick::Exception& error) {
        Msg = QString(tr("Erro: ")) + error.what()< + "\n";
        QMessageBox::information(this,tr("Aviso!"),Msg);
    }
}

void MainWindow::capturarNomeArquivoOcultarMensagemImagem(){
    this->nomeArquivoOcultarMensagemImagem = QFileDialog::getOpenFileName(this, tr("Arquivo que vai ser ocultado"),".");
    ui->nomeOcultarArquivoImagem->setText(this->nomeArquivoOcultarMensagemImagem);
}

void MainWindow::capturarNomeArquivoOcultarArquivoAlvo(){
    this->nomeArquivoOcultarArquivoAlvo = QFileDialog::getOpenFileName(this,tr("Arquivo onde ocultar mensagem"),".");
    ui->nomeOcultarArquivoAlvo->setText(this->nomeArquivoOcultarArquivoAlvo);
}

void MainWindow::capturarNomeArquivoRevelarMensagemImagem(){
    this->nomeArquivoRevelarMensagemImagem = QFileDialog::getOpenFileName(this, tr("Arquivo com mensagem oculta"),".");
    ui->nomeRevelarArquivoImagem->setText(this->nomeArquivoRevelarMensagemImagem);
}

void MainWindow::capturarNomeArquivoRevelarArquivoDestino(){
    this->nomeArquivoRevelarArquivoDestino = QFileDialog::getSaveFileName(this,tr("Arquivo onde armazenar informação recuperada"),".");
    ui->nomeRevelarArquivoDestino->setText(this->nomeArquivoRevelarArquivoDestino);
}

void MainWindow::capturarNomeArquivoComMensagemASerOcultada(){
	this->nomeArquivoMensagemASerOcultada = QFileDialog::getOpenFileName(this, tr("Arquivo que vai ser ocultado"),".");
	ui->arquivoASerEscondido->setText(this->nomeArquivoMensagemASerOcultada);
}

void MainWindow::capturarNomeArquivoComMensagemOculta(){
	this->nomeArquivoComMensagemASerRecuperada= QFileDialog::getOpenFileName(this, tr("Arquivo com mensagem oculta"),".");
	ui->arquivoOndeRecuperarInformacao->setText(this->nomeArquivoComMensagemASerRecuperada);
}

void MainWindow::capturarNomeArquivoOndeEsconderMensagem(){
	this->nomeArquivoOndeEsconderMensagem = QFileDialog::getOpenFileName(this,tr("Arquivo onde ocultar mensagem"),".");
	ui->arquivoOndeEsconderAInformacao->setText(this->nomeArquivoOndeEsconderMensagem);
}

void MainWindow::chamarOcultarInformacao(){
	this->nomeArquivoMensagemASerOcultada=ui->arquivoASerEscondido->text();
	if(this->nomeArquivoMensagemASerOcultada==""){
		QMessageBox::information(this,tr("Aviso!"),tr("Por favor, entre com o nome do arquivo que vai ser escondido..."));
		return;
	}
	this->nomeArquivoOndeEsconderMensagem=ui->arquivoOndeEsconderAInformacao->text();
	if(this->nomeArquivoOndeEsconderMensagem==""){
		QMessageBox::information(this,tr("Aviso!"),tr("Por favor, entre com o nome do arquivo onde a informação vai ser escondida..."));
		return;
	}

	//QtConcurrent::run(oculta,nomeArquivoMensagemASerOcultada.toAscii(),nomeArquivoOndeEsconderMensagem.toAscii());
	oculta(nomeArquivoMensagemASerOcultada.toAscii(),nomeArquivoOndeEsconderMensagem.toAscii(),this);

}

void MainWindow::chamarRevelarInformacao(){
	this->nomeArquivoComMensagemASerRecuperada=ui->arquivoOndeRecuperarInformacao->text();
	if(this->nomeArquivoComMensagemASerRecuperada==""){
		QMessageBox::information(this,tr("Aviso!"),tr("Por favor, entre com o nome do arquivo que tem informação escondida..."));
		return;
	}

	QString fn=QFileDialog::getSaveFileName(this,tr("Arquivo onde armazenar informação recuperada"),".");
	if(fn==""){
		QMessageBox::information(this,tr("Aviso!"),tr("Por favor, entre com o nome do arquivo onde a informação recuperada será armazenada..."));
		return;
	}

	//QtConcurrent::run(revela,nomeArquivoComMensagemASerRecuperada.toAscii(),fn.toAscii());
	revela(nomeArquivoComMensagemASerRecuperada.toAscii(),fn.toAscii(),this);
}

void MainWindow::chamarEncriptador(){
	this->nomeArquivoAlvo=ui->arquivoAlvoCript->text();
	if(this->nomeArquivoAlvo==""){
		QMessageBox::information(this,tr("Aviso!"),tr("Por favor, entre com o nome do arquivo alvo..."));
		return;
	}
	this->nomeArquivoChave=ui->arquivoChaveCript->text();

	vector<char> key;
	if(usarArquivoChave){
		if(this->nomeArquivoChave==""){
			QMessageBox::information(this,tr("Aviso!"),tr("Por favor, entre com o nome do arquivo chave..."));
			return;
		}
		FILE* fin=fopen(this->nomeArquivoChave.toAscii(),"rb");
		if(!fin){
			QMessageBox::information(this,tr("Aviso!"),tr("Falha ao abrir arquivo:")+this->nomeArquivoChave);
			return;
		}
		while(!feof(fin)){
			char c;
			fread(&c,sizeof(char),1,fin);
			key.push_back(c);
		}
	}else{
		bool ok;
		QString s1=QInputDialog::getText(this,tr("PASME"),tr("Crie uma senha:"),QLineEdit::Password,
				QString::null, &ok );
		if(!ok) return;

		QString s2=QInputDialog::getText(this, tr("PASME"), tr("Por favor, repita a senha:"), QLineEdit::Password,
				QString::null, &ok );
		if(!ok) return;

		if(s1!=s2){
			QMessageBox::information(this,tr("Aviso!"),tr("As senhas digitadas são diferentes..."));
			return;
		}
		for(int i=0;i<s1.size();i++) key.push_back(s1.at(i).toAscii());
	}

	pc.set(ui->pA->value(),ui->pB->value(),ui->pC->value(),ui->pD->value(),ui->pTamChave->value());
	QString fn=QFileDialog::getSaveFileName(this, tr("Arquivo onde será armazenada a informação encriptada"),".");
	if(fn==""){
		QMessageBox::information(this,tr("Aviso!"),tr("Por favor, entre com o nome do arquivo onde a informação encriptada será armazenada..."));
		return;
	}
	this->hide();
	switch(this->tipoAlgoritmoCriptografia){
		case PASME:
			encripta_PASME(key,this->nomeArquivoAlvo.toAscii(),fn.toAscii(),&this->pc,this);
		break;


		case XOR:
			encripta_XOR(key,this->nomeArquivoAlvo.toAscii(),fn.toAscii(),&this->pc,this);
		break;
	}
	this->show();

}

void MainWindow::chamarDesencriptador(){
	this->nomeArquivoAlvo=ui->arquivoAlvoCript->text();
	this->nomeArquivoChave=ui->arquivoChaveCript->text();

	vector<char> key;
	if(usarArquivoChave){
		if(this->nomeArquivoChave==""){
			QMessageBox::information(this,tr("Aviso!"),tr("Por favor, entre com o nome do arquivo chave..."));
			return;
		}
		FILE* fin=fopen(this->nomeArquivoChave.toAscii(),"rb");
		if(!fin){
			QMessageBox::information(this,tr("Aviso!"),tr("Falha ao abrir arquivo:")+this->nomeArquivoChave);
			return;
		}
		while(!feof(fin)){
			char c;
			fread(&c,sizeof(char),1,fin);
			key.push_back(c);
		}
	}else{
		bool ok;
		QString s1=QInputDialog::getText(this,
				tr("PASME"), tr("Entre com a senha:"), QLineEdit::Password,
				QString::null, &ok);
		if(!ok) return;
		for(int i=0;i<s1.size();i++) key.push_back(s1.at(i).toAscii());
	}

	pc.set(ui->pA->value(),ui->pB->value(),ui->pC->value(),ui->pD->value(),ui->pTamChave->value());

	QString fn=QFileDialog::getSaveFileName(this, tr("Arquivo onde será armazenada a informação desencriptada"),".");
	if(fn==""){
		QMessageBox::information(this,tr("Aviso!"),tr("Por favor, entre com o nome do arquivo onde a informação desencriptada será armazenada..."));
		return;
	}
	this->hide();
	switch(this->tipoAlgoritmoCriptografia){
		case PASME:
			desencripta_PASME(key,this->nomeArquivoAlvo.toAscii(),fn.toAscii(),&this->pc,this);
		break;

		case XOR:
			desencripta_XOR(key,this->nomeArquivoAlvo.toAscii(),fn.toAscii(),&this->pc,this);
		break;

	}
	this->show();
}


void MainWindow::isXORclicked(){
	tipoAlgoritmoCriptografia=XOR;
	ui->isXOR->setChecked(true);
	ui->isPasme->setChecked(false);
}

void MainWindow::isPASMEclicked(){
	tipoAlgoritmoCriptografia=PASME;
	ui->isPasme->setChecked(true);
	ui->isXOR->setChecked(false);
}

void MainWindow::capturarNomeArquivoAlvo(){
	this->nomeArquivoAlvo=QFileDialog::getOpenFileName(this, tr("Arquivo que vai ser encriptado/desencriptado"),".");
	ui->arquivoAlvoCript->setText(this->nomeArquivoAlvo);
}

void MainWindow::capturarNomeArquivoChave(){
	this->nomeArquivoChave=QFileDialog::getOpenFileName(this, tr("Arquivo que vai ser usado como chave"),".");
	ui->arquivoChaveCript->setText(this->nomeArquivoChave);
}

void MainWindow::useArquivoChaveClicked(){
	this->usarArquivoChave=!this->usarArquivoChave;
}

void MainWindow::chamarAjuda(){
	ajuda w;
	this->hide();
	w.show();
	w.exec();
	this->show();
}

void MainWindow::chamarSobre(){
	sobre w;
	this->hide();
	w.show();
	w.exec();
	this->show();
}
