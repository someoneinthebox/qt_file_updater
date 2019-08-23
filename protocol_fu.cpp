#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include "protocol_fu.h"

Protocol_FU::Protocol_FU(int currentVersion, const QByteArray &msg)
{
    QJsonDocument doc = QJsonDocument::fromJson(msg);

    if(doc.isNull() || !doc.isObject())
        return;

    QJsonObject mainObj = doc.object();

    if(mainObj.isEmpty() || !mainObj.contains("versions"))
        return;

    if(mainObj.contains(_keys.programName))
        _programName = mainObj.value(_keys.programName).toString();

    if(mainObj.contains(_keys.actualVersion))
        _beautyVersion = mainObj.value(_keys.actualVersion).toString();

    QJsonObject versionsObj = mainObj.value("versions").toObject();

    QVector<int> versSortList;
    for(QString k : versionsObj.keys())
    {
        int version = k.toInt();
        if(currentVersion < version)
            versSortList << k.toInt();
    }

    qSort(versSortList);

    for(int v : versSortList)
    {
        _version = v;

        QJsonObject itemObj = versionsObj.value(QString::number(v)).toObject();

        if(itemObj.contains(_keys.desc))
            _description += itemObj.value(_keys.desc).toString();

        if(itemObj.contains(_keys.updateFiles))
        {
            QJsonObject urlListObj = itemObj.value(_keys.updateFiles).toObject();
            for(QString key : urlListObj.keys())
            {
                QString url = urlListObj.value(key).toString().trimmed();
                if(!url.isEmpty())
                    _fileNameUrlList.insert(key, url);
            }
        }
    }

    _isValid = true;
}
