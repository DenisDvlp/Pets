/*1. Составить алгоритм поиска заданного слова в тексте.
Слово и текст являются массивами символов заданной длины. Если заданное слово присутствует в тексте,
то алгоритм должен возвращать номер позиции совпадения, в противном случае - значение -1.
2. Разработать программу перевода римских чисел в десятичную систему счисления.
3. Ввести N слов и определить, можно ли построить из них цепочку,
в которой каждое последующее число начинается с той же буквы на которую оканчивается предыдущее.
Вывести возможную цепочку, являющуюся решением задачи. Если цепочки нет, вывести ответ "нет".*/

#include <iostream>
#include <cstring>

using namespace std;

//возварт позиции вхождения слова в текст
int getWordPositionInText(char *word, char *text);

//перевода римских чисел в десятичную систему
int convertNumberFromRomanToArabic(char *romansNumbers);

//перевода римской цифры в десятичную систему
int convertDigitFromRomanToArabic(char romanDigit);

//получение слов из текста
char** getWords(char *text);

//получение количества слов в тексте
int getWordsCount(char *text);

//получение цепочки слов
char* getWordsChain(char *text);

//получение цепочки слов (вспомогательная, рекурсивная)
char* getWordsChainBeginningFromLetter(char **words, int count, char letter = '\0');

//получение копии списка слов
char** getStringListCopy(char **list, int count);

//удаление слова из списка слов по индексу
void removeElementFromStringListByIndex(char ***list, int count, int index);

void main() {

	int size = 255;
	char *text = new char[size];
	char *word = new char[size];

	gets_s(text, size);
	cin >> word;
	cin.get();
	cout << "Position of the word \"" << word << "\": " << getWordPositionInText(word, text) << endl;

	gets_s(text, size);
	cout << convertNumberFromRomanToArabic(text) <<endl;

	gets_s(text, size);
	char *wordsChain = getWordsChain(text);
	if(!wordsChain)
		cout << "NO" << endl;
	else
		cout << wordsChain << endl;

	delete[] text;
	delete[] wordsChain;
}


int convertDigitFromRomanToArabic(char romanDigit) {
	switch (romanDigit) {
		case 'i':
		case 'I': return 1;
		case 'v':
		case 'V': return 5;
		case 'x':
		case 'X': return 10;
		case 'l':
		case 'L': return 50;
		case 'c':
		case 'C': return 100;
		case 'd':
		case 'D': return 500;
		case 'm':
		case 'M': return 1000;
		default:  return 0;
	}
}

int convertNumberFromRomanToArabic(char *romansNumbers) {

	int textLength = strlen(romansNumbers);
	int sum = 0, number = 0, prevNumber = 0;

	for (int i = textLength - 1; i >= 0; i--) {
		number = convertDigitFromRomanToArabic(romansNumbers[i]);
		sum += (prevNumber > number) ? -number : number;
		prevNumber = number;
	}
	return sum;
}

int getWordPositionInText(char *word, char *text) {

	char *context = NULL;
	char *nextWord = NULL;
	const char delims[] = " ,\t\n";

	//разбираем текст по одному слову
	nextWord = strtok_s(text, delims, &context);
	while (nextWord != NULL) {
		//если нашли слово
		if (!strcmp(nextWord, word))
			//возвращаем его позицию
			return int(context - text - strlen(nextWord) - 1);
		nextWord = strtok_s(NULL, delims, &context);
	}
	return -1;
}

char** getWords(char *text) {

	int length = strlen(text) + 1;
	char *textCopy = new char[length];
	strcpy_s(textCopy, length, text);

	int wordsCount = getWordsCount(text);
	char **words = new char*[wordsCount];

	char *context = NULL;
	char delims[] = " ,\t\n";
	char *nextWord = strtok_s(text, delims, &context);
	int index = 0;
	while (nextWord) {
		int len = strlen(nextWord) + 1;
		words[index] = new char[len];
		strcpy_s(words[index++], len, nextWord);
		nextWord = strtok_s(NULL, delims, &context);
	}

	strcpy_s(text, length, textCopy);
	delete[] textCopy;

	return words;
}


int getWordsCount(char *text) {

	int length = strlen(text) + 1;
	char *textCopy = new char[length];
	strcpy_s(textCopy, length, text);

	char *context = NULL;
	char delims[] = " ,\t\n";
	int count = 0;
	char *nextWord = strtok_s(text, delims, &context);
	while (nextWord) {
		count++;
		nextWord = strtok_s(NULL, delims, &context);
	}

	strcpy_s(text, length, textCopy);
	delete[] textCopy;

	return count;
}

char* getWordsChain(char *text) {

	int count = getWordsCount(text);
	char **words = getWords(text);
	char *chain = getWordsChainBeginningFromLetter(words, count);
	delete[] words;
	return chain;
}

char* getWordsChainBeginningFromLetter(char **words, int count, char letter) {

	//если в списке одно слово и оно начинается на заданную букву
	if (letter && count == 1 && words[0][0] == letter)
		//возвращаем это слово
		return words[0];

	//проход по словам
	for (int i = 0; i < count; i++) {

		//слово начинается на заданную букву
		if (!letter || words[i][0] == letter) {

			//делаем копию массива слов
			char **restWords = getStringListCopy(words, count);
			//удаляем из копии текущее слово
			removeElementFromStringListByIndex(&restWords, count, i);
			//получаем цепочку слов из оставшихся
			int wordLength = strlen(words[i]);
			char *chain = getWordsChainBeginningFromLetter(restWords, count - 1, words[i][wordLength - 1]);
			delete[] restWords;
			//если цепочка не найдена
			if (!chain)
				//если проверено последнее слово
				if (i + 1 == count)
					return NULL;
				else
					continue;
			//составляем новую цепочку слов
			int chainLength = strlen(chain);
			int newChainLength = wordLength + chainLength + 2;
			char *newChain = new char[newChainLength];
			//присоединяем найденую цепочку к текущему слову
			strcpy_s(newChain, newChainLength, words[i]);
			strcat_s(newChain, newChainLength, " ");
			strcat_s(newChain, newChainLength, chain);
			//удаляем найденую цепочку
			delete[] chain;
			return newChain;
		}		
	}
	return NULL;
}

char** getStringListCopy(char **list, int count) {
	char **newList = new char*[count];
	for (int i = 0; i < count; i++)
		newList[i] = list[i];
	return newList;
}

void removeElementFromStringListByIndex(char ***list, int count, int index) {
	char **newList = new char*[count - 1];
	for (int i = 0, j = 0; i < count; i++)
		if(i != index)
			newList[j++] = (*list)[i];
	*list = newList;
}
