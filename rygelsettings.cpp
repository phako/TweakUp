#include "rygelsettings.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QtDBus>

static const QLatin1String RYGEL_DBUS_INTERFACE = QLatin1String("org.gnome.Rygel1");

RygelSettings::RygelSettings(QObject *parent)
    : QObject(parent)
    , m_keyFile(g_key_file_new())
    , m_available(false)
    , m_fdo(0)
    , m_dirty(false)
    , m_watcher(RYGEL_DBUS_INTERFACE, QDBusConnection::sessionBus())
{
    QFile binary(QLatin1String("/usr/bin/rygel"));
    m_available = binary.exists();
    if (not m_available) {
        return;
    }

    QString configDirPath = QString::fromUtf8(g_get_user_config_dir());
    QDir userConfigDir(configDirPath);
    QFile userConfigFile(userConfigDir.filePath(QLatin1String("rygel.conf")));
    m_configFile.setFileName(userConfigFile.fileName());

    // copy system config file to user directory
    if (not userConfigFile.exists()) {
        QFile::copy(QLatin1String("/etc/rygel.conf"), userConfigFile.fileName());
    }

    GError *error = 0;

    g_key_file_load_from_file(m_keyFile,
                              userConfigFile.fileName().toUtf8().constData(),
                              G_KEY_FILE_KEEP_COMMENTS,
                              &error);
    if (error != 0) {
        m_available = false;
        g_error_free (error);

        return;
    }

    // setup D-Bus connection and check its state
    m_fdo = new QDBusInterface(QLatin1String("org.freedesktop.DBus"),
                                 QLatin1String("/"),
                                 QLatin1String("org.freedesktop.DBus"));
    connect(&m_watcher,
            SIGNAL(serviceOwnerChanged(QString,QString,QString)),
            SIGNAL(runningChanged()));
}

RygelSettings::~RygelSettings()
{
    delete m_fdo;
    m_fdo = 0;
    if (m_keyFile != 0) {
        sync();
        g_key_file_free(m_keyFile);
        m_keyFile = 0;
    }
}

bool RygelSettings::available()
{
    return m_available;
}

QString RygelSettings::friendlyName() const
{
    return getString("title", QLatin1String("Media on @DEVICE@"), "Tracker");
}

void RygelSettings::setFriendlyName(const QString& friendlyName)
{
    setString("title", friendlyName, "Tracker");
    emit friendlyNameChanged();
}

QString RygelSettings::homeWLAN() const
{
    return getString("interface", QLatin1String(""));
}

void RygelSettings::setHomeWLAN(const QString &homeWLAN)
{
    setString("interface", homeWLAN);
    emit homeWLANChanged();
}

bool RygelSettings::strictSharing() const
{
    return getBool("strict-sharing", true, "Tracker");
}

void RygelSettings::setStrictSharing(bool enable)
{
    setBool("strict-sharing", enable, "Tracker");
    emit friendlyNameChanged();
}

bool RygelSettings::allowUpload() const
{
    return getBool("allow-upload", true);
}

void RygelSettings::setAllowUpload(bool enable)
{
    setBool("allow-upload", enable);
    emit allowUploadChanged();
}

bool RygelSettings::allowRemoveUpload() const
{
    return getBool("allow-deletion", true);
}

void RygelSettings::setAllowRemoveUpload(bool enable)
{
    setBool("allow-deletion", enable);
    emit allowRemoveUploadChanged();
}

bool RygelSettings::lpcmTranscoding() const
{
    return getBool("enable-lpcm-transcoder", true);
}

void RygelSettings::setLPCMTranscoding(bool enable)
{
    setBool("enable-lpcm-transcoder", enable);
    emit lpcmTranscodingChanged();
}

bool RygelSettings::running() const
{
    if (m_fdo == 0) {
        return false;
    }

    QDBusMessage reply = m_fdo->call(QLatin1String("ListNames"));
    return reply.arguments().first().toStringList().contains(RYGEL_DBUS_INTERFACE);
}

bool RygelSettings::dirty() const
{
    return m_dirty;
}

void RygelSettings::restart()
{
    if (m_dirty) {
        system("pkill -HUP rygel");
        m_dirty = false;
        emit dirtyChanged();
    }
}

bool RygelSettings::getBool(const char *key, bool defaultValue, const char *section) const
{
    gboolean configValue;
    GError *error = 0;

    configValue = g_key_file_get_boolean(m_keyFile, section, key, &error);
    if (error == 0) {
        return configValue == TRUE;
    }

    return defaultValue;
}

void RygelSettings::setBool(const char *key, bool newValue, const char *section)
{
    g_key_file_set_boolean(m_keyFile, section, key, newValue ? TRUE : FALSE);
    sync();
}

QString RygelSettings::getString(const char *key, const QString& defaultValue, const char *section) const
{
    char *configValue;
    GError *error = 0;

    configValue = g_key_file_get_string(m_keyFile, section, key, &error);
    if (error == 0) {
        QString result = QString::fromUtf8(configValue);
        g_free(configValue);

        return result;
    }

    return defaultValue;
}

void RygelSettings::setString(const char *key, const QString &newValue, const char *section)
{
    g_key_file_set_string(m_keyFile, section, key, newValue.toUtf8().constData());
    sync();
}

void RygelSettings::sync()
{
    GError *error = 0;
    gsize   length;

    char *data = g_key_file_to_data(m_keyFile, &length, &error);
    if (m_configFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        m_configFile.write(data);
        m_configFile.close();
    }

    g_free(data);

    if (not m_dirty && running()) {
        m_dirty = true;
        emit dirtyChanged();
    }
}
