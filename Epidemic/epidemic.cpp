//---В связи с эпидемией гриппа в больницу направляется А больных гриппом "А" и В больных гриппом "В".Больных гриппом "А" нельзя помещать в одну палату с больными гриппом "В".Имеется информация об 
//общем количестве палат P в больнице, пронумерованных от 1 до P, и о распределении уже имеющихся там больных.
//Необходимо определить максимальное количество больных M, которое больница в состоянии принять.При размещении новых больных не разрешается переселять уже имеющихся больных из палаты в палату.
//---Входные данные находятся в текстовом файле с именем input.txt  и имеют следующую структуру :
//•	в первой строке находится целое число A(0≤A≤100);
//•	во второй строке – целое число B(0≤B≤100);
//•	в третьей строке – натуральное число P(P≤20);
//•	в каждой из последующих P строк находятся 3 числа n, a, b, разделенных пробелом, где n - вместимость палаты, a - количество уже имеющихся в палате больных гриппом "А", b - количество уже 
//имеющихся в палате больных гриппом "В".Информация о вместимости палат вводится последовательно для палат с номерами 1, 2, ..., P.Числа n, a, b - целые неотрицательные, меньшие 100.
//---Выходные данные должны быть записаны в текстовый файл с именем output.txt и иметь следующий формат :
//•	в первой строке должно находиться число M;
//•	если все поступившие больные размещены, то во второй строке должны находиться номера палат, разделенные пробелом, куда помещаются больные гриппом "А" (в порядке возрастания).

#include <fstream>
#include <cstdlib>

using namespace std;

struct Patients {

	int patientsA;
	int patientsB;

	Patients() {

		this->patientsA = 0;
		this->patientsB = 0;
	}

	Patients(int patientsA, int patientsB) {

		this->patientsA = patientsA;
		this->patientsB = patientsB;
	}

	Patients operator+(const Patients patients) {

		Patients result;

		result.patientsA = this->patientsA + patients.patientsA;
		result.patientsB = this->patientsB + patients.patientsB;

		return result;
	}

	Patients operator-(const Patients patients) {

		Patients result;

		result.patientsA = this->patientsA - patients.patientsA;
		result.patientsB = this->patientsB - patients.patientsB;

		return result;
	}
};

struct HospitalWard {

	Patients patients;
	int beds;
	int number;

	HospitalWard() {

		this->patients = Patients();
		this->beds = 0;
		this->number = 0;
	}

	HospitalWard(int beds, int patientsA, int patientsB, int number) {

		this->patients = Patients(patientsA, patientsB);
		this->beds = beds;
		this->number = number;
	}
};

int compareCapacity(const void* ward1, const void* ward2) {

	const HospitalWard* ward11 = (HospitalWard*)ward1;
	const HospitalWard* ward22 = (HospitalWard*)ward2;

	return ward11->beds < ward22->beds ? -1 : ward11->beds > ward22->beds ? 1 : 0;;
}

class Epidemic {

public:

	Patients patients;
	int P; //number of hospital wards
	HospitalWard *wards;
	HospitalWard *videWards;

	Epidemic(int A, int B, int P) {

		this->patients.patientsA = A;
		this->patients.patientsB = B;
		this->P = P;
		this->wards = new HospitalWard[this->P];
		this->videWards = new HospitalWard[this->P];
	}

	void nonVideWards() {

		for (int i = 0; i < P; i++) {

			if (wards[i].patients.patientsA != 0) {

				if (wards[i].beds - wards[i].patients.patientsA >= patients.patientsA) {
					
					wards[i].patients.patientsA += patients.patientsA;
					patients.patientsA = 0;
				}
				else {
					
					patients.patientsA -= wards[i].beds - wards[i].patients.patientsA;
					wards[i].patients.patientsA = wards[i].beds;
				}
			}
			else if (wards[i].patients.patientsB != 0) {

				if (wards[i].beds - wards[i].patients.patientsB >= patients.patientsB) {

					wards[i].patients.patientsB += patients.patientsB;
					patients.patientsB = 0;
				}
				else {

					patients.patientsB -= wards[i].beds - wards[i].patients.patientsB;
					wards[i].patients.patientsB = wards[i].beds;
				}
			}
		}
	}

	int videWard() {

		int bedsInFreeWards = 0;
		int j = 0;

		for (int i = 0; i < P; i++) {

			if (wards[i].patients.patientsA == 0 && wards[i].patients.patientsB == 0) {

				bedsInFreeWards += wards[i].beds;
				videWards[j++] = wards[i];
			}
		}

		return bedsInFreeWards;
	}

	int fullOccupansy(int bedsInFreeWards, int newA, int newB) {

		int *S = new int[bedsInFreeWards + 1]; // numbering of array starts on 1

		int firstRightOne = 0;

		for (int i = 0; i < bedsInFreeWards + 1; i++) {

			S[i] = 0;
		}

		int latestOne = 0;

		for (int i = 0; i < P; i++) {

			S[videWards[i].beds] = 1;

			latestOne += videWards[i].beds;

			S[latestOne] = 1;

			for (int j = videWards[i].beds - 1; j > 0; j--) {

				if (S[j] == 1) {

					S[j + videWards[i].beds] = 1;
				}
			}
		}

		for (int i = newA; i < bedsInFreeWards + 1; i++) {

			if (S[i] == 1) {

				firstRightOne = i;
				break;
			}
		}

		if (firstRightOne == 0) {

			//call a function that will calculate partial occupancy
		}
		else if (newB <= bedsInFreeWards - firstRightOne) {

			return patients.patientsA + patients.patientsB;
		}
		else {

			//call a function that will calculate partial occupancy
		}



		return 0;
	}

	int partialOssupancy() {

		return 0;
	}

	int task() {

		int bedsInFreeWards = 0;
		int M = 0;

		nonVideWards();

		qsort(wards, P, sizeof(HospitalWard), compareCapacity); // I must create new array

		bedsInFreeWards = videWard();
		//M = fullOccupansy(bedsInFreeWards, newA, newB);




		return M;	
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
	int M = 0;

	fin >> A;
	fin >> B;
	fin >> P;

	Epidemic epidemic(A, B, P);

	for (int i = 0; i < P; i++) {

		fin >> n;
		fin >> a;
		fin >> b;

		epidemic.wards[i] = HospitalWard(n, a, b, i);
	}

	M = epidemic.task();

	fout << M;

	return 0;
}






/*
-------! переработать рассмотрение уже "слегка" наполненных палат (создать отдельные поля для подсчета !!размещенных!! больных каждым гриппом (возможно даже отдельные функции))
-------! в функции task написать вызовы функций (п.1) и проверку на размещение всех больных в палаты из п.1. Если размещаются - return структурку больных и номера палат для больных А (optionally).
			Если не размещаются - вызывать функцию подсчета для пустых палат.
-------! в функции для пустых палат (videWards)


доделать частичное размещение сука заебало


*/