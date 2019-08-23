#ifndef DOWNLOADER_FU_H
#define DOWNLOADER_FU_H

#include <QMap>
#include <QObject>

/*!
 * \brief The Content_FU struct
 * Struct with update data
 */
struct Content_FU
{
    /*!
     * \brief version
     * Numeric version
     */
    int version = 0;
    /*!
     * \brief filesSize
     * Update file array size
     */
    int filesSize = 0;
    /*!
     * \brief beautyVersion
     * User-like version string
     */
    QString beautyVersion;
    /*!
     * \brief desc
     * Update description
     */
    QString desc;
};

class QNetworkAccessManager;
class QNetworkReply;
class QAuthenticator;
/*!
 * \brief The Downloader_FU class
 * Download manager
 */
class Downloader_FU : public QObject        
{
    Q_OBJECT

    QNetworkAccessManager *_manager = nullptr;
    QString _userName;
    QString _password;
    int _version = 0;
    QMap<QString,QString> _downloadMap;
    QStringList _fileNames;

    void download(const QString &url);

public:
    explicit Downloader_FU(QObject *parent = nullptr);
    ~Downloader_FU(){}
    /*!
     * \param updateStr
     * URL to update JSON file
     * \param version
     * Numeric version
     */
    void checkUpdate(const QString &updateStr, int version);
    /*!
     * \brief setUserName
     * Sets username if authentication required
     * \param userName
     * Username
     */
    void setUserName(const QString &userName) { _userName = userName; }
    /*!
     * \brief setPassword
     * Sets password if authentication required
     * \param password
     * Password
     */
    void setPassword(const QString &password) { _password = password; }
    /*!
     * \brief getFileNames
     * Filenames list for rename during update
     */
    QStringList getFileNames() const { return _fileNames; }

signals:
    /*!
     * \brief error
     * Error sig
     */
    void error(const QString &errStr);
    /*!
     * \brief newVersionAvailable
     * New version sig. Sending struct with update data.
     */
    void newVersionAvailable(Content_FU *content);
    /*!
     * \brief noNewVersion
     * No need update sig. It emits when the version is actual
     */
    void noNewVersion();
    /*!
     * \brief filesRemain
     * Remain files for download sig
     */
    void filesRemain(int nums);
    /*!
     * \brief successDownloadUpdate
     * Success files download sig
     */
    void successDownloadUpdate();

private slots:
    void getReply(QNetworkReply *reply);
    void auth(QNetworkReply *reply, QAuthenticator *authenticatior);

public slots:
    /*!
     * \brief downloadUpdate
     * Downloads update by available files map
     */
    void downloadUpdate();
};

#endif // DOWNLOADER_FU_H
