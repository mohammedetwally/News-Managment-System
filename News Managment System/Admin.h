#pragma once
#include"User.h"
class Admin : public User
{
public:

    // Constructors
    Admin() : User() {};
    Admin(const User& user) : User(user) {};

    // Conrtainers 
    static map<string, User> admin_container;

    // Admin Functionalities
    void addNews();
    void removeNews();
    void editNews();
    void addCategories();
    void viewNewsArticles();
    void rateTitle();
    void editProfile();
    void view_proile();
};