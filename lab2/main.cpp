#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * Выделяет память под квадратную матрицу n * n и заполняет её нулями.
 *
 * @param n размер стороны матрицы
 * @return указатель на выделенную матрицу
 */
int** allocateMatrix(const int n){
    int** p_matrix = new int*[n];
    for(int i = 0; i < n; i++){
        p_matrix[i] = new int[n];
        for(int j = 0; j < n; j++){
            p_matrix[i][j] = 0;
        }
    }
    return p_matrix;
}

/**
 * Освобождает память, выделенную под квадратную матрицу n * n.
 *
 * @param p_matrix указатель на матрицу
 * @param n размер стороны матрицы
 */
void freeMatrix(int** p_matrix, const int n){
    if(p_matrix == nullptr){
        return;
    }
    for(int i = 0; i < n; i++){
        delete[] p_matrix[i];
    }
    delete[] p_matrix;
}

/**
 * Заполняет матрицу случайными целыми числами от 0 до 9.
 *
 * @param p_matrix указатель на матрицу
 * @param n размер стороны матрицы
 */
void fillRandom(int** p_matrix, const int n){
    const int MIN_VALUE = 0;
    const int MAX_VALUE = 9;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            p_matrix[i][j] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
        }
    }
}

/**
 * Выводит матрицу в терминал.
 *
 * @param p_matrix указатель на матрицу
 * @param n размер стороны матрицы
 */
void printMatrix(int** p_matrix, const int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << p_matrix[i][j];
            if(j + 1 < n){
                cout << " ";
            }
        }
        cout << endl;
    }
}

/**
 * Создаёт зеркальное отражение матрицы относительно вертикальной оси.
 * Столбцы меняются местами: левый становится правым и наоборот.
 *
 * @param p_source исходная матрица
 * @param n размер стороны матрицы
 * @return новая матрица с вертикальным отражением
 */
int** createVerticalMirror(int** p_source, const int n){
    int** p_result = allocateMatrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            p_result[i][j] = p_source[i][n - 1 - j];
        }
    }
    return p_result;
}

/**
 * Создаёт зеркальное отражение матрицы относительно горизонтальной оси.
 * Строки меняются местами: верхняя становится нижней и наоборот.
 *
 * @param p_source исходная матрица
 * @param n размер стороны матрицы
 * @return новая матрица с горизонтальным отражением
 */
int** createHorizontalMirror(int** p_source, const int n){
    int** p_result = allocateMatrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            p_result[i][j] = p_source[n - 1 - i][j];
        }
    }
    return p_result;
}

/**
 * Строит матрицу, в которой каждый элемент равен сумме соседних элементов.
 * Соседями считаются клетки сверху, снизу, слева и справа, если они есть.
 * Сам элемент в сумму не входит.
 *
 * @param p_source исходная матрица
 * @param n размер стороны матрицы
 * @return новая матрица из сумм соседей
 */
int** buildNeighborSumMatrix(int** p_source, const int n){
    int** p_result = allocateMatrix(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int neighbor_sum = 0;
            if(i > 0){
                neighbor_sum = neighbor_sum + p_source[i - 1][j];
            }
            if(i + 1 < n){
                neighbor_sum = neighbor_sum + p_source[i + 1][j];
            }
            if(j > 0){
                neighbor_sum = neighbor_sum + p_source[i][j - 1];
            }
            if(j + 1 < n){
                neighbor_sum = neighbor_sum + p_source[i][j + 1];
            }
            p_result[i][j] = neighbor_sum;
        }
    }
    return p_result;
}

/**
 * Принимает матрицу через параметр void* и выводит её содержимое.
 * Указатель приводится обратно к типу int**, после чего матрица печатается.
 *
 * @param p_data указатель на матрицу, переданный как void*
 * @param n размер стороны матрицы
 */
void printMatrixViaVoid(void* p_data, const int n){
    int** p_matrix = (int**)p_data;
    printMatrix(p_matrix, n);
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
    int** p_matrix = allocateMatrix(n);
    fillRandom(p_matrix, n);

    cout << "N = " << n << endl;
    cout << "Matrix:" << endl;
    printMatrix(p_matrix, n);

    cout << endl;
    cout << "Choose an operation:" << endl;
    cout << "1. Create a vertical-axis mirror" << endl;
    cout << "2. Create a horizontal-axis mirror" << endl;
    cout << "3. Build a matrix where each element is the sum of neighbors" << endl;
    cout << "4. Pass the array to a function via void*" << endl;
    cout << "Operation: ";

    int choice = 0;
    cin >> choice;

    int** p_result = nullptr;
    cout << endl;
    cout << "Output:" << endl;

    if(choice == 1){
        p_result = createVerticalMirror(p_matrix, n);
        printMatrix(p_result, n);
    }else if(choice == 2){
        p_result = createHorizontalMirror(p_matrix, n);
        printMatrix(p_result, n);
    }else if(choice == 3){
        p_result = buildNeighborSumMatrix(p_matrix, n);
        printMatrix(p_result, n);
    }else if(choice == 4){
        printMatrixViaVoid((void*)p_matrix, n);
    }else{
        cout << "Unknown operation." << endl;
    }

    if(p_result != nullptr){
        freeMatrix(p_result, n);
    }
    freeMatrix(p_matrix, n);
    return 0;
}
