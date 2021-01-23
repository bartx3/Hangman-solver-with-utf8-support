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

vector <wstring> matches;

const long long codes[60] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296, 8589934592, 17179869184, 34359738368, 68719476736, 137438953472, 274877906944, 549755813888, 1099511627776, 2199023255552, 4398046511104, 8796093022208, 17592186044416, 35184372088832, 70368744177664, 140737488355328, 281474976710656, 562949953421312, 1125899906842624, 2251799813685248, 4503599627370496, 9007199254740992, 18014398509481984, 36028797018963968, 72057594037927936, 144115188075855872, 288230376151711744, 576460752303423488};

wfstream dic;

class letter
{
public:
    wchar_t character;
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

bool vector_search (vector<wstring> V, wstring t)
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
        cout << char(letters[i].character)<<" ";
    for (int j = 0; j < matches.size(); j++)
    {
        cout << "\n";
        wcout << matches[j]<<" ";
        for (int i = 0; i < letters.size(); i++)
            cout << letters[i].match_codes[j]<< " ";
    }
}

void gen_codes ()                       //spisuje dla każdego słowa, kod, będący 64-bitowym intem, podający, gdzie jest dana litera.
{
    int l = matches.size();
    for (int i = 0; i < l; i++)
    {
        int l2 = matches[i].size();

        for (int i0 = 0; i0 < l2; i0++)
        {
            int l3 = letters.size();
            int i1;
            for (i1 = 0; i1 < l3; i1++)
            {
                if (matches[i][i0] == letters[i1].character)
                {
                    letters[i1].match_codes[i]+=codes[i0];
                    break;
                }
            }
            if (i1 == l3)
            {
                letter let (matches.size());
                let.character = matches[i][i0];
                let.match_codes[i]+=codes[i0];
                letters.push_back(let);
            }
        }
    }
}

long long differences (wstring state1, wstring state2)        //sprawdza różnice stanu i odpowiednio wyznacza kod słów, które spełniają warunek
{
    int length = state1.size();

    if (state2.size() == length)
    {
        long long x = 0;
        for (int i = 0; i < length; i++)
        {
            if (state1[i] != state2[i])
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
    vector <wstring> new1;

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
    dic.open("slowa.txt", ios::in);
    wstring state, s;

    getline(wcin, state);

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
        if (s.size() == l)
        {
            for (int i = 0; i < l; i++)
                s[i] = tolower(s[i]);
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
        wcout << wchar_t(letters[c].character);cout << endl;
        wstring state0 = state;
        getline(wcin, state);
        int y = state.size();
        for (int x = 0; x < y; x++)
        {
            state[x] = tolower(state[x]);
        }
        step_part2(c, differences(state0, state));
        letters[c].used = true;
        steps++;
        if (matches.size() <= 20)
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
        //show();
    }
    if (matches.size() == 1)
    {
        wcout << matches[0]<<"\n"
        <<steps<<" wymaganych krokow."<<"\n"
        <<matches[0].size();
    }
    else
    {
        wcout << "Nie ma w slowniku." << "\n";
    }

    return 0;
}

