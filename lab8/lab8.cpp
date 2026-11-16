#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/*
 * Интерфейс курса.
 */
class ICourse{
public:
    virtual ~ICourse(){}
    virtual int getId() const = 0;
    virtual string getTitle() const = 0;
    virtual int getCredits() const = 0;
};

/*
 * Интерфейс преподавателя.
 */
class IInstructor{
public:
    virtual ~IInstructor(){}
    virtual int getId() const = 0;
    virtual string getName() const = 0;
    virtual const vector<string>& getSubjects() const = 0;
};

/*
 * Интерфейс каталога.
 */
class ICatalog{
public:
    virtual ~ICatalog(){}
    virtual void addCourse(const ICourse* p_course) = 0;
    virtual void addInstructor(const IInstructor* p_instructor) = 0;
    virtual bool assignInstructor(int course_id, int instructor_id) = 0;
    virtual const IInstructor* getInstructorByCourse(int course_id) const = 0;
};

/*
 * Временной интервал занятия.
 */
struct TimeInterval{
    int start;
    int end;

    /*
     * Проверяет пересечение с другим интервалом.
     *
     * @param other другой интервал.
     * @return true, если интервалы пересекаются.
     */
    bool overlaps(const TimeInterval& other) const{
        return start < other.end && other.start < end;
    }
};

/*
 * Расписание преподавателя.
 * Хранит отображение день недели -> список интервалов.
 */
class Schedule{
private:
    map<int, vector<TimeInterval>> _day_to_slots;

public:
    /*
     * Проверяет, свободен ли слот в указанный день.
     *
     * @param day день недели (1-7).
     * @param slot интервал.
     * @return true, если слот свободен.
     */
    bool isFree(int day, const TimeInterval& slot) const{
        auto it = _day_to_slots.find(day);
        if(it == _day_to_slots.end()){
            return true;
        }
        for(const auto& existing : it->second){
            if(existing.overlaps(slot)){
                return false;
            }
        }
        return true;
    }

    /*
     * Резервирует слот, если он свободен.
     *
     * @param day день недели.
     * @param slot интервал.
     * @return true, если успешно зарезервирован.
     */
    bool reserve(int day, const TimeInterval& slot){
        if(!isFree(day, slot)){
            return false;
        }
        _day_to_slots[day].push_back(slot);
        return true;
    }

    /*
     * Выводит расписание.
     *
     * @return функция не возвращает значение.
     */
    void print() const{
        if(_day_to_slots.empty()){
            cout << "  No slots reserved." << endl;
            return;
        }
        for(const auto& pair : _day_to_slots){
            cout << "  Day " << pair.first << ": ";
            for(const auto& slot : pair.second){
                cout << "[" << slot.start << "-" << slot.end << "] ";
            }
            cout << endl;
        }
    }
};

/*
 * Реализация курса.
 */
class Course : public ICourse{
private:
    int _id;
    string _title;
    int _credits;

public:
    /*
     * Создаёт курс.
     *
     * @param id идентификатор.
     * @param title название.
     * @param credits количество кредитов.
     */
    Course(int id, const string& title, int credits)
        : _id(id), _title(title), _credits(credits){}

    int getId() const override{
        return _id;
    }

    string getTitle() const override{
        return _title;
    }

    int getCredits() const override{
        return _credits;
    }
};

/*
 * Реализация преподавателя.
 */
class Instructor : public IInstructor{
private:
    int _id;
    string _name;
    vector<string> _subjects;
    Schedule _schedule;

public:
    /*
     * Создаёт преподавателя.
     *
     * @param id идентификатор.
     * @param name имя.
     * @param subjects список предметов.
     */
    Instructor(int id, const string& name, const vector<string>& subjects)
        : _id(id), _name(name), _subjects(subjects){}

    int getId() const override{
        return _id;
    }

    string getName() const override{
        return _name;
    }

    const vector<string>& getSubjects() const override{
        return _subjects;
    }

    Schedule& getSchedule(){
        return _schedule;
    }

    const Schedule& getSchedule() const{
        return _schedule;
    }

    /*
     * Проверяет, ведёт ли преподаватель данную дисциплину.
     *
     * @param subject название предмета.
     * @return true, если предмет в списке.
     */
    bool teaches(const string& subject) const{
        return find(_subjects.begin(), _subjects.end(), subject) != _subjects.end();
    }
};

/*
 * Каталог курсов и преподавателей.
 * Использует vector (последовательный) и map (ассоциативный).
 */
class Catalog : public ICatalog{
private:
    vector<const Course*> _courses;
    map<int, const Instructor*> _instructors;
    map<int, int> _course_to_instructor;

public:
    void addCourse(const ICourse* p_course) override{
        const Course* p_c = dynamic_cast<const Course*>(p_course);
        if(p_c != nullptr){
            _courses.push_back(p_c);
        }
    }

    void addInstructor(const IInstructor* p_instructor) override{
        const Instructor* p_i = dynamic_cast<const Instructor*>(p_instructor);
        if(p_i != nullptr){
            _instructors[p_i->getId()] = p_i;
        }
    }

    /*
     * Назначает преподавателя на курс с проверкой дисциплины и слота.
     *
     * @param course_id идентификатор курса.
     * @param instructor_id идентификатор преподавателя.
     * @param day день недели.
     * @param slot временной интервал.
     * @return true, если назначение успешно.
     */
    bool assignInstructor(int course_id, int instructor_id, int day, const TimeInterval& slot){
        const Course* p_course = nullptr;
        for(const auto* p_c : _courses){
            if(p_c->getId() == course_id){
                p_course = p_c;
                break;
            }
        }
        if(p_course == nullptr){
            return false;
        }

        auto it = _instructors.find(instructor_id);
        if(it == _instructors.end()){
            return false;
        }
        Instructor* p_instr = const_cast<Instructor*>(it->second);

        if(!p_instr->teaches(p_course->getTitle())){
            return false;
        }

        if(!p_instr->getSchedule().reserve(day, slot)){
            return false;
        }

        _course_to_instructor[course_id] = instructor_id;
        return true;
    }

    bool assignInstructor(int course_id, int instructor_id) override{
        TimeInterval dummy = {0, 0};
        return assignInstructor(course_id, instructor_id, 1, dummy);
    }

    const IInstructor* getInstructorByCourse(int course_id) const override{
        auto it = _course_to_instructor.find(course_id);
        if(it == _course_to_instructor.end()){
            return nullptr;
        }
        auto instr_it = _instructors.find(it->second);
        if(instr_it == _instructors.end()){
            return nullptr;
        }
        return instr_it->second;
    }

    /*
     * Выводит содержимое каталога.
     *
     * @return функция не возвращает значение.
     */
    void printAll() const{
        cout << "Courses:" << endl;
        for(const auto* p_c : _courses){
            cout << "  ID=" << p_c->getId() << " Title=" << p_c->getTitle()
                 << " Credits=" << p_c->getCredits();
            const IInstructor* p_instr = getInstructorByCourse(p_c->getId());
            if(p_instr != nullptr){
                cout << " -> Instructor: " << p_instr->getName();
            }
            cout << endl;
        }
        cout << "Instructors:" << endl;
        for(const auto& pair : _instructors){
            cout << "  ID=" << pair.first << " Name=" << pair.second->getName() << endl;
            cout << "    Subjects: ";
            for(const auto& subj : pair.second->getSubjects()){
                cout << subj << " ";
            }
            cout << endl;
            pair.second->getSchedule().print();
        }
    }
};

/*
 * Кафедра. Агрегирует каталог.
 */
class Department{
private:
    Catalog _catalog;

public:
    Catalog& getCatalog(){
        return _catalog;
    }

    const Catalog& getCatalog() const{
        return _catalog;
    }
};

int main(){
    Department department;
    Catalog& catalog = department.getCatalog();

    Course course1(1, "Algorithms", 4);
    Course course2(2, "Databases", 3);
    Course course3(3, "Networks", 3);

    catalog.addCourse(&course1);
    catalog.addCourse(&course2);
    catalog.addCourse(&course3);

    Instructor instr1(101, "Anna Smith", {"Algorithms", "Data Structures"});
    Instructor instr2(102, "John Carter", {"Databases", "SQL"});
    Instructor instr3(103, "Maria Lopez", {"Networks", "Security"});

    catalog.addInstructor(&instr1);
    catalog.addInstructor(&instr2);
    catalog.addInstructor(&instr3);

    cout << "=== Initial catalog ===" << endl;
    catalog.printAll();

    cout << endl << "=== Assignments ===" << endl;

    TimeInterval slot1 = {9, 11};
    TimeInterval slot2 = {10, 12};
    TimeInterval slot3 = {14, 16};

    bool ok1 = catalog.assignInstructor(1, 101, 1, slot1);
    cout << "Assign Algorithms to Anna (day 1, 9-11): " << (ok1 ? "OK" : "FAILED") << endl;

    bool ok2 = catalog.assignInstructor(2, 102, 2, slot2);
    cout << "Assign Databases to John (day 2, 10-12): " << (ok2 ? "OK" : "FAILED") << endl;

    bool ok3 = catalog.assignInstructor(3, 103, 1, slot1);
    cout << "Assign Networks to Maria (day 1, 9-11): " << (ok3 ? "OK" : "FAILED") << endl;

    bool conflict = catalog.assignInstructor(1, 101, 1, slot2);
    cout << "Try second slot for Anna same day overlapping: " << (conflict ? "OK" : "FAILED (expected)") << endl;

    bool wrong_subject = catalog.assignInstructor(1, 102, 3, slot3);
    cout << "Try assign Algorithms to John (wrong subject): " << (wrong_subject ? "OK" : "FAILED (expected)") << endl;

    cout << endl << "=== Final catalog ===" << endl;
    catalog.printAll();

    cout << endl << "=== Lookup ===" << endl;
    const IInstructor* p_found = catalog.getInstructorByCourse(1);
    if(p_found != nullptr){
        cout << "Instructor for course 1: " << p_found->getName() << endl;
    }else{
        cout << "No instructor for course 1" << endl;
    }

    return 0;
}
