#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Course{
    string title;
    string instructor;
    int duration;
    float rating;
    float price;
    bool is_advanced;
};

/**
 * Возвращает случайное целое число из отрезка [min_value, max_value].
 *
 * @param min_value нижняя граница
 * @param max_value верхняя граница
 * @return случайное целое число из диапазона
 */
int randomInt(const int min_value, const int max_value){
    return min_value + rand() % (max_value - min_value + 1);
}

/**
 * Возвращает случайное вещественное число из отрезка [min_value, max_value].
 *
 * @param min_value нижняя граница
 * @param max_value верхняя граница
 * @return случайное вещественное число из диапазона
 */
float randomFloat(const float min_value, const float max_value){
    const float scale = (float)rand() / (float)RAND_MAX;
    return min_value + scale * (max_value - min_value);
}

/**
 * Создаёт один курс со случайными, но реалистичными значениями полей.
 *
 * @return сгенерированный курс
 */
Course createRandomCourse(){
    const string TITLES[] = {
        "C++ Basics",
        "Advanced Algorithms",
        "Web Development",
        "Data Structures",
        "Machine Learning Intro",
        "Database Design",
        "Linux Administration",
        "Computer Networks",
        "Object Oriented Design",
        "Parallel Programming"
    };
    const string INSTRUCTORS[] = {
        "Anna Smith",
        "John Carter",
        "Maria Lopez",
        "Petr Ivanov",
        "Emily Brown",
        "David Chen"
    };
    const int TITLE_COUNT = 10;
    const int INSTRUCTOR_COUNT = 6;
    const int MIN_DURATION = 4;
    const int MAX_DURATION = 80;
    const float MIN_RATING = 0.0f;
    const float MAX_RATING = 5.0f;
    const float MIN_PRICE = 15.0f;
    const float MAX_PRICE = 250.0f;

    Course course;
    course.title = TITLES[randomInt(0, TITLE_COUNT - 1)];
    course.instructor = INSTRUCTORS[randomInt(0, INSTRUCTOR_COUNT - 1)];
    course.duration = randomInt(MIN_DURATION, MAX_DURATION);
    course.rating = randomFloat(MIN_RATING, MAX_RATING);
    course.price = randomFloat(MIN_PRICE, MAX_PRICE);
    course.is_advanced = randomInt(0, 1) == 1;
    return course;
}

/**
 * Заполняет каталог n случайно сгенерированными курсами.
 *
 * @param n количество курсов
 * @return вектор сгенерированных курсов
 */
vector<Course> generateCatalog(const int n){
    vector<Course> catalog;
    for(int i = 0; i < n; i++){
        catalog.push_back(createRandomCourse());
    }
    return catalog;
}

/**
 * Печатает один курс в читаемом виде.
 *
 * @param course курс для вывода
 */
void printCourse(const Course& course){
    cout << fixed << setprecision(2);
    cout << course.title
         << " | " << course.instructor
         << " | " << course.duration << " h"
         << " | rating " << course.rating
         << " | price " << course.price
         << " | " << (course.is_advanced ? "advanced" : "basic")
         << endl;
}

/**
 * Печатает все курсы каталога.
 *
 * @param catalog список курсов
 */
void printCatalog(const vector<Course>& catalog){
    const int size = (int)catalog.size();
    for(int i = 0; i < size; i++){
        cout << i + 1 << ". ";
        printCourse(catalog[i]);
    }
}

/**
 * Находит курсы с рейтингом выше min_rating и ценой ниже max_price.
 *
 * @param catalog список курсов
 * @param min_rating минимально допустимый рейтинг
 * @param max_price максимально допустимая цена
 */
void recommendCourses(const vector<Course>& catalog, const float min_rating, const float max_price){
    const int size = (int)catalog.size();
    int found = 0;
    cout << "Recommended courses:" << endl;
    for(int i = 0; i < size; i++){
        if(catalog[i].rating > min_rating && catalog[i].price < max_price){
            printCourse(catalog[i]);
            found = found + 1;
        }
    }
    if(found == 0){
        cout << "No courses match the filters." << endl;
    }
}

/**
 * Выводит самый короткий и самый длинный курс по продолжительности.
 *
 * @param catalog список курсов
 */
void compareDuration(const vector<Course>& catalog){
    const int size = (int)catalog.size();
    if(size == 0){
        cout << "Catalog is empty." << endl;
        return;
    }

    int min_index = 0;
    int max_index = 0;
    for(int i = 1; i < size; i++){
        if(catalog[i].duration < catalog[min_index].duration){
            min_index = i;
        }
        if(catalog[i].duration > catalog[max_index].duration){
            max_index = i;
        }
    }

    cout << "Shortest course: " << catalog[min_index].title
         << " (" << catalog[min_index].duration << " h)" << endl;
    cout << "Longest course: " << catalog[max_index].title
         << " (" << catalog[max_index].duration << " h)" << endl;
}

/**
 * Выводит средний рейтинг базовых и продвинутых курсов.
 *
 * @param catalog список курсов
 */
void groupAverageRating(const vector<Course>& catalog){
    const int size = (int)catalog.size();
    float basic_sum = 0.0f;
    float advanced_sum = 0.0f;
    int basic_count = 0;
    int advanced_count = 0;

    for(int i = 0; i < size; i++){
        if(catalog[i].is_advanced){
            advanced_sum = advanced_sum + catalog[i].rating;
            advanced_count = advanced_count + 1;
        }else{
            basic_sum = basic_sum + catalog[i].rating;
            basic_count = basic_count + 1;
        }
    }

    cout << fixed << setprecision(2);
    if(basic_count > 0){
        cout << "Average rating of basic courses: " << basic_sum / basic_count << endl;
    }else{
        cout << "No basic courses in the catalog." << endl;
    }
    if(advanced_count > 0){
        cout << "Average rating of advanced courses: " << advanced_sum / advanced_count << endl;
    }else{
        cout << "No advanced courses in the catalog." << endl;
    }
}

/**
 * Сортирует курсы по рейтингу по убыванию, при равенстве — по цене по возрастанию.
 *
 * @param catalog список курсов, изменяется на месте
 */
void sortByRatingAndPrice(vector<Course>& catalog){
    const int size = (int)catalog.size();
    for(int i = 0; i < size; i++){
        int best = i;
        for(int j = i + 1; j < size; j++){
            const int rating_j = (int)(catalog[j].rating * 100.0f + 0.5f);
            const int rating_best = (int)(catalog[best].rating * 100.0f + 0.5f);
            const bool better_rating = rating_j > rating_best;
            const bool same_rating_cheaper =
                rating_j == rating_best &&
                catalog[j].price < catalog[best].price;
            if(better_rating || same_rating_cheaper){
                best = j;
            }
        }
        if(best != i){
            Course tmp = catalog[i];
            catalog[i] = catalog[best];
            catalog[best] = tmp;
        }
    }
}

/**
 * Покупает курсы с лучшим отношением рейтинга к цене,
 * пока не исчерпаны бюджет или лимит часов.
 *
 * @param catalog список курсов
 * @param budget максимальная сумма денег
 * @param max_hours максимальная суммарная продолжительность
 */
void buyBestCourses(const vector<Course>& catalog, const float budget, const int max_hours){
    const int size = (int)catalog.size();
    vector<bool> used;
    for(int i = 0; i < size; i++){
        used.push_back(false);
    }

    float spent = 0.0f;
    int hours = 0;
    int bought = 0;

    cout << "Purchased courses:" << endl;
    while(true){
        int best_index = -1;
        float best_ratio = -1.0f;
        for(int i = 0; i < size; i++){
            if(used[i]){
                continue;
            }
            if(spent + catalog[i].price > budget){
                continue;
            }
            if(hours + catalog[i].duration > max_hours){
                continue;
            }
            const float ratio = catalog[i].rating / catalog[i].price;
            if(ratio > best_ratio){
                best_ratio = ratio;
                best_index = i;
            }
        }
        if(best_index < 0){
            break;
        }
        used[best_index] = true;
        spent = spent + catalog[best_index].price;
        hours = hours + catalog[best_index].duration;
        bought = bought + 1;
        printCourse(catalog[best_index]);
    }

    if(bought == 0){
        cout << "No courses fit the budget and time limits." << endl;
    }else{
        cout << fixed << setprecision(2);
        cout << "Courses bought: " << bought << endl;
        cout << "Money spent: " << spent << " / " << budget << endl;
        cout << "Hours taken: " << hours << " / " << max_hours << endl;
    }
}

int main(){
    srand((unsigned int)time(nullptr));

    int input_n = 0;
    cout << "Enter N: ";
    cin >> input_n;
    if(input_n < 1){
        cout << "N must be a positive integer." << endl;
        return 1;
    }

    const int n = input_n;
    vector<Course> catalog = generateCatalog(n);

    cout << endl;
    cout << "Generated catalog:" << endl;
    printCatalog(catalog);

    int choice = 0;
    cout << endl;
    cout << "Choose an operation:" << endl;
    cout << "1. Recommend courses by rating and price" << endl;
    cout << "2. Show shortest and longest courses" << endl;
    cout << "3. Average rating for basic and advanced courses" << endl;
    cout << "4. Sort by rating (desc) and price (asc)" << endl;
    cout << "5. Buy best rating/price courses within limits" << endl;
    cout << "Operation: ";
    cin >> choice;
    cout << endl;

    if(choice == 1){
        float min_rating = 0.0f;
        float max_price = 0.0f;
        cout << "Minimum rating: ";
        cin >> min_rating;
        cout << "Maximum price: ";
        cin >> max_price;
        recommendCourses(catalog, min_rating, max_price);
    }else if(choice == 2){
        compareDuration(catalog);
    }else if(choice == 3){
        groupAverageRating(catalog);
    }else if(choice == 4){
        sortByRatingAndPrice(catalog);
        cout << "Sorted catalog:" << endl;
        printCatalog(catalog);
    }else if(choice == 5){
        float budget = 0.0f;
        int max_hours = 0;
        cout << "Budget: ";
        cin >> budget;
        cout << "Max hours: ";
        cin >> max_hours;
        buyBestCourses(catalog, budget, max_hours);
    }else{
        cout << "Unknown operation." << endl;
    }

    return 0;
}
