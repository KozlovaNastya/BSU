#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// Структура для хранения данных вопроса
struct Voprosi {
    std::string textVoprosov;  // Строка с текстом вопроса
    std::vector<std::string> otveti;  // Вектор строк с вариантами ответов 
    int indexPravOtv;  // Индекс правильного ответа
};

std::vector<Voprosi> ZagruzkaVoprosov() {
    // Функция, в которой вопросы записываются в вектор
    std::vector<Voprosi> questions;
    std::ifstream test("test.txt");  // Открываем файл test.txt

    if (!test.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл test.txt" << std::endl;
        return questions; // Если файл не открылся, вернет пустой вектор
    }

    std::string line;
    while (std::getline(test, line)) { // Поточное считывание файла
        if (line.empty()) continue;  // Пропускаем пустые строки

        Voprosi question; // Экземпляр нашей структуры
        question.textVoprosov = line;  // Инициализируем поле структуры

        // Чтение вариантов ответа до тех пор, пока не встретим цифру, подразумевается, что цифра - индекс ответа
        while (std::getline(test, line) && line[0] != '0' && line[0] != '1' && line[0] != '2') {
            question.otveti.push_back(line.substr(0, line.size() - 1)); // Убираем последний ';'
        }

        // Считываем индекс правильного ответа
        question.indexPravOtv = std::stoi(line); // Преобразуем в индекс (string to int)

        questions.push_back(question);  // Добавляем вопрос в вектор вопросов
    }

    test.close();  // Закрываем файл
    return questions;
}

bool zadatVopros(const Voprosi& question) {
    std::cout << question.textVoprosov << "\n"; // Выводим текст вопроса на экран
    for (size_t i = 0; i < question.otveti.size(); ++i) {  // Выводим по порядку все наши вопросы
        std::cout << question.otveti[i] << "\n";
    }

    int Otvet;
    std::cout << "Ваш ответ (введите номер варианта по порядку): ";
    std::cin >> Otvet;
    // Проверка корректности ввода
    return (Otvet - 1) == question.indexPravOtv;
}

// Функция для выставления итоговой оценки с параметрами в виде правильных ответов и количества вопросов
void otobrazItog(int correctAnswers, int totalQuestions) {
    double score = (static_cast<double>(correctAnswers) / totalQuestions) * 10; // Преобразовали correctAnswers в double
    std::cout << "Вы ответили правильно на " << correctAnswers << " из " << totalQuestions << " вопросов.\n";
    std::cout << "Ваша оценка: " << score << "\n";
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0))); // Для генерации рандома
    // Загрузка вопросов из файла в вектор
    std::vector<Voprosi> questions = ZagruzkaVoprosov();

    std::random_shuffle(questions.begin(), questions.end());  // Перемешивание вопросов

    int correctAnswers = 0;

    // Задаем 10 из 26 вопросов пользователю
    for (int i = 0; i < 10; ++i) {
        std::cout << "\nВопрос " << (i + 1) << ":\n";
        if (zadatVopros(questions[i])) {
            std::cout << "Правильно!\n";
            ++correctAnswers;
        }
        else {
            std::cout << "Неправильно!\n";
        }
    }

    // Вывод итоговой оценки
    otobrazItog(correctAnswers, 10);

    return 0;
}
