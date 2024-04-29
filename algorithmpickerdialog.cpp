#include "algorithmpickerdialog.h"
#include "ui_algorithmpickerdialog.h"

AlgorithmPickerDialog::AlgorithmPickerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AlgorithmPickerDialog)
{
    ui->setupUi(this);

    connect(ui->kosarajuButton, &QPushButton::clicked, this, [this]() {
        this->done(1);
    });

    connect(ui->tarjanButton, &QPushButton::clicked, this, [this]() {
        this->done(2);
    });
}

AlgorithmPickerDialog::~AlgorithmPickerDialog()
{
    delete ui;
}
