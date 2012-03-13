#ifndef RYGELSETTINGS_H
#define RYGELSETTINGS_H

#include <glib.h>

#include <QObject>
#include <QSettings>
#include <QFile>
#include <QtDBus>

class RygelSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString friendlyName READ friendlyName WRITE setFriendlyName NOTIFY friendlyNameChanged)
    Q_PROPERTY(QString homeWLAN READ homeWLAN WRITE setHomeWLAN NOTIFY homeWLANChanged)
    Q_PROPERTY(bool strictSharing READ strictSharing WRITE setStrictSharing NOTIFY strictSharingChanged)
    Q_PROPERTY(bool lpcmTranscoding READ lpcmTranscoding WRITE setLPCMTranscoding NOTIFY lpcmTranscodingChanged)
    Q_PROPERTY(bool allowUpload READ allowUpload WRITE setAllowUpload NOTIFY allowUploadChanged)
    Q_PROPERTY(bool allowRemoveUpload READ allowRemoveUpload WRITE setAllowRemoveUpload NOTIFY allowRemoveUploadChanged)
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(bool dirty READ dirty NOTIFY dirtyChanged)
public:
    explicit RygelSettings(QObject *parent = 0);
    ~RygelSettings();

    QString friendlyName() const;
    void setFriendlyName(const QString& friendlyName);

    QString homeWLAN() const;
    void setHomeWLAN(const QString& homeWLAN);

    bool lpcmTranscoding() const;
    void setLPCMTranscoding(bool enable);

    bool strictSharing() const;
    void setStrictSharing(bool enable);

    bool allowUpload() const;
    void setAllowUpload(bool enable);

    bool allowRemoveUpload() const;
    void setAllowRemoveUpload(bool enable);

    bool running() const;

    bool dirty() const;

signals:
    void friendlyNameChanged();
    void homeWLANChanged();
    void strictSharingChanged();
    void lpcmTranscodingChanged();
    void allowUploadChanged();
    void allowRemoveUploadChanged();
    void runningChanged();
    void dirtyChanged();

public slots:
    bool available();
    void restart();
private:
    bool getBool(const char *key,
                 bool        defaultValue = false,
                 const char *section = "general") const;
    void setBool(const char *key, bool newValue, const char *section = "general");
    QString getString(const char    *key,
                      const QString &defaultValue = QLatin1String(""),
                      const char    *section = "general") const;
    void setString(const char *key, const QString &newValue, const char *section = "general");
    void sync();

    GKeyFile           *m_keyFile;
    bool                m_available;
    QDBusInterface     *m_fdo;
    bool                m_dirty;
    QFile               m_configFile;
    QDBusServiceWatcher m_watcher;
};

#endif // RYGELSETTINGS_H
