#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QFile>
#include <QDir>
#include "protocol_fu.h"
#include "downloader_fu.h"

Downloader_FU::Downloader_FU(QObject *parent) : QObject(parent)
{
    _manager = new QNetworkAccessManager(this);
    connect(_manager, &QNetworkAccessManager::authenticationRequired, this, &Downloader_FU::auth);
    connect(_manager, &QNetworkAccessManager::finished, this, &Downloader_FU::getReply);
}

void Downloader_FU::checkUpdate(const QString &updateStr, int version)
{
    _version = version;
    download(updateStr);
}

void Downloader_FU::getReply(QNetworkReply *reply)
{
    QString errStr;

    switch(reply->error())
    {
        case QNetworkReply::ConnectionRefusedError: errStr = tr("Connection refused.");
            break;
        case QNetworkReply::RemoteHostClosedError: errStr = tr("Connection closed.");
            break;
        case QNetworkReply::HostNotFoundError: errStr = tr("Host not found.");
            break;
        case QNetworkReply::TimeoutError: errStr = tr("Timeout error.");
            break;
        case QNetworkReply::NoError: break;
        default: errStr = reply->errorString();
    }

    if(!errStr.trimmed().isEmpty())
    {
        emit error(tr("Server error! %1").arg(errStr));
        return;
    }

    QByteArray r = reply->readAll();

    if(r.trimmed().isEmpty())
    {
        emit error(tr("No update data."));
        return;
    }

    Protocol_FU p(_version, r);
    if(p.isValid())
    {
        _downloadMap = p.fileNameUrlList();

        Content_FU c;
        c.version = p.version();
        c.desc = p.description();
        c.beautyVersion = p.beautyVersion();
        c.filesSize = _downloadMap.size();

        if(c.version > _version)
            emit newVersionAvailable(&c);
        else
            emit noNewVersion();
    }
    else
    {
        QString key = _downloadMap.key(reply->url().toString(), "");
        if(!key.trimmed().isEmpty())
        {
            QDir d(QDir::current().path() + "/fu_update");

            if(!d.exists())
                d.mkdir(d.path());

            QFile f(d.dirName() + "/" + key);
            if(!f.open(QIODevice::WriteOnly))
            {
                emit error(tr("File open error: %1").arg(key));
                return;
            }

            f.write(r);
            f.close();            
            _downloadMap.remove(key);
            downloadUpdate();
        }
        else
            emit error(tr("Unknown server reply. "
                          "Check the update file for correct input."));
    }
}

void Downloader_FU::download(const QString &url)
{
    QNetworkRequest request(url);
    _manager->get(request);
}

void Downloader_FU::auth(QNetworkReply *reply, QAuthenticator *authenticatior)
{
    Q_UNUSED(reply)

    authenticatior->setUser(_userName);
    authenticatior->setPassword(_password);
}

void Downloader_FU::downloadUpdate()
{
    emit filesRemain(_downloadMap.size());

    if(!_downloadMap.isEmpty())
    {
        _fileNames << _downloadMap.firstKey();
        download(_downloadMap.first());
    }
    else
        emit successDownloadUpdate();
}
