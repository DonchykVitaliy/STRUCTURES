#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

struct Credit
{
	double money;
	double procent;
	int term;
};


// обрахунок формули для кількості виплати коштів на місяць
double MonthMoney(struct Credit &credit)
{
	return ( (credit.money * (credit.procent/1200) ) / (1-pow(1 + (credit.procent / 1200) , -credit.term ) ) );
}

void GenerateStat(const Credit& credit, double monthMoney) {
	double balance = credit.money;
	double monthRate = credit.procent / 12 / 100;

	// вивід стовпців
	cout << "\nГрафік платежів:\n";
	cout << setw(0) << "Місяць"
		<< setw(15) << "Платіж"
		<< setw(13) << "Проценти"
		<< setw(20) << "Основний борг"
		<< setw(20) << "Залишок боргу" << endl;

	for (int month = 1; month <= credit.term; ++month) {
		double interestPayment = balance * monthRate;
		double principalPayment = monthMoney - interestPayment;
		balance -= principalPayment;

		// вивід даних
		cout << setw(0) << month
			<< setw(20) << fixed << setprecision(2) << monthMoney
			<< setw(12) << interestPayment
			<< setw(18) << principalPayment
			<< setw(20) << max(0.0, balance) << endl;
	}
}

int main()
{
	setlocale(LC_CTYPE, "ukr");
	SetConsoleOutputCP(CP_UTF8);

	Credit credit;

	cout << "Введіть суму для кредиту (грн): ";
	cin >> credit.money;
	cout << "Введіть процентну ставку (%): ";
	cin >> credit.procent;
	cout << "Введіть термін виплати (місяці): ";
	cin >> credit.term;

	double monthMoney = MonthMoney(credit);
	cout << "\nЩомісячний платіж: " << monthMoney << " грн\n";

	char an;
	do
	{
		cout << "Ви хочете побачити розрахунок графіку виплати кредиту? Y - так; N - ні." << endl;
		cin >> an;

		if (an == 'Y')
		{
			GenerateStat(credit, monthMoney);
			break;
		}
		else if (an != 'N')
		{
			cout << "Ви ввели не правильну відповідь, спробуйте ще раз" << endl;
		}

	} while (an != 'N');
	
	cout << "Програма завершила свою роботу..." << endl;

	system("pause");
}
