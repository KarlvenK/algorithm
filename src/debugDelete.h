#ifndef debugDelete_h
#define debugDelete_h

#include <iostream>

class DebugDelete {
public:
    DebugDelete(std::ostream& s = std::cerr) : os(s) { }
    template<typename T>
    void operator() (T* p) const {
        os << "deleting unq_ptr" << std::endl;
        delete p;
    }
private:
    std::ostream& os;
};

#endif