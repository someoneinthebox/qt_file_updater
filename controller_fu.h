#ifndef CONTROLLER_FU_H
#define CONTROLLER_FU_H

#include <QObject>

class Gui_FU;
class Downloader_FU;
struct Content_FU;

/*!
 * \brief The Controller_FU class
 * Main controller for update check
 */
class Controller_FU : public QObject
{
    Q_OBJECT

    Gui_FU *_gui = nullptr;
    Downloader_FU *_downloader = nullptr;

    int _curVersion = 0;
    QString _checkVersionUrl;

public:
    /*!
     * \param version
     * Software numeric version
     * \param checkVersionUrl
     * URL to JSON protocol file of updater on server
     * \param versionBeauty
     * User-like version string
     */
    explicit Controller_FU(int version, const QString &checkVersionUrl,
                           const QString &versionBeauty = QString(), QObject *parent = nullptr);
    ~Controller_FU(){}
    /*!
     * \brief exec
     * Starts controller
     */
    int exec();

private slots:
    /*!
     * \brief checkUpdate
     * Checks update
     */
    void checkUpdate();
    /*!
     * \brief contentAvailable
     * If update is available this slot will use
     * \param content
     * Struct with update data
     */
    void contentAvailable(Content_FU *content);
    /*!
     * \brief install
     * Starts install
     */
    void install();
};

#endif // CONTROLLER_FU_H
