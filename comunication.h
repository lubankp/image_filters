//includes files and libraries
#include <memory>
#include "inversion.h"
#include "treshold.h"
#include "frame.h"
#include <vector>
#include <array>


class Comunication {
// allows to comunicate with user by terminal

	std::string imageName_;
	std::string operation_ = "";
	int vertical_int;
	int horizontal_int;
	int value_int_;
	int canal_;

public:


	std::string init() {
		//starts comunication and return image name
		
		std::cout << "Choose an image: \n";
		std::cin >> imageName_;
		return imageName_;
	}

	Picture open(std::string& imageName) {
		//opens choosen picture

		Picture picture;

		while (!picture.openPicture("./" + imageName)) {
			std::cout << "Wrong image name, provide a different one: \n";
			std::cin >> imageName;
		}
		return picture;
	}


	std::vector <std::array<int,3>> createOperationVec(Picture picture ) {
		//creates operation veector accourding to choise 
		
		bool correct_oper = false;
		std::vector<std::array<int,3>> operation_vec;
		std::cout << "Choose an operation (1-inversion, 2-white frame, 3-cannal tresholding, 0-end of providing): \n";
		std::cin.ignore();
		
		while (!correct_oper) {

			int num = 0;
			
			try {
				std::getline(std::cin, operation_);
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
						std::cout << "Wrong operation name, provide (1 or 2 or 3): \n";
					}
				}
			}
			catch(std::invalid_argument e)
			{
				std::cout << "Wrong operation name, provide (1 or 2 or 3): \n";
			}
			
		}
		return operation_vec;
	}

	std::vector<std::shared_ptr<Effect>> chooseOperation(std::vector<std::array<int,3>> operation_vec) {
		//create vector of objects - modifications

		std::vector<std::shared_ptr<Effect>> finish_vec;
		
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
		//takes additional informations for frame operation

		std::cout << "Provide horizontal value of frame: \n";
		std::string horizontal;
		bool correct_value = false;

		//while not correct takes horizontal value
		while (!correct_value)
		{
			try {
				std::getline(std::cin, horizontal);
				horizontal_int = std::stoi(horizontal);
				if ((horizontal_int < picture.getImage()->getSize().x / 2) && (horizontal_int > 0)) {
					correct_value = true;
				}
				else {
					std::cout << "Provide numerical value in range (0 - " << picture.getImage()->getSize().x / 2 << ") :\n";
				}
			}
			catch (std::invalid_argument e) {
				std::cout << "Provide numerical value: \n";
			}
		}

		std::cout << "Provide vertical value of frame: \n";
		std::string vertical;
		bool correct_value1 = false;

		//while not correct takes vertical value
		while (!correct_value1)
		{
			try {
				std::getline(std::cin, vertical);
				vertical_int = std::stoi(vertical);
				if ((vertical_int < picture.getImage()->getSize().y / 2) && (vertical_int > 0)) {
					correct_value1 = true;
				}
				else {
					std::cout << "Provide numerical value in range (0 - " << picture.getImage()->getSize().y / 2 << ") :\n";
				}
			}
			catch (std::invalid_argument e) {
				std::cout << "Provide numerical value: \n";
			}
		}
	}

	void makeTresholdComunication() {
		//takes additional informations for treshold operation

			std::cout << "Provide a cannal (r or g or b): \n";
			std::string canal_value;
			bool correct_canal = false;

			//while not correct takes canal value
			while (!correct_canal) {
				std::getline(std::cin, canal_value);
				if (canal_value == "r" || canal_value == "g" || canal_value == "b") {
					correct_canal = true;
				}
				else {
					std::cout << "Wrong cannal name, provide (r or g or b): \n";
				}
			}
			canal_ = (int)canal_value[0];
			std::cout << "Provide treshold value (0 - 255): \n";
			std::string value;
			bool correct_value2 = false;

			//while not correct takes value of treshold
			while (!correct_value2)
			{
				try {
					std::getline(std::cin, value);
					value_int_ = std::stoi(value);
					if ((value_int_ < 255) && (value_int_ > 0)) {
						correct_value2 = true;
					}
					else {
						std::cout << "Provide numerical value in range (0 - 255) :\n";
					}
				}
				catch (std::invalid_argument e) {
					std::cout << "Provide numerical value: \n";
				}
			}
	}
	
};