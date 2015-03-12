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

	int A = 0; //number of patients A
	int B = 0; //number of patients B
	int P = 0; //number of hospital wards
	int n = 0; //number of beds
	int a = 0; //number of patients A in a hospital ward
	int b = 0; //number of patients B in a hospital ward

	fin >> A;
	fin >> B;
	fin >> P;

	HospitalWard *wards = new HospitalWard[P];

	for (int i = 0; i < P; i++) {

		fin >> n;
		fin >> a;
		fin >> b;

		wards[i] = HospitalWard(n, a, b);
	}

	delete []wards;
	return 0;
}