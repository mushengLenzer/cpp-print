#ifndef PRINT_PRINT_H
#define PRINT_PRINT_H

#include <type_traits>
#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <list>

struct Params {
    char sep;
    char end;
    std::ostream *file;
};

template<typename T>
void _print(const T &obj, std::ostream &out);

void _print(const bool &obj, std::ostream &out);

template<typename T>
void _print(const std::vector<T> &obj, std::ostream &out);

template<typename T>
void _print(const std::deque<T> &obj, std::ostream &out);

template<typename T, std::size_t N>
void _print(const std::array<T, N> &obj, std::ostream &out);

template<typename T>
struct isSequenceContainers : public std::false_type {
};

template<typename T>
struct isSequenceContainers<std::vector<T>> : public std::true_type {
};

template<typename T>
struct isSequenceContainers<std::deque<T>> : public std::true_type {
};

template<typename T, std::size_t N>
struct isSequenceContainers<std::array<T, N>> : public std::true_type {
};

template<typename T>
struct isSequenceContainers<std::list<T>> : public std::true_type {
};


template<typename T>
void _print(const T &obj, std::ostream &out) {
    if (isSequenceContainers<T>::value) {
        bool isFirst = true;
        out << '[';
        for (auto const &entry: obj) {
            if (!isFirst)
                out << ", ";
            isFirst = false;
            _print(entry, out);
        }
        out << ']';
    } else {
        out << obj;
    }


}

// bool
void _print(const bool &obj, std::ostream &out) {
    if (obj)
        out << "True";
    else
        out << "False";
}

//vector
template<typename T>
void _print(const std::vector<T> &obj, std::ostream &out) {
    bool isFirst = true;
    out << '[';
    for (auto const &entry: obj) {
        if (!isFirst)
            out << ", ";
        isFirst = false;
        _print(entry, out);
    }
    out << ']';
}

//deque
template<typename T>
void _print(const std::deque<T> &obj, std::ostream &out) {
    bool isFirst = true;
    out << '[';
    for (auto const &entry: obj) {
        if (!isFirst)
            out << ", ";
        isFirst = false;
        _print(entry, out);
    }
    out << ']';
}

//array
template<typename T, std::size_t N>
void _print(const std::array<T, N> &obj, std::ostream &out) {
    bool isFirst = true;
    out << '[';
    for (auto const &entry: obj) {
        if (!isFirst)
            out << ", ";
        isFirst = false;
        _print(entry, out);
    }
    out << ']';
}

template<typename T>
void _print(const std::list<T> &obj, std::ostream &out) {
    bool isFirst = true;
    out << '[';
    for (auto const &entry: obj) {
        if (!isFirst)
            out << ", ";
        isFirst = false;
        _print(entry, out);
    }
    out << ']';
}


template<typename... Args>
void print(const Args &... args) {
//    initialization
    Params params = {' ', '\n', &std::cout};

    std::ostream &out = *params.file;
    bool isFirst = true;
    ([&isFirst, &out, &params](const Args &args) {
        if (!isFirst)
            out << params.sep;
        isFirst = false;
        _print(args, out);
    }(args), ...);
    out << params.end;
}


template<typename... Args>
void print(Params params, const Args &... args) {
//    initialization
    if (params.sep == 0) params.sep = ' ';
    if (params.end == 0) params.end = '\n';
    if (params.file == nullptr) params.file = &std::cout;


    std::ostream &out = *params.file;
    bool isFirst = true;
    ([&isFirst, &out, &params](const Args &args) {
        if (!isFirst)
            out << params.sep;
        isFirst = false;
        _print(args, out);
    }(args), ...);
    out << params.end;
}


#endif //PRINT_PRINT_H
