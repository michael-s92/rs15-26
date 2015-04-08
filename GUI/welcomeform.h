#ifndef WELCOMEFORM_H
#define WELCOMEFORM_H

#include <QWidget>

namespace Ui {
class WelcomeForm;
}

class WelcomeForm : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeForm(QWidget *parent = 0);
    ~WelcomeForm();

private slots:
    void onload();

private:
    Ui::WelcomeForm *ui;
};

#endif // WELCOMEFORM_H
