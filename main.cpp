#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

//creates partial match table base on pattern
void partialMatchTable(string p, int pi[])
{
	int m = p.length();
	int q;
	pi[0] = -1;
	
	for (int i = 1; i < m; ++i)
	{
		q = pi[i-1];
		while (q >= 0)
		{
			if (p[q] == p[i-1])
				break;
			else
				q = pi[q];
		}
		pi[i] = q + 1;
	}
}

// menjalankan pencarian menggunakan metode KMP
int KMP(string p, string t)
{
	// menghitung jumlah karakter dari target dan pola
	int n = t.length();
	int m = p.length();
	int pi[m];
	
	partialMatchTable(p, pi);
	
	int i = 0;
	int q = 0;
	
	while (i < n)
	{
		if (q == -1)
		{
			++i;
			q = 0;
		}
		else if (t[i] == p[q]) // pencocokan karakter pola dengan target
		{
			++i;
			++q;
			if (q == m){
				return i;
			}
		}
		else // reset pencarian, karena tidak cocok
			q = pi[q];
	}
	return 0;
}

int findLine(int i, string fileName){

	ifstream file(fileName);
	string target = "" ;
	string line;
	int result = 0 ;
	int lineCount = 0 ;

	while (!file.eof())
	{
		getline(file, line);
		target += line;

		if (result == 0 && target.length() > i){
			result = lineCount ;
		}
		++lineCount;
	}
	file.close();

	return result ;
}

int main(int argc, char *argv[])
{
	//shows how program needs to run if command line entry was wrong
	if (argc != 2)
	{
		cout << "Cara Menggunakan : "<< argv[0] << "</../nameOfText.txt>" << endl;
	}
	//actual program
	else
	{		
		string fileName = argv[1];
		ifstream file(fileName);
		
		string line;
		char answer;
		int lineCount = 0;
		int start;
		int end;
		string target = "";
		string pattern;
		
		//check if did not open
		if (!file.is_open())
		{
     		cout<< "Could not open file" << endl;
		}
		else
		{
			// Membuka dokumen dan menghitung jumlah baris
			while (!file.eof())
			{
				getline(file, line);
				target += line;
				++lineCount;
			}
			cout << "Jumlah Baris pada file : " << lineCount << endl;
			file.close();
			
			// konfirmasi untuk menjalankan KMP
			cout << "Jalankan pencarian menggunakan metode KMP ? (y/n) "; cin >> answer;
			cin.ignore();
			while (answer == 'y' || answer == 'Y')
			{
				cout << "Masukkan kata kunci :" ;
				getline(cin, pattern);
				
				//Mulai timer untuk menghitung durasi
				start = clock();
				
				cout << endl << "==================" << endl << endl;

				//KMP
				int res = KMP(pattern, target); 
				if (res > 0){
					int lineTarget = findLine(res, fileName) ; 
					cout << "Kata kunci ditemukan pada :" << endl ;
					cout << "index :" << res << endl;
					cout << "line : " << lineTarget << endl;
				} else
					cout << "Kata kunci '" << pattern << "' tidak ditemukan" << endl;
				
				// menghentikan timer
				end = clock();
				
				//prints clock test
				cout <<  "Durasi : " << ((float)end - start)/CLOCKS_PER_SEC << " detik" << endl;
				cout << "---------------------------------" << endl;
				cout << "Jalankan lagi ? (y/n) "; cin >> answer;
				cin.ignore();
			}
		}
	}	
	return 0;
}