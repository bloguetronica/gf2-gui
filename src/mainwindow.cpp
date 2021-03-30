/* GF2 GUI - Version 1.0 for Debian Linux
   Copyright (c) 2018 Samuel Lourenço

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation, either version 3 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <https://www.gnu.org/licenses/>.


   Please feel free to contact me via e-mail: samuel.fmlourenco@gmail.com */


// Includes
#include <QProcess>
#include "about.h"
#include "mainwindow.h"
#include "serial.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    About about;
    about.exec();
}

void MainWindow::on_actionSerial_triggered()
{
    Serial serial;
    if (serial.exec() == QDialog::Accepted)
    {
        serialstr_ = serial.getSerial();
        if (serialstr_ == "")
            this->setWindowTitle("GF2 Function Generator");
        else
            this->setWindowTitle("GF2 Function Generator (S/N: " + serialstr_ + ")");
    }
}

void MainWindow::on_checkBoxZload_stateChanged()
{
    if (ui->checkBoxZload->isChecked())
    {
        ui->doubleSpinBoxAmp->setValue(ui->doubleSpinBoxAmp->value() / 2);
        ui->doubleSpinBoxAmp->setSingleStep(0.05);
        ui->doubleSpinBoxAmp->setMaximum(4);
    }
    else
    {
        ui->doubleSpinBoxAmp->setMaximum(8);
        ui->doubleSpinBoxAmp->setSingleStep(0.1);
        ui->doubleSpinBoxAmp->setValue(ui->doubleSpinBoxAmp->value() * 2);
    }
}

void MainWindow::on_comboBoxWave_currentIndexChanged(int index)
{
    QProcess sh;
    QString command;
    if (ui->actionAutoApply->isChecked())
    {
        if(index == 0)
            command = ("gf2-sine " + serialstr_).simplified();
        else if (index == 1)
            command = ("gf2-tri " + serialstr_).simplified();
        ui->textBrowserCommand->append("$ " + command);
        sh.setProcessChannelMode(QProcess::MergedChannels);
        sh.start("sh", QStringList() << "-c" << command);
        sh.waitForFinished();
        ui->textBrowserCommand->append(sh.readAll());
        sh.close();
    }
}

void MainWindow::on_doubleSpinBoxAmp_valueChanged(const QString &arg)
{
    QProcess sh;
    QString command, zload;
    if (ui->actionAutoApply->isChecked())
    {
        if (ui->checkBoxZload->isChecked())
            zload = "50";
        command = ("gf2-amp" + zload + " " + arg + " " + serialstr_).simplified();
        ui->textBrowserCommand->append("$ " + command);
        sh.setProcessChannelMode(QProcess::MergedChannels);
        sh.start("sh", QStringList() << "-c" << command);
        sh.waitForFinished();
        ui->textBrowserCommand->append(sh.readAll());
        sh.close();
    }
}

void MainWindow::on_doubleSpinBoxFreq0_valueChanged(const QString &arg)
{
    QProcess sh;
    QString command;
    if (ui->actionAutoApply->isChecked())
    {
        command = ("gf2-freq0 " + arg + " " + serialstr_).simplified();
        ui->textBrowserCommand->append("$ " + command);
        sh.setProcessChannelMode(QProcess::MergedChannels);
        sh.start("sh", QStringList() << "-c" << command);
        sh.waitForFinished();
        ui->textBrowserCommand->append(sh.readAll());
        sh.close();
    }
}

void MainWindow::on_doubleSpinBoxFreq1_valueChanged(const QString &arg)
{
    QProcess sh;
    QString command;
    if (ui->actionAutoApply->isChecked())
    {
        command = ("gf2-freq1 " + arg + " " + serialstr_).simplified();
        command.simplified();
        ui->textBrowserCommand->append("$ " + command);
        sh.setProcessChannelMode(QProcess::MergedChannels);
        sh.start("sh", QStringList() << "-c" << command);
        sh.waitForFinished();
        ui->textBrowserCommand->append(sh.readAll());
        sh.close();
    }
}

void MainWindow::on_doubleSpinBoxPhase0_valueChanged(const QString &arg)
{
    QProcess sh;
    QString command;
    if (ui->actionAutoApply->isChecked())
    {
        command = ("gf2-phase0 " + arg + " " + serialstr_).simplified();
        ui->textBrowserCommand->append("$ " + command);
        sh.setProcessChannelMode(QProcess::MergedChannels);
        sh.start("sh", QStringList() << "-c" << command);
        sh.waitForFinished();
        ui->textBrowserCommand->append(sh.readAll());
        sh.close();
    }
}

void MainWindow::on_doubleSpinBoxPhase1_valueChanged(const QString &arg)
{
    QProcess sh;
    QString command;
    if (ui->actionAutoApply->isChecked())
    {
        command = ("gf2-phase1 " + arg + " " + serialstr_).simplified();
        ui->textBrowserCommand->append("$ " + command);
        sh.setProcessChannelMode(QProcess::MergedChannels);
        sh.start("sh", QStringList() << "-c" << command);
        sh.waitForFinished();
        ui->textBrowserCommand->append(sh.readAll());
        sh.close();
    }
}

void MainWindow::on_pushButtonApply_clicked()
{
    QProcess sh;
    QString amp, clkstate, command, dacstate, freq0, freq1, fsel, phase0, phase1, psel, wave, zload;
    amp = QString::number(ui->doubleSpinBoxAmp->value());
    if (ui->radioButtonClkOn->isChecked())
        clkstate = "on";
    else if (ui->radioButtonClkOff->isChecked())
        clkstate = "off";
    if (ui->radioButtonDACOn->isChecked())
        dacstate = "on";
    else if (ui->radioButtonDACOff->isChecked())
        dacstate = "off";
    freq0 = QString::number(ui->doubleSpinBoxFreq0->value());
    freq1 = QString::number(ui->doubleSpinBoxFreq1->value());
    if (ui->radioButtonSelFreq0->isChecked())
        fsel = "0";
    else if (ui->radioButtonSelFreq1->isChecked())
        fsel = "1";
    phase0 = QString::number(ui->doubleSpinBoxPhase0->value());
    phase1 = QString::number(ui->doubleSpinBoxPhase1->value());
    if (ui->radioButtonSelPhase0->isChecked())
        psel = "0";
    else if (ui->radioButtonSelPhase1->isChecked())
        psel = "1";
    if (ui->comboBoxWave->currentIndex() == 0)
        wave = "sine";
    else if (ui->comboBoxWave->currentIndex() == 1)
        wave = "tri";
    if (ui->checkBoxZload->isChecked())
        zload = "50";
    command = ("gf2-" + wave + " " + serialstr_ + " && gf2-freq0 " + freq0 + " " + serialstr_ + " && gf2-freq1 " + freq1 + " " + serialstr_ + " && gf2-selfreq" + fsel + " " + serialstr_ + " && gf2-phase0 " + phase0 + " " + serialstr_ + " && gf2-phase1 " + phase1 + " " + serialstr_ + " && gf2-selphase" + psel + " " + serialstr_ + " && gf2-amp" + zload + " " + amp + " " + serialstr_ + " && gf2-dac" + dacstate + " " + serialstr_ + " && gf2-clk" + clkstate + " " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_pushButtonClear_clicked()
{
    QProcess sh;
    QString command = ("gf2-clear " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_pushButtonReset_clicked()
{
    QProcess sh;
    QString command;
    if (ui->actionResetClear->isChecked())
        command = ("gf2-reset " + serialstr_ + " && sleep 2 && gf2-clear " + serialstr_).simplified();
    else
        command = ("gf2-reset " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_pushButtonStart_clicked()
{
    QProcess sh;
    QString command = ("gf2-start " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_pushButtonStop_clicked()
{
    QProcess sh;
    QString command = ("gf2-stop " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_radioButtonClkOff_clicked()
{
    QProcess sh;
    QString command = ("gf2-clkoff " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_radioButtonClkOn_clicked()
{
    QProcess sh;
    QString command = ("gf2-clkon " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_radioButtonDACOff_clicked()
{
    QProcess sh;
    QString command = ("gf2-dacoff " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_radioButtonDACOn_clicked()
{
    QProcess sh;
    QString command = ("gf2-dacon " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_radioButtonSelFreq0_clicked()
{
    QProcess sh;
    QString command = ("gf2-selfreq0 " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_radioButtonSelFreq1_clicked()
{
    QProcess sh;
    QString command = ("gf2-selfreq1 " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_radioButtonSelPhase0_clicked()
{
    QProcess sh;
    QString command = ("gf2-selphase0 " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}

void MainWindow::on_radioButtonSelPhase1_clicked()
{
    QProcess sh;
    QString command = ("gf2-selphase1 " + serialstr_).simplified();
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    ui->textBrowserCommand->append(sh.readAll());
    sh.close();
}
