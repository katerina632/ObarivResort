#include <iostream>
#include <list>

using namespace std;


enum ChooseActivity {
	Pool,
	Bar,
	Billiard,
	Massage
};

enum ChooseMassage {
	AntiCellulite,
	Wellness
};

struct Visitor
{
	int age;
	bool isMale;
	bool needForAlcohol;

	//Visitor() {}
	Visitor(int age, bool isMale, bool needForAlcohol) : age(age), isMale(isMale), needForAlcohol(needForAlcohol) {}


};

class UsePool {
public:
	int VisitForOneHour(int age) {
		if (age >= 0 && age <= 3)
			return 0;
		else if (age > 3 && age <= 60)
			return 100;
		else if (age >= 60 && age <= 90)
			return 65;
		else throw  exception("Only visitors aged 1 to 90 can visit the pool!");
	}

	int VisitForTWoeHours(int age) { //zhnyzhka, koly kupujesh 2 god
		if (age >= 0 && age <= 3)
			return 0;
		else if (age > 3 && age <= 60)
			return 100 * 2 * 0.9;
		else if (age >= 60 && age <= 90)
			return 65 * 2 * 0.9;
		else throw  exception("Only visitors aged 1 to 90 can visit the pool!");
	}
};

class BarSystem {
public:
	int VisitBarOneHour(bool needForAlcohol, int age) {
		if (needForAlcohol==true && age >= 21)
			return 500;
		else
			return 200;
	}

	int VisitBarTwoeHours(bool needForAlcohol, int age) { //zhnyzhka, koly kupujesh 2 god
		if (needForAlcohol == true && age >= 21)
			return 500 * 2 * 0.9;
		else
			return 200 * 2 * 0.9;
	}
};

class RestaurantSystem {
public:

	int Breakfast() {
		return 100;
	}
	int Lunch() {
		return 200;
	}
	int Dinner() {
		return 400;
	}
	int СhildrenMenu() {
		return 200;
	}
};

class UseBilliard { //zhinkam zhnyzhka 20%
public:
	int VisitForOneHour(bool male) {
		if (male)
			return 300;
		else
			return 300 * 0.9;
	}

	int VisitForTwoeHours(bool male) {
		if (male)
			return 300*2;
		else
			return 300 *2* 0.9;
	}
};

class MassageService {
public:
	int MassageForAdults(ChooseMassage cm, bool male, int age) {

		switch (cm)
		{
		case AntiCellulite:
			if (!male && age >= 18 && age <= 90)
				return 500;
			else
				throw exception("This type of massage is only for women aged 18 to 90!");
			break;
		case Wellness:
			if (age >= 15 && age <= 90)
				return 400;
			else
				throw exception("This type of massage is only for for visitors aged 18 to 90!");
		default:
			throw exception("This typies of massage is only for adults!");
		}

	}

	int BabyMassage(int age) {
		if (age >= 0 && age <= 15)
			return 300;
		else
			throw  exception("This type of massage is only for children from 0 to 15 years!");
	}
};

class RoomReservation {
public:
	int NumberOfBeds(int numberOfBeds)
	{
		switch (numberOfBeds)
		{
		case 2:
			return 250;
		case 3:
			return 500;
		case 4:
			return 900;
		default:
			throw  exception("Available rooms for 2, 3 and 4 people only!");
		}
	}
};

class ObarivResort {

private:
	UsePool usingPool;
	BarSystem usingBar;
	RestaurantSystem usingRestaurant;
	UseBilliard usingBilliard;
	MassageService orderMassage;
	RoomReservation rentingNumber;

public:

	void OneHourPleasure(ChooseActivity choice, ChooseMassage cm, list <Visitor> visitors) {
		int price = 0;
		int sum = 0;
		switch (choice)
		{
		case Pool:

			for (auto i = visitors.begin(); i != visitors.end(); i++)
			{
				price = usingPool.VisitForOneHour(i->age);
				sum += price;
			}

			cout << "== One Hour Pleasure == for " << visitors.size()
				<< " visitors: \n \t-Visiting the pool -  " 
				<< "\n\t\t\t\tTotal - " << sum << endl;

			break;

		case Bar:

			for (auto i = visitors.begin(); i != visitors.end(); i++)
			{
				price = usingBar.VisitBarOneHour(i->needForAlcohol, i->age);
				sum += price;
			}

			cout << "== One Hour Pleasure == for " << visitors.size()
				<< " visitors: \n \t-Visiting the bar -  "
				<< "\n\t\t\t\tTotal - " << sum << endl;

			break;

		case Billiard:

			for (auto i = visitors.begin(); i != visitors.end(); i++)
			{
				price = usingBilliard.VisitForOneHour(i->isMale);
				sum += price;
			}

			cout << "== One Hour Pleasure == for " << visitors.size()
				<< " visitors: \n \t-Visiting the Billiard -  " 
				<< "\n\t\t\t\tTotal - " << sum << endl;

			break;

		case Massage:
			for (auto i = visitors.begin(); i != visitors.end(); i++)
			{
				if (i->age <= 15) {
					price = orderMassage.BabyMassage(i->age);
					sum += price;
				}
				else {
					price = orderMassage.MassageForAdults(cm, i->isMale, i->age);
					sum += price;
				}
			}

			cout << "== One Hour Pleasure == for " << visitors.size()
				<< " visitors: \n \t-Visiting the Massage-  " 
				<< "\n\t\t\t\tTotal - " << sum << endl;
			break;

		default:
			throw  exception("You can select only between: Pool, Bar, Billiard or Massage!");
		}
	}


	void OneEveningPleasure(list <Visitor> &visitors) {	
		int sum = 0;

		for (auto i = visitors.begin(); i != visitors.end(); i++)
		{
			if (i->age <= 7) {
				int priceRestaurant = usingRestaurant.СhildrenMenu();
				int priceBar = usingBar.VisitBarTwoeHours(i->age, i->needForAlcohol);
				sum += priceRestaurant + priceBar;
			}
			else {			
				int priceRestaurant = usingRestaurant.Dinner();
				int priceBar = usingBar.VisitBarTwoeHours(i->age, i->needForAlcohol);
				int priceBilliard = usingBilliard.VisitForTwoeHours(i->isMale);

				sum += priceRestaurant + priceBar+ priceBilliard;
			}
		}

		cout << "== One Evening Pleasure == for " << visitors.size()
			<< " visitors: \n\t-Visiting the Billiard for 2 hours" <<
			"\n\t-Visiting the Bar for 2 hours"<<
			"\n\t-Dinner in Restaurant" 
			<<"\n\t\t\t\tTotal - "<< sum << endl;
	}

	void OneNightPleasure(list <Visitor> &visitors) {

		int sum = 0;

		if (visitors.size() <= 5) {
			int priceRoom = rentingNumber.NumberOfBeds(visitors.size())*2;
			sum += priceRoom;
		}
		else if (visitors.size() == 1) {
			int priceRoom = rentingNumber.NumberOfBeds(2);
			sum += priceRoom;
		}

		for (auto i = visitors.begin(); i != visitors.end(); i++)
		{
			if (i->age <= 7) {
				int priceRestaurant = usingRestaurant.СhildrenMenu()*2; //snidanok  + vecherja
				int priceBar = usingBar.VisitBarTwoeHours(i->age, i->needForAlcohol)*2;
				sum += priceRestaurant + priceBar;
			}
			else {
				int priceRestaurant = usingRestaurant.Dinner();
				int priceRestaurant2 = usingRestaurant.Breakfast();

				int priceBar = usingBar.VisitBarTwoeHours(i->age, i->needForAlcohol)*2; //4 godyny
				int priceBilliard = usingBilliard.VisitForTwoeHours(i->isMale);

				sum += priceRestaurant + priceBar + priceBilliard+ priceRestaurant2;
			}
		}

		cout << "== One Evening Pleasure == for " << visitors.size()
			<< " visitors: \n\t - Rent room for 1 night\n \t-Visiting the Billiard for 2 hours" <<
			"\n\t-Visiting the Bar for 4 hours" <<
			"\n\t-Dinner and Breakfast in Restaurant"
			<< "\n\t\t\t\tTotal - " << sum << endl;
	}

	void HolidaysPleasure(ChooseMassage cm,list <Visitor>& visitors) {

		int sum = 0;

		if (visitors.size() <= 5) {
			int priceRoom = rentingNumber.NumberOfBeds(visitors.size())*2; //orenda na 2 dni
			sum += priceRoom;
		}
		else if (visitors.size() == 1) {
			int priceRoom = rentingNumber.NumberOfBeds(2)*2;
			sum += priceRoom;
		}

		for (auto i = visitors.begin(); i != visitors.end(); i++)
		{
			if (i->age <= 7) {
				int priceRestaurant = usingRestaurant.СhildrenMenu() * 3*2; //snidanok  + vecherja + obid na 2 dni
				int priceBar = usingBar.VisitBarTwoeHours(i->age, i->needForAlcohol)*3;

				int pricePool = usingPool.VisitForTWoeHours(i->age)*2;
				int priceMassage = orderMassage.BabyMassage(i->age)*2;

				sum += priceRestaurant + priceBar;
			}
			else {
				int priceRestaurant = usingRestaurant.Dinner()*2;
				int priceRestaurant2 = usingRestaurant.Breakfast()*2;
				int priceRestaurant3 = usingRestaurant.Lunch()*2;

				int pricePool = usingPool.VisitForTWoeHours(i->age) * 2;
				int priceMassage = orderMassage.MassageForAdults(cm, i->isMale, i->age)*2;




				int priceBar = usingBar.VisitBarTwoeHours(i->age, i->needForAlcohol) *3; 
				int priceBilliard = usingBilliard.VisitForTwoeHours(i->isMale)*2;

				sum += priceRestaurant+ priceRestaurant3+ priceRestaurant3 + priceBar + priceBilliard;
			}
		}

		cout << "== One Evening Pleasure == for " << visitors.size()
			<< " visitors: \n\t - Rent room for 2 nights\n \t-Visiting the Billiard for 6 hours" <<
			"\n\t-Visiting the Bar for 4 hours" <<
			"\n\t-Visiting the Massage " <<
			"\n\t-Dinner,Breakfast and Lunch  in Restaurant"
			<< "\n\t\t\t\tTotal - " << sum << endl;
	}
};



int main() {

	ObarivResort obarivResort;

	list<Visitor> visitors;
	Visitor mother(35, false, false);
	Visitor son(3, true, false);

	visitors.push_back(mother);
	visitors.push_back(son);


	try
	{
		obarivResort.OneHourPleasure(Massage, AntiCellulite, visitors);
		cout << endl;
		obarivResort.OneEveningPleasure(visitors);
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}



	system("pause");
	return 0;
}

