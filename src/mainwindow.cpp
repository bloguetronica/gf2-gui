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


// Includes
#include <QFileDialog>
#include <QMessageBox>
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
    ui->pushButtonClear->setFocus();
    filepath_ = QDir::homePath();
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

void MainWindow::on_actionLoad_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Load Settings from File"), filepath_, tr("XML files (*.xml);;All files (*)"));
    if (!filename.isEmpty())  // Note that the previous dialog will return an empty string if the user cancels it
    {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox errorRead;
            errorRead.critical(this, tr("Error"), tr("Could not read from %1.\n\nPlease verify that you have read access to this file.").arg(QDir::toNativeSeparators(filename)));
        }
        else
        {
            QDomDocument document;
            bool error = !document.setContent(&file);
            file.close();
            if (error)
            {
                QMessageBox errorInvalid;
                errorInvalid.critical(this, tr("Error"), tr("Invalid XML. The file might be corrupted or incomplete."));
            }
            else
            {
                QDomElement root = document.firstChildElement();
                if (root.tagName() != "settings" || root.attribute("target") != "GF2")
                {
                    QMessageBox errorNoSettings;
                    errorNoSettings.critical(this, tr("Error"), tr("The selected file is not a GF2 settings file."));
                }
                else
                {
                    int errorcount = implementSettings(root);
                    if (errorcount > 0)
                    {
                        QMessageBox warningDebug;
                        warningDebug.warning(this, tr("Warning"), tr("Found %1 setting(s) with invalid attribute values.\n\nPlease check your settings file for out-of-bounds or unsupported attribute values.").arg(errorcount));
                    }
                    filepath_ = filename;
                }
            }
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Settings to File"), filepath_, tr("XML files (*.xml);;All files (*)"));
    if (!filename.isEmpty())  // Note that the previous dialog will return an empty string if the user cancels it
    {
        QDomDocument document;
        QDomProcessingInstruction instruction = document.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
        document.appendChild(instruction);
        QDomElement root = document.createElement("settings");
        root.setAttribute("target", "GF2");
        document.appendChild(root);
        if (ui->comboBoxWave->currentIndex() == 0)
            appendSetting(document, root, "waveform", "sinusoidal");
        else if (ui->comboBoxWave->currentIndex() == 1)
            appendSetting(document, root, "waveform", "triangular");
        appendSetting(document, root, "frequency_0", QString::number(ui->doubleSpinBoxFreq0->value()));
        appendSetting(document, root, "frequency_1", QString::number(ui->doubleSpinBoxFreq1->value()));
        if (ui->radioButtonSelFreq0->isChecked())
            appendSetting(document, root, "active_frequency", "frequency_0");
        else if (ui->radioButtonSelFreq1->isChecked())
            appendSetting(document, root, "active_frequency", "frequency_1");
        appendSetting(document, root, "phase_0", QString::number(ui->doubleSpinBoxPhase0->value()));
        appendSetting(document, root, "phase_1", QString::number(ui->doubleSpinBoxPhase1->value()));
        if (ui->radioButtonSelPhase0->isChecked())
            appendSetting(document, root, "active_phase", "phase_0");
        else if (ui->radioButtonSelPhase1->isChecked())
            appendSetting(document, root, "active_phase", "phase_1");
        appendSetting(document, root, "amplitude", QString::number(ui->doubleSpinBoxAmp->value()));
        if (ui->checkBoxZload->isChecked())
            appendSetting(document, root, "50r_load", "on");
        else
            appendSetting(document, root, "50r_load", "off");
        if (ui->radioButtonDACOn->isChecked())
            appendSetting(document, root, "dac_state", "on");
        else if (ui->radioButtonDACOff->isChecked())
            appendSetting(document, root, "dac_state", "off");
        if (ui->radioButtonClkOn->isChecked())
            appendSetting(document, root, "clock_state", "on");
        else if (ui->radioButtonClkOff->isChecked())
            appendSetting(document, root, "clock_state", "off");
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox errorWrite;
            errorWrite.critical(this, tr("Error"), tr("Could not write to %1.\n\nPlease verify that you have write access to this file.").arg(QDir::toNativeSeparators(filename)));
        }
        else
        {
            QTextStream out(&file);
            out.setCodec("UTF-8");
            out << document.toString();
            file.close();
            filepath_ = filename;
        }
    }
}

void MainWindow::on_actionSerial_triggered()
{
    Serial serial;
    serial.setSerialLineEditText(serialstr_);
    if (serial.exec() == QDialog::Accepted)
    {
        serialstr_ = serial.serialLineEditText();
        if (serialstr_.isEmpty())
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
    if (ui->actionAutoApply->isChecked())
    {
        if(index == 0)
            execute(("gf2-sine " + serialstr_).simplified());
        else if (index == 1)
            execute(("gf2-tri " + serialstr_).simplified());
    }
}

void MainWindow::on_doubleSpinBoxAmp_valueChanged(const QString &arg)
{
    if (ui->actionAutoApply->isChecked())
    {
        QString zload;
        if (ui->checkBoxZload->isChecked())
            zload = "50";
        execute(("gf2-amp" + zload + " " + arg + " " + serialstr_).simplified());
    }
}

void MainWindow::on_doubleSpinBoxFreq0_valueChanged(const QString &arg)
{
    if (ui->actionAutoApply->isChecked())
        execute(("gf2-freq0 " + arg + " " + serialstr_).simplified());
}

void MainWindow::on_doubleSpinBoxFreq1_valueChanged(const QString &arg)
{
    if (ui->actionAutoApply->isChecked())
        execute(("gf2-freq1 " + arg + " " + serialstr_).simplified());
}

void MainWindow::on_doubleSpinBoxPhase0_valueChanged(const QString &arg)
{
    if (ui->actionAutoApply->isChecked())
        execute(("gf2-phase0 " + arg + " " + serialstr_).simplified());
}

void MainWindow::on_doubleSpinBoxPhase1_valueChanged(const QString &arg)
{
    if (ui->actionAutoApply->isChecked())
        execute(("gf2-phase1 " + arg + " " + serialstr_).simplified());
}

void MainWindow::on_pushButtonApply_clicked()
{
    QString amp, clkstate, dacstate, freq0, freq1, fsel, phase0, phase1, psel, wave, zload;
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
    execute(("gf2-" + wave + " " + serialstr_ + " && gf2-freq0 " + freq0 + " " + serialstr_ + " && gf2-freq1 " + freq1 + " " + serialstr_ + " && gf2-selfreq" + fsel + " " + serialstr_ + " && gf2-phase0 " + phase0 + " " + serialstr_ + " && gf2-phase1 " + phase1 + " " + serialstr_ + " && gf2-selphase" + psel + " " + serialstr_ + " && gf2-amp" + zload + " " + amp + " " + serialstr_ + " && gf2-dac" + dacstate + " " + serialstr_ + " && gf2-clk" + clkstate + " " + serialstr_).simplified());
}

void MainWindow::on_pushButtonClear_clicked()
{
    execute(("gf2-clear " + serialstr_).simplified());
}

void MainWindow::on_pushButtonReset_clicked()
{
    if (ui->actionResetClear->isChecked())
        execute(("gf2-reset " + serialstr_ + " && sleep 2 && gf2-clear " + serialstr_).simplified());
    else
        execute(("gf2-reset " + serialstr_).simplified());
}

void MainWindow::on_pushButtonStart_clicked()
{
    execute(("gf2-start " + serialstr_).simplified());
}

void MainWindow::on_pushButtonStop_clicked()
{
    execute(("gf2-stop " + serialstr_).simplified());
}

void MainWindow::on_radioButtonClkOff_clicked()
{
    execute(("gf2-clkoff " + serialstr_).simplified());
}

void MainWindow::on_radioButtonClkOn_clicked()
{
    execute(("gf2-clkon " + serialstr_).simplified());
}

void MainWindow::on_radioButtonDACOff_clicked()
{
    execute(("gf2-dacoff " + serialstr_).simplified());
}

void MainWindow::on_radioButtonDACOn_clicked()
{
    execute(("gf2-dacon " + serialstr_).simplified());
}

void MainWindow::on_radioButtonSelFreq0_clicked()
{
    execute(("gf2-selfreq0 " + serialstr_).simplified());
}

void MainWindow::on_radioButtonSelFreq1_clicked()
{
    execute(("gf2-selfreq1 " + serialstr_).simplified());
}

void MainWindow::on_radioButtonSelPhase0_clicked()
{
    execute(("gf2-selphase0 " + serialstr_).simplified());
}

void MainWindow::on_radioButtonSelPhase1_clicked()
{
    execute(("gf2-selphase1 " + serialstr_).simplified());
}

void MainWindow::appendSetting(QDomDocument &document, QDomElement &parent, const QString &name, const QString &value)
{
    QDomElement element = document.createElement("setting");
    element.setAttribute("value", value);
    element.setAttribute("name", name);
    parent.appendChild(element);
}

int MainWindow::implementSettings(const QDomElement &parent)
{
    int errcnt = 0;
    QDomNodeList settings = parent.elementsByTagName("setting");
    int cnt = settings.count();
    for (int i = 0; i < cnt; ++i)  // Modifier settings
    {
        QDomNode node = settings.item(i);
        if (node.isElement())
        {
            QDomElement element = node.toElement();
            if(element.attribute("name").toLower() == "50r_load")
            {
                QString value = element.attribute("value").toLower();
                if (value == "on")
                    ui->checkBoxZload->setChecked(true);
                else if (value == "off")
                    ui->checkBoxZload->setChecked(false);
                else
                    ++errcnt;
            }
        }
    }
    for (int i = 0; i < cnt; ++i)  // Normal settings
    {
        QDomNode node = settings.item(i);
        if (node.isElement())
        {
            QDomElement element = node.toElement();
            QString name = element.attribute("name").toLower();
            if(name == "active_frequency")
            {
                QString value = element.attribute("value").toLower();
                if (value == "frequency_0")
                    ui->radioButtonSelFreq0->click();
                else if (value == "frequency_1")
                    ui->radioButtonSelFreq1->click();
                else
                    ++errcnt;
            }
            else if(name == "active_phase")
            {
                QString value = element.attribute("value").toLower();
                if (value == "phase_0")
                    ui->radioButtonSelPhase0->click();
                else if (value == "phase_1")
                    ui->radioButtonSelPhase1->click();
                else
                    ++errcnt;
            }
            else if(name == "amplitude")
            {
                bool ok;
                double value = element.attribute("value").toDouble(&ok);
                if (ok && value >= ui->doubleSpinBoxAmp->minimum() && value <= ui->doubleSpinBoxAmp->maximum())
                    ui->doubleSpinBoxAmp->setValue(value);
                else
                    ++errcnt;
            }
            else if(name == "clock_state")
            {
                QString value = element.attribute("value").toLower();
                if (value == "on")
                    ui->radioButtonClkOn->click();
                else if (value == "off")
                    ui->radioButtonClkOff->click();
                else
                    ++errcnt;
            }
            else if(name == "dac_state")
            {
                QString value = element.attribute("value").toLower();
                if (value == "on")
                    ui->radioButtonDACOn->click();
                else if (value == "off")
                    ui->radioButtonDACOff->click();
                else
                    ++errcnt;
            }
            else if(name == "frequency_0")
            {
                bool ok;
                double value = element.attribute("value").toDouble(&ok);
                if (ok && value >= ui->doubleSpinBoxFreq0->minimum() && value <= ui->doubleSpinBoxFreq0->maximum())
                    ui->doubleSpinBoxFreq0->setValue(value);
                else
                    ++errcnt;
            }
            else if(name == "frequency_1")
            {
                bool ok;
                double value = element.attribute("value").toDouble(&ok);
                if (ok && value >= ui->doubleSpinBoxFreq1->minimum() && value <= ui->doubleSpinBoxFreq1->maximum())
                    ui->doubleSpinBoxFreq1->setValue(value);
                else
                    ++errcnt;
            }
            else if(name == "phase_0")
            {
                bool ok;
                double value = element.attribute("value").toDouble(&ok);
                if (ok && value >= ui->doubleSpinBoxPhase0->minimum() && value <= ui->doubleSpinBoxPhase0->maximum())
                    ui->doubleSpinBoxPhase0->setValue(value);
                else
                    ++errcnt;
            }
            else if(name == "phase_1")
            {
                bool ok;
                double value = element.attribute("value").toDouble(&ok);
                if (ok && value >= ui->doubleSpinBoxPhase1->minimum() && value <= ui->doubleSpinBoxPhase1->maximum())
                    ui->doubleSpinBoxPhase1->setValue(value);
                else
                    ++errcnt;
            }
            else if(name == "waveform")
            {
                QString value = element.attribute("value").toLower();
                if (value == "sinusoidal")
                    ui->comboBoxWave->setCurrentIndex(0);
                else if (value == "triangular")
                    ui->comboBoxWave->setCurrentIndex(1);
                else
                    ++errcnt;
            }
        }
    }
    return errcnt;
}

void MainWindow::execute(const QString &command)
{
    QProcess sh;
    ui->textBrowserCommand->append("$ " + command);
    sh.setProcessChannelMode(QProcess::MergedChannels);
    sh.start("sh", QStringList() << "-c" << command);
    sh.waitForFinished();
    QString result = sh.readAll();
    result.chop(1);
    ui->textBrowserCommand->append(result);
    sh.close();
}
