#include <cstdlib>
#include <ctime>
#include <iostream>

/*
 * Р’С‹РґРµР»СЏРµС‚ РїР°РјСЏС‚СЊ РґР»СЏ РєРІР°РґСЂР°С‚РЅРѕР№ РјР°С‚СЂРёС†С‹ С†РµР»С‹С… С‡РёСЃРµР».
 *
 * @param size РєРѕР»РёС‡РµСЃС‚РІРѕ СЃС‚СЂРѕРє Рё СЃС‚РѕР»Р±С†РѕРІ РјР°С‚СЂРёС†С‹.
 * @return СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СЃРѕР·РґР°РЅРЅСѓСЋ РјР°С‚СЂРёС†Сѓ.
 */
int** createMatrix(int const size){
    int** matrix = new int*[size];

    for(int i = 0; i < size; i++){
        matrix[i] = new int[size];
    }

    return matrix;
}

/*
 * РћСЃРІРѕР±РѕР¶РґР°РµС‚ РїР°РјСЏС‚СЊ, Р·Р°РЅСЏС‚СѓСЋ РєРІР°РґСЂР°С‚РЅРѕР№ РјР°С‚СЂРёС†РµР№.
 *
 * @param matrix СѓРєР°Р·Р°С‚РµР»СЊ РЅР° СѓРґР°Р»СЏРµРјСѓСЋ РјР°С‚СЂРёС†Сѓ.
 * @param size РєРѕР»РёС‡РµСЃС‚РІРѕ СЃС‚СЂРѕРє РјР°С‚СЂРёС†С‹.
 * @return С„СѓРЅРєС†РёСЏ РЅРµ РІРѕР·РІСЂР°С‰Р°РµС‚ Р·РЅР°С‡РµРЅРёРµ.
 */
void deleteMatrix(int** matrix, int const size){
    for(int i = 0; i < size; i++){
        delete[] matrix[i];
    }

    delete[] matrix;
}

/*
 * Р—Р°РїРѕР»РЅСЏРµС‚ РјР°С‚СЂРёС†Сѓ СЃР»СѓС‡Р°Р№РЅС‹РјРё С‡РёСЃР»Р°РјРё РѕС‚ 0 РґРѕ 9.
 *
 * @param matrix Р·Р°РїРѕР»РЅСЏРµРјР°СЏ РјР°С‚СЂРёС†Р°.
 * @param size РєРѕР»РёС‡РµСЃС‚РІРѕ СЃС‚СЂРѕРє Рё СЃС‚РѕР»Р±С†РѕРІ РјР°С‚СЂРёС†С‹.
 * @return С„СѓРЅРєС†РёСЏ РЅРµ РІРѕР·РІСЂР°С‰Р°РµС‚ Р·РЅР°С‡РµРЅРёРµ.
 */
void fillMatrix(int** matrix, int const size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            matrix[i][j] = rand() % 10;
        }
    }
}

/*
 * Р’С‹РІРѕРґРёС‚ РјР°С‚СЂРёС†Сѓ РІ С‚РµСЂРјРёРЅР°Р».
 *
 * @param matrix РІС‹РІРѕРґРёРјР°СЏ РјР°С‚СЂРёС†Р°.
 * @param size РєРѕР»РёС‡РµСЃС‚РІРѕ СЃС‚СЂРѕРє Рё СЃС‚РѕР»Р±С†РѕРІ РјР°С‚СЂРёС†С‹.
 * @return С„СѓРЅРєС†РёСЏ РЅРµ РІРѕР·РІСЂР°С‰Р°РµС‚ Р·РЅР°С‡РµРЅРёРµ.
 */
void printMatrix(int** matrix, int const size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cout << matrix[i][j] << ' ';
        }

        std::cout << '\n';
    }
}

/*
 * РћС‚СЂР°Р¶Р°РµС‚ РјР°С‚СЂРёС†Сѓ РѕС‚РЅРѕСЃРёС‚РµР»СЊРЅРѕ РІРµСЂС‚РёРєР°Р»СЊРЅРѕР№ РѕСЃРё.
 *
 * @param matrix РёР·РјРµРЅСЏРµРјР°СЏ РјР°С‚СЂРёС†Р°.
 * @param size РєРѕР»РёС‡РµСЃС‚РІРѕ СЃС‚СЂРѕРє Рё СЃС‚РѕР»Р±С†РѕРІ РјР°С‚СЂРёС†С‹.
 * @return С„СѓРЅРєС†РёСЏ РЅРµ РІРѕР·РІСЂР°С‰Р°РµС‚ Р·РЅР°С‡РµРЅРёРµ.
 */
void mirrorVertical(int** matrix, int const size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size / 2; j++){
            int const opposite_index = size - 1 - j;
            int temporary_value = matrix[i][j];
            matrix[i][j] = matrix[i][opposite_index];
            matrix[i][opposite_index] = temporary_value;
        }
    }
}

/*
 * РћС‚СЂР°Р¶Р°РµС‚ РјР°С‚СЂРёС†Сѓ РѕС‚РЅРѕСЃРёС‚РµР»СЊРЅРѕ РіРѕСЂРёР·РѕРЅС‚Р°Р»СЊРЅРѕР№ РѕСЃРё.
 *
 * @param matrix РёР·РјРµРЅСЏРµРјР°СЏ РјР°С‚СЂРёС†Р°.
 * @param size РєРѕР»РёС‡РµСЃС‚РІРѕ СЃС‚СЂРѕРє Рё СЃС‚РѕР»Р±С†РѕРІ РјР°С‚СЂРёС†С‹.
 * @return С„СѓРЅРєС†РёСЏ РЅРµ РІРѕР·РІСЂР°С‰Р°РµС‚ Р·РЅР°С‡РµРЅРёРµ.
 */
void mirrorHorizontal(int** matrix, int const size){
    for(int i = 0; i < size / 2; i++){
        int const opposite_index = size - 1 - i;

        for(int j = 0; j < size; j++){
            int temporary_value = matrix[i][j];
            matrix[i][j] = matrix[opposite_index][j];
            matrix[opposite_index][j] = temporary_value;
        }
    }
}

/*
 * РЎРѕР·РґР°С‘С‚ РјР°С‚СЂРёС†Сѓ СЃСѓРјРј СЃРѕСЃРµРґРЅРёС… СЌР»РµРјРµРЅС‚РѕРІ СЃРІРµСЂС…Сѓ, СЃРЅРёР·Сѓ, СЃР»РµРІР° Рё СЃРїСЂР°РІР°.
 *
 * @param matrix РёСЃС…РѕРґРЅР°СЏ РјР°С‚СЂРёС†Р°.
 * @param size РєРѕР»РёС‡РµСЃС‚РІРѕ СЃС‚СЂРѕРє Рё СЃС‚РѕР»Р±С†РѕРІ РјР°С‚СЂРёС†С‹.
 * @return СѓРєР°Р·Р°С‚РµР»СЊ РЅР° РјР°С‚СЂРёС†Сѓ СЃСѓРјРј СЃРѕСЃРµРґРЅРёС… СЌР»РµРјРµРЅС‚РѕРІ.
 */
int** buildNeighborSumMatrix(int** matrix, int const size){
    int** sum_matrix = createMatrix(size);

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int sum = 0;

            if(i > 0){
                sum += matrix[i - 1][j];
            }

            if(i < size - 1){
                sum += matrix[i + 1][j];
            }

            if(j > 0){
                sum += matrix[i][j - 1];
            }

            if(j < size - 1){
                sum += matrix[i][j + 1];
            }

            sum_matrix[i][j] = sum;
        }
    }

    return sum_matrix;
}

/*
 * РџСЂРёРЅРёРјР°РµС‚ СѓРєР°Р·Р°С‚РµР»СЊ РЅР° РјР°С‚СЂРёС†Сѓ С‡РµСЂРµР· РїР°СЂР°РјРµС‚СЂ С‚РёРїР° void* Рё РІС‹РІРѕРґРёС‚ РµС‘.
 *
 * @param matrix_pointer СѓРєР°Р·Р°С‚РµР»СЊ void* РЅР° РјР°С‚СЂРёС†Сѓ.
 * @param size РєРѕР»РёС‡РµСЃС‚РІРѕ СЃС‚СЂРѕРє Рё СЃС‚РѕР»Р±С†РѕРІ РјР°С‚СЂРёС†С‹.
 * @return С„СѓРЅРєС†РёСЏ РЅРµ РІРѕР·РІСЂР°С‰Р°РµС‚ Р·РЅР°С‡РµРЅРёРµ.
 */
void printMatrixFromVoid(void* matrix_pointer, int const size){
    int** matrix = static_cast<int**>(matrix_pointer);
    printMatrix(matrix, size);
}

/*
 * Р—Р°РїСЂР°С€РёРІР°РµС‚ СЂР°Р·РјРµСЂ РјР°С‚СЂРёС†С‹ Рё РІС‹Р±СЂР°РЅРЅСѓСЋ РѕРїРµСЂР°С†РёСЋ, Р·Р°С‚РµРј РІС‹РІРѕРґРёС‚ СЂРµР·СѓР»СЊС‚Р°С‚.
 *
 * @param Сѓ С„СѓРЅРєС†РёРё РЅРµС‚ РїР°СЂР°РјРµС‚СЂРѕРІ.
 * @return 0 РїСЂРё СѓСЃРїРµС€РЅРѕРј Р·Р°РІРµСЂС€РµРЅРёРё, 1 РїСЂРё РЅРµРІРµСЂРЅРѕРј РІРІРѕРґРµ.
 */
int main(){
    int size = 0;
    int operation = 0;

    std::cout << "Enter matrix size N: ";
    std::cin >> size;

    if(size <= 0){
        std::cout << "N must be greater than zero.\n";
        return 1;
    }

    int** matrix = createMatrix(size);
    srand(time(NULL));
    fillMatrix(matrix, size);

    std::cout << "Original matrix:\n";
    printMatrix(matrix, size);
    std::cout << "\n1 - Vertical mirror\n";
    std::cout << "2 - Horizontal mirror\n";
    std::cout << "3 - Sum of neighbors\n";
    std::cout << "4 - Pass matrix through void*\n";
    std::cout << "Choose operation: ";
    std::cin >> operation;

    if(operation == 1){
        mirrorVertical(matrix, size);
        std::cout << "\nVertical mirror:\n";
        printMatrix(matrix, size);
    }else if(operation == 2){
        mirrorHorizontal(matrix, size);
        std::cout << "\nHorizontal mirror:\n";
        printMatrix(matrix, size);
    }else if(operation == 3){
        int** sum_matrix = buildNeighborSumMatrix(matrix, size);
        std::cout << "\nSum of neighbors:\n";
        printMatrix(sum_matrix, size);
        deleteMatrix(sum_matrix, size);
    }else if(operation == 4){
        std::cout << "\nMatrix received through void*:\n";
        printMatrixFromVoid(matrix, size);
    }else{
        std::cout << "Unknown operation.\n";
        deleteMatrix(matrix, size);
        return 1;
    }

    deleteMatrix(matrix, size);
    return 0;
}

