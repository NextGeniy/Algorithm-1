#include <iostream>
#include <string>
#include "windows.h" 

using namespace std;

class LinckedList;
class Node {
    int Data;
public:
    friend LinckedList;
    Node* Prev, * Next;
    Node(int Data) {               
        this->Data = Data;
        this->Prev = this->Next = nullptr;

    }
};
class LinckedList
{
public:
    Node* Head, * Tail;
    LinckedList() {
        Head = Tail = nullptr;
    }
    ~LinckedList() {
        while (Head != nullptr)
            DeleteFirst();
    }
    Node* CreateListRandom() {  
        Node* Ptr = 0;
        int Lenght = 10;
        for (int i = 1; i <= Lenght; ++i) {
            int Data = rand() % 100;
            Node* Ptr = new Node(Data);
            Ptr->Next = Head;
            if (Head != nullptr)
                Head->Prev = Ptr;
            if (Tail == nullptr)
                Tail = Ptr;
            Head = Ptr;

        }
        return Ptr;
    }
    Node* GetIndex(int Index) {
        Node* Ptr = Head;
        int Temp = 0;
        while (Temp != Index) {
            if (Ptr == nullptr)
                return nullptr;
            Ptr = Ptr->Next;
            Temp++;
        }
        return Ptr;
    }
    int GetIndexData(int Index) {
        Node* Ptr = Head;
        int Temp = 0;
        while (Temp != Index) {
            if (Ptr == nullptr)
                return NULL;
            Ptr = Ptr->Next;
            Temp++;
        }
        return Ptr->Data;
    }
    Node* AddFirst(int Data) {
        Node* Ptr = new Node(Data);
        Ptr->Prev = Tail;
        if (Tail != nullptr)
            Tail->Next = Ptr;
        if (Head == nullptr)
            Head = Ptr;
        Tail = Ptr;
        return Ptr;
    }
    Node* AddLast(int Data) {
        Node* Ptr = new Node(Data);
        Ptr->Next = Head;
        if (Head != nullptr)
            Head->Prev = Ptr;
        if (Tail == nullptr)
            Tail = Ptr;
        Head = Ptr;
        return Ptr;
    }
    Node* Insertion(int Index, int Data) {
        Node* Right = GetIndex(Index);
        if (Right == nullptr) {
            return AddFirst(Data);
        }
        Node* Left = Right->Prev;
        if (Left == nullptr) {
            return AddLast(Data);
        }
        Node* Ptr = new Node(Data);
        Ptr->Prev = Left;
        Ptr->Next = Right;
        Left->Next = Ptr;
        Right->Prev = Ptr;
        return Ptr;
    }
    void DeleteFirst() {
        if (Head == nullptr)
            return;
        Node* Ptr = Head->Next;
        if (Ptr != nullptr)
            Ptr->Prev = nullptr;
        else
            Tail = nullptr;
        delete Head;
        Head = Ptr;
    }
    void DeleteLast() {
        if (Tail == nullptr)
            return;
        Node* Ptr = Tail->Prev;
        if (Ptr != nullptr)
            Ptr->Next = nullptr;
        else
            Head = nullptr;
        delete Tail;
        Tail = Ptr;
    }
    void Delete(int Index) {
        Node* Ptr = GetIndex(Index);
        if (Ptr == nullptr)
            return;
        if (Ptr->Prev == nullptr) {
            DeleteFirst();
            return;
        }
        if (Ptr->Next == nullptr) {
            DeleteLast();
            return;
        }
        Node* Right = Ptr->Next;
        Node* Left = Ptr->Prev;
        Left->Next = Right;
        Right->Prev = Left;
        delete Ptr;
    }
    int NumObj() {
        Node* Ptr = Head;
        int Temp = 0;
        while (Ptr != nullptr) {
            if (Ptr == nullptr)
                return NULL;
            Ptr = Ptr->Next;
            Temp++;
        }
        return Temp;
    }
    int GetDataIndex(int Data) {
        Node* Ptr = Head;
        for (int Temp = 0; Temp <= NumObj(); ++Temp) {
            if (Ptr->Data == Data)
                return Temp;
            Ptr = Ptr->Next;
        }
        return (-1);
    }
    void Output() {
        cout << "Двусвязный список:\n  ";
        Node* Ptr = Head;
        Node* Ptr2 = Head;
        int temp = 0;
        while (Ptr != nullptr) {
            cout << Ptr->Data << " ";
            Ptr = Ptr->Next;
           
        }
        cout << "\n  ";
        while (Ptr2 != nullptr) {
            cout << temp << "  ";
            Ptr2 = Ptr2->Next;
            temp++;
        }
        cout << "\n\n";
    }
};
string operations = "+-*/^";
class Stack;
class list {
    string symbol;
public:
    friend Stack;
    list* next;
    list() {
        this->next = nullptr;
    }
};

class Stack {
public:
    list* tail;
    Stack() : tail(nullptr) {}  //конструктор
    bool isEmpty() {
        if (tail == nullptr) return 1;
        return 0;
    }
    void output() {
        cout << "Операторы: ";
        list* curr = tail;
        if (!curr) {
            cout << "Пусто";
        }
        while (curr) {
            cout << curr->symbol << " ";
            curr = curr->next;
        }
        cout << "\n";
    }
    string pop(bool print = 1) {
        if (tail == nullptr) return "конец";
        if (print) cout << tail->symbol << " ";
        string answer = tail->symbol;
        list* p = new list;
        p = tail;
        tail = tail->next;
        p->next = nullptr;
        delete p;
        return answer;
    }
    void push(string sym) {
        list* p = new list;
        p->symbol = sym;
        p->next = tail;
        tail = p;
    }
    int prior(char c) {
        switch (c) {
        case '(': return 1;
        case '+': case '-': return 2;
        case '*': case '/': return 3;
        case '^': return 4;
        default: return 0;
        }
    }
    void revPolishNotation(string& data, bool print = 1)
    {
        Stack stack;
        string note;
        string sym;
        for (int i = 0; i <= data.length(); ++i) {
            if (data[i] == ' ') data.erase(i, 1);
        }
        for (int i = 0; i < data.length(); i++) {
            sym = data[i];
            if (sym >= "0" && sym <= "9" || sym == ".") {
                note += sym;
                if (sym == "." || data[i + 1] == '.' || data[i + 1] >= '0' && data[i + 1] <= '9') continue;
                note += " ";
                if (print) {
                    cout << "\nЧисла: " << note << "\n";
                    stack.output();
                }
            }
            if (sym == "c" || sym == "o"|| sym == "s"|| sym == "i"|| sym == "n") {
                note += sym;
            }
            if (sym == "(") {
                stack.push(sym);
                if (print) {
                    cout << "\nЧисла: " << note << "\n";
                    stack.output();
                }
                continue;
            }
            if (sym == ")") {
                while (stack.tail->symbol != "(") {
                    note += stack.pop(0);
                    note += " ";
                }
                stack.pop(0);
                if (print) {
                    cout << "\nЧисла: " << note << "\n";
                    stack.output();
                }
                continue;
            }
            if (operations.find(sym) != -1) {

                if (stack.isEmpty() || prior(stack.tail->symbol[0] < prior(sym[0]))) {
                    stack.push(sym);
                    if (print) {
                        cout << "\nЧисла: " << note << "\n";
                        stack.output();
                    }
                }
                else {
                    while (!stack.isEmpty() && prior(stack.tail->symbol[0]) >= prior(sym[0])) {
                        note += stack.pop(0);
                        note += " ";
                    }
                    stack.push(sym);
                    if (print) {
                        cout << "\nЧисла: " << note << "\n";
                        stack.output();

                    }
                }
            }
        }
        if (print) {
            cout << "\nЧисла: " << note << "\n";
            stack.output();

        }
        while (!stack.isEmpty()) {
            note += stack.pop(0);
            note += " ";
        };
        if (print) {
            cout << "\nСтек: ";
        }
        cout << note << "\n";
        data = note;
    }
};
class DynamicArr{
    int* Arr;
public:
    int size;
    DynamicArr() {
        size = 5;
        Arr = new int[size];
        for (int i = 0; i < size; i++) {
            Arr[i] = rand() % 100;
        }
    }
    ~DynamicArr() {
        delete[] Arr; Arr = nullptr;
    }
    void AddElem(int index,int val) {
        int* temp = new int[size + 1];
        memcpy((void*)temp, (const void*)Arr, sizeof(int) * size);

        for (int i = size - 1; i >= index; i--) {
            temp[i + 1] = temp[i];
        }
        temp[index] = val;

        size++;

        if (temp != nullptr)
        {
            Arr = new int[size];
            memcpy((void*)&Arr[0], (const void*)temp, sizeof(int) * size);
        }

        delete[] temp; temp = nullptr;
    
    }
    void ShowArr() {
        cout << "Динамический массив: \n";
        for (int i = 0; i < size; i++) {
            cout << Arr[i] << " ";
        }
        cout << "\n";
        for (int i = 0; i < size; i++) {
            cout << i << "  ";
        }
        cout << "\n\n";
    }
    void DeleteElem(int index) {
        int* temp = new int[size-1];
        for (int i = 0; i < size; i++) {
            if (i != size) {
                if (i < index) {
                    temp[i] = Arr[i];
                }
                else if (i >= index) {
                    temp[i] = Arr[i + 1];
                }
                else {

                }
            }

        }
        size--;
        Arr = new int[size];
        for (int i = 0; i < size; i++) {
            Arr[i] = temp[i];
        }
        
    }
    void GetIndexArr(int data) {
        for (int i = 0; i < size; i++) {
            if (Arr[i] == data) {
                cout << i << " ";
            }
        }
        cout << "\n";
    }
    void GetDataArr(int index) {
        for (int i = 0; i < size; i++) {
            if (i == index) {
                cout << Arr[i] << " ";
            }
        }
        cout << "\n";
    }
};
int inputInt()
{
    int N;
    int m = 1, M = 5;
    for (;;) {
        if ((cin >> N).good() && (m <= N) && (N <= M)) return N;
        if (cin.fail()) {
            cin.clear();
            cout << "Неверный ввод, повторите.\n";
        }
        else {
            cout << "Число вне допустимого диапазона значений. Повторите ввод.\n";
        }
        cin.ignore(100, '\n');
    }
}
int main()
{
    setlocale(0, "Rus");
    int i = 1;
    while (i!= 4) {
        system("CLS");
            cout << "Меню \n";
            cout << "1. Двусвзязный список\n";
            cout << "2. Стэк\n";
            cout << "3. Динамический массив\n";
            cout << "4. Выход\n";
            i = inputInt();
        switch (i) {
        case 1: {
            system("CLS");
            int q = 1;
            LinckedList MainList;
            MainList.CreateListRandom();
            while(q!=5){
                system("CLS");
                MainList.Output();
                cout << "1.Вставка в список \n";
                cout << "2.Получение значения по индексу \n";
                cout << "3.Получение индекса по значению \n";
                cout << "4.Удаление элемента \n";
                cout << "5.Выход \n";
                q = inputInt();
                switch (q) {
                case 1: {
                    int index, data;
                    cout << "Введите индекс (c 0) \n";
                    cin >> index;
                    cout << "Введите значение \n";
                    cin >> data;
                    MainList.Insertion(index, data);
                    break;
                }
                case 2: {
                    int index;
                    cout << "Введите индекс (c 0)\n";
                    cin >> index;
                    cout << "Значение под заданным индексом\n";
                    cout << MainList.GetIndexData(index)<<"\n";
                    system("pause");
                    break;
                }
                case 3: {
                    int data;
                    cout << "Введите значение элемента \n";
                    cin >> data;
                    cout << "Индекс значения в списке \n";
                    cout << MainList.GetDataIndex(data) << "\n";
                    system("pause");
                    break;
                }
                case 4: {
                    int index;
                    cout << "Введите индекс \n";
                    cin >> index;
                    cout << "Список с удаленным элементом\n";
                    MainList.Delete(index);
                    break;
                }
                case 5: {
                    break;
                }
                }
            }
            break;
        }
        case 2: {
            system("CLS");
            Stack MainStack;
            int w = 1;
            while (w != 2) {
                system("CLS");
                cout << "Стэк \n\n";
                cout << "1.Алгоритм \n";
                cout << "2.Выход \n";
                w = inputInt();
                switch (w)
                {
                case 1: {
                    string data= "";
                    data.erase(0, data.length());
                    cin.ignore();
                    cout << "Введите выражение: ";
                    getline(cin, data);
                    MainStack.revPolishNotation(data);
                    system("pause");
                    break;
                }
                case 2: {
                    break;
                }  
                }
            }
            break;
        }
        case 3: {
            system("CLS");
            int e = 1;
            DynamicArr MainArr;
            while (e != 5) {
                system("CLS");
                MainArr.ShowArr();
                cout << "1.Вставка в массив \n";
                cout << "2.Получение значения по индексу \n";
                cout << "3.Получение индекса по значению \n";
                cout << "4.Удаление элемента \n";
                cout << "5.Выход \n";
                e = inputInt();
                switch (e) {
                case 1: {
                    int index, data;
                    cout << "Введите индекс (c 0)\n";
                    cin >> index;
                    cout << "Введите значение \n";
                    cin >> data;
                    MainArr.AddElem(index, data);
                    MainArr.ShowArr();
                    break;
                }
                case 2: {
                    int index;
                    cout << "Введите индекс (c 0)\n";
                    cin >> index;
                    cout << "Значение под заданным индексом\n";
                    MainArr.GetDataArr(index);
                    system("pause");
                    break;
                }
                case 3: {
                    int data;
                    cout << "Введите значение элемента \n";
                    cin >> data;
                    cout << "Индекс значения в списке \n";
                    MainArr.GetIndexArr(data);
                    system("pause");
                    break;
                }
                case 4: {
                    int index;
                    cout << "Введите индекс (c 0)\n";
                    cin >> index;
                    cout << "Список с удаленным элементом\n";
                    MainArr.DeleteElem(index);
                    break;
                }
                case 5: {
                    break;
                }
                }
            }
            break;
        }
        case 4: {
            return 0;
        }
        }
    }
    
}
