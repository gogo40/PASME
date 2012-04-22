#include "ajuda.h"
#include "ui_ajuda.h"

ajuda::ajuda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajuda)
{
    ui->setupUi(this);
}

ajuda::~ajuda()
{
    delete ui;
}
