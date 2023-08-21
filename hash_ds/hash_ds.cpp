#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <list>
#include <algorithm>
#include <set>

using namespace std;

string randomWord(int minlength, int maxlength)
{
    string letters = "abcdefghijklmnopqrstuvwxyz";
    string word = "";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> lengthDis(minlength, maxlength);
    uniform_int_distribution<> letterDis(0, 25);

    int length = lengthDis(gen);
    for (int i = 0; i < length; i++)
    {
        word += letters[letterDis(gen)];
    }
    return word;
}

vector<bool> sieveOfEratosthenes(int n)
{

    vector<bool> isPrimes(n + 1, true);
    isPrimes[0] = false;
    isPrimes[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (isPrimes[i])
        {
            for (int j = i * i; j <= n; j += i)
            {
                isPrimes[j] = false;
            }
        }
    }
    cout << "sieveOfEratosthenes" << endl;
    return isPrimes;
}

int findNextPrime(int num, const vector<bool> &isPrimes)
{
    int nextPrime = num;
    while (!isPrimes[nextPrime])
    {
        nextPrime++;
    }
    return nextPrime;
}

uint32_t murmurhash2(const char *key, int len, uint32_t seed)
{
    uint32_t h = seed;
    const uint32_t c1 = 0xcc9e2d51; // e
    const uint32_t c2 = 0x1b873593;

    int i;
    for (i = 0; i < len; i++)
    {
        uint32_t k = (uint32_t)key[i];
        k *= c1;
        k ^= k >> 17;
        k *= c2;
        h ^= k;
        h = (h << 13) ^ (h >> 19);
        h = h * 5 + 0xe6546b64; // d
    }

    return h;
}
// uint32_t fnv1a(const char *key, int len)
// {
//     uint32_t hash = 2166136261;
//     int i;
//     for (i = 0; i < len; i++)
//     {
//         hash = (hash * 16777619) ^ key[i];
//     }
//     return hash;
// }
int fnv1a(const char *key, int len)
{
    int hash = 2166136261;
    int i;
    for (i = 0; i < len; i++)
    {
        hash ^= key[i];
        hash *= 16777619;
    }

    return hash;
}

class HashTable
{
private:
    int tableSize;
    static vector<bool> isPrimes;
    // vector<string> table;

public:
    HashTable(int size)
    {
        if (isPrimes.empty())
            isPrimes = sieveOfEratosthenes(size + 2000);
        tableSize = findNextPrime(size, isPrimes);
        // table.resize(tableSize);
    }
    int hash1(string &word)
    {
        int hash = 0;
        // int prime = tableSize;
        for (int i = 0; i < word.length(); i++)
        {
            hash = (hash * 31 + word[i]) % tableSize;
        }
        if (hash < 0)
            hash += tableSize;

        return hash;
    }

    int hash2(string &word)
    {
        uint32_t h = murmurhash2((const char *)word.c_str(), word.length(), 0);
        // cout << h << endl;
        return h % tableSize;
    }

    int auxiliaryHash(string &word)
    {
        // int tableSize = getSize();
        // int hash = 0;
        // // int prime = tableSize;
        // for (int i = 0; i < word.length(); i++)
        // {
        //     hash = (hash * 37 + (int)word[i]) % tableSize;
        // }
        // // hash = (hash * 10 + 1) % tableSize;

        // if (hash < 0)
        // {
        //     hash += tableSize;
        // }

        // Perform an additional operation to further mix the bits
        // hash ^= (hash >> 16);
        // hash *= 0x85ebca6b;
        // hash ^= (hash >> 13);
        // hash *= 0xc2b2ae35;
        // hash ^= (hash >> 16);
        // return (hash % 2 == 0) ? hash + 1 : hash;
        int hash = fnv1a((const char *)word.c_str(), word.length());
        return hash % tableSize;
    }

    int getSize()
    {
        return tableSize;
    }
};

class chainHashTable : public HashTable
{
private:
    vector<list<pair<string, int>>> table;
    vector<bool> isOccupied;

    int chSize;
    int collision;
    int probe;

public:
    chainHashTable(int size) : HashTable(size)
    {
        chSize = 0;
        collision = 0;
        probe = 0;
        table.resize(getSize());
        isOccupied.resize(getSize(), false);
    }
    void p()
    {
        string s = "ami";
        cout << hash2(s) << endl;
    }

    void insert(string &word, int option)
    {
        if (find(word, option) != -1)
            return;
        probe = 0;
        int index = 0;
        if (option == 1)
            index = hash1(word);
        else
            index = hash2(word);

        table[index].push_back(make_pair(word, ++chSize));
        if (isOccupied[index])
            collision++;
        else
            isOccupied[index] = true;
    }

    int find(string word, int option)
    {
        int index = 0;
        if (option == 1)
            index = hash1(word);
        else
            index = hash2(word);
        for (auto it = table[index].begin(); it != table[index].end(); it++)
        {
            if (it->first == word)
            {
                return it->second;
            }
            probe++;
        }
        return -1;
    }

    void Delete(string &word, int option)
    {
        int index = 0;
        if (option == 1)
            index = hash1(word);
        else
            index = hash2(word);
        for (auto it = table[index].begin(); it != table[index].end(); it++)
        {
            if (it->first == word)
            {
                table[index].erase(it);
                chSize--;
                return;
            }
        }
    }

    int getCollision()
    {
        return collision;
    }

    int getProbe()
    {
        return probe;
    }

    int getChSize()
    {
        return chSize;
    }
};

class doubleHashTable : public HashTable
{
private:
    vector<pair<string, int>> table;
    vector<bool> isOccupied;

    int dhSize;
    int collision;
    int probe;
    int maxSize;
    bool isFilled;

public:
    doubleHashTable(int size) : HashTable(size)
    {
        dhSize = 0;
        collision = 0;
        probe = 0;
        maxSize = getSize();
        isFilled = false;

        table.resize(maxSize);
        isOccupied.resize(maxSize, false);
    }
    void p()
    {
        string s = "ami";
        cout << hash2(s) << endl;
    }

    void insert(string &word, int option)
    {
        if (isFilled)
            return;
        if (find(word, option) != -1)
            return;
        probe = 0;
        int index = 0;
        if (option == 1)
            index = hash1(word);
        else
            index = hash2(word);
        int i = 0;
        int aux_index = auxiliaryHash(word);

        while (isOccupied[index] && i < maxSize)
        {
            collision++;
            i++;
            index = (index + i * aux_index) % maxSize;
            if (index < 0)
                index += maxSize;
        }
        table[index] = make_pair(word, ++dhSize);
        isOccupied[index] = true;
        if (dhSize == maxSize)
            isFilled = true;
    }

    int find(string word, int option)
    {
        int index = 0;
        if (option == 1)
            index = hash1(word);
        else
            index = hash2(word);
        int i = 0;
        int aux_index = auxiliaryHash(word);

        while (isOccupied[index] && i < maxSize)
        {
            if (table[index].first == word)
            {
                return table[index].second;
            }
            i++;
            probe++;
            index = (index + i * aux_index) % maxSize;
            if (index < 0)
                index += maxSize;
        }
        return -1;
    }

    void Delete(string &word, int option)
    {
        int index = 0;
        if (option == 1)
            index = hash1(word);
        else
            index = hash2(word);
        int i = 0;
        int aux_index = auxiliaryHash(word);
        while (isOccupied[index])
        {
            if (table[index].first == word)
            {
                table[index].first = "";
                dhSize--;
                isOccupied[index] = false;
                return;
            }
            index = (index + i * aux_index) % maxSize;
            i++;
        }
    }

    int getCollision()
    {
        return collision;
    }

    int getProbe()
    {
        return probe;
    }

    int getDhSize()
    {
        return dhSize;
    }
};

class customProbingHashTable : public HashTable
{
private:
    vector<string> table;
    vector<bool> isOccupied;

    int cphSize;
    int collision;
    int probe;
    int maxSize;

public:
    customProbingHashTable(int size) : HashTable(size)
    {
        cphSize = 0;
        collision = 0;
        probe = 0;
        maxSize = getSize();

        table.resize(maxSize);
        isOccupied.resize(maxSize, false);
    }
    // customHash(k, i) = (Hash1(k) + C1 × i × cpHash(k) + C2 × i^2) % tabelSize

    void insert(string &word, int option)
    {
        if (find(word, option) != -1)
            return;
        probe = 0;
        int index = 0;
        if (option == 1)
            index = hash1(word);
        else
            index = hash2(word);
        int i = 0;
        int aux_index = auxiliaryHash(word);
        while (isOccupied[index] && i < maxSize)
        {
            collision++;
            i++;
            index = (index + 15 * i * aux_index + 39 * i * i) % maxSize;
            if (index < 0)
                index += maxSize;
        }
        table[index] = word;
        isOccupied[index] = true;
        cphSize++;
    }

    int find(string word, int option)
    {
        int index = 0;
        if (option == 1)
            index = hash1(word);
        else
            index = hash2(word);
        int i = 0;
        int aux_index = auxiliaryHash(word);
        while (isOccupied[index] && i < maxSize)
        {
            if (table[index] == word)
            {
                return index;
            }
            probe++;
            i++;
            index = (index + 15 * i * aux_index + 39 * i * i) % maxSize;
            if (index < 0)
                index += maxSize;
        }
        return -1;
    }

    void Delete(string &word, int option)
    {
        int index = 0;
        if (option == 1)
            index = hash1(word);
        else
            index = hash2(word);
        int i = 0;
        int aux_index = auxiliaryHash(word);
        while (isOccupied[index])
        {
            if (table[index] == word)
            {
                table[index] = "";
                cphSize--;
                isOccupied[index] = false;
                return;
            }
            index = (index + 15 * i * aux_index + 39 * i * i) % maxSize;
            i++;
        }
    }

    int getCollision()
    {
        return collision;
    }

    int getProbe()
    {
        return probe;
    }

    int getCphSize()
    {
        return cphSize;
    }
};

vector<bool> HashTable::isPrimes;

set<string> suffleWords(int num, vector<string> &words)
{
    set<string> searchWords;
    random_device rd;
    mt19937 reg(rd());
    shuffle(words.begin(), words.end(), reg);
    for (int i = 0, j = 0; j < num; i++)
    {
        // check if the word is inserted correctly
        auto p = searchWords.insert(words[i]);
        if (p.second)
        {
            j++;
        }
    }
    return searchWords;
}

int main()
{
    vector<string> words;
    int totalWords = 10000;
    // cin >> totalWords;
    for (int i = 0; i < totalWords; i++)
    {
        words.push_back(randomWord(5, 10));
    }
    // for (int i = 0; i < 10; i++)
    // {
    //     cout << words[i] << endl;
    // }
    int tableSize;
    cin >> tableSize;

    // vector<bool> isPrimes = sieveOfEratosthenes(tableSize + 2000);
    // int nextPrime = findNextPrime(totalWords, isPrimes);

    // tableSize = nextPrime;
    // HashTable hashTable(tableSize);
    chainHashTable ch1(tableSize), ch2(tableSize);
    doubleHashTable dh1(tableSize), dh2(tableSize);
    customProbingHashTable cph1(tableSize), cph2(tableSize);

    for (int i = 0; i < totalWords; i++)
    {
        ch1.insert(words[i], 1);
        ch2.insert(words[i], 2);
        dh1.insert(words[i], 1);
        dh2.insert(words[i], 2);
        cph1.insert(words[i], 1);
        cph2.insert(words[i], 2);
    }

    int searchWordnum = 1000;
    set<string> testWords = suffleWords(searchWordnum, words);

    // cout << ch1.find(words[4], 1) << endl;
    set<string>::iterator it = testWords.begin();
    for (; it != testWords.end(); it++)
    {
        ch1.find(*it, 1);
        ch2.find(*it, 2);
        dh1.find(*it, 1);
        dh2.find(*it, 2);
        cph1.find(*it, 1);
        cph2.find(*it, 2);
    }
    cout << "Chain Hashing\t" << ch1.getCollision() << " " << (1.0 * ch1.getProbe()) / 1000 << endl;
    cout << "\t\t" << ch2.getCollision() << " " << 1.0 * ch2.getProbe() / ch2.getChSize() << endl;

    cout << "Double Hashing\t" << dh1.getCollision() << " " << 1.0 * dh1.getProbe() / dh1.getDhSize() << endl;
    cout << "\t\t" << dh2.getCollision() << " " << 1.0 * dh2.getProbe() / dh2.getDhSize() << endl;

    cout << "Custom Probing\t" << cph1.getCollision() << " " << 1.0 * cph1.getProbe() / cph1.getCphSize() << endl;
    cout << "\t\t" << cph2.getCollision() << " " << 1.0 * cph2.getProbe() / cph2.getCphSize() << endl;
    // words.erase(words.begin(), words.end());
    return 0;
}