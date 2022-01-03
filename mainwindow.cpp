#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTimer>
#include <stdlib.h>


uint8_t countH = 0;
uint8_t countM = 0;
uint8_t setH = 0;
uint8_t setM = 0;
bool startCounter = false;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(401, 193)); // Fix window size

    // Set timer to call function setCounter every tick
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(setCounter()));
    timer->start(60000); //timer tick: 1 min
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ApplyBtn_clicked() //Start button
{
    startCounter = true;
    countH = ui->SetH->value();
    countM = ui->SetM->value();
    ui->CountH->display(countH);
    ui->CountM->display(countM);
    ui->statusbar->showMessage("Countdown started ...");
}

void MainWindow::setCounter() //Counting fuction
{
    if (startCounter == true)
    {
        ui->CountH->display(countH);
        ui->CountM->display(countM);
        if (countH != 0 && countM ==0){
            countM = 59;
            countH--;
        }

        else if (countH == 0 && countM == 0)
        {
            ui->statusbar->showMessage("Shutting down");
            startCounter = false;

            system("c:\\windows\\system32\\shutdown /s"); //Windows shutdown

            ui->statusbar->showMessage("Quitting application");
            QApplication::quit();
        }
        else{
            countM--;
        }
     }

}

void MainWindow::on_CancelBtn_clicked() //Stop counting
{
    startCounter = false;
    ui->statusbar->showMessage("Countdown stopped");
}


void MainWindow::on_pushButton_clicked() //Resume counting
{
    startCounter = true;
    ui->statusbar->showMessage("Countdown started ...");
}

