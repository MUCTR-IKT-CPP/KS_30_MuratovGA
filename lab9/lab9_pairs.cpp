#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

/*
 * Возвращает случайное целое число из отрезка.
 *
 * @param min_value нижняя граница.
 * @param max_value верхняя граница.
 * @return случайное целое.
 */
int randomInt(int const min_value, int const max_value){
    return min_value + rand() % (max_value - min_value + 1);
}

/*
 * Возвращает случайное вещественное число из отрезка.
 *
 * @param min_value нижняя граница.
 * @param max_value верхняя граница.
 * @return случайное число.
 */
double randomDouble(double const min_value, double const max_value){
    double const scale = (double)rand() / (double)RAND_MAX;
    return min_value + scale * (max_value - min_value);
}

/*
 * Создаёт вектор из 25 случайных пар (целое, дробное).
 *
 * @return заполненный вектор пар.
 */
vector<pair<int, double>> createRandomPairs(){
    vector<pair<int, double>> pairs;
    const int PAIR_COUNT = 25;
    for(int i = 0; i < PAIR_COUNT; i++){
        int int_part = randomInt(1, 10);
        double double_part = randomDouble(0.0, 1.0);
        pairs.push_back(make_pair(int_part, double_part));
    }
    return pairs;
}

/*
 * Выводит вектор пар.
 *
 * @param pairs вектор пар.
 * @return функция не возвращает значение.
 */
void printPairs(const vector<pair<int, double>>& pairs){
    cout << fixed << setprecision(2);
    for(size_t i = 0; i < pairs.size(); i++){
        cout << "(" << pairs[i].first << ", " << pairs[i].second << ") ";
        if((i + 1) % 5 == 0){
            cout << endl;
        }
    }
    cout << endl;
}

/*
 * Структура для накопления статистики.
 */
struct Statistics{
    int sum_int;
    double sum_double;
    int count;

    Statistics() : sum_int(0), sum_double(0.0), count(0){}
};

/*
 * Создаёт лямбда-фильтр по порогу дробной части.
 *
 * @param threshold пороговое значение.
 * @return лямбда-предикат.
 */
auto createFilter(double threshold){
    return [threshold](const pair<int, double>& p){
        return p.second > threshold;
    };
}

int main(){
    srand((unsigned int)time(nullptr));
    cout << fixed << setprecision(2);

    vector<pair<int, double>> pairs = createRandomPairs();

    cout << "Generated pairs:" << endl;
    printPairs(pairs);

    // Поиск минимума по целому
    auto min_it = min_element(pairs.begin(), pairs.end(),
        [](const pair<int, double>& a, const pair<int, double>& b){
            return a.first < b.first;
        });
    cout << "Min integer pair: (" << min_it->first << ", " << min_it->second << ")" << endl;

    // Поиск максимума по дробному
    auto max_it = max_element(pairs.begin(), pairs.end(),
        [](const pair<int, double>& a, const pair<int, double>& b){
            return a.second < b.second;
        });
    cout << "Max double pair: (" << max_it->first << ", " << max_it->second << ")" << endl;

    // Partition: дробная часть > 0.5 в начале
    auto partition_it = partition(pairs.begin(), pairs.end(),
        [](const pair<int, double>& p){
            return p.second > 0.5;
        });
    cout << endl << "After partition (double > 0.5 first):" << endl;
    printPairs(pairs);
    cout << "Partition point at index: " << distance(pairs.begin(), partition_it) << endl;

    // Сумма целых
    int sum_int = accumulate(pairs.begin(), pairs.end(), 0,
        [](int acc, const pair<int, double>& p){
            return acc + p.first;
        });
    cout << "Sum of integer parts: " << sum_int << endl;

    // Усложнение: статистика через for_each и замыкание
    Statistics stats;
    for_each(pairs.begin(), pairs.end(),
        [&stats](const pair<int, double>& p){
            stats.sum_int += p.first;
            stats.sum_double += p.second;
            stats.count++;
        });

    cout << endl << "Statistics via for_each:" << endl;
    cout << "Average integer: " << (double)stats.sum_int / stats.count << endl;
    cout << "Average double: " << stats.sum_double / stats.count << endl;

    // Фильтр высшего порядка
    auto filter = createFilter(0.7);
    int count_above = count_if(pairs.begin(), pairs.end(), filter);
    cout << "Pairs with double > 0.7: " << count_above << endl;

    return 0;
}
