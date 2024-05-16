#include "io_files.h"
#include <windows.h>
#include <thread>
#include <conio.h> 
#include <stack>
#include "Reader.h"

/*
	Username
	Passward
	First Name
	Second Name
*/

// ADMIN
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
	ofstream reader_file;
	reader_file.open("reader.txt", ios::trunc);

	if (reader_file.is_open()) {
		for (auto t : Reader::reader_container) {
			reader_file << t.second.getUserName() << endl;
			reader_file << t.second.getPassword() << endl;
			reader_file << t.second.getFirstName() << endl;
			reader_file << t.second.getSecondName() << endl;
			reader_file << t.second.getLastLoginDate() << endl;
			set<string> preferredCategories = t.second.getPreferredCategories();
			for (auto it = preferredCategories.begin(); it != preferredCategories.end(); it++) {
				reader_file << *it << endl;
			}
			reader_file << "start\n";
			for (int i = 0; i < t.second.bookmarking_container.size(); i++) {
				reader_file << t.second.bookmarking_container[i]->getTitle() << endl;
			}
			reader_file << "end\n";
		}
	}
	reader_file.close();
}

void io_files::fetch_reader_data() {

	string line[9];
	int count = 0;
	ifstream reader_file;
	reader_file.open("reader.txt", ios::in);
	reader_file.seekg(0);
	Reader reader, emptyReader;
	if (reader_file.is_open()) {
		while (getline(reader_file, line[count])) {
			if (line[count] == "start") {
				string title;
				while (getline(reader_file, title)) {
					if (title == "end") {
						count = 0;
						reader.setUserName(line[0]);
						reader.setPassword(line[1]);
						reader.setFirstName(line[2]);
						reader.setSecondName(line[3]);
						reader.setLastLoginDate(line[4]);
						// Uncomment this if you wish to reset readers' date
						// to a value that shows some notifications
						//reader.setLastLoginDate("2022-09-15 00:00:00");
						reader.setPreferredCategories(line[5]);
						reader.setPreferredCategories(line[6]);
						reader.setPreferredCategories(line[7]);
						Reader::reader_container.insert({ reader.getUserName() , reader });
						reader = emptyReader;
						break;
					}
					else {
						reader.bookmarking_container.push_back(&News::News_Container[title]);
					}
				}
			}
			else {
				count++;
			}
		}
	}
	reader_file.close();
}

// NEWS
void io_files::save_news_data() {

	ofstream news_file;
	news_file.open("news.txt", ios::trunc);

	if (news_file.is_open()) {
		for (auto t : News::News_Container) {
			news_file << t.second.getAdminUserName() << endl;
			news_file << t.second.getCategory() << endl;
			news_file << t.second.getTitle() << endl;
			news_file << t.second.getDescription() << endl;
			news_file << t.second.getAdminFirstName() << endl;
			news_file << t.second.getAdminSecondName() << endl;
			news_file << t.second.getRate() << endl;
			news_file << "start_rates" << endl;
			for (auto r : t.second.newsRates) {
				news_file << r.first << endl;
				news_file << r.second << endl;
			}
			news_file << "end_rates" << endl;
			news_file << "start_spam" << endl;
			for (auto spam : t.second.getSpamSet()) {
					news_file << spam << endl;
			}
			news_file << "end_spam" << endl;
			news_file << t.second.getDate() << endl;
		}
	}
	news_file.close();
}

void io_files::fetch_news_data()
{
	string line[8];
	int count = 0;
	ifstream news_file;
	news_file.open("news.txt", ios::in);
	news_file.seekg(0);
	News news, emptyNews;
	if (news_file.is_open()) {
		while (getline(news_file, line[count])) {
			if (line[count] == "start_rates") {
				string rate[2];
				int j = 0;
				while (getline(news_file, rate[j])) {
					if (rate[j] == "end_rates") break;
					else if (j == 1)
					{
						news.newsRates[rate[0]] = stof(rate[1]);
						j = 0;
					}
					else
						j++;
				}
			}
			else if (line[count] == "start_spam") {
				string user;
				while (getline(news_file, user)) {
					if (user == "end_spam") break;

					news.addUserToSpamSet(user);
				}
			}
			else if (count == 7) {
				count = 0;
				news.setAdminUserName(line[0]);
				news.setCategory(line[1]);
				news.setTitle(line[2]);
				news.setDescription(line[3]);
				news.setAdminFirstName(line[4]);
				news.setAdminSecondName(line[5]);
				news.setAvgRate(stof(line[6]));
				news.setDate(line[7]);
				float rate = news.getRate();
				if (rate > 2) {
					News::News_Container.insert({ news.getTitle(), news });
				}
				news = emptyNews;
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

// CATEGORIES
void io_files::save_categories() {
	ofstream category_file;
	category_file.open("categories.txt", ios::trunc);
	if (category_file.is_open()) {
		for (auto category : Admin::categories) {
			category_file << category << endl;
		}
	}
	category_file.close();
}

void io_files::fetch_categories() {
	string line;
	ifstream category_file;
	category_file.open("categories.txt", ios::in);
	category_file.seekg(0);
	if (category_file.is_open()) {
		while (getline(category_file, line)) {
			Admin::categories.insert(line);
		}
	}
	category_file.close();
}

//COMMENTS
void io_files::save_comments()
{
	ofstream outputFile("comments.txt");
	if (outputFile.is_open()) {
		for (const auto& pair : Reader::commentsMap) {
			News news = pair.first;
			stack<string> comments = pair.second;

			outputFile << "News Title: " << news.getTitle() << "\n";
			outputFile << "Comments:\n";

			// Temporary vector to store comments in correct order :(
			vector<string> tempVec;

			
			stack<string> tempStack = comments; 
			while (!tempStack.empty()) {
				tempVec.push_back(tempStack.top());
				tempStack.pop();
			}

			// Write comments from vector to file in reverse order (since stack was reversed)
			for (auto rit = tempVec.rbegin(); rit != tempVec.rend(); ++rit) {
				outputFile << "- " << *rit << "\n";
			}

			outputFile << "\n"; 
		}

		outputFile.close();
		cout << "Comments saved to 'comments.txt' successfully.\n";
	}
	else {
		cout << "Error: Unable to open file 'comments.txt' for writing.\n";
	}
}

void io_files::fetch_comments_from_file()
{
	ifstream inputFile("comments.txt");
	string line;
	News currentNews;
	stack<string> currentComments;
	
	if (inputFile.is_open()) {
		while (getline(inputFile, line)) {
			if (line.substr(0, 11) == "News Title:") {
				if (!currentNews.getTitle().empty()) {
					Reader::commentsMap[currentNews] = currentComments;
					currentComments = stack<string>(); // Reset comments for new news
				}
				string title = line.substr(12); //  title
				currentNews.setTitle(title);
			}
			else if (line.substr(0, 10) == "Comments:") {
				
				while (getline(inputFile, line) && !line.empty()) {
					currentComments.push(line.substr(2)); // Ignore  "- " 
				}
			}
		}

		// Add last news and its comments
		if (!currentNews.getTitle().empty()) {
			Reader::commentsMap[currentNews] = currentComments;
		}

		inputFile.close();
		cout << "Comments loaded from " << "comments.txt" << " successfully.\n";
	}
	else {
		cout << "Error: Unable to open file " << "comments.txt" << " for reading.\n";
	}
}