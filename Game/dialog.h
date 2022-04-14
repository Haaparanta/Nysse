#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Dialog;
}

namespace Mikael {


class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void accept();    

signals:
    // Ask name and send it upon accepting
    void sendName (QString name);    

private slots:
    void on_buttonAcceptName_clicked();

    // Name of the player
    void on_lineEditName_textChanged(const QString &arg1);

    void on_buttonQuit_clicked();

private:
    Ui::Dialog *ui;
};
}

#endif // DIALOG_H
