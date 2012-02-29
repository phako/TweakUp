#ifndef RYGELSETTINGS_H
#define RYGELSETTINGS_H

#include <glib.h>

#include <QObject>
#include <QSettings>

class RygelSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString friendlyName READ friendlyName WRITE setFriendlyName NOTIFY friendlyNameChanged)
    Q_PROPERTY(bool strictSharing READ strictSharing WRITE setStrictSharing NOTIFY strictSharingChanged)
    Q_PROPERTY(bool extendedMediaProfiles READ extendedMediaProfiles WRITE setExtendedMediaProfiles NOTIFY extendedMediaProfilesChanged)
    Q_PROPERTY(bool allowUpload READ allowUpload WRITE setAllowUpload NOTIFY allowUploadChanged)
    Q_PROPERTY(bool allowRemoveUpload READ allowRemoveUpload WRITE setAllowRemoveUpload NOTIFY allowRemoveUploadChanged)
public:
    explicit RygelSettings(QObject *parent = 0);
    ~RygelSettings();

    QString friendlyName() const;
    void setFriendlyName(const QString& friendlyName);

    bool strictSharing() const;
    void setStrictSharing(bool enable);

    bool extendedMediaProfiles() const;
    void setExtendedMediaProfiles(bool enable);

    bool allowUpload() const;
    void setAllowUpload(bool enable);

    bool allowRemoveUpload() const;
    void setAllowRemoveUpload(bool enable);

signals:
    void friendlyNameChanged();
    void strictSharingChanged();
    void extendedMediaProfilesChanged();
    void allowUploadChanged();
    void allowRemoveUploadChanged();

public slots:
    bool available();
    void sync();
private:
    GKeyFile *m_settings;
    bool m_available;
};

#endif // RYGELSETTINGS_H
