#include "user.h"

User::User()
{
    this->name = "";
}

User::User(const QString& aName)
{
    this->name = aName;
}
