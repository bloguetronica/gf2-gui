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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Includes
#include <QMainWindow>
#include <QtXml>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();
    void on_actionLoad_triggered();
    void on_actionSave_triggered();
    void on_actionSerial_triggered();
    void on_checkBoxZload_stateChanged();
    void on_comboBoxWave_currentIndexChanged(int index);
    void on_doubleSpinBoxAmp_valueChanged(const QString &arg);
    void on_doubleSpinBoxFreq0_valueChanged(const QString &arg);
    void on_doubleSpinBoxFreq1_valueChanged(const QString &arg);
    void on_doubleSpinBoxPhase0_valueChanged(const QString &arg);
    void on_doubleSpinBoxPhase1_valueChanged(const QString &arg);
    void on_pushButtonApply_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonReset_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_radioButtonClkOff_clicked();
    void on_radioButtonClkOn_clicked();
    void on_radioButtonDACOff_clicked();
    void on_radioButtonDACOn_clicked();
    void on_radioButtonSelFreq0_clicked();
    void on_radioButtonSelFreq1_clicked();
    void on_radioButtonSelPhase0_clicked();
    void on_radioButtonSelPhase1_clicked();

private:
    Ui::MainWindow *ui;
    QString filepath_, serialstr_;
    void appendSetting(QDomDocument &doc, QDomElement &parent, const QString &name, const QString &value);
    int implementSettings(const QDomElement &parent);
    void execute(const QString &command);
};

#endif // MAINWINDOW_H
