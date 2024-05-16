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

float News::getRate()
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

string News::getAdminFirstName()
{
    return adminFirstName;
}

string News::getAdminSecondName()
{
    return adminSecondName;
}

set<string> News::getSpamSet() {
    return spamSet;
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

void News::setCategory(string category)
{
    this->category = category;
}

void News::setAdminUserName(string adminUserName)
{
    this->adminUserName = adminUserName;
}

void News::setAdminFirstName(string adminFirstName)
{
    this->adminFirstName = adminFirstName;
}
void News::setAdminSecondName(string adminSecondName)
{
    this->adminSecondName = adminSecondName;
}

void News::setAvgRate(float avg) 
{
    this->average_rate = avg;
}

void News::addSpamSet(string name) {
    if (spamSet.count(name) == 0)
    {
        spamSet.insert(name);
        cout << "\nMarked as spam successfully!";
    }
    else
        cout << "\Mark as spam UNSUCCESSFUL!";

    if (spamSet.size() > 5) {
        News_Container.erase(this->title);
    }
}

void News::addUserToSpamSet(string name)
{
    spamSet.insert(name);
}

// Functionalities
void News::calcRate()
{
    float sum = 0.0;
    for (auto r : this->newsRates) {
        sum += r.second;
    }
    this->setAvgRate(sum / this->newsRates.size());
}