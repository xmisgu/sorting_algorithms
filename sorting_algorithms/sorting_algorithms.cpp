#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include <random>

template <typename T>
class List {
public:
	struct node {
		T dane;
		node* next, * prev;
		node() {
			next = nullptr;
			prev = nullptr;
		}
	};

	List() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	~List() {
		delete_all();
	}

	T& operator[](unsigned int index) {
		if (index > size) {
			abort();
		}
		else {
			node* ptr = head;
			int i = 0;
			while (ptr && i < index) {
				ptr = ptr->next;
				i++;
			}
			return ptr->dane;
		}	
	}

	int get_size() {
		return size;
	}

	void new_node_back(const T& dane) {
		node* n = new node;
		n->dane = dane;
		n->next = nullptr;
		if (tail == nullptr) {
			n->prev = nullptr;
			head = n;
			tail = n;
		}
		else {
			n->prev = tail;
			tail->next = n;
			tail = n;
		}
		size++;
	}

	void new_node_front(const T& dane) {
		node* n = new node;
		n->dane = dane;
		n->prev = nullptr;
		if (head == nullptr) {
			n->prev = nullptr;
			head = n;
			tail = n;
		}
		else {
			n->next = head;
			head->prev = n;
			head = n;
		}
		size++;
	}

	void new_node_ordered(const T& dane) {

		node* n = new node;
		n->dane = dane;
		if (head == nullptr) {
			n->next = nullptr;
			n->prev = nullptr;
			head = n;
			tail = n;
			size++;
			return;
		}

		if (dane < head->dane) {
			new_node_front(dane);
			return;
		}
		else if (tail->dane < dane || tail->dane == dane) {
			new_node_back(dane);
			return;
		}


		node* ptr = head;
		while (ptr) {
			if (ptr->dane < dane && dane < ptr->next->dane) {
				n->prev = ptr;
				n->next = ptr->next;
				ptr->next->prev = n;
				ptr->next = n;
				size++;
				return;
			}
			else if (ptr->dane == dane) {
				n->prev = ptr;
				n->next = ptr->next;
				ptr->next->prev = n;
				ptr->next = n;
				size++;
				return;
			}

			ptr = ptr->next;
		}

	}

	void delete_last() {
		if (size == 0) {
			//std::cout << "Brak elementow do usuniecia" << std::endl;
		}
		else if (size == 1) {
			delete_all();
		}
		else {
			node* temp = tail;
			tail = temp->prev;
			tail->next = nullptr;
			delete temp;
			size--;
		}
	}

	void delete_first() {
		if (size == 0) {
			std::cout << "Brak elementow do usuniecia" << std::endl;
		}
		else if (size == 1) {
			delete_all();
		}
		else {
			node* temp = head;
			head = temp->next;
			head->prev = nullptr;
			delete temp;
			size--;
		}
	}

	node* find_node(const T& key) {
		node* ptr = head;
		while (ptr) {
			if ((ptr->dane == key)) {
				return ptr;
			}
			else {
				ptr = ptr->next;
			}
		}
		return nullptr;
	}

	T find_element(int n) {
		node* ptr;
		if (size / 2 > n) {
			ptr = head;
			int i = 0;
			while (ptr && i < n) {
				ptr = ptr->next;
				i++;
			}
		}
		else {
			ptr = tail;
			int i = size - 1;
			while (ptr && i > n) {
				ptr = ptr->prev;
				i--;
			}
		}

		if (!ptr) {
			abort();
		}

		return ptr->dane;
	}

	bool find_and_delete(const T& key) {

		node* ptr = head;
		while (ptr) {
			if ((ptr->dane == key)) {
				if (ptr == head) {
					this->delete_first();

					return 1;
				}
				else if (ptr == tail) {
					this->delete_last();
					return 1;
				}
				else {

					ptr->prev->next = ptr->next;
					ptr->next->prev = ptr->prev;
					delete ptr;
					size--;
					return 1;
				}

			}
			else {
				ptr = ptr->next;
			}
		}
		return 0;

	}

	void swap_element(int n, const T& new_data) {
		node* ptr = head;
		int i = 0;
		while (ptr && i < n) {
			ptr = ptr->next;
			i++;
		}
		if (ptr) {
			ptr->dane = new_data;
		}
	}

	void delete_all() {
		if (size == 0) {
			//std::cout << "Lista pusta" << std::endl;
		}
		else if (size == 1) {
			delete head;
			size--;
		}
		else {
			node* tmp = head;
			while (tmp) {
				tmp = tmp->next;
				delete head;
				head = tmp;
				size--;
			}
			tail = nullptr;
			delete tmp;
		}

	}

	std::string display_list(int n = 0) {
		node* ptr = head;
		int i = 0;
		std::ostringstream output;
		if (!n) {
			n = size;
		}
		while (ptr && i < n) {
			output << "Node: " << i << ", ADDR: " << ptr << std::endl;
			output << ptr->dane << std::endl;
			i++;
			ptr = ptr->next;
		}
		return output.str();
	}


private:
	node* head, * tail;
	unsigned int size;
};

template <typename T>
class DynamicArr {
private:
	unsigned int arr_size;
	unsigned int num_of_elements;
	T* array;

	
public:
	DynamicArr() {
		arr_size = 1; //array size
		num_of_elements = 0; //number of elements in array
		array = new T[arr_size];
	}

	DynamicArr(const DynamicArr& new_arr) {
		delete_all();
		array = new_arr.array;
		num_of_elements = new_arr.num_of_elements;
		arr_size = new_arr.arr_size;
	}

	~DynamicArr() {
		delete[] array;
	}

	void swap_array(T* new_arr,unsigned int size) {
		array = new_arr;
		num_of_elements = size;
	}

	unsigned int size() {
		return num_of_elements;
	}

	T& operator[](unsigned int index) {
		return array[index];
	}

	void add_element(const T& new_data) {
		if (arr_size == num_of_elements) make_arr_bigger();

		array[num_of_elements] = new_data;
		num_of_elements++;
	}

	void make_arr_bigger() {
		arr_size = arr_size * 2;
		T* tmp_arr = new T[arr_size];

		for (unsigned int i = 0; i < num_of_elements; i++) {
			tmp_arr[i] = array[i];
		}

		delete[] array;
		array = tmp_arr;
	}

	T find_element(unsigned int i) {
		if (i < num_of_elements) {
			return array[i];
		}
		else {
			abort();
		}
	}

	void swap_data(unsigned int i, const T& new_data) {
		if (i < num_of_elements) {
			array[i] = new_data;
		}
		else {
			abort();
		}
	}

	void sort() {
		T tmp;
		bool flag;
		for (int i = 0; i < num_of_elements - 1; i++) {
			flag = 0;
			for (int j = 0; j < num_of_elements - i - 1; j++) {
				if (array[j] > array[j + 1]) {
					tmp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = tmp;
					flag = 1;
				}
			}
			if (!flag) break;
		}
	}

	void remove(unsigned int index) {
		if (index < num_of_elements && index >= 0) {
			for (int i = index; i < num_of_elements; i++) {
				array[i] = array[i + 1];
			}
			num_of_elements--;
		}
	}

	void delete_all() {
		delete[] array;
		arr_size = 1;
		num_of_elements = 0;
		array = new T[arr_size];
	}

	std::string display_array(unsigned int n = 0) {
		std::ostringstream output;

		output << "Rozmiar tablicy: " << arr_size << std::endl;
		output << "Liczba elementow: " << num_of_elements << std::endl;

		if (n > num_of_elements) n = num_of_elements;

		for (unsigned int i = 0; i < n; i++) {
			output << *&array[i] << std::endl;
		}

		return output.str();
	}
};

template <typename D>
class BinaryHeap {
public:
	BinaryHeap(){}
	BinaryHeap(D* array, int size, bool method) {
		
		for (int i = 0; i < size; i++) {
			arr.add_element(array[i]);
		}
		if (method) {
			for (int i = (arr.size() / 2 - 1); i >= 0; i--) {
				przekopcowanie_w_dol(i);
			}
		}
		else {
			naprawa_top_down();
		}
	}

	void add(const D& data) {
		arr.add_element(data);
		przekopcowanie_w_gore(arr.size() - 1);
	}

	D delete_max() {
		if (arr.size() == 0) {
			abort();
		}
		else {
			D max = arr[0];
			if (arr.size() == 1) {
				clear();
			}
			else {
				std::swap(arr[0], arr[arr.size() - 1]);
				arr.remove(arr.size() - 1);
				przekopcowanie_w_dol(0);
			}
			return max;
		}
	}

	void clear() {
		arr.delete_all();
	}

	void sort() {
		int size = arr.size();
		D* tmp_arr = new D[size];
		for (int i = 0; i < size; i++) {
			tmp_arr[i] = delete_max();
		}
		arr.swap_array(tmp_arr, size);
	}

	std::string display(unsigned int n = 0) {
		return arr.display_array(n);
	}

private:
	DynamicArr<D> arr;

	void przekopcowanie_w_gore(unsigned int i) {
		if (i != 0) {
			if (arr[i] > arr[(i - 1) / 2]) {
				std::swap(arr[i], arr[(i - 1) / 2]);
				przekopcowanie_w_gore((i - 1) / 2);
			}
		}
		else {
			return;
		}
	}
	void przekopcowanie_w_dol(unsigned int i) {

		if ((2 * i + 1 < arr.size() && arr[2 * i + 1] > arr[i]) || (2 * i + 2 < arr.size() && arr[2 * i + 2] > arr[i])) {
			if (arr[2 * i + 1] > arr[2 * i + 2]) {
				std::swap(arr[i], arr[2 * i + 1]);
				przekopcowanie_w_dol(2 * i + 1);
			}
			else {
				std::swap(arr[i], arr[2 * i + 2]);
				przekopcowanie_w_dol(2 * i + 2);
			}
		}
		return;
	}
	void naprawa_top_down() {
		//todo
	}
};


void counting_sort(int *arr, unsigned int size, int range) {  
    int* counter = new int[range];
    for (int i = 0; i < range; i++) {
        counter[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        counter[arr[i]]++;
    }

    int current_index = 0;
    for (int i = 0; i < range; i++) {
        for (int j = current_index; j < current_index + counter[i]; j++) {
            arr[j] = i;
        }
        current_index += counter[i];
    }
	delete[] counter;
}

template <typename T>
void bucket_sort(T* arr, unsigned int size, double range) {
    std::vector<List<T>> buckets;
    buckets.resize(size);
    double w = range / size;
    
	for (int i = 0; i < size; i++) {
		int bucket_index = std::floor(arr[i] / w);
		buckets[bucket_index].new_node_ordered(arr[i]);
	}

    int current_index = 0;
    for (int i = 0; i < size; i++) {
		int bucket_index = 0;
		for (int j = current_index; j < current_index + buckets[i].get_size(); j++) {
			arr[j] = buckets[i][bucket_index];
			bucket_index++;
        }
        current_index += buckets[i].get_size();
    }
	buckets.resize(0);
	buckets.shrink_to_fit();
}
void bucket_sort(int *arr, unsigned int size, int range) {
    std::vector<std::vector<int>> buckets;
    buckets.resize(range);

    for (int i = 0; i < size; i++) {
        buckets[arr[i]].push_back(arr[i]);
    }

    int current_index = 0;
    for (int i = 0; i < range; i++) {
        for (int j = current_index; j < current_index + buckets[i].size(); j++) {
            arr[j] = i;
        }
        current_index += buckets[i].size();
    }
	buckets.resize(0);
	buckets.shrink_to_fit();
}

struct Data {
    float key;
    char value;
};


int main()
{
	{
		srand(0);
		const int MAX_ORDER = 7;
		const double m_double = (double)pow(2, 30);

		for (int o = 1; o <= MAX_ORDER; o++) {
			std::cout << "===============================================" << std::endl;
			std::cout << "                    TEST" << o << std::endl;
			std::cout << "===============================================" << std::endl;
			const int n = (int)pow(10, o);

			double* arr1 = new double[n];
			for (int i = 0; i < n; i++) {
				arr1[i] = ((rand() << 15) + rand()) / m_double;
			}
			std::cout << "Nieposortowana tablica" << std::endl;
			for (int i = 0; i < 10; i++) {
				std::cout << arr1[i] << std::endl;
			}

			double* arr2 = new double[n];
			std::memcpy(arr2, arr1, n * sizeof(double));
			clock_t t1 = clock();
			BinaryHeap<double> heap(arr1, n, 1);
			heap.sort();
			clock_t t2 = clock();
			std::cout << "-----------------------------------------------" << std::endl;

			std::cout << "Posortowana tablica(kopcowanie)" << std::endl;
			std::cout << heap.display(10) << std::endl;
			std::cout << "-----------------------------------------------" << std::endl;
			double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "Calkowity czas dodawania: " << time << std::endl;
			std::cout << "Sredni czas dodawania: " << time / n << std::endl;
			std::cout << "-----------------------------------------------" << std::endl;

			t1 = clock();
			bucket_sort(arr2, n, 1.0);
			t2 = clock();
			std::cout << "Posortowana tablica(kubelkowe)" << std::endl;
			for (int i = 0; i < 10; i++) {
				std::cout << arr2[i] << std::endl;
			}
			std::cout << "-----------------------------------------------" << std::endl;
			time = (t2 - t1) / (double)CLOCKS_PER_SEC;
			std::cout << "Calkowity czas dodawania: " << time << std::endl;
			std::cout << "Sredni czas dodawania: " << time / n << std::endl;
			std::cout << "-----------------------------------------------" << std::endl;
			std::cout << "\n\n";

			heap.clear();
			delete[] arr1, arr2;
		}		
		return 0;
	}
	srand(0);

	const int MAX_ORDER = 7;
	const int m = (int)pow(10, 7);

	for (int o = 1; o <= MAX_ORDER; o++) {
		std::cout << "===============================================" << std::endl;
		std::cout << "                    TEST" << o << std::endl;
		std::cout << "===============================================" << std::endl;
		const int n = (int)pow(10, o);

		int* arr1 = new int[n];
		for (int i = 0; i < n; i++) {
			arr1[i] = rand() % 1000;
		}
		std::cout << "Nieposortowana tablica" << std::endl;
		for (int i = 0; i < 10; i++) {
			std::cout << arr1[i] << std::endl;
		}
		int* arr2 = new int[n];
		int* arr3 = new int[n];
		std::memcpy(arr2, arr1, n * sizeof(int));
		std::memcpy(arr3, arr1, n * sizeof(int));
		std::cout << "-----------------------------------------------" << std::endl;
		clock_t t1 = clock();
		counting_sort(arr1, n, m);
		clock_t t2 = clock();

		std::cout << "Posortowana tablica (zliczanie)" << std::endl;
		for (int i = 0; i < 10; i++) {
			std::cout << arr1[i] << std::endl;
		}
		std::cout << "-----------------------------------------------" << std::endl;
		double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Calkowity czas dodawania: " << time << std::endl;
		std::cout << "Sredni czas dodawania: " << time / n << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;

		t1 = clock();
		BinaryHeap<int> heap(arr2, n, 1);
		heap.sort();
		t2 = clock();
		std::cout << "-----------------------------------------------" << std::endl;

		std::cout << "Posortowana tablica(kopcowanie)" << std::endl;
		std::cout << heap.display(10) << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Calkowity czas dodawania: " << time << std::endl;
		std::cout << "Sredni czas dodawania: " << time / n << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;

		t1 = clock();
		bucket_sort(arr3, n, m);
		t2 = clock();
		std::cout << "Posortowana tablica(kubelkowe)" << std::endl;
		for (int i = 0; i < 10; i++) {
			std::cout << arr3[i] << std::endl;
		}
		std::cout << "-----------------------------------------------" << std::endl;
		time = (t2 - t1) / (double)CLOCKS_PER_SEC;
		std::cout << "Calkowity czas dodawania: " << time << std::endl;
		std::cout << "Sredni czas dodawania: " << time / n << std::endl;
		std::cout << "-----------------------------------------------" << std::endl;
		std::cout << "\n\n";

		//heap.clear();
		delete[] arr1, arr2, arr3;
	}
	system("pause");
}

