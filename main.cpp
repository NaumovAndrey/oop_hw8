#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

// Класс для аудиозаписи
class Track {
public:
    std::string title;
    std::tm creationDate;
    int duration;

    Track(const std::string& t, const std::tm& cd, int dur) : title(t), creationDate(cd), duration(dur) {}
};

// Класс для аудиоплеера
class AudioPlayer {
private:
    std::vector<Track> tracks;
    Track* currentTrack = nullptr;

public:
    void addTrack(const Track& track) {
        tracks.push_back(track);
    }

    void play(const std::string& title) {
        for (Track& track : tracks) {
            if (track.title == title && currentTrack == nullptr) {
                currentTrack = &track;
                std::cout << "Воспроизведение: " << currentTrack->title << std::endl;
                return;
            }
        }
        std::cout << "Запись не найдена или уже воспроизводится" << std::endl;
    }

    void pause() {
        if (currentTrack != nullptr) {
            std::cout << "Пауза: " << currentTrack->title << std::endl;
            currentTrack = nullptr;
        }
    }

    void next() {
        if (!tracks.empty()) {
            currentTrack = &tracks[rand() % tracks.size()];
            std::cout << "Следующая запись: " << currentTrack->title << std::endl;
        } else {
            std::cout << "Нет доступных записей" << std::endl;
        }
    }

    void stop() {
        if (currentTrack != nullptr) {
            std::cout << "Остановка: " << currentTrack->title << std::endl;
            currentTrack = nullptr;
        } else {
            std::cout << "Нет текущей записи для остановки" << std::endl;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(std::time(nullptr)));

    Track track1("Track 1", std::tm{0, 0, 0, 1, 0, 121}, 180);
    Track track2("Track 2", std::tm{0, 0, 0, 2, 0, 121}, 210);

    AudioPlayer player;
    player.addTrack(track1);
    player.addTrack(track2);

    std::string command;
    while (true) {
        std::cout << "Введите команду (play/pause/next/stop/exit): ";
        std::cin >> command;

        if (command == "play") {
            std::string title;
            std::cout << "Введите название записи для воспроизведения: ";
            std::cin >> title;
            player.play(title);
        } else if (command == "pause") {
            player.pause();
        } else if (command == "next") {
            player.next();
        } else if (command == "stop") {
            player.stop();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Некорректная команда. Попробуйте снова." << std::endl;
        }
    }

    return 0;
}