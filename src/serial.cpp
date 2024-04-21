/* GF2 GUI - Version 2.1 for Debian Linux
   Copyright (c) 2018-2024 Samuel Lourenço

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
    ui->setupUi(this);
    list();
    ui->lineEditSerial->setValidator(new QRegExpValidator(QRegExp("[A-Za-z\\d-]{1,12}"), this));
}

Serial::~Serial()
{
    delete ui;
}

QString Serial::serialLineEditText() const
{
    return ui->lineEditSerial->text();
}

void Serial::setSerialLineEditText(const QString &serialstr)
{
    ui->lineEditSerial->setText(serialstr);
}

void Serial::on_pushButtonRefresh_clicked()
{
    ui->textBrowserList->clear();
    list();
}

void Serial::list()
{
    QProcess sh;
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << "gf2-list");
    sh.waitForFinished();
    QString result = sh.readAll();
    result.chop(1);
    ui->textBrowserList->append(result);
    sh.close();
}
