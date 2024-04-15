#include "News.h"

// Constructors

// Getters
string News::getTitle()
{
    return title;
}

string News::getDescription()
{
    return description;
}

string News::getDate()
{
    return date;
}

string News::getRate()
{
    return rate;
}

string News::getCategory()
{
    return category;
}

string News::getAdminUserName()
{
    return adminUserName;
}



// Setters
void News::setTitle(string title)
{
    this->title = title;
}

void News::setDescription(string description)
{
    this->description = description;
}

void News::setDate(string date)
{
    this->date = date;
}

void News::setRate(string rate)
{
    this->rate = rate;
}

void News::setCategory(string category)
{
    this->category = category;
}

void News::setAdminUserName(string adminUserName)
{
    this->adminUserName = adminUserName;
}
