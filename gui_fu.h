#ifndef GUI_FU_H
#define GUI_FU_H

#include <QDialog>

namespace Ui { class Gui_FU; }
class Gui_FU : public QDialog
{
    Q_OBJECT

    Ui::Gui_FU *ui;

public:
    explicit Gui_FU(const QString &version, QWidget *parent = nullptr);
    ~Gui_FU();    
    /*!
     * \brief askForRestart
     * Question for restart app after update installed
     */
    bool askForRestart();

signals:
    /*!
     * \brief checkUpdate
     * Check update sig
     */
    void checkUpdate();
    /*!
     * \brief downloadUpdate
     * Download update sig
     */
    void downloadUpdate();
    /*!
     * \brief install
     * Install update sig
     */
    void install();

public slots:
    /*!
     * \brief updateAvailable
     * Shows update data
     * \param version
     * Version
     * \param desc
     * Description
     * \param filesSize
     * Sizeof files to download for progress bar
     */
    void updateAvailable(const QString &version, const QString &desc, int filesSize);
    /*!
     * \brief showError
     * Shows error
     */
    void showError(const QString &err);
    /*!
     * \brief showStatus
     * Displays status
     */
    void showStatus(const QString &err);
    /*!
     * \brief successDownloadUpdate
     * Settings widgtes after success download update
     */
    void successDownloadUpdate();
    /*!
     * \brief updateProgress
     * Update progress bar procent
     */
    void updateProgress(int remain);
    /*!
     * \brief noNeedUpdate
     * Displays no need update
     */
    void noNeedUpdate() { showStatus(tr("Your software does not need to update.")); }
};

#endif // GUI_FU_H
