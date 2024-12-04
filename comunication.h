//#include "yami.h"
#include <memory>
#include "inversion.h"
#include "treshold.h"
#include "frame.h"
#include <vector>
#include <array>


class Comunication {


	std::string imageName_;
	std::string operation_ = "";
	int vertical_int;
	int horizontal_int;
	int value_int_;
	int canal_;

public:


	std::string init() {
		std::cout << "Wyberz obraz: \n";
		std::cin >> imageName_;
		return imageName_;
	}

	Picture open(std::string& imageName) {

		Picture picture;

		while (!picture.openPicture("./" + imageName)) {
			std::cout << "Niewlasciwa nazwa pliku, podaj inna: \n";
			std::cin >> imageName;
		}
		return picture;
	}


	std::vector <std::array<int,3>> createOperationVec(Picture picture ) {

		bool correct_oper = false;
		std::vector<std::array<int,3>> operation_vec;
		std::cout << "Wyberz operacje (1-inwersja, 2-biala_ramka, 3-tresholding_kanalu, 0-koniec wprowadzania): \n";
		while (!correct_oper) {

			int num = 0;
			
			std::getline(std::cin, operation_);
			try {
				int operation_num = std::stoi(operation_);
				switch (operation_num) {
					case 1:
					{
						std::array<int, 3> tab = { 1, 0, 0 };
						operation_vec.push_back(tab);
						num++;
						break;
					}
					case 2:
					{
						makeFrameComunication(picture);
						std::array<int, 3> tab1 = { 2, horizontal_int, vertical_int };
						operation_vec.push_back(tab1);
						num++;
						break;
					}
					case 3:
					{
						makeTresholdComunication();
						std::array<int, 3> tab2= { 3, canal_, value_int_ };
						std::cout << canal_ << '\n';
						operation_vec.push_back(tab2);
						num++;
						break;
					}
					case 0:
					{
						correct_oper = true;
						break;
					}
					default:
					{
						std::cout << "Niewlasciwa nazwa operacji, podaj (1, 2, 3): \n";
					}
				}
			}
			catch(std::invalid_argument e)
			{
				std::cout << "Niewlasciwa nazwa operacji, podaj (1, 2, 3): \n";
			}
			
		}
		return operation_vec;
	}

	std::vector<std::shared_ptr<Effect>> chooseOperation(std::vector<std::array<int,3>> operation_vec) {

		std::vector<std::shared_ptr<Effect>> finish_vec;
		;
		for (auto element : operation_vec) {
			switch (element[0]) {
				case 1:
				{
					std::shared_ptr<Effect> inversion = std::make_shared<Inversion>();
					finish_vec.push_back(inversion);
					break;
				}
				case 2:
				{
					std::shared_ptr<Effect> frame = std::make_shared<Frame>(element[1], element[2]);
					finish_vec.push_back(frame);
					break;
				}
				case 3:
				{
					std::shared_ptr<Effect> treshold = std::make_shared<Treshold>(element[1], element[2]);
					finish_vec.push_back(treshold);
					break;
				}
			}
		}	
		return finish_vec;
	}

	void makeFrameComunication(Picture picture) {

		std::cout << "Podaj wartosc horyzontalna ramki: \n";
		std::string horizontal;
		bool correct_value = 0;

		while (!correct_value)
		{
			try {
				std::getline(std::cin, horizontal);
				horizontal_int = std::stoi(horizontal);
				if ((horizontal_int < picture.getImage()->getSize().x) && (horizontal_int > 0)) {
					correct_value = true;
				}
				else {
					std::cout << "Podaj wartosc liczbowa z zakresu (0 - " << picture.getImage()->getSize().x << ") :\n";
				}
			}
			catch (std::invalid_argument e) {
				std::cout << "Podaj wartosc liczbowa: \n";
			}
		}

		std::cout << "Podaj wartosc wertykalna ramki: \n";
		std::string vertical;
		bool correct_value1 = false;

		while (!correct_value1)
		{
			try {
				std::getline(std::cin, vertical);
				vertical_int = std::stoi(vertical);
				if ((vertical_int < picture.getImage()->getSize().y) && (vertical_int > 0)) {
					correct_value1 = true;
				}
				else {
					std::cout << "Podaj wartosc liczbowa z zakresu (0 - " << picture.getImage()->getSize().y << ") :\n";
				}
			}
			catch (std::invalid_argument e) {
				std::cout << "Podaj wartosc liczbowa: \n";
			}
		}
	}

	void makeTresholdComunication() {

			std::cout << "Podaj kanal (r, g, b): \n";
			std::string canal_value;
			std::getline(std::cin, canal_value);
			
			bool correct_canal = false;
			while (!correct_canal) {
				if (canal_value == "r" || canal_value == "g" || canal_value == "b") {
					correct_canal = true;
				}
				else {
					std::cout << "Niewlasciwa nazwa kanalu, podaj (r, g, b): \n";
					std::cin >> canal_value;
				}
			}
			canal_ = (int)canal_value[0];
			std::cout << "Podaj wartosc tresholdu (0 - 255): \n";
			std::string value;
			bool correct_value2 = false;

			while (!correct_value2)
			{
				try {
					std::getline(std::cin, value);
					value_int_ = std::stoi(value);
					if ((value_int_ < 255) && (value_int_ > 0)) {
						correct_value2 = true;
					}
					else {
						std::cout << "Podaj wartosc liczbowa z zakresu (0 - 255) :\n";
					}
				}
				catch (std::invalid_argument e) {
					std::cout << "Podaj wartosc liczbowa: \n";
				}
			}
	}
	
};