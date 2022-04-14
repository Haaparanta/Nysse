#include "dialog.h"
#include "ui_dialog.h"

Mikael::Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->buttonAcceptName->setDisabled(true);
    ui->lineEditName->setPlaceholderText("Enter hero name");
    ui->buttonQuit->setText("Quit");
    ui->buttonQuit->setStyleSheet("background-color: red");

    connect(ui->buttonAcceptName, &QPushButton::clicked,
            this, &Dialog::accept);

    connect(ui->buttonQuit, &QPushButton::clicked,
            this, &Dialog::reject);

    this->setFixedSize(500, 500);
    this->setWindowTitle("Nysse meni Vaasaan!");

    ui->buttonAcceptName->setGeometry(190, 400, 120, 25);
    ui->lineEditName->setGeometry(150, 350, 200, 25);
    ui->textBrowser->setGeometry(50, 50, 400, 250);
    ui->buttonQuit->setGeometry(50, 450, 50, 25);

    QFile file(":/dialog_intro.txt");

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        ui->textBrowser->setText(in.readAll());
    }
}

Mikael::Dialog::~Dialog()
{
    delete ui;
}

void Mikael::Dialog::accept()
{
    QString playerName = ui->lineEditName->text().trimmed();
    emit sendName(playerName);
    QDialog::accept();
}


void Mikael::Dialog::on_buttonAcceptName_clicked()
{
    close();
}

void Mikael::Dialog::on_lineEditName_textChanged(const QString &arg1)
{
    // Name must contain letters, empty gets trimmed
    if ( arg1.trimmed().isEmpty()) {
        ui->buttonAcceptName->setDisabled(true);
    } else {
        ui->buttonAcceptName->setEnabled(true);
    }
}

void Mikael::Dialog::on_buttonQuit_clicked()
{
    close();
}
