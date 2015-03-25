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

int compare(const void* ward1, const void* ward2) {

	const HospitalWard* ward11 = (HospitalWard*)ward1;
	const HospitalWard* ward22 = (HospitalWard*)ward2;

	return ward11->beds < ward22->beds ? -1 : ward11->beds > ward22->beds ? 1 : 0;;
}

class Epidemic {

public:

	int A; //number of patients A
	int B; //number of patients B
	int P; //number of hospital wards
	HospitalWard *wards;
	HospitalWard *videWards;

	int bedsForA; //number of free beds for patientsA
	int bedsForB; //number of free beds for patientsB

	int satisfiedA;
	int satisfiedB;

	Epidemic(int A, int B, int P) {

		this->A = A;
		this->B = B;
		this->P = P;
		this->wards = new HospitalWard[this->P];
		this->videWards = new HospitalWard[this->P];

		this->bedsForA = 0;
		this->bedsForB = 0;

		this->satisfiedA = 0;
		this->satisfiedB = 0;
	}

	void nonVideWards() {

		for (int i = 0; i < P; i++) {

			if (wards[i].patientsA != 0) {

				bedsForA += wards[i].beds - wards[i].patientsA;
			}
			else if (wards[i].patientsB != 0) {

				bedsForB += wards[i].beds - wards[i].patientsB;
			}
		}
	}

	bool isSatisfiedA() {

		if (bedsForA >= A) {

			return true;
		}
		else {

			return false;
		}
	}

	bool isSatisfiedB() {

		if (bedsForB >= B) {

			return true;
		}
		else {

			return false;
		}
	}

	int videWard() {

		int bedsInFreeWards = 0;
		int j = 0;

		for (int i = 0; i < P; i++) {

			if (wards[i].patientsA == 0 && wards[i].patientsB == 0) {

				bedsInFreeWards += wards[i].beds;
				videWards[j++] = wards[i];
			}
		}

		return bedsInFreeWards;
	}

	void capacitySet(int bedsInFreeWards) {

		if (isSatisfiedA() && isSatisfiedB()) {

			return;
		}

		int *S = new int[bedsInFreeWards + 1]; // numbering of array starts on 1

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
	}

	int task() {

		int bedsInFreeWards = 0;

		nonVideWards();

		if (isSatisfiedA() && isSatisfiedB()) {

			return A + B;
		}
		else {

			qsort(wards, P, sizeof(HospitalWard), compare); // I must create new array

			bedsInFreeWards = videWard();
			capacitySet(bedsInFreeWards);


			return 0;
		}
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

		epidemic.wards[i] = HospitalWard(n, a, b);
	}

	M = epidemic.task();

	fout << M;

	return 0;
}