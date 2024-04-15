#include "io_files.h"
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <cstdlib>
/*
    Username
    Passward
    First Name
    Second Name
*/

// Admin
void io_files::save_admin_data() {

    ofstream admin_file;
    admin_file.open("admin.txt", ios::trunc);

    if (admin_file.is_open()) {
        for (auto t : Admin::admin_container) {
            admin_file << t.second.getUserName() << endl;
            admin_file << t.second.getPassword() << endl;
            admin_file << t.second.getFirstName() << endl;
            admin_file << t.second.getSecondName() << endl;
        }
    }
    admin_file.close();
}

void io_files::fetch_admin_data() {

    /*
         Username
         Passward
         First Name
         Second Name
     */

    string line[4];
    int count = 0;
    ifstream admin_file;
    admin_file.open("admin.txt", ios::in);
    admin_file.seekg(0);
    if (admin_file.is_open()) {
        while (getline(admin_file, line[count])) {
            // add admin to DS
            if (count == 3) {
                Admin admin;
                count = 0;
                admin.setUserName(line[0]);
                admin.setPassword(line[1]);
                admin.setFirstName(line[2]);
                admin.setSecondName(line[3]);
                Admin::admin_container.insert({ admin.getUserName() , admin });
            }
            else {
                count++;
            }
        }
    }
    admin_file.close();
    /*int i = 1;
    for (auto t : Admin::admin_container) {
        cout << "Admin" << " [" << i << " ]" << endl;
        cout << "\t" << "KEY: \n" << t.first << endl;
        cout << "VALUE: \n";
        cout << "\t" << t.second.getUserName() << endl;
        cout << "\t" << t.second.getPassword() << endl;
        cout << "\t" << t.second.getFirstName() << endl;
        cout << "\t" << t.second.getSecondName() << endl;
        i++;
    }*/
}



// READER
void io_files::save_reader_data() {

    string line[4];
    int count = 0;
    ofstream reader_file;
    reader_file.open("reader.txt", ios::trunc);

    if (reader_file.is_open()) {
        for (auto t : Reader::reader_container) {
            reader_file << t.second.getUserName() << endl;
            reader_file << t.second.getPassword() << endl;
            reader_file << t.second.getFirstName() << endl;
            reader_file << t.second.getSecondName() << endl;
        }
    }
    reader_file.close();
}

void io_files::fetch_reader_data() {

    string line[4];
    int count = 0;
    ifstream reader_file;
    reader_file.open("reader.txt", ios::in);
    reader_file.seekg(0);
    if (reader_file.is_open()) {
        while (getline(reader_file, line[count])) {
            // add admin to DS
            if (count == 3) {
                Reader reader;
                count = 0;
                reader.setUserName(line[0]);
                reader.setPassword(line[1]);
                reader.setFirstName(line[2]);
                reader.setSecondName(line[3]);
                Reader::reader_container.insert({ reader.getUserName() , reader });
            }
            else {
                count++;
            }
        }
    }
    reader_file.close();
    /* int i = 1;
     for (auto t : Reader::reader_container) {
         cout << "Reader" << " [" << i << "]" << " | KEY: " << t.first << endl;
         cout << "VALUE: \n";
         cout << "\t" << t.second.getUserName() << endl;
         cout << "\t" << t.second.getPassword() << endl;
         cout << "\t" << t.second.getFirstName() << endl;
         cout << "\t" << t.second.getSecondName() << endl;
         i++;
     }*/
}


void io_files::save_news_data() {

    ofstream news_file;
    news_file.open("news.txt", ios::trunc);

    if (news_file.is_open()) {
        for (auto t : News::latestNews) {
            news_file << t.getAdminUserName() << endl;
            news_file << t.getCategory() << endl;
            news_file << t.getTitle() << endl;
            news_file << t.getDescription() << endl;
            news_file << t.getRate() << endl;
            news_file << t.getDate() << endl;
        }
    }
    news_file.close();
}

void io_files::fetch_news_data() 
{
    string line[6];
    int count = 0;
    ifstream news_file;
    news_file.open("news.txt", ios::in);
    news_file.seekg(0);
    if (news_file.is_open()) {
        while (getline(news_file, line[count])) {
            if (count == 5) {
                News news;
                count = 0;
                news.setAdminUserName(line[0]);
                news.setCategory(line[1]);
                news.setTitle(line[2]);
                news.setDescription(line[3]);
                news.setRate(line[4]);
                news.setDate(line[5]);
                News::latestNews.insert(News::latestNews.begin() , news);
                pair<tuple<string, string, string>, News> keyValue = make_pair(make_tuple(news.getAdminUserName(), news.getTitle(), news.getDescription()), news);
                News::allNews.insert(keyValue);
                News::newsCategories.emplace(news.getCategory(), news);
            }
            else {
                count++;
            }
        }
    }
/*
    cout << "\n\nData From Map";
    int i = 1;
    for (auto t : News::allNews) {
        cout << "News" << " [" << i << "]" << " | KEY: " << get<0>(t.first) << endl;
        cout << "News" << " [" << i << "]" << " | KEY: " << get<1>(t.first) << endl;
        cout << "News" << " [" << i << "]" << " | KEY: " << get<2>(t.first) << endl;
        cout << "\t" << t.second.getAdminUserName() << endl;
        cout << "\t" << t.second.getCategory() << endl;
        cout << "\t" << t.second.getTitle() << endl;
        cout << "\t" << t.second.getDescription() << endl;
        cout << "\t" << t.second.getRate() << endl;
        cout << "\t" << t.second.getDate() << endl;
        i++;
    }

    cout << "Data From Hash Table";
    i = 1;
    for (auto t : News::newsCategories) {
        cout << "Reader" << " [" << i << "]" << " | KEY: " << t.first << endl;
        cout << "VALUE: \n";
        cout << "\t" << t.second.getAdminUserName() << endl;
        cout << "\t" << t.second.getCategory() << endl;
        cout << "\t" << t.second.getTitle() << endl;
        cout << "\t" << t.second.getDescription() << endl;
        cout << "\t" << t.second.getRate() << endl;
        cout << "\t" << t.second.getDate() << endl;
        i++;
    }
    this_thread::sleep_until(chrono::steady_clock::now() + chrono::seconds(20));

*/
    news_file.close();
}