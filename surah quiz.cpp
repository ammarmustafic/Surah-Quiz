#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

const int MAX_PLAYERS = 25; 

struct Player {
    string name;
    int score;
};

void loadLeaderboard(Player leaderboard[], int& playerCount) {
    ifstream file("leaderboard.txt");
    if (file.is_open()) {
        playerCount = 0;
        while (file >> leaderboard[playerCount].name >> leaderboard[playerCount].score) {
            playerCount++;
            if (playerCount >= MAX_PLAYERS) {
                break;
            }
        }
        file.close();
    }
}

void saveLeaderboard(const Player leaderboard[], int playerCount) {
    ofstream file("leaderboard.txt");
    if (file.is_open()) {
        for (int i = 0; i < playerCount; i++) {
            file << leaderboard[i].name << " " << leaderboard[i].score << "\n";
        }
        file.close();
    }
}

bool doesUserExist(const string& playerName, const Player leaderboard[], int playerCount) {
    for (int i = 0; i < playerCount; i++) {
        if (leaderboard[i].name == playerName) {
            return true;
        }
    }
    return false;
}

void sortLeaderboard(Player leaderboard[], int playerCount) {
    sort(leaderboard, leaderboard + playerCount, [](const Player& a, const Player& b) {
        return a.score > b.score;
    });
}

int main() {
    string surahMap[114] = {
        "Al-Fatiha", "Al-Baqarah", "Aali Imran", "An-Nisa", "Al-Ma'idah", "Al-An'am", "Al-A'raf", "Al-Anfal",
        "At-Tawbah", "Yunus", "Hud", "Yusuf", "Ar-Ra'd", "Ibrahim", "Al-Hijr", "An-Nahl", "Al-Isra", "Al-Kahf",
        "Maryam", "Ta-Ha", "Al-Anbiya", "Al-Hajj", "Al-Mu'minun", "An-Nur", "Al-Furqan", "Ash-Shu'ara",
        "An-Naml", "Al-Qasas", "Al-Ankabut", "Ar-Rum", "Luqman", "As-Sajda", "Al-Ahzab", "Saba", "Fatir",
        "Ya-Sin", "As-Saffat", "Sad", "Az-Zumar", "Ghafir", "Fussilat", "Ash-Shura", "Az-Zukhruf", "Ad-Dukhan",
        "Al-Jathiya", "Al-Ahqaf", "Muhammad", "Al-Fath", "Al-Hujurat", "Qaf", "Adh-Dhariyat", "At-Tur",
        "An-Najm", "Al-Qamar", "Ar-Rahman", "Al-Waqi'a", "Al-Hadid", "Al-Mujadila", "Al-Hashr", "Al-Mumtahina",
        "As-Saff", "Al-Jumu'a", "Al-Munafiqun", "At-Taghabun", "At-Talaq", "At-Tahrim", "Al-Mulk", "Al-Qalam",
        "Al-Haqqah", "Al-Ma'arij", "Nuh", "Al-Jinn", "Al-Muzzammil", "Al-Muddathir", "Al-Qiyamah", "Al-Insan",
        "Al-Mursalat", "An-Naba", "An-Nazi'at", "Abasa", "At-Takwir", "Al-Infitar", "Al-Mutaffifin", "Al-Inshiqaq",
        "Al-Buruj", "At-Tariq", "Al-A'la", "Al-Ghashiyah", "Al-Fajr", "Al-Balad", "Ash-Shams", "Al-Lail",
        "Ad-Duha", "Ash-Sharh", "At-Tin", "Al-Alaq", "Al-Qadr", "Al-Bayyinah", "Az-Zalzalah", "Al-Adiyat",
        "Al-Qari'ah", "At-Takathur", "Al-Asr", "Al-Humazah", "Al-Fil", "Quraysh", "Al-Ma'un", "Al-Kawthar",
        "Al-Kafirun", "An-Nasr", "Al-Masad", "Al-Ikhlas", "Al-Falaq", "An-Nas"
    };

    Player leaderboard[MAX_PLAYERS];
    int playerCount = 0;
    string playerName;
    string answer;
    int score = 0;
    int incorrectCount = 0;

    cout << "Welcome to the Surah Quiz!\n";
    cout << "Enter your name: ";
    getline(cin, playerName);

    loadLeaderboard(leaderboard, playerCount);

    if (doesUserExist(playerName, leaderboard, playerCount)) {
        cout << "This user already exists. Please choose a different name." << endl;
        return 0;
    }

    srand(time(0));

    while (score < 114 && incorrectCount < 3) {
        int surahNumber = rand() % 114 + 1;
        string surahName = surahMap[surahNumber - 1];

        cout << "What number is Surah " << surahName << "? ";
        getline(cin, answer);

        if (stoi(answer) == surahNumber) {
            cout << "Ma sha Allah, you are right!\n";
            score++;
        } else {
            cout << "Sorry, that's incorrect. The correct answer is: " << surahNumber << "\n";
            incorrectCount++;
        }
    }

    Player currentPlayer;
    currentPlayer.name = playerName;
    currentPlayer.score = score;

    leaderboard[playerCount] = currentPlayer;
    playerCount++;
    sortLeaderboard(leaderboard, playerCount);

    saveLeaderboard(leaderboard, playerCount);

    cout << "\n--- Leaderboard ---\n";
    for (int i = 0; i < playerCount; i++) {
        cout << leaderboard[i].name << " " << leaderboard[i].score << "\n";
    }

    return 0;
}

