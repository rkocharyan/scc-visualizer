#ifndef ANIMATIONSPEEDDIALOG_H
#define ANIMATIONSPEEDDIALOG_H

#include <QDialog>

namespace Ui {
class AnimationSpeed;
}

class AnimationSpeed : public QDialog
{
    Q_OBJECT

public:
    explicit AnimationSpeed(qreal currentSpeed, QWidget *parent = nullptr);
    ~AnimationSpeed();

private:
    Ui::AnimationSpeed *ui;
};

#endif // ANIMATIONSPEEDDIALOG_H
