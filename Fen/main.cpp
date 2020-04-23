#include <iostream>

using namespace std;
class Abs
{
public:
    virtual int getTemperatura()const = 0;
    virtual void setTemperatura(int) = 0;
};
class Grejac : public Abs
{
protected:
    int temperatura;
public:
    Grejac(){temperatura = 0;}
    Grejac(int t)
    {
        if(t >= 100)
        {
            temperatura = 100;
        }else if(t <= 0)
        {
            temperatura = 0;
        }else
            temperatura = t;
    }
    Grejac(const Grejac &g){temperatura = g.temperatura;}

    int getTemperatura()const
    {
        return temperatura;
    }
    void setTemperatura(int temp)
    {
        if(temp >= 0 && temp <= 100)
        {
            temperatura = temp;
        }
    }
};
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
enum Modovi {HLADNO,TOPLO};
class Fen
{
private:
    DinString marka;
    Modovi mod;
    Grejac grejac;
public:
    Fen(DinString m, Modovi mm, int t)
    {
        marka = m;
        mod = mm;

        if(mod == HLADNO)
        {
            grejac.setTemperatura(0);
        }else
            grejac.setTemperatura(1);
    }
    Fen(const Fen &f): grejac(f.grejac){marka = f.marka; mod = f.mod;}
    DinString getMarka(){return marka;}
    Modovi getMod(){return mod;}
    Grejac getGrejac()const{return grejac;}

    void setMod(Modovi m)
    {
        if(mod == HLADNO && m == TOPLO)
        {
            grejac.setTemperatura(1);
        }else if(mod == TOPLO && m == HLADNO)
        {
            grejac.setTemperatura(0);
        }
        mod = m;
    }
    void setMarka(DinString m){marka = m;}
    void setTemperatura(int t)
    {
        if(t >= 1)
        {
            if(mod == TOPLO)
            {
                grejac.setTemperatura(t);
            }
        }
    }

};
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
