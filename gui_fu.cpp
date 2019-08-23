#include <QMessageBox>
#include "gui_fu.h"
#include "ui_gui_fu.h"

Gui_FU::Gui_FU(const QString &version, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gui_FU)
{
    ui->setupUi(this);

    setWindowTitle(tr("Update master"));

    connect(ui->closeBtn, &QPushButton::clicked, this, &Gui_FU::accept);
    connect(ui->checkUpdBtn, &QPushButton::clicked, this, &Gui_FU::checkUpdate);
    connect(ui->downloadBtn, &QPushButton::clicked, this, &Gui_FU::downloadUpdate);
    connect(ui->installBtn, &QPushButton::clicked, this, &Gui_FU::install);

    ui->availableVersionLbl->setVisible(false);
    ui->availableversionValueLbl->setVisible(false);
    ui->currentVerLbl->setText(version);
    ui->installBtn->setVisible(false);
}

Gui_FU::~Gui_FU()
{
    delete ui;
}

bool Gui_FU::askForRestart()
{
    return !QMessageBox::question(0, tr("Retstart application"), tr("Do you want to restart the app?"),
                                  tr("Yes"), tr("No"));
}

void Gui_FU::updateAvailable(const QString &version, const QString &desc, int filesSize)
{
    ui->downloadBtn->setEnabled(true);
    ui->descLabel->setText(desc);
    ui->availableVersionLbl->setVisible(true);
    ui->availableversionValueLbl->setVisible(true);
    ui->availableversionValueLbl->setText(version);
    ui->downloadBar->setMaximum(filesSize);
    ui->checkUpdBtn->setEnabled(false);
}

void Gui_FU::showError(const QString &err)
{
    QMessageBox::critical(0, tr("Error"), err);
}

void Gui_FU::showStatus(const QString &err)
{
    ui->statusLabel->setText(err);
}

void Gui_FU::successDownloadUpdate()
{
    ui->statusLabel->setText(tr("Update successfully downloaded!"));
    ui->downloadBtn->setVisible(false);
    ui->installBtn->setVisible(true);
}

void Gui_FU::updateProgress(int remain)
{
    ui->downloadBar->setValue(ui->downloadBar->maximum() - remain);
}
