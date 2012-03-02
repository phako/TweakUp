#ifndef KEYFILE_H
#define KEYFILE_H

#include <exception>

#include <QFile>

#include <glib.h>

class GerrorException : public std::exception
{
public:
    GerrorException(GError* the_error) throw() : m_internal_error(the_error) { }
    ~GerrorException() throw() { g_error_free(m_internal_error); }

    const char * what() const throw() {
        return m_internal_error->message;
    }
private:
    GError *m_internal_error;
};

class KeyFile {
public:
    explicit KeyFile (const QString& path);
    ~KeyFile();

    bool getBool(const char *key,
                 bool        defaultValue = false,
                 const char *section = "general");
    void setBool(const char *key, bool newValue, const char *section = "general");
    QString getString(const char    *key,
                      const QString &defaultValue = QLatin1String(""),
                      const char    *section = "general");
    void setString(const char *key, const QString &newValue, const char *section = "general");
    void sync();
private:
    GKeyFile *m_keyFile;
    QFile     m_configFile;
};

#endif // KEYFILE_H
