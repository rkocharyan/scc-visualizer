#ifndef ALGORITHMPICKERDIALOG_H
#define ALGORITHMPICKERDIALOG_H

#include <QDialog>

namespace Ui {
class AlgorithmPickerDialog;
}

class AlgorithmPickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlgorithmPickerDialog(QWidget *parent = nullptr);
    ~AlgorithmPickerDialog();

private:
    Ui::AlgorithmPickerDialog *ui;
};

#endif // ALGORITHMPICKERDIALOG_H
