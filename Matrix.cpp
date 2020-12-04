
#include<iostream>
#include<math.h>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include<sstream>
#include<ctime>
#include<iomanip>
using namespace std;
template<typename T>
class Matrix
{
public:
	void setCol(int col);
	//Matrise ait sutunun seti
	void setRow(int row);
	//Matrise ait satirin seti
	int getCol();
	//Matrise ait sutunun geti
	int getRow();
	//Matrise ait satırınseti
	Matrix();
	//10*10 girişli Matris constructor
	Matrix(int, int);
	//r*c girişli Matris constructor
	Matrix(int, int, T);
	//r*c ve int girişli Matris constructor
	Matrix(int, int, char);
	//char değerine göre random veya birim matris
	void setij(int, int, T);
	//ij değerlerinin set methodu
	T getij(int, int);
	//ij değerlerinin get methodu
	void print();
	//Matrix yazma methodu
	void print(const char*);
	//Matrixi dosyaya yazma methodu
	void resize(int, int);
	//Matrix Boyutlandırma Methodu
	void emul(Matrix&);
	//Eleman düzeyinde çarpım
	int determinant(Matrix&, double);
	//determinant methodu
	Matrix transpoze();
	//Matrixin transpoz methodu
	Matrix inverse();
	//Matrix tersinin methodu
	Matrix operator+(Matrix&);
	//Matrixi başka matris ile toplama operatörü
	Matrix operator-(Matrix&);
	//Matrix başka matris ile çıkarma operatörü
	Matrix operator*(Matrix&);
	//Matrix başka matris ile çarpma operatörü
	Matrix operator+(T);
	//Matrisi sayı ile topla
	Matrix operator-(T);
	//Matrisi sayı ile çıkar
	Matrix operator*(T);
	//Matrisi sayı ile çarp
	Matrix operator/(T);
	//Matrisi sayı ile böl
	Matrix operator%(T);
	//Matrisi sayı ile modunu al
	Matrix operator^(int);
	//Matrisi sayı ile üs al
	~Matrix();
	//deconstructor
protected:
	T** Array;
	//İki Boyutlu Matris Dizisi
	int row;
	//Satir
	int col;
	//Sutun
};
template<typename T>
class Table :public Matrix<T>
{
public:
	Table();
	//Table constructoru
	Table(int, int, T);
	Table(int, int, char);
	T itemAt(int, int);
	T itemAt(string);
	//İçinde satir sutunu birleşik yazılmış string
	T itemAt(string, string);
	//İçinde satir sutunu ayrı yazılmış string
	void print();
	void setRowName(string*, T);
	//Satir ismini değiştirmek için alınan string methodu
	void setColName(string*, T);
	//Sutun ismini değiştirmek için alınan string methodu
	~Table();
private:
	T* tm;
	//tek boyutlu satir ve sutun için dizi
	string* rowName;
	string* colName;
};
template<typename T>
void Matrix<T>::setRow(int row) {
	this->row = row;
}
template<typename T>
int Matrix<T>::getRow() {
	return this->row;
}
template<typename T>
void Matrix<T>::setCol(int col) {
	this->col = col;
}
template<typename T>
int Matrix<T>::getCol() {
	return col;
}
template<typename T>
Matrix<T>::Matrix()
{
	col = 10;
	row = 10;
	Array = new int* [row];
	for (int i = 0; i < row; i++) {
		Array[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			Array[i][j] = 0;
		//tüm satir ve sutunların içerğini sıfır yapar
	}
}
template<typename T>
Matrix<T>::Matrix(int r, int c)
{
	int counter = 0;
	this->row = r;
	this->col = c;
	this->Array = new int* [row];
	for (int i = 0; i < row; i++) {
		Array[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Array[i][j] = counter++;
		}
	}
}
template<typename T>
Matrix<T>::Matrix(int r, int c, T x)
{
	this->row = r;
	this->col = c;
	this->Array = new int* [row];
	for (int i = 0; i < row; i++) {
		Array[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Array[i][j] = x;
			//satir ve sutun içeriğini istenilen sayı ile doldurur
		}
	}
}
template<typename T>
Matrix<T>::Matrix(int r, int c, char ch)
{
	row = r;
	col = c;
	Array = new int* [row];
	for (int i = 0; i < row; i++) {
		Array[i] = new int[col];
	}
	switch (ch) {
	case 'e':
		//birim matris için seçilen case
		if (row != col) {
			cout << "Birim Matris icin girdi hatasi
				alindi";
		}
		else {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++)
					if (i == j) {
						Array[i][j] = 1;
					}
					else {
						Array[i][j] = 0;
					}
			}
		}
		break;
	case 'r':
		//random matris için seçilen case
		int x;
		srand((unsigned int)time(NULL));
		//farklı sayı üretmek için kullanılan hazır fonksiyon
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				x = rand() % 10 + 0;
				Array[i][j] = x;
			}
		}
	}
}
template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix& rightObj)
{
	if (this->row == rightObj.row && this->col == rightObj.col)
	{
		Matrix Result(this->row, this->col);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				Result.Array[i][j] = this->Array[i][j]
				+ rightObj.Array[i][j]; //operatörün
			uygulandığı satır
		}
		return Result;
	}
	else {
		cout << "Matris boyutlari uyumsuz";
		//catch atıldı
	}
}
template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix& rightObj)
{
	if (this->col == rightObj.row) {
		Matrix Result(this->row, rightObj.col);
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < rightObj.col; j++) {
				for (int k = 0; k < this->col; k++) {
					Result.Array[i][j] += this -
				> Array[i][k] * rightObj.Array[k][j];
					//operatörün uygulandığı satır
				}
			}
		}
		return Result;
	}
	else {
		cout << "Matris boyutlari uyumsuz";//catch atıldı
	}
}
template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix& rightObj)
{
	if (this->row == rightObj.row && this->col == rightObj.col)
	{
		Matrix Result(this->row, this->col);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				Result.Array[i][j] = this->Array[i][j]
				- rightObj.Array[i][j]; //operatörün
			uygulandığı satır
		}
		return Result;
	}
	else {
		cout << "Matris boyutlari uyumsuz";
		//catch atıldı
	}
}
template<typename T>
Matrix<T> Matrix<T>::operator+(T number)
{
	Matrix Result(this->row, this->col);
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++)
			Result.Array[i][j] = this->Array[i][j] +
			number;
		//operatörün uygulandığı satır
	}
	return Result;
}
template<typename T>
Matrix<T> Matrix<T>::operator -(T number)
{
	Matrix Result(this->row, this->col);
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++)
			Result.Array[i][j] = this->Array[i][j] -
			number;
		//operatörün uygulandığı satır
	}
	return Result;
}
template<typename T>
Matrix<T> Matrix<T>::operator*(T number)
{
	Matrix Result(this->row, this->col);
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++)
			Result.Array[i][j] = this->Array[i][j] *
			number;
		//operatörün uygulandığı satır
	}
	return Result;
}
template<typename T>
Matrix<T> Matrix<T>::operator/(T number)
{
	Matrix Result(this->row, this->col);
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++)
			Result.Array[i][j] = this->Array[i][j] /
			number;
		//operatörün uygulandığı satır
	}
	return Result;
}
template<typename T>
Matrix<T> Matrix<T>::operator%(T number)
{
	Matrix Result(this->row, this->col);
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++)
			Result.Array[i][j] = this->Array[i][j] %
			number;
		//operatörün uygulandığı satır
	}
	return Result;
}
template<typename T>
Matrix<T> Matrix<T>::operator^(int numb)
{
	Matrix Result(this->row, this->col);
	for (int i = 1; i < numb; i++) {
		for (int i = 0; i < this->row; i++) {
			for (int j = 0; j < this->col; j++) {
				for (int k = 0; k < this->col; k++) {
					Result.Array[i][j] += this -
				> Array[i][k] * this->Array[k][j];
					//operatörün uygulandığı satır
				}
			}
		}
	}
	return Result;
}
template<typename T>
Matrix<T> Matrix<T>::inverse()
{
	T x, y;
	int a = this->row;
	Matrix brm(a, a, 'e');
	for (int i = 0; i < a; i++) {
		x = Array[i][i];
		for (int j = 0; j < a; j++) {
			Array[i][j] = Array[i][j] / x;
			brm.Array[i][j] = brm.Array[i][j] / x;
		}
		for (int k = 0; k < a; k++) {
			if (k != i) {
				y = Array[k][i];
				for (int j = 0; j < a; j++) {
					Array[k][j] = Array[k][j] -
						(Array[i][j] * y);
					brm.Array[k][j] = brm.Array[k]
						[j] - (brm.Array[i][j] * y);
					//kofaktörün kullanıldığı satır
				}
			}
		}
	}
	return brm.Array;
	//dönen dizi
}
template<typename T>
Matrix<T> Matrix<T>::transpoze()
{
	this->row = row ^ col;
	//satırın set edildiği yer
	this->col = row ^ col;
	//sutunun set edildiği yer
	this->row = row ^ col;
	Matrix Result(this->row, this->col);
	int** temp = new int* [row];
	for (int i = 0; i < row; i++) {
		temp[i] = new int[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			temp[i][j] = this->Array[j][i];
		}
	}
	for (int i = 0; i < row; i++) {
		delete[] Array[i];
		//ana matrisin silinmesi
	}
	delete[] Array;
	Array = temp;
	//transpozun ana matrisin adresini alması
	Result.Array = Array;
	return Result;
}
template<typename T>
void Matrix<T>::emul(Matrix& rightObj)
{
	if (this->col == rightObj.col && this->row == rightObj.row) {
		for (int i = 0; i < this->col; i++) {
			for (int j = 0; j < this->row; j++)
				this->Array[i][j] = Array[i][j] *
				rightObj.Array[i][j];
			//operatörün uygulandığı satır
		}
		this->print();
	}
	else {
		cout << "-->Satir ve sutun sayilari esit degil<--" <<
			endl;
		//catch basıldı
	}
}
template<typename T>
int Matrix<T>::determinant(Matrix& orgObj, double sz)
{
	if (sz == 2) {
		return orgObj.Array[0][0] * orgObj.Array[1][1] -
			orgObj.Array[1][0] * orgObj.Array[0][1]; //2*2 lik
		matris için determinant
	}
	double det = 0;
	Matrix subMat(orgObj.row, orgObj.col);
	for (int x = 0; x < sz; x++) {
		int subi = 0;
		//alt matrisin satırı
		int subj = 0;
		//alt matrisin sutunu
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				if (j != x && i != 0) {
					subMat.Array[subi][subj] =
						orgObj.Array[i][j];
					subj++;
					if (subj == sz - 1)
					{
						subj = 0;
						subi++;
					}
				}
			}
		}
		det += pow(-1, x) * orgObj.Array[0][x] *
			determinant(subMat, sz - 1);//recursive
	}
	return det;
}
template<typename T>
void Matrix<T>::print(const char* dosyaAdi)
{
	ofstream dosya(dosyaAdi);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			dosya << Array[i][j] << " ";
		}
		dosya << endl;
	}
}
template<typename T>
void Matrix<T>::resize(int r, int c)
{
	Matrix Result(r, c);
	for (int i = this->row; i < r; i++) {
		//asıl matris satırına kadar basar
		for (int j = this->col; j < c; j++) {
			//asıl matris sutununa kadar basar
			for (int k = 0; k < this->row; k++) {
				//verilen fazla saturlar için
				for (int l = 0; l < this->col; l++) {
					//verilen fazla sutunlar için
					Result.Array[k][l] = Array[k]
						[l];
				}
			}
		}
	}
	Result.print();
}
template<typename T>
Table<T>::Table() : Matrix<T>(10, 10, 0)
{
	this->colName = new string[this->col];
	this->rowName = new string[this->row];
	for (int i = 0; i < this->row; i++)
		this->rowName[i] = std::to_string(i);
	// rownames[i];
	for (int j = 0; j < this->col; j++)
		this->colName[j] += char(j + 65);
	//colnames[j];
}
template<typename T>
Table<T>::Table(int r, int c, T x) : Matrix<T>(r, c, x)
{
	this->colName = new string[this->col];
	this->rowName = new string[this->row];
	for (int i = 0; i < this->row; i++)
		this->rowName[i] = std::to_string(i);
	for (int j = 0; j < this->col; j++)
		this->colName[j] += char(j + 65);
}
template<typename T>
Table<T>::Table(int r, int c, char ch) : Matrix<T>(r, c, ch)
{
	this->colName = new string[this->col];
	this->rowName = new string[this->row];
	for (int i = 0; i < this->row; i++)
		this->rowName[i] = std::to_string(i);
	//satirlar için i değerilerini stringe çevirir
	for (int j = 0; j < this->col; j++)
		this->colName[j] += char(j + 65);
	//sutunlar için i değerilerini stringe çevirir
}
template<typename T>
T Table<T>::itemAt(int r, int c)
{
	T item = this->getij(r, c);
	//method verilen r ve c değerleri için ana matristen sayi getirir
	return item;
}
template<typename T>
T Table<T>::itemAt(string loc)
{
	int cc = loc[0] - 65;
	//stringin ilk değerini ASCII e göre integera çevirir.
	int rc = loc[1] - 48;
	//stringin ikinci değerini ASCII e göre integera çevirir.
	T item = this->getij(rc, cc);
	return item;
}
template<typename T>
T Table<T>::itemAt(string loc1, string loc2)
{
	int cc = loc2[0] - 65;
	//stringin ilk değerini ASCII e göre integera çevirir.
	int rc = loc1[0] - 48;
	//stringin ikinci değerini ASCII e göre integera çevirir.
	T item = this->getij(rc, cc);
	return item;
}
template<typename T>
void Table<T>::print() {
	cout << " " << setw(4);
	for (int i = 0; i < this->col; i++) {
		cout << setw(4) << this->colName[i] << " ";
	}
	cout << endl;
	cout << "-----------------------------------------------------
		-- - " << endl;
		for (int i = 0; i < this->row; i++) {
			cout << this->rowName[i] << "> ";
			for (int j = 0; j < this->col; j++) {
				cout << setw(4) << this->getij(i, j) << " ";
			}
			cout << endl << endl;
		}
	cout << endl;
}
template<typename T>
void Table<T>::setColName(string* s, T a)
//verilen diziye göre isim değiştirir
{
	colName = new string[a];
	colName = s;
}
template<typename T>
Table<T>::~Table()
{}
template<typename T>
void Table<T>::setRowName(string* s, T a)
//verilen diziye göre isim değiştirir
{
	rowName = new string[a];
	rowName = s;
}
template<typename T>
void Matrix<T>::setij(int i, int j, T x)
{
	Array[i][j] = x;
}
template<typename T>
T Matrix<T>::getij(int i, int j) {
	return this->Array[i][j];
}
template<typename T>
void Matrix<T>::print()
{
	cout << endl;
	for (int i = 0; i < row; i++) {
		cout << " ";
		for (int j = 0; j < col; j++) {
			cout << Array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
template<typename T>
Matrix<T>::~Matrix() {}
int main()
{
	return 0;
}