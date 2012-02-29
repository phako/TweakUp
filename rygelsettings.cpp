#include "rygelsettings.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QtDBus>
#include <QStringList>

#include <glib.h>

RygelSettings::RygelSettings(QObject *parent)
    : QObject(parent)
    , m_settings(g_key_file_new())
    , m_available(false)
{
    QFile binary(QLatin1String("/usr/bin/rygel"));

    m_available = binary.exists();

    qDebug() << "Rygel is" << (m_available ? "" : "not") << "available.";

    if (m_available) {
        QString configDirPath = QString::fromUtf8(g_get_user_config_dir());
        QDir userConfigDir(configDirPath);
        QFile userConfigFile(userConfigDir.filePath(QLatin1String("rygel.conf")));
        qDebug() << userConfigFile.fileName();

        // copy system config file to user directory
        if (not userConfigFile.exists()) {
            QFile::copy(QLatin1String("/etc/rygel.conf"), userConfigFile.fileName());
        }

        GError *error = 0;

        g_key_file_load_from_file(m_settings,
                                  userConfigFile.fileName().toUtf8().constData(),
                                  G_KEY_FILE_KEEP_COMMENTS,
                                  &error);
        if (error != 0) {
            m_available = false;
            qWarning() << "Could not read config file";
            g_error_free(error);
        }
    }
}

RygelSettings::~RygelSettings()
{
    if (m_settings != 0) {
        g_key_file_free(m_settings);
    }
}

bool RygelSettings::available()
{
    return m_available;
}

QString RygelSettings::friendlyName() const
{
    char *friendlyName;
    GError *error = 0;

    friendlyName = g_key_file_get_string(m_settings, "Tracker", "title", &error);
    if (error == 0) {
        return QString::fromUtf8(friendlyName);
    }

    qWarning() << "Failed to get friendly name" << error->message;
    g_error_free(error);

    return QString::fromLatin1("Media on @DEVICE@");
}

void RygelSettings::setFriendlyName(const QString& friendlyName)
{
    g_key_file_set_string(m_settings, "Tracker", "title", friendlyName.toUtf8().constData());
    emit friendlyNameChanged();
}

bool RygelSettings::strictSharing() const
{
    gboolean strict;
    GError *error = 0;

    strict = g_key_file_get_boolean(m_settings, "Tracker", "strict-sharing", &error);
    if (error == 0) {
        return strict == TRUE;
    }

    qWarning() << "Failed to get strict sharing" << error->message;
    g_error_free(error);

    return true;
}

void RygelSettings::setStrictSharing(bool enable)
{
    g_key_file_set_boolean(m_settings, "Tracker", "strict-sharing", enable ? TRUE : FALSE);
    emit friendlyNameChanged();
}

bool RygelSettings::extendedMediaProfiles() const
{
    static QDir dir = QDir(QLatin1String("/usr/share/gupnp-dlna/dlna-profiles"));

    // do a rough guess to check if the additional profiles are installed
    return !dir.entryList(QStringList() << QLatin1String("*-extra.xml")).isEmpty();
}

void RygelSettings::setExtendedMediaProfiles(bool enable)
{
    if (enable) {
    } else {
    }
}

bool RygelSettings::allowUpload() const
{
    gboolean upload;
    GError *error = 0;

    upload = g_key_file_get_boolean(m_settings, "general", "allow-upload", &error);
    if (error == 0) {
        return upload == TRUE;
    }

    qWarning() << "Failed to get strict sharing" << error->message;
    g_error_free(error);

    return true;
}

void RygelSettings::setAllowUpload(bool enable) {
    g_key_file_set_boolean(m_settings, "general", "allow-upload", enable ? TRUE : FALSE);
    emit friendlyNameChanged();
}

bool RygelSettings::allowRemoveUpload() const
{
    gboolean remove;
    GError *error = 0;

    remove = g_key_file_get_boolean(m_settings, "general", "allow-deletion", &error);
    if (error == 0) {
        return remove == TRUE;
    }

    qWarning() << "Failed to get strict sharing" << error->message;
    g_error_free(error);

    return true;
}

void RygelSettings::setAllowRemoveUpload(bool enable) {
    g_key_file_set_boolean(m_settings, "general", "allow-deletion", enable ? TRUE : FALSE);
    emit friendlyNameChanged();
}

void RygelSettings::sync()
{
    char *data;
    gsize length;
    GError *error = 0;

    data = g_key_file_to_data(m_settings, &length, &error);

    qDebug () << data;

    g_free(data);
}
