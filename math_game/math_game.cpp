// math_game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <string>

using namespace std;

enum enQuestionsLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4};
enum enOperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};

struct stQuestion {
	int Number1;
	int Number2;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer;
	int PlayerAnswer;
	bool AnswerResult;
};

struct stQuizz {
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfRightAnswers;
	short NumberOfWrongAnswers;
	bool isPass;
};

enQuestionsLevel ReadQuestionsLevel() {
	short QuestionLevel = 0;
	do {
	cout<<"Enter questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ?";
	cin >> QuestionLevel;
	} while(QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOperationType() {
	short OperationType = 0;
	do {
	cout << "Enter operation type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?";
	cin >> OperationType;
	} while(OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

int RandomNumber(int From, int To) {
	int randNumber = rand() % (To - From + 1) + From;
	return randNumber;
}

short ReadPositiveNumber(string message) {
	int number = 0;
	cout <<message<<endl;
	cin >> number;

	return number;
}

int ReadNumber() {
	int number = 0;
	cin >> number;

	return number;
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

short ReadHowManyQuestions() {
	short NumberOfQuestions;

	do {
	cout<<"How many questions do you want to answer ? ";
	cin >> NumberOfQuestions;
	} while(NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

int ReadQuestionAnswer() {
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType) {
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
		break;
	case enOperationType::Sub:
		return Number1 - Number2;
		break;
	case enOperationType::Mul:
		return Number1 * Number2;
		break;
	case enOperationType::Div:
		return Number1 / Number2;
		break;
	default:
		return Number1 + Number2;
	}
}

string GetOpTypeSymbol(enOperationType OpType) {
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
		break;
	case enOperationType::Sub:
		return "-";
		break;
	case enOperationType::Mul:
		return "*";
		break;
	case enOperationType::Div:
		return "/";
		break;
	default:
		return "Mix";
	}
}

void PrintTheQuestion(stQuizz Quizz, short QuestionNumber) {
	cout <<"\n";
	cout<<"Question ["<<QuestionNumber + 1<<"/"<<Quizz.NumberOfQuestions<<"]\n\n";
	cout<<Quizz.QuestionList[QuestionNumber].Number1 <<endl;
	cout<<Quizz.QuestionList[QuestionNumber].Number2 <<" ";
	cout<<GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType)<<endl;
	cout<<"\n_________"<<endl;
}

void SetScreenColor(bool Answer) {
	if(Answer)
		system("color 2F");
	else { 
	 system("color 4F");
	 cout << "\a"; 
	 }
}

void CorrectTheQuestionAnswer(stQuizz &Quizz, short QuestionNumber) {

	if(Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer) {
	 Quizz.QuestionList[QuestionNumber].AnswerResult = false;
	 Quizz.NumberOfWrongAnswers++;

	 cout << "Worng Answer :-( \n"; 
	 cout << "The right answer is: "; 
	 cout <<Quizz.QuestionList[QuestionNumber].CorrectAnswer; 
	 cout << "\n"; 
	}
	else { 
	 Quizz.QuestionList[QuestionNumber].AnswerResult = true; 
	 Quizz.NumberOfRightAnswers++; 
	 cout << "Right Answer :-) \n"; 
	 }
	cout<<endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz &Quizz) {
	for(short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType) {
	stQuestion Question;

	if(QuestionLevel == enQuestionsLevel::Mix) {
		QuestionLevel = (enQuestionsLevel) RandomNumber(1,3);
	}

	if(OpType == enOperationType::MixOp) {
		OpType = (enOperationType) RandomNumber(1,4);
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::Easy:
		Question.Number1 = RandomNumber(1,10);
		Question.Number2 = RandomNumber(1,10);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
		break;

	case enQuestionsLevel::Med:
		Question.Number1 = RandomNumber(10,50);
		Question.Number2 = RandomNumber(10,50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
		break;

	case enQuestionsLevel::Hard:
		Question.Number1 = RandomNumber(50,100);
		Question.Number2 = RandomNumber(50,100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}

	return Question;
}

void GenerateQuizzQuestions(stQuizz&Quizz) {
	for(short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

string GetFinalResultsText(bool Pass) 
{ 
	if (Pass) 
	 return "PASS :-)"; 
	else
	 return "Fail :-("; 
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel) 
{ 
string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" }; 
return arrQuestionLevelText[QuestionLevel - 1]; 
} 

void PrintQuizzResults(stQuizz Quizz) {
	 cout << "\n"; 
	 cout << "______________________________\n\n"; 
	 cout << " Final Resutls is " << GetFinalResultsText(Quizz.isPass); 
	 cout << "\n______________________________\n\n"; 
	 cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	 cout << "Questions Level : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl; 
     cout << "OpType : " << GetOpTypeSymbol(Quizz.OpType) << endl; 
	 cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl; 
	 cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl; 
	 cout << "______________________________\n"; 
}

void PlayMathGame () {
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);

}

void StartGame() {
	char playAgain = 'Y';
	do {
	ResetScreen();
	PlayMathGame();
	
	cout<<endl<<"Do you want to play again ? Y/N ?\n";
	cin >> playAgain;
	} while(playAgain == 'Y' || playAgain == 'y');
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}

