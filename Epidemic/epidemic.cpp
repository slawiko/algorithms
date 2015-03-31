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
#include <vector>

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

struct Element {

	vector<int> ancestry;
	int index;

	Element() {

		this->index = 0;
	}
};
int compareCapacity(const void* ward1, const void* ward2) {

	const HospitalWard* ward11 = (HospitalWard*)ward1;
	const HospitalWard* ward22 = (HospitalWard*)ward2;

	return ward11->beds < ward22->beds ? -1 : ward11->beds > ward22->beds ? 1 : 0;;
}

int compareNumber(const void* ward1, const void* ward2) {

	const HospitalWard* ward11 = (HospitalWard*)ward1;
	const HospitalWard* ward22 = (HospitalWard*)ward2;

	return ward11->number < ward22->number ? -1 : ward11->number > ward22->number ? 1 : 0;;
}

class Epidemic {

public:

	Patients defaultPatients;

	int P;

	Patients currentPatients;

	HospitalWard *wards;
	HospitalWard *videWards;

	Epidemic(int A, int B, int P) {

		this->defaultPatients.patientsA = A;
		this->defaultPatients.patientsB = B;

		this->P = P;

		this->currentPatients.patientsA = A;
		this->currentPatients.patientsB = B;

		this->wards = new HospitalWard[this->P];
		this->videWards = new HospitalWard[this->P];
	}

	void nonVideWards() {

		for (int i = 0; i < P; i++) {

			if (wards[i].patients.patientsA != 0) {

				if (wards[i].beds - wards[i].patients.patientsA >= currentPatients.patientsA) {
					
					wards[i].patients.patientsA += currentPatients.patientsA;
					currentPatients.patientsA = 0;
				}
				else {
					
					currentPatients.patientsA -= wards[i].beds - wards[i].patients.patientsA;
					wards[i].patients.patientsA = wards[i].beds;
				}
			}
			else if (wards[i].patients.patientsB != 0) {

				if (wards[i].beds - wards[i].patients.patientsB >= currentPatients.patientsB) {

					wards[i].patients.patientsB += currentPatients.patientsB;
					currentPatients.patientsB = 0;
				}
				else {

					currentPatients.patientsB -= wards[i].beds - wards[i].patients.patientsB;
					wards[i].patients.patientsB = wards[i].beds;
				}
			}
		}
	}

	void videWard() {

		int bedsInFreeWards = 0;
		int j = 0;

		for (int i = 0; i < P; i++) {

			if (wards[i].patients.patientsA == 0 && wards[i].patients.patientsB == 0) {

				bedsInFreeWards += wards[i].beds;
				videWards[j++] = wards[i];
			}
		}

		fullOccupansy(bedsInFreeWards);
	}


	void fullOccupansy(int bedsInFreeWards) {

		Element *S = new Element[bedsInFreeWards + 1]; // numbering of array starts on 1

		for (int i = 0; i < bedsInFreeWards + 1; i++) {

			S[i].ancestry.reserve(P);
		}

		S[0].index = 1;

		int latestOne = 0;

		for (int i = 0; i < P; i++) {

			latestOne += videWards[i].beds;

			if (videWards[i].beds == 0) break;

			if (S[videWards[i].beds].ancestry.size() == 0) {

				S[videWards[i].beds].ancestry.push_back(videWards[i].number);
			}

			for (int j = latestOne - 1; j > 0; j--) {

				if (S[j].index == 1) {

					S[j + videWards[i].beds].index = 1;

					if (S[j + videWards[i].beds].ancestry.size() < S[j].ancestry.size() + 1) {

						for (int k = 0; k < S[j].ancestry.size(); k++) {

							S[j + videWards[i].beds].ancestry.push_back(S[j].ancestry[k]);
						}

						S[j + videWards[i].beds].ancestry.push_back(videWards[i].number);
					}
				}
			}

			S[videWards[i].beds].index = 1;
		}

		int firstRightOne = 0;

		for (int i = currentPatients.patientsA; i < bedsInFreeWards + 1; i++) {

			if (S[i].index == 1) {

				firstRightOne = i;
				break;
			}
		}

		if ((firstRightOne != 0) && (bedsInFreeWards - firstRightOne >= currentPatients.patientsB)) {

			for (int i = 0; i < S[firstRightOne].ancestry.size(); i++) {

				int temp = S[firstRightOne].ancestry[i];
				int difference = wards[temp].beds - wards[temp].patients.patientsA;

				if (currentPatients.patientsA >= difference) {

					wards[temp].patients.patientsA = wards[temp].beds;
					currentPatients.patientsA -= difference;
				}
				else {

					wards[temp].patients.patientsA = currentPatients.patientsA;
					currentPatients.patientsA = 0;
				}
			}

			currentPatients.patientsB = 0;
			return;
		}
		else {

			int firstleftOneA = 0;
			int firstleftOneB = 0;

			for (int i = currentPatients.patientsA; i > 0; i--) {

				if (S[i].index == 1) {

					firstleftOneA = i;
					break;
				}
			}
			for (int i = currentPatients.patientsB; i > 0; i--) {

				if (S[i].index == 1) {

					firstleftOneB = i;
					break;
				}
			}

			partialOccupancy(bedsInFreeWards, firstleftOneA, firstleftOneB);
			return;
		}
	}

	void partialOccupancy(int bedsInFreeWards, int firstLeftOneA, int firstLeftOneB) {

		int lostBedsForB = bedsInFreeWards - firstLeftOneA;
		int happyB = 0;

		if (lostBedsForB > currentPatients.patientsB) {

			happyB = currentPatients.patientsB;
		}
		else {

			happyB = lostBedsForB;
		}


		int lostBedsForA = bedsInFreeWards - firstLeftOneB;
		int happyA = 0;

		if (lostBedsForA > currentPatients.patientsA) {

			happyA = currentPatients.patientsA;
		}
		else {

			happyA = lostBedsForA;
		}

		if (happyB + firstLeftOneA > happyA + firstLeftOneB) {

			currentPatients.patientsA -= firstLeftOneA;
			currentPatients.patientsB -= happyB;
		}
		else {

			currentPatients.patientsA -= happyA;
			currentPatients.patientsB -= firstLeftOneB;
		}
		
		return;
	}

	int task() {

		int bedsInFreeWards = 0;
		int M = 0;

		nonVideWards();

		if (currentPatients.patientsA == 0 && currentPatients.patientsB == 0) {

			M = defaultPatients.patientsA + defaultPatients.patientsB;
			return M;
		}

		qsort(wards, P, sizeof(HospitalWard), compareNumber);

		videWard();

		M = (defaultPatients.patientsA - currentPatients.patientsA) + (defaultPatients.patientsB - currentPatients.patientsB);
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

	fout << M << endl;

	qsort(epidemic.wards, epidemic.P, sizeof(HospitalWard), compareCapacity);

	if (epidemic.currentPatients.patientsA == 0 && epidemic.currentPatients.patientsB == 0) {

		for (int i = 0; i < epidemic.P; i++) {

			if (epidemic.wards[i].patients.patientsA != 0) {

				fout << epidemic.wards[i].number + 1 << " "; //+1 because array starts with 0
			}
		}
	}

	return 0;
}