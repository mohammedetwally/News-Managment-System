#pragma once
#include"User.h"
#include"News.h"
class Admin : public User
{
public:
    // Constructors
    Admin() : User() {};
    Admin(const User& user) : User(user) {};

    // Containers 
    static map<string, User> admin_container;
    static set<string> categories;

    // Admin Functionalities
    // Admin's data
    void editProfile();
    void viewProfile();

    // News Management
    void addNews();
    void editNews();
    void removeNews();
    void viewNewsArticles();
    void rateTitle();
    
    // Categories management
    void addCategory();
    void delete_category();
};