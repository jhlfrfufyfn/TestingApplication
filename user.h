#ifndef USER_H
#define USER_H

#include <QString>



class User
{
public:
    User();
    User(const QString& name);

private:
    QString name;
};

#endif // USER_H
