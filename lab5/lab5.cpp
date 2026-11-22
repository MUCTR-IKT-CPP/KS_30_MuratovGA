#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int TYPE_SQUARE = 1;
const int TYPE_RECTANGLE = 2;
const int TYPE_TRIANGLE = 3;

const int MAX_FIGURES = 20;

struct Figure{
    int type;
    double side;
    double width;
    double height;
    double side_a;
    double side_b;
    double side_c;
};

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
 * Проверяет, что стороны образуют треугольник.
 *
 * @param a сторона a.
 * @param b сторона b.
 * @param c сторона c.
 * @return 1, если треугольник возможен, иначе 0.
 */
int isValidTriangle(double const a, double const b, double const c){
    if(a <= 0.0 || b <= 0.0 || c <= 0.0){
        return 0;
    }
    if(a + b > c && a + c > b && b + c > a){
        return 1;
    }
    return 0;
}

/*
 * Создаёт квадрат.
 *
 * @param side сторона.
 * @return фигура типа квадрат.
 */
Figure createSquare(double const side){
    Figure figure;
    figure.type = TYPE_SQUARE;
    figure.side = side;
    if(figure.side <= 0.0){
        figure.side = 1.0;
    }
    figure.width = 0.0;
    figure.height = 0.0;
    figure.side_a = 0.0;
    figure.side_b = 0.0;
    figure.side_c = 0.0;
    return figure;
}

/*
 * Создаёт прямоугольник.
 *
 * @param width ширина.
 * @param height высота.
 * @return фигура типа прямоугольник.
 */
Figure createRectangle(double const width, double const height){
    Figure figure;
    figure.type = TYPE_RECTANGLE;
    figure.side = 0.0;
    figure.width = width;
    figure.height = height;
    if(figure.width <= 0.0){
        figure.width = 1.0;
    }
    if(figure.height <= 0.0){
        figure.height = 1.0;
    }
    figure.side_a = 0.0;
    figure.side_b = 0.0;
    figure.side_c = 0.0;
    return figure;
}

/*
 * Создаёт треугольник.
 *
 * @param a сторона a.
 * @param b сторона b.
 * @param c сторона c.
 * @return фигура типа треугольник.
 */
Figure createTriangle(double const a, double const b, double const c){
    Figure figure;
    figure.type = TYPE_TRIANGLE;
    figure.side = 0.0;
    figure.width = 0.0;
    figure.height = 0.0;
    if(isValidTriangle(a, b, c) == 1){
        figure.side_a = a;
        figure.side_b = b;
        figure.side_c = c;
    }else{
        figure.side_a = 3.0;
        figure.side_b = 3.0;
        figure.side_c = 3.0;
    }
    return figure;
}

/*
 * Вычисляет площадь фигуры.
 *
 * @param figure фигура.
 * @return площадь.
 */
double area(Figure const figure){
    if(figure.type == TYPE_SQUARE){
        return figure.side * figure.side;
    }
    if(figure.type == TYPE_RECTANGLE){
        return figure.width * figure.height;
    }
    if(figure.type == TYPE_TRIANGLE){
        double const semi = (figure.side_a + figure.side_b + figure.side_c) / 2.0;
        double value = semi * (semi - figure.side_a) * (semi - figure.side_b) * (semi - figure.side_c);
        if(value <= 0.0){
            return 0.0;
        }
        double root = value;
        for(int i = 0; i < 20; i++){
            root = 0.5 * (root + value / root);
        }
        return root;
    }
    return 0.0;
}

/*
 * Вычисляет периметр фигуры.
 *
 * @param figure фигура.
 * @return периметр.
 */
double perimeter(Figure const figure){
    if(figure.type == TYPE_SQUARE){
        return 4.0 * figure.side;
    }
    if(figure.type == TYPE_RECTANGLE){
        return 2.0 * (figure.width + figure.height);
    }
    if(figure.type == TYPE_TRIANGLE){
        return figure.side_a + figure.side_b + figure.side_c;
    }
    return 0.0;
}

/*
 * Печатает информацию о фигуре.
 *
 * @param figure фигура.
 * @return функция не возвращает значение.
 */
void printFigure(Figure const figure){
    cout << fixed;
    cout.precision(2);

    if(figure.type == TYPE_SQUARE){
        cout << "Square {side=" << figure.side
             << "} S=" << area(figure)
             << " P=" << perimeter(figure) << endl;
    }else if(figure.type == TYPE_RECTANGLE){
        cout << "Rectangle {width=" << figure.width
             << ", height=" << figure.height
             << "} S=" << area(figure)
             << " P=" << perimeter(figure) << endl;
    }else if(figure.type == TYPE_TRIANGLE){
        cout << "Triangle {a=" << figure.side_a
             << ", b=" << figure.side_b
             << ", c=" << figure.side_c
             << "} S=" << area(figure)
             << " P=" << perimeter(figure) << endl;
    }
}

/*
 * Создаёт случайную фигуру.
 *
 * @return случайная фигура.
 */
Figure createRandomFigure(){
    int const kind = randomInt(1, 3);
    if(kind == TYPE_SQUARE){
        double const side = randomDouble(1.0, 10.0);
        return createSquare(side);
    }
    if(kind == TYPE_RECTANGLE){
        double const width = randomDouble(1.0, 8.0);
        double const height = randomDouble(1.0, 6.0);
        return createRectangle(width, height);
    }

    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    int valid = 0;
    while(valid == 0){
        a = randomDouble(3.0, 7.0);
        b = randomDouble(3.0, 7.0);
        c = randomDouble(3.0, 7.0);
        valid = isValidTriangle(a, b, c);
    }
    return createTriangle(a, b, c);
}

/*
 * Считает общую площадь массива фигур.
 *
 * @param figures массив фигур.
 * @param count количество фигур.
 * @return сумма площадей.
 */
double totalArea(Figure figures[], int const count){
    double sum = 0.0;
    for(int i = 0; i < count; i++){
        sum = sum + area(figures[i]);
    }
    return sum;
}

/*
 * Выводит все фигуры.
 *
 * @param figures массив фигур.
 * @param count количество фигур.
 * @return функция не возвращает значение.
 */
void printAll(Figure figures[], int const count){
    for(int i = 0; i < count; i++){
        printFigure(figures[i]);
    }
}

/*
 * Сравнивает две фигуры по площади.
 *
 * @param first первая фигура.
 * @param second вторая фигура.
 * @return 1, если площадь первой больше, иначе 0.
 */
int compareByArea(Figure const first, Figure const second){
    if(area(first) > area(second)){
        return 1;
    }
    return 0;
}

/*
 * Сортирует массив фигур по площади по убыванию.
 *
 * @param figures массив фигур.
 * @param count количество фигур.
 * @return функция не возвращает значение.
 */
void sortByArea(Figure figures[], int const count){
    for(int i = 0; i < count; i++){
        int best = i;
        for(int j = i + 1; j < count; j++){
            if(compareByArea(figures[j], figures[best]) == 1){
                best = j;
            }
        }
        if(best != i){
            Figure tmp = figures[i];
            figures[i] = figures[best];
            figures[best] = tmp;
        }
    }
}

/*
 * Находит индекс фигуры с максимальным периметром.
 *
 * @param figures массив фигур.
 * @param count количество фигур.
 * @return индекс фигуры.
 */
int findMaxPerimeterIndex(Figure figures[], int const count){
    int best = 0;
    for(int i = 1; i < count; i++){
        if(perimeter(figures[i]) > perimeter(figures[best])){
            best = i;
        }
    }
    return best;
}

int main(){
    srand((unsigned int)time(nullptr));

    int const collection_size = randomInt(5, 15);
    Figure collection[MAX_FIGURES];

    for(int i = 0; i < collection_size; i++){
        collection[i] = createRandomFigure();
    }

    cout << "Collection size: " << collection_size << endl;
    cout << "Figures:" << endl;
    printAll(collection, collection_size);
    cout << "Total area: " << totalArea(collection, collection_size) << endl;

    cout << endl;
    cout << "Advanced test on 10 figures:" << endl;

    int const TEST_COUNT = 10;
    Figure test_figures[MAX_FIGURES];
    for(int i = 0; i < TEST_COUNT; i++){
        test_figures[i] = createRandomFigure();
    }

    sortByArea(test_figures, TEST_COUNT);

    cout << "Sorted by area:" << endl;
    for(int i = 0; i < TEST_COUNT; i++){
        cout << i + 1 << ". ";
        printFigure(test_figures[i]);
    }

    int const max_index = findMaxPerimeterIndex(test_figures, TEST_COUNT);
    cout << "Max perimeter figure:" << endl;
    cout << max_index + 1 << ". ";
    printFigure(test_figures[max_index]);

    return 0;
}
