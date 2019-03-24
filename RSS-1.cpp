/*
Without Sorting.
Algoritma dan Struktur Data membuat program Round-Robin Schedulling
Menggunakan implementasi linked list dengan menggunakan bahasa Cpp
*/
#include <iostream>
#include <stdlib.h>
using namespace std;

#define boolean int
#define true 1
#define false 0

#define Nil NULL
typedef int infotype;
typedef struct TElmtList * address;
typedef struct TElmtList{
	infotype quanta; /*Untuk Menyimpan Info Quanta didalam elemen P pada sebuah List L yang mempunyai Type Data Int */
	char infoname; /*Untuk Menyimpan Info Nama elemen P pada sebuah List L yang mempunyai Type Data Char */
	address next; /*Alamat Elemen Selanjutnya yang bertipe Address*/
}ElmtList;

typedef struct{
	address first; /*Alamat Elemen pertama pada List L*/
}List;

#define InfoQ(P) (P)->quanta
#define InfoN(P) (P)->infoname
#define Next(P) (P)->next
#define First(L) (L).first

boolean IsEmpty (List L){
/*Mengirimkan True jika List Kosong dan false jika list Tidak Kosong*/

	return (First(L) == Nil);
}

void CreateEmpty (List *L){
/*I.S. List Sembarang*/
/*F.S. List Menjadi Kosong*/

	First(*L) = Nil;
}

address Alokasi (infotype X,char Y){
/*Membuat List Baru dengan isi List yaitu Data (char)*/
/*dan Quanta(Int) serta alamat elemen selanjutnya adalah Nil.*/
/*F.S. Mengirimkan alamat elemen yang sudah diAlokasi*/

	address P;
	P = (address) malloc (sizeof(ElmtList));
	if (P != Nil){
		InfoQ(P) = X;
		InfoN(P) = Y;
		Next(P) = Nil;
		return P;
	}

}

void Dealokasi (address *P){
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

	free(*P);
}


void InsertVFirst (List *L, infotype X, char Y){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */

	address P, Prec;
	P = Alokasi(X,Y);
	Prec = First(*L);
	if (P != Nil){
		Next(P) = First(*L);
		if (IsEmpty(*L)){
			Next(P) = P;
			First(*L) = P;
		}
		else{
			while (Next(Prec) != First(*L)){
				Prec = Next(Prec);
			}
			Next(Prec) = P;
		}
		First(*L) = P;
	}
}


void PrintList(List L){
	/* Mencetak Data Quanta dan membuat table */

	address P;
	P = First(L);
	cout<<"Data : \n"<<endl;
	cout<<"+------------------+---------------+\n"<<endl;
	cout<<"|\tData\t   |\tQuanta\t   |\n"<<endl;
	cout<<"+------------------+---------------+\n"<<endl;
	if (IsEmpty(L)){

	}
	else{
		while (Next(P) != First(L)){
		cout<<"|\t " << InfoN(P)<< "\t   |"<<"\t "<< InfoQ(P) <<"   \t   |\n";
			P = Next(P);
		}
		cout<<"|\t " << InfoN(P)<< "\t   |"<<"\t "<< InfoQ(P) <<"   \t   |\n";
	}
	cout<<"+------------------+---------------+\n"<<endl;
}


address SearchPrec (List L){
/*Prec adalah address elemen sebelum P */
/*Jika Quanta <= 0 berada pada First L, maka mengirimkan Address Prec yaitu address Elemen Terakhir*/
/*F.S. Mengirimkan address Prec */

	address P;
	address Prec;
	P = Prec = First(L);
	while (Next(Prec) != First(L)){
		Prec = Next(Prec);
	}

	while (Next(P) != First(L)){
		if (InfoQ(P) <= 0){
			return Prec;
		}
		Prec = P;
		P = Next(P);
	}
	return Prec;
}


void DeleteVFirst (List *L, infotype * X){
	/* Melakukan penghapusan jika element <= 0 dari List dan Dealokasi */

	address P,Q;
	P = Q = First(*L);
	*X = InfoQ(P);
	if(Next(P) == P){
		First(*L) = Nil;
	}
	else{
		while(Next(P)!=First(*L))
			P = Next(P);
		First(*L) = Next(P) = Next(First(*L));
	}
	Dealokasi(&Q);
}


void Dispose (List *L, address *P){
	/* Menghapus element yang kosong atau quanta habis */

	address Q;
	infotype X;
	Q = SearchPrec(*L);
	if ((Next(*P) == *P) && (InfoQ(*P)<=0)){
		*P = First(*L);
		X = InfoQ(*P);
		First(*L) = Nil;
		Dealokasi(P);
	}
	else if (InfoQ(First(*L))<=0){
		DeleteVFirst(L,&X);
	}
	else{
		*P = Next(Q);
		X = InfoQ(*P);
		Next(Q) = Next(Next(Q));
		Next(*P) = Nil;
	}

}


void RoundRobin (List *L, address *P, infotype Quantum){
	/* Melakukan proses round robin dengan melakukan pengurangan quanta */
	/* Jika nilai quanta <= 0 maka akan di hapus dari list */
	/* Perpindahan dari suatu element ke element lain disebut switch */
	/* Menjumlahkan seluruh quantum setelah proses round robin selesai */
	/* Menampilkan seluruh proses */

	int TotalQuantum = 0;
	int Switch = 1;
	address Q;
	*P = First(*L);
	cout<<"Proses >> \n"<<endl;
	cout<<"+---------------+---------------+\n"<<endl;
	cout<<"|Data\t\t|\tQuantum\t|\n"<<endl;
	cout<<"+---------------+---------------+\n"<<endl;
	while(!IsEmpty(*L)){
		if (Next(*P) == *P){
				if(InfoQ(*P) > 0){
				cout<<"|  "<< InfoN(*P)<<"\t\t";
				cout<<"|  \t"<<Quantum<<"\t|";
				cout<< " "<<InfoN(*P)<<" : ";
				InfoQ(*P)-= Quantum;
				cout<<"  = "<< InfoQ(*P);
				if (InfoQ(*P)<=0){
					cout<<". Dispose "<<InfoN(*P)<<"\n" ;
					Q = *P;
					Dispose(L,&Q);
				}
				else{
					cout<<"\n"<<endl;
				}

			}
			TotalQuantum += Quantum;
		}
		else if(P != Nil){
			cout<<"|  "<< InfoN(*P)<<"\t\t";
			cout<<"|  \t"<< Quantum<<"\t| ";
			cout<<" "<< InfoN(*P)<<" : ";
			InfoQ(*P)-= Quantum;
			cout<<"  = "<< InfoQ(*P);
			if(InfoQ(*P)>0){
				cout<<"\n";
				cout<<"| Switch \t| \t"<<Switch<<" \t|\n";
				*P = Next(*P);
			}
			else {
				cout<<". Dispose "<<InfoN(*P)<<"\n";
				cout<<"| Switch \t| \t"<<Switch<<" \t|\n";
				Q = *P;
				*P = Next(*P);
				Dispose(L,&Q);
			}
		TotalQuantum += Quantum + Switch;
		}
	}
	cout<<"+---------------+---------------+\n";
	cout<<"|Total Quantum  : \t"<< TotalQuantum<<"\t|\n";
    cout<<"+---------------+---------------+\n";

}


int main (){
	cout<<"\t==================================================================="<<endl;
	cout<<"\t\t\t    Round-Robin Schedulling\n"<<endl;
	cout<<"\t\t\t  Algoritma dan Struktur Data\n"<<endl;
	cout<<"\t===================================================================\n\n\n"<<endl;

	int i, N, Quantum, Quanta;
	address P;
	char Data;
	List L;
	CreateEmpty(&L);

	cout<<"Jumlah data minimal adalah 5!\n\n"<<endl;
	do{
  		cout<<"Jumlah Data \t\t: ";
  		cin>> N;
  		if (N >= 3){
   			cout<<"Quantum Per Proses\t: ";
   			cin>>Quantum;
   			cout<< "\n" <<endl;
    for (i=1; i<=N; i++){
            cout<<"Simpul #"<<i<<endl;
    		cout<<"Data #"<<i<<" : ";
    		cin>>Data;
    		cout<<"Quanta #"<< i<<" : ";
    		cin>>Quanta;
    		cout<<endl;
    	InsertVFirst(&L, Quanta, Data);
    	}
    	PrintList(L);
    	}
    else{
   		cout<<"Jumlah minimal Data adalah 5\nSilahkan input ulang\n\n"<<endl;
    }
}   while(N < 3);
    RoundRobin(&L,&P,Quantum);
    return 0;

}
