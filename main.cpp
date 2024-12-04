//Include files
#include "comunication.h"
#include "execute.h"

int main() {

//creates comunication object
	Comunication comunication;
	
//starts comunication with user
	std::string file_name = comunication.init();

//opens choosen picture
	Picture  picture = comunication.open(file_name);
	
//creates operation vector
	std::vector<std::array<int,3>> operation_vector;
//returns operation vector according to choise 
	operation_vector = comunication.createOperationVec(picture);

//creates vector of pointers to operations
	std::vector<std::shared_ptr<Effect>> finish_vect;
//return vector of pointers to operations according to data in operation vector
	finish_vect = comunication.chooseOperation(operation_vector);
	
	Execute execute;
//execute operations in prepared vector
	execute.execute(finish_vect, picture);
	
	picture.writePicture("./obraz4.bmp");
	//picture.show();

}