/* GF2 GUI - Version 2.0 for Debian Linux
   Copyright (c) 2018-2019 Samuel Lourenço

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


#ifndef SERIAL_H
#define SERIAL_H

// Includes
#include <QDialog>

namespace Ui {
class Serial;
}

class Serial : public QDialog
{
    Q_OBJECT

public:
    explicit Serial(QWidget *parent = 0);
    ~Serial();
    QString serialLineEditText() const;
    void setSerialLineEditText(const QString &serialstr);

private slots:
    void on_pushButtonRefresh_clicked();

private:
    Ui::Serial *ui;
    void list();
};

#endif // SERIAL_H
