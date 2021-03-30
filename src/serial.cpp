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
#include "serial.h"
#include "ui_serial.h"

Serial::Serial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Serial)
{
    QProcess sh;
    ui->setupUi(this);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << "gf2-list");
    sh.waitForFinished();
    ui->textBrowserList->append(sh.readAll());
    sh.close();
}

Serial::~Serial()
{
    delete ui;
}

QString Serial::getSerial()
{
    QString serialstr = ui->lineEditSerial->text().simplified();
    serialstr.remove(" ");
    serialstr.remove("&");
    serialstr.remove("|");
    serialstr.remove("(");
    serialstr.remove(")");
    return serialstr;
}

void Serial::on_pushButtonRefresh_clicked()
{
    QProcess sh;
    ui->textBrowserList->clear();
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << "gf2-list");
    sh.waitForFinished();
    ui->textBrowserList->append(sh.readAll());
    sh.close();
}
