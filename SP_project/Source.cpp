#include<iostream>
#include<string>


using namespace std;


int const  road_max_speed = 200;
int const  max_num_cars = 3;
int const  max_num_drivers = 10;
int const  max_num_fines = 10;

struct date
{
	int day;
	int month;
	int year;
};

struct fine_s
{
	float value = 0;
	string street;
	date date;
	string statue;

};
struct car_s
{

	int plate_num;
	string model;
	int NumOfFine = 0;
	fine_s fine[max_num_fines];
	float total_fine = 0;
	int product_year;
	float speed;

};

struct driver_s
{
	int license_num;
	string name;
	date birth_day;
	int NumOfCars;
	car_s own_car[max_num_cars];
};

//fuction decleration

void input_driver_information(driver_s d[]);
void search_name(driver_s d[]);
void search_plate(driver_s d[]);
void pay_fines(driver_s d[]);
void unpaid_fines(driver_s d[]);
void traffic_man(driver_s d[]);

int  main()
{
	int optionOfMenu;
	char answer = 'y';
	driver_s  driver[max_num_drivers];

	do
	{
		//menu

		cout << "choose one option:\n";
		cout << "1- Add Driver\n"
			<< "2- Un Paid Fines\n"
			<< "3- Pay the Fine\n"
			<< "4- Search by Name\n"
			<< "5- Search by Plate Number\n"
			<< "6- traffic man\n";

		cin >> optionOfMenu;

		switch (optionOfMenu)
		{
		case 1:
		{
			input_driver_information(driver);

			break;
		}
		case 2:
		{
			unpaid_fines(driver);
			break;
		}
		case 3:
		{
			pay_fines(driver);
			break;
		}
		case 4:
		{
			search_name(driver);

			break;
		}
		case 5:
		{
			search_plate(driver);

			break;
		}
		case 6:
		{

			traffic_man(driver);

			break;
		}
		default:
		{
			cout << "In Valid Option \n";
		}

		}

		cout << "Do you want to go to the menu again? (y/n)\n";
		cin >> answer;

	} while (answer == 'y' || answer == 'Y');

	return 0;
}
//end of main


//allow the user to add a driner info

void input_driver_information(driver_s user[])
{
	int num_drivers;

	cout << "Enter the number of the users you want to Add\n"
		<< "You are allowed to enter 10 drivers only\n";

	cin >> num_drivers;
	if (num_drivers > max_num_drivers || num_drivers <= 0)
	{
		cout << "THIS NUMBER IS NOT ALLOWED!, SORRY\n";
		input_driver_information(user);
	}

	else
	{


		for (int i = 0; i < num_drivers; i++)
		{
			cout << "Enter the data of the #" << i + 1 << "driver\n";

			cout << "Enter the license number\n";
			cin >> user[i].license_num;

			cout << "Enter the driver name\n";
			cin.ignore();
			getline(cin, user[i].name);

			cout << "Enter driver's birth day, example: dd mm yyyy\n";

			cin >> user[i].birth_day.day;
			cin >> user[i].birth_day.month;
			cin >> user[i].birth_day.year;

			cout << "Enter the number of the cars the driver own not more than 3 cars\n";
			cin >> user[i].NumOfCars;

			while (user[i].NumOfCars > max_num_cars || user[i].NumOfCars <= 0)
			{
				cout << "IN VALID NUMBER\n"
					<< "Enter the number of the cars the driver own not more than 3 cars\n";

				cin >> user[i].NumOfCars;

			}



			for (int ii = 0; ii < user[i].NumOfCars; ii++)
			{
				cout << "Enter the data of #" << ii + 1 << "car\n";


				cout << "Enter the car plate number\n";
				cin >> user[i].own_car[ii].plate_num;

				cout << "Enter the car modle\n";
				cin.ignore();
				getline(cin, user[i].own_car[ii].model);

				cout << "Enter the car's product year\n";
				cin >> user[i].own_car[ii].product_year;

			}

		}
	}
}

//Add a fine to the driver when he exceed the limited speed

void  traffic_man(driver_s d[])
{

	int plateOfCar;

	bool found = false;

	cout << "Enter the plate number\n";
	cin >> plateOfCar;

	for (int i = 0; i < max_num_drivers; i++)
	{
		for (int ii = 0; ii < d[i].NumOfCars; ii++)
		{

			if (d[i].own_car[ii].plate_num == plateOfCar)
			{
				found = true;

				cout << "Enter the speed of the car\n";
				cin >> d[i].own_car[ii].speed;

				if (d[i].own_car[ii].speed > road_max_speed)
				{

					d[i].own_car[ii].fine[d[i].own_car[ii].NumOfFine].value = 2 * (d[i].own_car[ii].speed - road_max_speed);

					cout << "Enter the name of the street\n";
					cin.ignore();
					getline(cin, d[i].own_car[ii].fine[d[i].own_car[ii].NumOfFine].street);

					cout << "Enter the date\n";
					cin >> d[i].own_car[ii].fine[d[i].own_car[ii].NumOfFine].date.day
						>> d[i].own_car[ii].fine[d[i].own_car[ii].NumOfFine].date.month
						>> d[i].own_car[ii].fine[d[i].own_car[ii].NumOfFine].date.year;

					d[i].own_car[ii].fine[d[i].own_car[ii].NumOfFine].statue = "Not paid";
					d[i].own_car[ii].total_fine += d[i].own_car[ii].fine[d[i].own_car[ii].NumOfFine].value;

					d[i].own_car[ii].NumOfFine++;

				}

				else
				{
					cout << "This is a suitable speed,NO FINE\n";
				}

			}


		}
		if (found)
		{
			break;
		}
	}
	if (found == false)
	{

		cout << "This car was not added\n";

	}
}

//search for the driver's data with his plate number

void search_plate(driver_s d[])
{
	int plateOfCar;

	bool found = false;


	cout << "Enter the car plate number\n";
	cin >> plateOfCar;

	for (int i = 0; i < max_num_drivers; i++)
	{
		for (int ii = 0; ii < d[i].NumOfCars; ii++)
		{

			if (d[i].own_car[ii].plate_num == plateOfCar)

			{
				found = true;

				cout << "The name of the driver is "
					<< d[i].name

					<< "\nThe license number of the driver is "
					<< d[i].license_num

					<< "\nThe model of the car is "
					<< d[i].own_car[ii].model

					<< "\nThe number of the fines on the car is "
					<< d[i].own_car[ii].NumOfFine << '\n';


				if (d[i].own_car[ii].NumOfFine == 0)
				{
					cout << "The fines on this car is : Paid\n";

				}

				else
				{


					for (int iii = 0; iii < d[i].own_car[ii].NumOfFine; iii++)
					{
						cout << "The #" << iii + 1 << "fine is\n";


						cout << "The value of fines on the car is :"
							<< d[i].own_car[ii].fine[iii].value << '\n'

							<< "The street in which the fine was happen is :"
							<< d[i].own_car[ii].fine[iii].street << '\n'

							<< "The date of the fine is :"
							<< d[i].own_car[ii].fine[iii].date.day << '/'
							<< d[i].own_car[ii].fine[iii].date.month << '/'
							<< d[i].own_car[ii].fine[iii].date.year << '\n'

							<< "The state of the fine is :"
							<< d[i].own_car[ii].fine[iii].statue << '\n';



					}
				}

				cout << "The total amount of fines on the car is :"
					<< d[i].own_car[ii].total_fine << '\n';

				break;

			}

		}

	}
	if (found == false)
	{
		cout << "This car was not added\n";
	}

}

//search for the driver's data with his name

void search_name(driver_s d[])
{
	string driver_name;
	bool found = false;

	cout << "Enter the driver name\n";
	cin.ignore();
	getline(cin, driver_name);


	for (int i = 0; i < max_num_drivers; i++)
	{

		if (d[i].name == driver_name)
		{
			found = true;
			cout << "The name of the driver is :"
				<< d[i].name << '\n'

				<< "The date of birth of the driver is :"
				<< d[i].birth_day.day << '/' << d[i].birth_day.month << '/' << d[i].birth_day.year << '\n'

				<< "The license number of the driver is :"
				<< d[i].license_num << '\n'

				<< "The number of the cars the driver own is :"
				<< d[i].NumOfCars << '\n';

			for (int ii = 0; ii < d[i].NumOfCars; ii++)
			{
				cout << "This is tha data of the #" << ii + 1 << "car\n"

					<< "The plate number is :"
					<< d[i].own_car[ii].plate_num << '\n'

					<< "The model of the car is :"
					<< d[i].own_car[ii].model << '\n'

					<< "The number of the fines on the car is :"
					<< d[i].own_car[ii].NumOfFine << '\n';

				if (d[i].own_car[ii].NumOfFine == 0)
				{
					cout << "The fines on this car is : Paid\n";

				}

				else
				{


					for (int iii = 0; iii < d[i].own_car[ii].NumOfFine; iii++)
					{
						cout << "The #" << iii + 1 << "fine is\n";

						cout << "The value of fines on the car is :"
							<< d[i].own_car[ii].fine[iii].value << '\n'

							<< "The street in which the fine was happen is :"
							<< d[i].own_car[ii].fine[iii].street << '\n'

							<< "The date of the fine is :"
							<< d[i].own_car[ii].fine[iii].date.day << '/'
							<< d[i].own_car[ii].fine[iii].date.month << '/'
							<< d[i].own_car[ii].fine[iii].date.year << '\n'

							<< "The state of the fine is :"
							<< d[i].own_car[ii].fine[iii].statue << '\n';



					}
				}

				cout << "The total amount of fines on the car is  :"
					<< d[i].own_car[ii].total_fine << '\n';

			}


		}

		if (found)
		{
			break;
		}

	}

	if (found == false)
	{
		cout << "This user was not added\n";

	}
}




//allow the driver to know the fines on the car

void unpaid_fines(driver_s d[])
{

	int plateOfCar;
	bool found = false;

	cout << "Enter the plate number of the car\n";
	cin >> plateOfCar;

	for (int i = 0; i < max_num_drivers; i++)
	{
		for (int ii = 0; ii < d[i].NumOfCars; ii++)
		{

			if (d[i].own_car[ii].plate_num == plateOfCar)
			{
				found = true;

				cout << "The number of fines on this car is :"
					<< d[i].own_car[ii].NumOfFine << '\n'

					<< "The car model is :"
					<< d[i].own_car[ii].model << '\n';

				for (int iii = 0; iii < d[i].own_car[ii].NumOfFine; iii++)
				{


					cout << "The #" << iii + 1 << "fine is\n"

						<< "The value of fines on the car is :"
						<< d[i].own_car[ii].fine[iii].value << '\n'

						<< "The street in which the fine was happen is :"
						<< d[i].own_car[ii].fine[iii].street << '\n'

						<< "tha date of the fine is :"
						<< d[i].own_car[ii].fine[iii].date.day << '/'
						<< d[i].own_car[ii].fine[iii].date.month << '/'
						<< d[i].own_car[ii].fine[iii].date.year << '\n';


				}
				cout << "You have to pay :"
					<< d[i].own_car[ii].total_fine << '\n';

			}

		}

	}

	if (found == false)
	{
		cout << "This car was not added\n";
	}

}

//allow the driver to pay the fine on a car and remove it from the total fines on him

void pay_fines(driver_s d[])
{
	float paid_fine;
	int plateOfCar;
	bool found = false;

	cout << "Enter the plate number of the car\n";

	cin >> plateOfCar;

	for (int i = 0; i < max_num_drivers; i++)
	{
		for (int ii = 0; ii < d[i].NumOfCars; ii++)
		{


			if (d[i].own_car[ii].plate_num == plateOfCar)
			{
				found = true;

				cout << "You have to pay the total fines on the car, The fines on this car is :"
					<< d[i].own_car[ii].total_fine << '\n';

				for (int iii = 0; iii < d[i].own_car[ii].NumOfFine; iii++)
				{
					cout << "The #" << iii + 1 << "fine is : "
						<< d[i].own_car[ii].fine[iii].value << '\n';

				}

				cout << "Enter the value you will pay \n";
				cin >> paid_fine;

				while (paid_fine != d[i].own_car[ii].total_fine)
				{
					cout << "You should the total fines, Only\n";
					cout << "Enter the value you will pay \n";
					cin >> paid_fine;

				}

				d[i].own_car[ii].total_fine -= paid_fine;

				cout << "NOW, The fines on this car is :"
					<< d[i].own_car[ii].total_fine << '\n';

				for (int iii = 0; iii < d[i].own_car[ii].NumOfFine; iii++)
				{
					d[i].own_car[ii].fine[iii].statue = "Paid";

				}

				d[i].own_car[ii].NumOfFine = 0;
			}
		}

	}

	if (found == false)
	{
		cout << "This car was not added\n";
	}

}