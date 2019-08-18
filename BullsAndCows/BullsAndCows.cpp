// Баинбетова Владлена В.
// Программа BullsAndCows
// Основной модуль
// 17.08.2019.

#include "pch.h"

using namespace std;

/* Функция для генерации неповторяющихся цифр */
vector<int> initialGameNumbers();

/* Функция ввода пользователем цифр */
vector<int> getUserNumbers();

/* Функция для подсчета количества "быков" и "коров" */
vector<int> checkBullsAndCows(vector<int> v1, vector<int> v2);

/* Функция для печати значений вектора на экран*/
void printVectorInt(vector<int> v);

/* Главная функция программы */
int main(int argc, char **argv)
{
	setlocale(0, "Russian");

	vector<int> bullsAndCows; // количество "быков" и "коров"
	vector<int> sequence_computer; // "загаданные" цифры
	vector<int> sequence_user; // введенные пользователем цифры
	vector<int> auxiliary = { 0, 0, 0, 0 }; // вспомогательный вектор для проверки

	sequence_computer = initialGameNumbers(); // инициализация "загаданного" числа

	while (true) {		
		cout << "Введите четыре цифры и нажмите <enter>:" << endl;
		sequence_user = getUserNumbers(); // инициализация числа, введенного пользователем
		if (sequence_user == auxiliary) { // была совершена ошибка
			return 0;
		}
		bullsAndCows = checkBullsAndCows(sequence_computer, sequence_user); // подсчитываем "быков" и "коров"
		if (bullsAndCows[0] == 4) { // найдено 4 "быка"
			break;
		}
		cout << bullsAndCows[0] << " бык., " << bullsAndCows[1] << " кор." << endl;
	}

	cout << "Число угадано:" << endl;
	printVectorInt(sequence_computer);

	return 0;
}

vector<int> initialGameNumbers()
{
	srand((int)time(0));
	vector<int> seq; // переменная для хранения допустимых цифр
	vector<int> ret; // "загаданное" число

	// инициализация последовательности 0...9
	for (int i = 0; i < 10; i++) {
		seq.push_back(i);
	}
	
	// "загадываем" число
	for (int i = 0; i < 4; i++) {
		int pos = rand() % seq.size(); // получаем рандомную позицию элемента
		ret.push_back(seq[pos]); // вставляем элемент из позицию pos в конечный массив
		seq.erase(seq.begin() + pos); // удаляем элемент из последовательности, что бы он снова не появился
	}
	return ret;
}

vector<int> checkBullsAndCows(vector<int> v1, vector<int> v2)
{
	vector<int> ret(2); // в первой ячейке - количество быков, во второй - количество коров
	// производим сравнение v1 и v2
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (v1[i] == v2[j]) {
				if (i == j) {
					ret[0] += 1; // увеличиваем количество быков
				} else {
					ret[1] += 1; // увеличиваем количество коров
				}
				break;
			}
		}
	}
	return ret;
}

void printVectorInt(vector<int> v)
{
	vector <int>::iterator cur;
	// вывод всех символов
	for (cur = v.begin(); cur < v.end(); cur++) {
		cout << *cur << " ";
	}
}

vector<int> getUserNumbers() {
	char txt[100]; // введенные символы
	vector<int> ret; // возвращаемый результат
	int flag = 0;

	// считываем введенные символы в буфер 
	cin.getline(txt, 100);

	size_t len = strlen(txt); // длина введенной строки

	while (true) // бесконечный цикл
	{
		if (len > 4) {
			cout << "Некорректный запрос: введено больше 4 символов, пожалуйста, почитайте правила игры еще раз." << endl;
			_getch();
			break;
		} else if (len < 4) {
			cout << "Некорректный запрос: введено меньше 4 символов, пожалуйста, почитайте правила игры еще раз." << endl;
			_getch(); 
			break;
		} else {
			for (size_t i = 0; i < len; i++) {
				for (size_t j = len; j > 0; j--) {
					if (txt[i] == txt[j] && i !=j) {
						flag++; // в числе есть повторяющиеся цифры
					}
				}
				if (txt[i] < '0' || txt[i] > '9') {
					cout << "Некорректный запрос: введено не 4х-значное число, пожалуйста, почитайте правила игры еще раз." << endl;
					_getch(); 
					ret = { 0, 0, 0, 0 }; // инициализация вектора, для возврата корректного значения
					return ret;
				} else {
					if (flag > 0) {
						cout << "Некорректный запрос: введено число с повторяющимися цифрами, пожалуйста, почитайте правила игры еще раз." << endl;
						_getch(); 
						ret = { 0, 0, 0, 0 }; // инициализация вектора, для возврата корректного значения
						return ret;
					}
					// в ret вносим число по отдельным цифрам
					char ch = txt[i];
					int N = atoi(&ch);
					ret.push_back(N);
				}
				// проверка: цифры в числе не должны повторяться
				if (i == 3) { // если все 4 цифры были корректны					
					return ret;
				}
			}
		}
	}
	ret = { 0, 0, 0, 0 }; // инициализация вектора, для возврата корректного значения
	return ret;
}