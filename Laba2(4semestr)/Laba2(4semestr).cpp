#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <intrin.h> 
#pragma intrinsic(__rdtsc)
using namespace std;

void generate_input(size_t n, string out_fyle) {
    setlocale(LC_ALL, "rus");
    string lane;
    string direct[] = { "Fizika", "Psihologiya", "Economica", "Himiya", "Geologiya",
        "Geographiya", "Biologiya", "Arhitektura", "Mashinostroenie", "Innovatika" };

    string grp_num[] = { "Б9120-09.03.04прогин","Б9119-09.03.04прогин", "Б9120-09.03.03прогин",
        "М3121-26.04.02кто", "М3121-26.04.02ксо", "М4120-37.04.01пм", "С3120-08.05.01сгспо",
        "С3216-20.05.01птпп", "С3216-21.05.04мрд", "А8121-04.06.01фх", "А8121-04.06.01бох" };

    string FIO[] = { "Агеев Андрей Владиславович","Аксенова Алёна Егоровна","Анохин Марк Николаевич",
        "Безруков Иван Никитич","Ильина Варвара Львовна","Ильина Дарья Константиновна","Казанцев Григорий Михайлович",
        "Калугина Виктория Дмитриевна","Кириллова Алиса Демьяновна",
        "Киселева Арина Александровна","Ковалев Роман Александрович",
        "Ковалев Артём Егорович","Козина Василиса Марковна","Козырев Кирилл Иванович",
        "Лебедева Анна Львовна","Орлов Илья Русланович","Сорокина Валерия Тимуровна","Шестакова Таисия Павловна" };

    srand(time(0));
    ofstream output(out_fyle, 'w');
    output << n;
    for (int i = 0; i < n; i++) {
        output << "\n";
        lane = "";
        int phone1 = rand() % 900 + 100;
        int phone2 = rand() % 9000 + 1000;
        int month = rand() % 12 + 1;
        int day;
        if (month == 2) {
            day = rand() % 27 + 1;
        }
        else if (month % 2 == 1 or month == 8) {
            day = rand() % 31 + 1;
        }
        else  day = rand() % 30 + 1;
        int year = rand() % 4 + 2000;
        lane += FIO[rand() % 18] + ' ' + direct[rand() % 10] + ' ' + grp_num[rand() % 11];
        lane += ' ' + (day < 10 ? '0' + to_string(day) : to_string(day)) + '.'
            + (month < 10 ? '0' + to_string(month) : to_string(month)) + '.' + to_string(year) + " 8914" + to_string(phone1) + to_string(phone2);

        output << lane;
    }
    output.close();
}

void split(string s, char delim, vector<string>& data)
{
    while (!s.empty())
    {
        auto word_end = s.find(delim);
        if (word_end == -1)
        {
            data.push_back(s);
            s.clear();
        }
        else
        {
            data.push_back(s.substr(0, word_end));
            s.erase(0, word_end + 1);
        }
    }
}

struct FIO
{
    string f;
    string i;
    string o;
};

struct BirthDate
{
    int dd;
    int mm;
    int yy;
};

struct Student
{
    FIO fio;
    string direct;
    string groupNum;
    BirthDate bdate;
    string phoneNum;
    int stringNum;
};

bool operator <(Student& l, Student& r)
{
    string tempL = l.fio.f + " " + l.fio.i + " " + l.fio.o;
    string tempR = r.fio.f + " " + r.fio.i + " " + r.fio.o;

    if (l.bdate.yy < r.bdate.yy)
        return true;
    else if (l.bdate.yy > r.bdate.yy)
        return false;
    else if (l.bdate.yy == r.bdate.yy)
    {
        if (l.bdate.mm < r.bdate.mm)
            return true;
        else if (l.bdate.mm > r.bdate.mm)
            return false;
        else if (l.bdate.mm == r.bdate.mm)
        {
            if (l.bdate.dd < r.bdate.dd)
                return true;
            else if (l.bdate.dd > r.bdate.dd)
                return false;
            else if (l.bdate.dd == r.bdate.dd)
            {
                if (l.groupNum < r.groupNum)
                    return true;
                else if (l.groupNum > r.groupNum)
                    return false;
                else if (l.groupNum == r.groupNum)
                {
                    if (tempL < tempR)
                        return true;
                    else if (tempL >= tempR)
                        return false;
                }
            }
        }
    }
}

int minusPhoneNum(string l, string r)
{
    l.erase(0, 3);
    r.erase(0, 3);
    int lNum = stoi(l);
    int rNum = stoi(r);
    return (lNum - rNum);
}

//Вывод
void outStudents(ofstream& fout, Student* studentsWithFoundPattern, double time, size_t count)
{
    fout << time;
    for (size_t i = 0; i < count; i++)
    {
        fout << "\n";
        //studentsWithFoundPattern[i].bdate.dd < 10 ? '0' + to_string(day) : to_string(day)
        fout << (studentsWithFoundPattern[i].bdate.dd < 10 ? '0' + to_string(studentsWithFoundPattern[i].bdate.dd) : to_string(studentsWithFoundPattern[i].bdate.dd)) << "." <<
            (studentsWithFoundPattern[i].bdate.mm < 10 ? '0' + to_string(studentsWithFoundPattern[i].bdate.mm) : to_string(studentsWithFoundPattern[i].bdate.mm)) << "." <<
            (studentsWithFoundPattern[i].bdate.yy) << " ";
        int l = 23 - studentsWithFoundPattern[i].groupNum.size();
        fout << studentsWithFoundPattern[i].groupNum;
        for (size_t i = 0; i < l; i++)
            fout << " ";
        string fio = studentsWithFoundPattern[i].fio.f + " " + studentsWithFoundPattern[i].fio.i + " " + studentsWithFoundPattern[i].fio.o;
        l = 31 - fio.size();
        fout << fio;
        for (size_t i = 0; i < l; i++)
            fout << " ";
        l = 47 - studentsWithFoundPattern[i].direct.size();
        fout << studentsWithFoundPattern[i].direct;
        for (size_t i = 0; i < l; i++)
            fout << " ";
        fout << studentsWithFoundPattern[i].phoneNum;
    }
}

//сортировка выбором
void choiceSort(int n, Student*& stud)
{
    // Перебираем каждый элемент массива (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберемся)
    for (int startIndex = 0; startIndex < n - 1; ++startIndex)
    {
        // В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
        // Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
        int smallestIndex = startIndex;

        // Затем ищем элемент поменьше в остальной части массива
        for (int currentIndex = startIndex + 1; currentIndex < n; ++currentIndex)
        {
            // Если мы нашли элемент, который меньше нашего наименьшего элемента,
            if (stud[smallestIndex].phoneNum > stud[currentIndex].phoneNum)
                // то запоминаем его
                smallestIndex = currentIndex;
        }

        // smallestIndex теперь наименьший элемент. 
        // Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
        std::swap(stud[startIndex], stud[smallestIndex]);
    }
}

//Линейный поиск
void naiveSearch(Student* students, size_t size, string key, vector<int>& stringNumbers, int& steps)
{
    for (size_t i = 0; i < size; i++)
    {
        if (students[i].phoneNum == key)
        {
            stringNumbers.push_back(students[i].stringNum);
        }
        steps += 1;
    }
}

void naiveSearchOut(Student* students, size_t size, string key)
{
    vector<int> stringNumbers;
    int steps = 0;
    naiveSearch(students, size, key, stringNumbers, steps);
    size_t stringNumbersSize = stringNumbers.size();
    cout << "Naive search:" << endl;
    if (stringNumbers.size() == 0)
    {
        cout << "String with search key not found." << endl
             << "Steps: " << steps << endl;
    }
    else
    {
        cout << "Found strings' numbers: " << stringNumbers[0];
        for (size_t i = 1; i < stringNumbersSize; i++)
        {
            cout << ", " << stringNumbers[i];
        }
        cout << endl << "Steps: " << steps << endl;
    }
}

void interpolationSearch(Student* students, size_t size, string key, vector<int>& stringNumbers, int& steps)
{
    int low = 0;
    int high = size - 1;
    int mid;
    int temp1, temp2;

    while ((students[high].phoneNum != students[low].phoneNum) && (key >= students[low].phoneNum) && (key <= students[high].phoneNum))
    {
        steps += 1;
        mid = low + (minusPhoneNum(key, students[low].phoneNum) * (high - low) / minusPhoneNum(students[high].phoneNum, students[low].phoneNum));

        if (students[mid].phoneNum < key)
            low = mid + 1;
        else if (students[mid].phoneNum > key)
            high = mid - 1;
        else
        {
            temp1 = mid;
            while (students[temp1].phoneNum == key)
            {
                steps += 1;
                stringNumbers.push_back(students[temp1].stringNum);
                temp1 -= 1;
            }
            temp2 = mid + 1;
            while (students[temp2].phoneNum == key)
            {
                steps += 1;
                stringNumbers.push_back(students[temp2].stringNum);
                temp2 += 1;
            }
            return;
        }
    }
}

void interpolationSearchOut(Student* students, size_t size, string key)
{
    vector<int> stringNumbers;
    int steps = 0;
    interpolationSearch(students, size, key, stringNumbers, steps);
    size_t stringNumbersSize = stringNumbers.size();

    cout << "Interpolation search" << endl;
    if (stringNumbers.size() == 0)
    {
        cout << "String with search key not found." << endl
             << "Steps: " << steps << endl;
    }
    else
    {
        cout << "Found strings' numbers: " << stringNumbers[stringNumbersSize];
        for (size_t i = 1; i < stringNumbersSize; i++)
        {
            cout << ", " << stringNumbers[i];
        }
        cout << endl << "Steps: " << steps << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string temp;
    vector<string> record;
    vector<string> sub_record;
    //generate_input(50, "C:\\Users\\mrgam\\OneDrive - ДВФУ\\Документы\\repos\\Laba3(fix)\\Laba3(fix)\\In_DVFUStudents_50.txt");
    //generate_input(10, "In_DVFUStudents_10.txt");
    //generate_input(100000, "In_DVFUStudents_worst1.txt");
    //generate_input(5000, "In_DVFUStudents_5000.txt");
    //generate_input(50000, "In_DVFUStudents_50000.txt");
    //generate_input(1000000, "DVFUStudents6.txt");

    ifstream fi1("In_DVFUStudents_10.txt");

    getline(fi1, temp);
    const int n = stoi(temp);
    Student* students = new Student[n];
    for (size_t i = 0; i < n; i++)
    {
        getline(fi1, temp);
        split(temp, ' ', record);
        students[i].fio.f = record[0];
        students[i].fio.i = record[1];
        students[i].fio.o = record[2];
        students[i].direct = record[3];
        students[i].groupNum = record[4];
        split(record[5], '.', sub_record);
        students[i].bdate.dd = stoi(sub_record[0]);
        students[i].bdate.mm = stoi(sub_record[1]);
        students[i].bdate.yy = stoi(sub_record[2]);
        students[i].phoneNum = record[6];
        students[i].stringNum = i + 2;
        sub_record.clear();
        record.clear();
    }

    string key = "89145662040";

    naiveSearchOut(students, n, key);

    cout << endl;

    choiceSort(n, students);
    interpolationSearchOut(students, n, key);

    //Вывод
    //outStudents(fout1, studentsWithFoundPattern, t1, count);


    //Вывод
    //outStudents(fout2, studentsWithFoundPattern, t1, count);
    delete[] students;
    fi1.close();
}