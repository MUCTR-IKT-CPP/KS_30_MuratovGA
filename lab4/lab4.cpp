#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct TemperatureSensor{
    double temperature;
};

struct PressureSensor{
    double pressure;
};

struct MotionSensor{
    int motion_detected;
};

enum SensorType{
    TEMPERATURE,
    PRESSURE,
    MOTION
};

struct Sensor{
    void* sensor_data;
    SensorType type;
    int timestamp;
};

const int MAX_SENSORS = 20;

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
 * Создаёт сенсор заданного типа и выделяет под него данные.
 *
 * @param sensor_type тип сенсора.
 * @param created_at время создания.
 * @return заполненный сенсор.
 */
Sensor createSensor(SensorType const sensor_type, int const created_at){
    Sensor sensor;
    sensor.type = sensor_type;
    sensor.timestamp = created_at;
    sensor.sensor_data = nullptr;

    if(sensor_type == TEMPERATURE){
        TemperatureSensor* p_temp = new TemperatureSensor;
        p_temp->temperature = 0.0;
        sensor.sensor_data = p_temp;
    }else if(sensor_type == PRESSURE){
        PressureSensor* p_press = new PressureSensor;
        p_press->pressure = 0.0;
        sensor.sensor_data = p_press;
    }else{
        MotionSensor* p_motion = new MotionSensor;
        p_motion->motion_detected = 0;
        sensor.sensor_data = p_motion;
    }

    return sensor;
}

/*
 * Освобождает данные одного сенсора.
 *
 * @param p_sensor указатель на сенсор.
 * @return функция не возвращает значение.
 */
void freeSensor(Sensor* p_sensor){
    if(p_sensor == nullptr || p_sensor->sensor_data == nullptr){
        return;
    }

    if(p_sensor->type == TEMPERATURE){
        delete (TemperatureSensor*)p_sensor->sensor_data;
    }else if(p_sensor->type == PRESSURE){
        delete (PressureSensor*)p_sensor->sensor_data;
    }else{
        delete (MotionSensor*)p_sensor->sensor_data;
    }

    p_sensor->sensor_data = nullptr;
}

/*
 * Возвращает название типа сенсора.
 *
 * @param sensor_type тип сенсора.
 * @return строка с названием типа.
 */
const char* getTypeName(SensorType const sensor_type){
    if(sensor_type == TEMPERATURE){
        return "Temperature";
    }
    if(sensor_type == PRESSURE){
        return "Pressure";
    }
    return "Motion";
}

/*
 * Печатает данные одного сенсора.
 *
 * @param sensor сенсор для вывода.
 * @return функция не возвращает значение.
 */
void printSensor(Sensor const sensor){
    cout << getTypeName(sensor.type) << " | time=" << sensor.timestamp << " | ";

    if(sensor.sensor_data == nullptr){
        cout << "no data" << endl;
        return;
    }

    if(sensor.type == TEMPERATURE){
        TemperatureSensor* p_temp = (TemperatureSensor*)sensor.sensor_data;
        cout << "value=" << p_temp->temperature << " C" << endl;
    }else if(sensor.type == PRESSURE){
        PressureSensor* p_press = (PressureSensor*)sensor.sensor_data;
        cout << "value=" << p_press->pressure << " hPa" << endl;
    }else{
        MotionSensor* p_motion = (MotionSensor*)sensor.sensor_data;
        if(p_motion->motion_detected == 1){
            cout << "value=motion" << endl;
        }else{
            cout << "value=still" << endl;
        }
    }
}

/*
 * Опрашивает все сенсоры и записывает случайные значения.
 *
 * @param sensors массив сенсоров.
 * @param count количество сенсоров.
 * @return функция не возвращает значение.
 */
void pollSensors(Sensor sensors[], int const count){
    for(int i = 0; i < count; i++){
        if(sensors[i].sensor_data == nullptr){
            continue;
        }

        if(sensors[i].type == TEMPERATURE){
            TemperatureSensor* p_temp = (TemperatureSensor*)sensors[i].sensor_data;
            p_temp->temperature = randomDouble(-10.0, 40.0);
        }else if(sensors[i].type == PRESSURE){
            PressureSensor* p_press = (PressureSensor*)sensors[i].sensor_data;
            p_press->pressure = randomDouble(980.0, 1040.0);
        }else{
            MotionSensor* p_motion = (MotionSensor*)sensors[i].sensor_data;
            p_motion->motion_detected = randomInt(0, 1);
        }
    }
}

/*
 * Выводит сенсоры заданного типа.
 *
 * @param sensors массив сенсоров.
 * @param count количество сенсоров.
 * @param filter_type тип для фильтрации.
 * @return функция не возвращает значение.
 */
void filterByType(Sensor sensors[], int const count, SensorType const filter_type){
    int found = 0;

    for(int i = 0; i < count; i++){
        if(sensors[i].type == filter_type){
            cout << i << ". ";
            printSensor(sensors[i]);
            found = found + 1;
        }
    }

    if(found == 0){
        cout << "No sensors of this type." << endl;
    }
}

/*
 * Калибрует сенсоры: сбрасывает значения.
 *
 * @param sensors массив сенсоров.
 * @param count количество сенсоров.
 * @return функция не возвращает значение.
 */
void calibrate(Sensor sensors[], int const count){
    for(int i = 0; i < count; i++){
        if(sensors[i].sensor_data == nullptr){
            continue;
        }

        if(sensors[i].type == TEMPERATURE){
            TemperatureSensor* p_temp = (TemperatureSensor*)sensors[i].sensor_data;
            p_temp->temperature = 0.0;
        }else if(sensors[i].type == PRESSURE){
            PressureSensor* p_press = (PressureSensor*)sensors[i].sensor_data;
            p_press->pressure = 0.0;
        }else{
            MotionSensor* p_motion = (MotionSensor*)sensors[i].sensor_data;
            p_motion->motion_detected = 0;
        }
    }
}

/*
 * Сохраняет последние значения в журнал (выводит в консоль).
 *
 * @param sensors массив сенсоров.
 * @param count количество сенсоров.
 * @return функция не возвращает значение.
 */
void saveJournal(Sensor sensors[], int const count){
    cout << "Journal:" << endl;
    for(int i = 0; i < count; i++){
        cout << "log " << i << ": ";
        printSensor(sensors[i]);
    }
}

/*
 * Ищет сенсор по времени создания.
 *
 * @param sensors массив сенсоров.
 * @param count количество сенсоров.
 * @param created_at искомое время.
 * @return индекс сенсора или -1, если не найден.
 */
int findByTimestamp(Sensor sensors[], int const count, int const created_at){
    for(int i = 0; i < count; i++){
        if(sensors[i].timestamp == created_at){
            return i;
        }
    }
    return -1;
}

/*
 * Выводит все сенсоры.
 *
 * @param sensors массив сенсоров.
 * @param count количество сенсоров.
 * @return функция не возвращает значение.
 */
void printAll(Sensor sensors[], int const count){
    for(int i = 0; i < count; i++){
        cout << i << ". ";
        printSensor(sensors[i]);
    }
}

/*
 * Освобождает данные всех сенсоров.
 *
 * @param sensors массив сенсоров.
 * @param count количество сенсоров.
 * @return функция не возвращает значение.
 */
void freeAll(Sensor sensors[], int const count){
    for(int i = 0; i < count; i++){
        freeSensor(&sensors[i]);
    }
}

int main(){
    srand((unsigned int)time(nullptr));

    Sensor sensors[MAX_SENSORS];
    int const sensor_count = 8;

    for(int i = 0; i < sensor_count; i++){
        int const kind_value = randomInt(0, 2);
        SensorType kind = TEMPERATURE;
        if(kind_value == 1){
            kind = PRESSURE;
        }else if(kind_value == 2){
            kind = MOTION;
        }
        int const created_at = 1000 + i * 10;
        sensors[i] = createSensor(kind, created_at);
    }

    cout << "Network created. Sensors: " << sensor_count << endl;
    cout << "Initial sensors:" << endl;
    printAll(sensors, sensor_count);

    cout << endl;
    cout << "Polling sensors..." << endl;
    pollSensors(sensors, sensor_count);
    printAll(sensors, sensor_count);

    cout << endl;
    cout << "Filter: temperature sensors" << endl;
    filterByType(sensors, sensor_count, TEMPERATURE);

    cout << endl;
    cout << "Filter: pressure sensors" << endl;
    filterByType(sensors, sensor_count, PRESSURE);

    cout << endl;
    cout << "Filter: motion sensors" << endl;
    filterByType(sensors, sensor_count, MOTION);

    cout << endl;
    cout << "Journal before calibration:" << endl;
    saveJournal(sensors, sensor_count);

    cout << endl;
    cout << "Calibrating..." << endl;
    calibrate(sensors, sensor_count);
    printAll(sensors, sensor_count);

    cout << endl;
    cout << "Search by timestamp:" << endl;
    int const search_time = 1020;
    int const found_index = findByTimestamp(sensors, sensor_count, search_time);
    if(found_index >= 0){
        cout << "Found sensor with time " << search_time << ":" << endl;
        printSensor(sensors[found_index]);
    }else{
        cout << "Sensor with time " << search_time << " not found." << endl;
    }

    freeAll(sensors, sensor_count);
    return 0;
}
