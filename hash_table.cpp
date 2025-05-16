#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

const int table_size = 2000;

struct Company {
    string name;
    string profit_tax;
    string address;
};
struct Node {
    Company data;
    Node* next;
    Node(Company c) : data(c), next(nullptr) {}
};

struct HashTable {
    Node* table[table_size] = { nullptr };
};

vector<Company> readCompanyList(string file_name) {
    vector<Company> companies;
    ifstream input(file_name);
    string line;
    // tham khao ham find và substr
    while (getline(input, line)) {
        if (!line.empty()) {
            Company c;
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);

            c.name = line.substr(0, pos1);
            c.profit_tax = line.substr(pos1 + 1, pos2 - pos1 - 1);
            c.address = line.substr(pos2 + 1);

            companies.push_back(c);
        }
    }
    return companies;
}

long long hashString(string company_name) {
    long long hash = 0;
    long long power = 1;
    int m = table_size;
    int P = 31;

    int start = max(0, (int)company_name.length() - 20);
    string s = company_name.substr(start);
    // tham khao cach xu ly cong thuc tinh tong
    for (char c : s) {
        hash = (hash + (c * power) % m) % m;
        power = (power * P) % m;
    }
    return hash;
}

HashTable* createHashTable(vector<Company> list_company) {
    HashTable* hash_table = new HashTable();

    for (const Company& c : list_company) {
        long long index = hashString(c.name);
        Node* newNode = new Node(c);
        newNode->next = hash_table->table[index];
        hash_table->table[index] = newNode;
    }

    return hash_table;
}
// tuong tu voi tao bang bam nhung ap dung cho 1 cong ty
void insert(HashTable* hash_table, Company company) {
    long long index = hashString(company.name);
    Node* newNode = new Node(company);
    newNode->next = hash_table->table[index];
    hash_table->table[index] = newNode;
}

Company* search(HashTable* hash_table, string company_name) {
    long long index = hashString(company_name);
    Node* cur = hash_table->table[index];
    while (cur) {
        if (cur->data.name == company_name) {
            return &cur->data;
        }
        cur = cur->next;
    }
    return nullptr;
}

vector<string> Input(string file_name) {
    vector<string> names;
    ifstream input(file_name);
    string line;
    while (getline(input, line)) {
        if (!line.empty()) names.push_back(line);
    }
    return names;
}
void Output(string output_file, vector<Company*> results) {
    ofstream output(output_file);
    for (Company* c : results) {
        if (c != nullptr) {
            output << c->name << "|" << c->profit_tax << "|" << c->address << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Error\n";
        return 1;
    }

    string f_mst = argv[1];
    string f_input = argv[2];
    string f_output = argv[3];

    vector<Company> companies = readCompanyList(f_mst);
    HashTable* hash_table = createHashTable(companies);

    vector<string> input_names = Input(f_input);
    vector<Company*> results;

    for (const string& name : input_names) {
        Company* result = search(hash_table, name);
        results.push_back(result);
    }

    Output(f_output, results);

    return 0;
}