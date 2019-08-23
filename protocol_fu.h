#ifndef PROTOCOL_FU_H
#define PROTOCOL_FU_H

#include <QByteArray>
#include <QMap>

/*!
 * \brief The Protocol_FU class
 *
 * JSON file that contains all needed info for update software
 *
 * Example:
 *
 * {
 *     "programName": "Your_Software_Name",
 *     "actualVersion": "3.7.6.6",
 *     "versions":
 *     {
 *          3766:
 *          {
 *               "desc": "Some update info",
 *               "updateFiles":
 *               {
 *                  "app.exe": "https://cloud.your_site.com/index.php/s/K2Tbejh54fvsEVdJI/download",
 *                  "test.ini": "https://cloud.your_site.com/index.php/s/K2Tbehgj7fs675fj/download"
 *               }
 *          },
 *          3765:
 *          {
 *               "desc": "
 *               <p>3.7.6.5</p>
 *               <ul>
 *                 <li>Description can be html-like.</li>
 *               </ul>
 *               ",
 *               "updateFiles":
 *               {
 *                  "need.dll": "https://cloud.your_site.com/index.php/s/K2Tbejh54fvsEVdJI/download",
 *                  "test.sh": "https://cloud.your_site.com/index.php/s/K2Tbejhf88vsEVdJI/download"
 *               }
 *          },
 *          3764:
 *          {
 *               "desc": "Another description",
 *               "updateFiles":
 *               {
 *                  "app.exe": "https://cloud.your_site.com/index.php/s/K2Tbejh54fvsEVdJI/download"
 *               }
 *          }
 *          <...>
 *     }
 * }
 *
 */
class Protocol_FU
{
    const struct Keys
    {
        const QString programName = "programName";
        const QString actualVersion = "actualVersion";
        const QString desc = "desc";
        const QString updateFiles = "updateFiles";
    } _keys;

    bool _isValid = false;
    QString _programName = "Unknown";
    int _version = 0;
    QString _beautyVersion;
    QString _description;
    QMap<QString,QString> _fileNameUrlList;

public:
    explicit Protocol_FU(int currentVersion, const QByteArray &msg);
    ~Protocol_FU(){}
    bool isValid() { return _isValid; }
    QString programName() const { return _programName; }
    int version() const { return _version; }
    QString beautyVersion() const { return _beautyVersion; }
    QString description() const { return _description; }
    QMap<QString,QString> fileNameUrlList() const { return _fileNameUrlList; }
};

#endif // PROTOCOL_FU_H
