#include <iostream>

using namespace std;
class DinString
{
private:
        int duzina;
        char *text;
public:
        DinString(){duzina = 0; text = NULL;}
        DinString(const char ulaz[])
        {
            duzina = 0;
            while (ulaz[duzina] != '\0')
            {
                duzina++;
            }
            text = new char [duzina + 1];
            for(int i = 0; i < duzina; i++)
            {
                text[i] = ulaz[i];
            }
            text[duzina] = '\0';
        }
        DinString(const DinString &ds)
        {
            duzina = ds.duzina;
            text = new char [duzina + 1];
            for(int i = 0; i < duzina; i++)
            {
                text[i] = ds.text[i];
            }
            text[duzina] = '\0';
        }
        ~DinString(){ delete[] text;}

        int length() const {return duzina;}
        char& operator[] (int i){return text[i];}
        char operator[] (int i) const {return text[i];}

        DinString& operator=(const DinString &ds)
        {
            if(this != &ds) {
            delete[] text;
            duzina = ds.duzina;
            text = new char[duzina + 1];
            for (int i = 0; i < duzina; i++)
            {
                text[i] = ds.text[i];
            }
            text[duzina] = '\0';
        }
            return *this;
        }
        DinString& operator+=(const DinString &ds)
        {
            int i;
            char *tempText = new char[duzina + ds.duzina + 1];
            for (i = 0; i < duzina; i++)
            {
                 tempText[i] = text[i];
            }
            for (i = 0; i < ds.duzina; i++)
            {
                tempText[duzina + i] = ds.text[i];
            }
            tempText[duzina + ds.duzina] = '\0';
            duzina += ds.duzina;
            delete[] text;
            text = tempText;

            return *this;
        }

        friend bool operator==(const DinString &ds1, const DinString &ds2)
        {
            if(ds1.duzina != ds2.duzina)
            {
                return false;
            }
            for(int i = 1; i < ds1.duzina; i++)
            {
                if(ds1.text[i] != ds2.text[i])
                {
                    return false;
                }
            }
        }
        friend bool operator!=(const DinString &ds1 , const DinString &ds2)
        {
            if(ds1.duzina != ds2.duzina)
            {
                return true;
            }
            for(int i = 1; i < ds1.duzina; i++)
            {
                if(ds1.text[i] != ds2.text[i])
                {
                    return true;
                }
            }
        }
        friend DinString operator+(const DinString &ds1, const DinString &ds2)
        {
            DinString temp;
            temp.duzina = ds1.duzina + ds2.duzina;
            temp.text = new char[temp.duzina + 1];
            int i;
            for(i = 0; i < ds1.duzina; i++)
            {
                temp.text[i] = ds1.text[i];
            }
            for(i = 0; i < ds2.duzina; i++)
            {
                temp.text[ds1.duzina + i] = ds2.text[i];
            }
            temp.text[temp.duzina] = '\0';
            return temp;
        }

        friend ostream& operator<<(ostream &out, const DinString &ds)
        {
            if(ds.duzina > 0)
            {
                cout<<ds.text;
            }
            return out;
        }
};
template <class T>
class List{
	private:
		struct listEl{
			T content;
			struct listEl* next;
		};
		listEl *head;
		listEl *tail;
		int noEl;

	public:
		List(){
			head=tail=NULL;
			noEl=0;
		}

		List(const List<T>&);

		List<T>& operator=(const List<T>&);

		virtual ~List();

		int size() const { return noEl; }

		bool empty() const { return head == NULL ? 1 : 0; }

		bool add(int, const T&);

		bool remove(int);

		bool read(int, T&)const;

		void clear();
};


template <class T>
ostream& operator<<(ostream& out, const List<T>& rl) {
	out << endl;
	out << "--------" << endl;
	for(int i = 1; i <= rl.size(); i++){
		if(i != 1) out << ", ";
		T res;
		rl.read(i, res);
		out << res;
	}
	out << endl << "--------" << endl;
	return out;
}

template <class T>
List<T>::List(const List<T>& rl) {
	head = NULL;
	tail = NULL;
	noEl = 0;

	for(int i = 1; i <= rl.noEl; i++){
		T res;
		if(rl.read(i, res))
			add(i, res);
	}
}

template <class T>
List<T>& List<T>::operator=(const List<T>& rl) {
	if(this != &rl) {
		clear();
		head = NULL;
		tail = NULL;
		noEl = 0;

		for(int i = 1; i <= rl.noEl; i++){
			T res;
			if(rl.read(i, res))
				add(i, res);
		}
	}
	return *this;
}

template <class T>
List<T>::~List() {
	while(!empty())
		remove(1);
}

template <class T>
bool List<T>::add(int n, const T& newContent) {
	if(n < 1 || n > noEl + 1)
		return false;
	else {
		listEl* newEl = new listEl;
		if(newEl == NULL)
			return false;
		else {
			newEl->content = newContent;
			if(n == 1) {
				newEl->next = head;
				head = newEl;
			} else if(n == noEl + 1) {
				newEl->next = NULL;
				tail->next = newEl;
			} else {
				listEl* temp = head;
				for(int i = 2; i < n; i++)
					temp = temp->next;
				newEl->next = temp->next;
				temp->next = newEl;
			}
			noEl++;
			if(newEl->next == NULL)
				tail = newEl;
			return true;
		}
	}
}

template <class T>
bool List<T>::remove(int n){
	if(n < 1 || n > noEl)
		return false;
	else {
		if(n == 1) {
			listEl* del = head;
			head = head->next;
			if(tail == del)
				tail = NULL;
			delete del;
			noEl--;
		} else {
			listEl* temp = head;
			for(int i = 2; i < n; i++)
				temp = temp->next;
			listEl* del = temp->next;
			temp->next = del->next;
			if(tail == del)
				tail = temp;
			delete del;
			noEl--;
		}
		return true;
	}
}

template <class T>
bool List<T>::read(int n,T& retVal) const {
	if(n < 1 || n > noEl)
		return false;
	else {
		if(n == 1)
			retVal = head->content;
		else if(n == noEl)
			retVal = tail->content;
		else {
			listEl* temp = head;
			for(int i = 1; i < n; i++)
				temp = temp->next;
			retVal = temp->content;
		}
		return true;
	}
}

template <class T>
void List<T>::clear()
{
	while(!empty())
		remove(1);
}
class Osoba
{
protected:
    DinString Ime;
    DinString Prezime;
public:
    Osoba(){Ime = "Iva"; Prezime = "Bojanic";}
    Osoba(DinString i, DinString p){Ime = i; Prezime = p;}
    Osoba(const Osoba &O){Ime = O.Ime; Prezime = O.Prezime;}

    virtual void ispisi()=0;
};
class Student : public Osoba
{
private:
    int brojIndeksa;
public:
    Student(){brojIndeksa = 123; Ime = "Iva"; Prezime = "Bojanic";}
    Student(int b, DinString i, DinString p){brojIndeksa = b; Ime = i; Prezime = p;}
    Student(const Student &S){brojIndeksa = S.brojIndeksa; Ime = S.Ime; Prezime = S.Prezime;}

    void ispisi()
    {
        cout<<Ime<<","<<Prezime<<","<<brojIndeksa<<endl;
    }

};
class Profesor : public Osoba
{
private:
    DinString predmet;
public:
    Profesor(){predmet = "Matematika"; Ime = "Iva"; Prezime = "Bojanic";}
    Profesor(DinString t, DinString i, DinString p){predmet = t; Ime = i; Prezime = p;}
    Profesor(const Profesor &P){predmet = P.predmet; Ime = P.Ime; Prezime = P.Prezime;}

    void ispisi()
    {
        cout<<Ime<<","<<Prezime<<","<<predmet<<endl;
    }
};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
