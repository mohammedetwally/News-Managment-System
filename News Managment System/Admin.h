#pragma once
#include"User.h"
class Admin : public User
{
public:

    // Constructors
    Admin() : User() {};
    Admin(const User& user) : User(user) {};

    // Conr=tainers 
    static map<string, User> admin_container;

    // Admin Functionalities
    void addNews();
    void viewNewsArticles();
    void manageCategories();
    void manageUsers();
    void analyticsAndReports();
    void editNews();
    void editProfile();
    void view_proile();
};