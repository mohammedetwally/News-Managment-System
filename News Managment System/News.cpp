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
    return average_rate;
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



void News::addNewRate(string rate) {
    rates.push_back(stoi(rate));
}

void News::setCategory(string category)
{
    this->category = category;
}

void News::setAdminUserName(string adminUserName)
{
    this->adminUserName = adminUserName;
}


void News::setAvgRate(string avg) {
    this->average_rate = avg;
}