#include <QDir>
#include <QDebug>

#include "keyfile.h"


KeyFile::KeyFile(const QString& configFile)
    : m_keyFile(g_key_file_new())
    , m_configFile()
{
    QString configDirPath = QString::fromUtf8(g_get_user_config_dir());
    QDir userConfigDir(configDirPath);
    QFile userConfigFile(userConfigDir.filePath(configFile));
    m_configFile.setFileName(userConfigFile.fileName());

    qDebug() << userConfigFile.fileName();

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
        g_prefix_error(&error, "Could not read config file:");
        throw GerrorException(error);
    }
}

KeyFile::~KeyFile()
{
    if (m_keyFile != 0) {
        sync();
        g_key_file_free(m_keyFile);
    }
}

bool KeyFile::getBool(const char *key, bool defaultValue, const char *section)
{
    gboolean configValue;
    GError *error = 0;

    configValue = g_key_file_get_boolean(m_keyFile, section, key, &error);
    if (error == 0) {
        return configValue == TRUE;
    }

    return defaultValue;
}

void KeyFile::setBool(const char *key, bool newValue, const char *section)
{
    g_key_file_set_boolean(m_keyFile, section, key, newValue ? TRUE : FALSE);
    sync();
}

QString KeyFile::getString(const char *key, const QString& defaultValue, const char *section)
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

void KeyFile::setString(const char *key, const QString &newValue, const char *section)
{
    g_key_file_set_string(m_keyFile, section, key, newValue.toUtf8().constData());
    sync();
}

void KeyFile::sync()
{
    GError *error = 0;
    gsize   length;

    char *data = g_key_file_to_data(m_keyFile, &length, &error);
    if (m_configFile.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        m_configFile.write(data);
        m_configFile.close();
    }

    g_free(data);
}
