#ifndef MAILDIALOG_H
#define MAILDIALOG_H

#include <QDialog>

namespace Ui {
class MailDialog;
}

class MailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MailDialog(QWidget *parent = 0);
    ~MailDialog();

private Q_SLOTS:
    void sendMail();

private:
    Ui::MailDialog *ui;
};

#endif // MAILDIALOG_H
