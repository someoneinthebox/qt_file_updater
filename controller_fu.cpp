#include <QDir>
#include <QApplication>
#include <QProcess>
#include "gui_fu.h"
#include "downloader_fu.h"
#include "controller_fu.h"

Controller_FU::Controller_FU(int version, const QString &checkVersionUrl, const QString &versionBeauty,
                             QObject *parent) : QObject(parent)
{
    _curVersion = version;
    _checkVersionUrl = checkVersionUrl;

    _gui = new Gui_FU(versionBeauty.trimmed().isEmpty() ? QString::number(version) : versionBeauty);
    _gui->setAttribute(Qt::WA_DeleteOnClose);

    _downloader = new Downloader_FU(this);

    connect(_downloader, &Downloader_FU::newVersionAvailable, this, &Controller_FU::contentAvailable);
    connect(_downloader, &Downloader_FU::error, _gui, &Gui_FU::showStatus);
    connect(_gui, &Gui_FU::checkUpdate, this, &Controller_FU::checkUpdate);
    connect(_gui, &Gui_FU::downloadUpdate, _downloader, &Downloader_FU::downloadUpdate);
    connect(_downloader, &Downloader_FU::filesRemain, _gui, &Gui_FU::updateProgress);
    connect(_downloader, &Downloader_FU::successDownloadUpdate, _gui, &Gui_FU::successDownloadUpdate);
    connect(_downloader, &Downloader_FU::noNewVersion, _gui, &Gui_FU::noNeedUpdate);
    connect(_gui, &Gui_FU::install, this, &Controller_FU::install);
}

int Controller_FU::exec()
{
    return _gui->exec();
}

void Controller_FU::checkUpdate()
{
    if(_checkVersionUrl.trimmed().isEmpty())
        return _gui->showError(tr("Update URL is empty!"));

    _downloader->checkUpdate(_checkVersionUrl, _curVersion);
}

void Controller_FU::contentAvailable(Content_FU *content)
{
    _gui->updateAvailable(!content->beautyVersion.trimmed().isEmpty() ? content->beautyVersion
                                                                      : QString::number(content->version),
                          content->desc, content->filesSize);
}

void Controller_FU::install()
{
    for(QString s : _downloader->getFileNames())
    {
        QDir d(QDir::currentPath() + "/fu_update/" + s);

        if(!d.exists(d.path()))
            return _gui->showError(tr("File for update not found!"));

        QFile fEx(s + "_bak");
        if(fEx.exists())
            fEx.remove();

        QFile::rename(s, s + "_bak");

        d.rename(d.path(), QDir::currentPath() + "/" + s);
    }

    _gui->showStatus(tr("Success update!"));

    if(_gui->askForRestart())
    {
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
}
