#include <fstream>

using namespace std;

struct HospitalWard{

	int beds;
	int patientsA;
	int patientsB;

	HospitalWard() {

		this->beds = 0;
		this->patientsA = 0;
		this->patientsB = 0;
	}

	HospitalWard(int beds, int patientsA, int patientsB) {

		this->beds = beds;
		this->patientsA = patientsA;
		this->patientsB = patientsB;
	}
};


int main() {

	ifstream fin("input.txt");
	ofstream fout("output.txt");




	return 0;
}