#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <intrin.h> 
#pragma intrinsic(__rdtsc)
using namespace std;

//Генератор "Студентов ДВФУ"
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
        int phone1 = rand() % 900000 + 100000;
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
            + (month < 10 ? '0' + to_string(month) : to_string(month)) + '.' + to_string(year) + " 8" + to_string(phone1) + to_string(phone2);

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
    long long int phoneNum;
    int stringNum;
};

//Сортировка выбором
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
void linearSearch(Student* students, size_t size, long long int key, vector<int>& stringNumbers, int& steps)
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

void linearSearchOut(Student* students, size_t size, long long int key)
{
    vector<int> stringNumbers;
    int steps = 0;
    linearSearch(students, size, key, stringNumbers, steps);
    size_t stringNumbersSize = stringNumbers.size();
    cout << "Linear search:" << endl;
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

//Интерполяционный поиск
void interpolationSearch(Student* students, size_t size, long long int key, vector<int>& stringNumbers, int& steps)
{
    int low = 0;
    int high = size - 1;
    int mid;
    int temp1, temp2;

    while ((key >= students[low].phoneNum) && (key <= students[high].phoneNum))
    {
        if (students[high].phoneNum == students[low].phoneNum)
        {
            stringNumbers.push_back(students[low].stringNum);
            if (low == high)
            {
                steps += 1;
                return;
            }
            low += 1;
        }
        else
        {
            mid = low + ((key - students[low].phoneNum) * (high - low) / (students[high].phoneNum - students[low].phoneNum));

            if (students[mid].phoneNum < key)
                low = mid + 1;
            else if (students[mid].phoneNum > key)
                high = mid - 1;
            else
            {
                //так как требуется найти каждое вхождение, то:
                //как нашли нужный элемент идем влево от него (от mid) по индексам, пока элементы равны ключу (т.к. это отсортированный массив, это будет работать)
                //и сохраняем номера строк, потом начиная с mid идем вправо по индексам, пока элементы равны ключу, и сохраняем номера строк
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
        steps += 1;
    }
}

void interpolationSearchOut(Student* students, size_t size, long long int key)
{
    vector<int> stringNumbers;
    int steps = 0;
    interpolationSearch(students, size, key, stringNumbers, steps);
    size_t stringNumbersSize = stringNumbers.size();

    cout << "Interpolation search:" << endl;
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

int main()
{
    setlocale(LC_ALL, "Russian");
    string temp;
    vector<string> record;
    vector<string> sub_record;
    //generate_input(15, "In_DVFUStudents_15.txt");

    ifstream fi1("In_DVFUStudents_15_allsame.txt");

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
        students[i].phoneNum = stoll(record[6]);
        students[i].stringNum = i + 2;
        sub_record.clear();
        record.clear();
    }

    long long int key = 89143164055; //искомый ключ

    linearSearchOut(students, n, key); //Линейный поиск
    cout << endl;

    choiceSort(n, students);                   //Сортировка массива и
    interpolationSearchOut(students, n, key);  //последующий интерполяционный поиск

    delete[] students;
    fi1.close();
}