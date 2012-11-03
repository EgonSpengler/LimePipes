/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ERROR_H
#define ERROR_H

#include <exception>

namespace LP {

class Error : public std::exception
{
public:
    explicit Error(const QString &message) throw()
        : m_message(message.toUtf8()) {}
    ~Error() throw() {}

    const char *what() const throw() { return m_message; }

private:
    const char *m_message;
};

}

#endif // ERROR_H
