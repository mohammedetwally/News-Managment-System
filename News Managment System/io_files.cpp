#include "io_files.h"

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