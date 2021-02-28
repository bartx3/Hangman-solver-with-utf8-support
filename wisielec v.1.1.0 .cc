//Autor: bartx3

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits.h>
#include <assert.h>
#include <wchar.h>


using namespace std;

//Niektóre funkcje nieużywane. Napisałem je, by ewentualnie kiedyś użyć

#include <windows.h>
#include <locale>

void settogoodconsole()
{
    setlocale(LC_ALL, "xx_XX.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
}

vector <string> matches;

const long long codes[60] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488};

fstream dic;


class utf8string
{
private:

    vector <unsigned long long> contents;
    const unsigned long long X[6] = {1, 256, 65536, 16777216, 4294967296, 1099511627776};

public:

    unsigned long long & operator [] (int i)
    {
        return (contents[i]);
    }

    int size()
    {
        return (contents.size());
    }

    utf8string (string s)   //przy założeniu dobrego wejścia.
    {
        int rozm = s.size();
        for (int i = 0; i < rozm; i++)
        {
            if (s[i] >= 0)
            {
                unsigned long long kod = s[i];
                contents.push_back(kod);
            }
            else if (s[i] >= -4)    //1111110x
            {
                unsigned long long kod = ((256+s[i])*X[5]+ (256+s[i+1])*X[4] + (256+s[i+2])*X[3] + (256+s[i+3])*X[2] + (256+s[i+4])*X[1] + (256+s[i+5]));
                contents.push_back(kod);
                i+=5;
            }
            else if (s[i] >= -8)    //111110xx
            {
                unsigned long long kod = ((256+s[i])*X[4]+ (256+s[i+1])*X[3] + (256+s[i+2])*X[2] + (256+s[i+3])*X[1] + (256+s[i+4]));
                contents.push_back(kod);
                i+=4;
            }
            else if (s[i] >= -16)   //11110xxx
            {
                unsigned long long kod = ((256+s[i])*X[3]+ (256+s[i+1])*X[2] + (256+s[i+2])*X[1] + (256+s[i+3]));
                contents.push_back(kod);
                i+=3;
            }
            else if (s[i] >= -32)   //1110xxxx
            {
                unsigned long long kod = ((256+s[i])*X[2]+ (256+s[i+1])*X[1] + (256+s[i+2]));
                contents.push_back(kod);
                i+=2;
            }
            else                    //110xxxxx
            {
                unsigned long long kod = ((256+s[i])*X[1]+ (256+s[i+1]));
                contents.push_back(kod);
                i+=1;
            }
        }
    }
};

string tochars (unsigned long long in)
{
    string answer;
    unsigned long long h = 2*2*2*2*2*2*2*2;
    unsigned long long l = h * h * h * h * h;
    bool b = false;
    for (int i = 0; i < 6; i++)
    {
        char c = in/l;
        if (c != 0 || b == true)
        {
            answer = answer + c;
            b = true;
        }
        l/=h;
    }
    return answer;
}


class letter
{
public:
    unsigned long long character;
    bool used;
    vector <long long> match_codes;
    letter (int i)
    {
        for (int i1 = 0; i1 < i; i1++)
            match_codes.push_back(0);
    }
};

vector <letter> letters;

int max (vector <int> V)
{
    int m = V[0];
    int s = V.size();
    for(int i = 1; i < s; i++)
        m = max(m, V[i]);
    return m;
}

int min (vector <int> V)
{
    int m = V[0];
    int s = V.size();
    for(int i = 1; i < s; i++)
        m = min(m, V[i]);
    return m;
}

int min (int *A, int a_size)
{
    int m = A[0];
    for(int i = 1; i < a_size; i++)
        m = min(m, A[i]);
    return m;
}

int max_value_for (vector <int> V)
{
    int s = V.size();
    if (s == 0)
        return (-1);
    else
    {
        int value = V[0];
        int number = 0;
        for (int i = 1; i < s; i++)
        {
            if (value < V[i])
            {
                number = i;
                value = V[i];
            }
        }
        return number;
    }
}

bool vector_search (vector<string> V, string t)
{
    int j = V.size();
    for (int i = 0; i < j; i++)
    {
        if (V[i]==t)
        {
            return true;
        }
    }
    return false;
}

int min_value_for (vector <int> V)
{
    int s = V.size();
    if (s == 0)
        return (-1);
    else
    {
        int value = V[0];
        int number = 0;
        for (int i = 1; i < s; i++)
        {
            if (value > V[i])
            {
                number = i;
                value = V[i];
            }
        }
        return number;
    }
}

void show ()
{
    cout << "\n" << "   ";
    for (int i = 0; i < letters.size(); i++)
        cout << tochars(letters[i].character)<<" ";
    for (int j = 0; j < matches.size(); j++)
    {
        cout << "\n";
        cout << matches[j]<<" ";
        for (int i = 0; i < letters.size(); i++)
            cout << letters[i].match_codes[j]<< " ";
    }
}

void gen_codes ()                       //spisuje dla każdego słowa, kod, będący 64-bitowym intem, podający, gdzie jest dana litera.
{
    int l = matches.size();
    for (int i = 0; i < l; i++)
    {
        utf8string univ (matches[i]);
        int l2 = univ.size();

        for (int i0 = 0; i0 < l2; i0++)
        {
            int l3 = letters.size();
            int i1;
            for (i1 = 0; i1 < l3; i1++)
            {
                if (univ[i0] == letters[i1].character)
                {
                    letters[i1].match_codes[i]+=codes[i0];
                    break;
                }
            }
            if (i1 == l3)
            {
                letter let (matches.size());
                let.character = univ[i0];
                let.match_codes[i]+=codes[i0];
                letters.push_back(let);
            }
        }
    }
}

long long differences (string state1, string state2)        //sprawdza różnice stanu i odpowiednio wyznacza kod słów, które spełniają warunek
{
    utf8string univ1(state1);
    utf8string univ2(state2);

    int length = univ1.size();

    if (univ2.size() == length)
    {
        long long x = 0;
        for (int i = 0; i < length; i++)
        {
            if (univ1[i] != univ2[i])
            {
                x += codes[i];
            }
        }
        return x;
    }
    else
        return -1;
}

void step_part2 (int c, long long kod)
{
    int l = matches.size();
    vector <vector <long long> > new2 (letters.size());
    vector <string> new1;

    for (int i = 0; i < l; i++)
    {
        if (letters[c].match_codes[i] == kod)
        {
            new1.push_back(matches[i]);
            for (int j = 0; j < letters.size(); j++)
            {
                new2[j].push_back(letters[j].match_codes[i]);
            }
        }
    }

    matches = new1;

    for (int j = 0; j < letters.size(); j++)
    {
        letters[j].match_codes = new2[j];
    }

}

int step_part1()                       //wyznacza na podstawie tego, która litera najlepiej ograniczy ilość słów w puli, dla pesymistycznego przypadku.
{
    int l = matches.size();
    vector <int> MAX_SAME_SET (letters.size());

    for (int i = 0; i < letters.size(); i++)
    {
        if (letters[i].used==false)
        {
            vector <long long> SET;
            vector <int> SET_counter;

            for(int j = 0; j < l; j++)
            {
                int k;
                int rozm = SET.size();

                for (k = 0; k < rozm; k++)
                {
                    if (SET[k] == letters[i].match_codes[j])
                    {
                        SET_counter[k]++;
                        break;
                    }
                }

                if (k == rozm)
                    {
                        SET.push_back(letters[i].match_codes[j]);
                        SET_counter.push_back(1);
                    }
            }

            MAX_SAME_SET[i] = max(SET_counter);
        }
        else
        {
            MAX_SAME_SET[i] = INT_MAX;
        }
    }
    return (min_value_for(MAX_SAME_SET));
}

int main()
{
    settogoodconsole();
    dic.open("slowaw.txt", ios::in);
    string state, s;

    getline(cin, state);

    bool b = true;     //upewnienie, że same _ dostałem

    int y = state.size();
    for (int x = 0; x < y; x++)
    {
        if (state[x] != '_')
        {
            b = false;
            break;
        }
    }
    assert (b);

    int l = state.size();

    if (!dic.good())
        return (-1);

    while (!dic.eof() && getline(dic, s))
    {
        utf8string u(s);
        if (u.size() == l)
        {
            for (int i = 0; i < l; i++)
                s[i] = tolower(s[i]);                   // Będzie to kolejną funkcją do przerobienia przy utf-8
            matches.push_back(s);
        }
    }

    dic.close();

    cout << "słownik załadowany" << "\n";

    gen_codes();

    cout << "przygotowano mozliwości"<<"\n";

    for (int i = 0; i < letters.size(); i++)
        letters[i].used = false;

    int steps = 0;

    while (matches.size()>1)
    {
        int c = step_part1();
        cout << tochars(letters[c].character);cout << endl;
        string state0 = state;
        getline(cin, state);
        int y = state.size();
        for (int x = 0; x < y; x++)
        {
            state[x] = tolower(state[x]);           // kolejny tolower
        }
        step_part2(c, differences(state0, state));

        letters[c].used = true;
        steps++;
        if (matches.size() <= 100)
        {
            for (int i = 0; i < matches.size(); i++)
            {
                for (int j = i+1; j < matches.size(); j++)
                {
                    if (matches[i]==matches[j])
                    {
                        matches.erase(matches.begin()+j);
                        for (int z = 0; z < letters.size(); z++)
                        {
                            letters[z].match_codes.erase(letters[z].match_codes.begin()+j);
                        }
                        i--;
                        j--;
                    }
                }
            }
        }
    }
    if (matches.size() == 1)
    {
        cout << matches[0]<<"\n"
        <<steps<<" wymaganych krokow."<<"\n"
        <<matches[0].size()<<" ";
    }
    else
    {
        cout << "Nie ma w slowniku." << "\n";
    }

    return 0;
}

