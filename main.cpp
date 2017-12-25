#include "test.cpp"
int main(void){ std::cout << "START" << std::endl;

    try {
        go_test();
    }
    catch (const std::exception &ex) {
        cout << ex.what() << std::endl;
    }
    catch (const std::exception * ex) {
        cout << ex->what() << std::endl;
    }

    return 0;
}
