#pragma once

#include "fset.cpp"
#include "util.cpp"
#include "initializator.cpp"
#include <stdlib.h>
#include <time.h>

struct GenParams {
    int SeqStart    = 0;
    int SeqCount    = 1000;
    int RandStart   = 10000;
    int RandEnd     = 100000;
    int RandCount   = 100;

    friend ostream& operator << (ostream& os, const GenParams& me);
};
ostream& operator << (ostream& os, const GenParams& me){
    os << '[' << "SeqStart: " << me.SeqStart << ';' << ' ' << "SeqCount: " << me.SeqCount << ';' << ' '
    << "RandStart: " << me.RandStart << ';' << ' ' << "RandEnd: " << me.RandEnd << ';' << ' ' << "RandCout: " << me.RandCount << ';' << ']';
}

class IGeneratable {
protected:
    IGeneratable() { srand(time(NULL)); }
    virtual Element& GenElement(int x, int mode) const = 0;
    virtual int NextRand(int down, int up) const { return (int)((rand() / (float)RAND_MAX) * (up - down) + down); }
public:
    virtual FiniteSet& Generate(const GenParams& p) const {
        Initial* zz = new Initial{};

        // cout << p << endl;
        
        for(int i = p.SeqStart, to = p.SeqStart + p.SeqCount; i < to; i++){
            zz->Add(GenElement(i, 0));
        }
        for(int i = 0, to = p.RandCount; i < to; i++){
            zz->Add(GenElement(NextRand(p.RandStart, p.RandEnd), 1));
        }

        cout << "Inited size = " << zz->size() << endl;

        return *new FiniteSet(*zz);
    }
};


