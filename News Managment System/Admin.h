#pragma once
#include"User.h"
class Admin : public User
{
public:
    Admin(const User& user) : User(user) {};
    void addNews();
    void viewNewsArticles();
    void manageCategories();
    void manageUsers();
    void analyticsAndReports();
    void editNews();
    void editProfile(Admin admin);
};