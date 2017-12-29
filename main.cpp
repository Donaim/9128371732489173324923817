#include "test.cpp"
using namespace std;
int main(void){ cout << "START" << endl;

    try {
        go_test();
    }
    catch (const exception &ex) {
        cerr << ex.what() << endl;
    }
    catch (const exception * ex) {
        cerr << ex->what() << endl;
    }

    return 0;
}
