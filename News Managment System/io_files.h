#include "Admin.h"
#include "Reader.h"
#include <iostream>
#include <fstream>

class io_files {


public:
    static void fetch_admin_data();
    static void fetch_reader_data();
    static void save_admin_data();
    static void save_reader_data();
};