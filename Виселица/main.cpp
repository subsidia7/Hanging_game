#include "main.h"
#include "Player.h"
#include <fstream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void getIndexQuestion(ifstream &fin, string &question, string &word, int index)
{
	int iter = 0;
	while (getline(fin, question))
	{
		getline(fin, word);
		iter++;
		if (iter == index)
			return;
	}
}

string getAnswer()
{
	string answer;
	bool error = false;
	while (true)
	{
		SetConsoleCursorPosition(hConsole, { 40,1 });
		cout << "Введите букву или слово целиком: ";
		SetConsoleCursorPosition(hConsole, { 40,2 });
		cin >> answer;
		for (unsigned int i = 0; i < answer.length(); i++)
		{
			if (!(answer[i] >= 'а' && answer[i] <= 'я'))
			{
				error = true;
				break;
			}
		}
		SetConsoleCursorPosition(hConsole, { 40,2 });
		for (unsigned int i = 0; i < answer.length(); i++)
		{
			cout << " ";
		}
		if (!error)
			break;
		error = false;
	}
	return answer;
}

void compareAnswerWithRight(Player &player, string &current, string answer, string right, bool &Win, short int y)
{
	bool good = false;
	if (answer.length() == 1)
	{
		for (unsigned short int i = 0; i < right.length(); i++)
		{
			if (answer[0] == right[i])
			{
				good = true;
				current[i] = answer[0];
			}
		}
	}
	if ((answer == right) || (current == right))
	{
		if (current != right)
			current = answer;
		Win = true;
		return;
	}
	if(!good)
	{
		player.decreaseDeathTime();
		player.drawPart();
	}
}

void updateCurrent(string current)
{
	for (unsigned short int i = 0; i < current.length(); i++)
	{
		SetConsoleCursorPosition(hConsole, { i * 2, 0});
		if (current[i] != ' ')
			cout << current[i] << "|";
		else
			cout << "_|";
	}
}

void gameLoop(Player &player, string right)
{
	int currentWordY = 0;
	string current = "", answer;
	for (unsigned int i = 0; i < right.length(); i++)
		current += " ";
	short int x = current.length();
	SetConsoleCursorPosition(hConsole, { x*2,0 });
	cout << " " <<current.length() << " букв";
	bool Win = false;
	updateCurrent(current);
	while (!Win)
	{
		answer = getAnswer();
		compareAnswerWithRight(player, current, answer, right, Win, currentWordY);
		updateCurrent(current);
		if (player.getDeathTime() == 0)
		{
			player.sayCurse();
			break;
		}
	}
	if(Win)
		player.sayThanks();
}

void askForContinue(bool &next)
{
	SetConsoleCursorPosition(hConsole, { 0,2 });
	cout << "Хотите продолжить(да, нет)?" << endl;
	string response;
	while (true)
	{
		getline(cin, response);
		if (response == "да")
		{
			next = true;
			break;
		}
		else if (response == "нет")
		{
			next = false;
			break;
		}
		else
		{
			SetConsoleCursorPosition(hConsole, { 0,3 });
			for (unsigned int i = 0; i < response.length(); i++)
				cout << " ";
			SetConsoleCursorPosition(hConsole, { 0,3 });
		}
	}
}

void printQuestion(COORD questionPos, string question)
{
	SetConsoleCursorPosition(hConsole, questionPos);
	cout << "Вопрос: " << question;
}

void setup(HWND hwnd, HDC hdc)
{
	Sleep(100);
	Rectangle(hdc, 0, 80, 300, 470);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitle(L"Виселица");
	srand((unsigned)time(NULL));
	Player player;
	string word, question;
	ifstream fin("D:\\C++ project\\Нечто игровое\\Виселица\\Виселица\\Questions.txt");
	bool next = true;
	int index;//index of question
	COORD questionPos = {40,0};
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(GetConsoleWindow());
	while (next)
	{
		system("CLS");
		player.toZero();
		setup(hwnd, hdc);
		index = 1 + rand() % 6;
		getIndexQuestion(fin, question, word, index);
		printQuestion(questionPos, question);
		gameLoop(player, word);
		askForContinue(next);
		fin.clear();
		fin.seekg(0);
	}
	system("pause");
	return 0;
}