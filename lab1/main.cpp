// g++ main.cpp -o main.exe
// .\main.exe

#include <cstdlib>
#include <ctime>
#include <iostream>

/*
 * Генерирует строку из случайных строчных букв английского алфавита.
 *
 * @param text массив, в который записывается строка.
 * @param length длина генерируемой строки.
 * @param first_letter первая буква алфавита.
 * @param alphabet_size количество букв в алфавите.
 * @return функция не возвращает значение.
 */
void generateString(char text[], int const length, char const first_letter,
                    int const alphabet_size){
    for(int i = 0; i < length; i++){
        text[i] = first_letter + rand() % alphabet_size;
    }

    text[length] = '\0';
}

/*
 * Подсчитывает количество появлений каждой буквы в строке.
 *
 * @param text строка из строчных букв английского алфавита.
 * @param letter_counts массив частот букв.
 * @param length длина строки.
 * @param first_letter первая буква алфавита.
 * @param alphabet_size количество букв в алфавите.
 * @return функция не возвращает значение.
 */
void countLetters(const char text[], int letter_counts[], int const length,
                  char const first_letter, int const alphabet_size){
    for(int i = 0; i < alphabet_size; i++){
        letter_counts[i] = 0;
    }

    for(int i = 0; i < length; i++){
        int const letter_index = text[i] - first_letter;
        letter_counts[letter_index]++;
    }
}

/*
 * Находит букву с наибольшей частотой появления.
 *
 * @param letter_counts массив частот букв.
 * @param first_letter первая буква алфавита.
 * @param alphabet_size количество букв в алфавите.
 * @return наиболее часто встречающаяся буква.
 */
char findMostFrequent(const int letter_counts[], char const first_letter,
                      int const alphabet_size){
    int most_frequent_index = 0;

    for(int i = 1; i < alphabet_size; i++){
        if(letter_counts[i] > letter_counts[most_frequent_index]){
            most_frequent_index = i;
        }
    }

    return first_letter + most_frequent_index;
}

/*
 * Выводит частоты букв в виде гистограммы из символов '*'.
 *
 * @param letter_counts массив частот букв.
 * @param first_letter первая буква алфавита.
 * @param alphabet_size количество букв в алфавите.
 * @return функция не возвращает значение.
 */
void printHistogram(const int letter_counts[], char const first_letter,
                    int const alphabet_size){
    for(int i = 0; i < alphabet_size; i++){
        if(letter_counts[i] > 0){
            char const letter = first_letter + i;
            std::cout << letter << ": ";

            for(int j = 0; j < letter_counts[i]; j++){
                std::cout << '*';
            }

            std::cout << '\n';
        }
    }
}

/*
 * Запрашивает длину строки, генерирует её и выводит результаты исследования.
 *
 * @param у функции нет параметров.
 * @return 0 при успешном завершении, 1 при длине вне диапазона от 1 до 1000.
 */
int main(){
    int const ALPHABET_SIZE = 26;
    int const MAX_LENGTH = 1000;
    char const FIRST_LETTER = 'a';
    int length = 0;

    std::cout << "Enter N: ";
    std::cin >> length;

    if(length <= 0 || length > MAX_LENGTH){
        std::cout << "N must be from 1 to 1000.\n";
        return 1;
    }

    char text[MAX_LENGTH + 1] = {};
    int letter_counts[ALPHABET_SIZE] = {};

    srand(time(NULL));
    generateString(text, length, FIRST_LETTER, ALPHABET_SIZE);
    countLetters(text, letter_counts, length, FIRST_LETTER, ALPHABET_SIZE);

    std::cout << "Generated string: " << text << "\n\n";
    std::cout << "Histogram:\n";
    printHistogram(letter_counts, FIRST_LETTER, ALPHABET_SIZE);
    std::cout << "Most frequent letter: "
              << findMostFrequent(letter_counts, FIRST_LETTER, ALPHABET_SIZE)
              << '\n';

    return 0;
}
