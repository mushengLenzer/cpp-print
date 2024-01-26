#ifndef PRINT_PRINT_H
#define PRINT_PRINT_H

#include <type_traits>
#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <iterator>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <tuple>
#include <memory>
#include <bitset>


struct Params {
    char sep;
    char end;
    std::ostream *file;
};

// Check if it is a sequence container
template<typename T>
struct isSequenceContainer : public std::false_type {
};

template<typename T>
struct isSequenceContainer<std::vector<T>> : public std::true_type {
};

template<typename T>
struct isSequenceContainer<std::deque<T>> : public std::true_type {
};

template<typename T, std::size_t N>
struct isSequenceContainer<std::array<T, N>> : public std::true_type {
};

template<typename T>
struct isSequenceContainer<std::list<T>> : public std::true_type {
};

template<typename T>
struct isSequenceContainer<std::forward_list<T>> : public std::true_type {
};

template<typename T, std::size_t N>
struct isSequenceContainer<T[N]> : public std::true_type {
};


// Check if it is a map container
template<typename T>
struct isMapContainer : public std::false_type {
};

template<typename K, typename V>
struct isMapContainer<std::map<K, V>> : public std::true_type {
};

template<typename K, typename V>
struct isMapContainer<std::multimap<K, V>> : public std::true_type {
};

template<typename K, typename V>
struct isMapContainer<std::unordered_map<K, V>> : public std::true_type {
};

template<typename K, typename V>
struct isMapContainer<std::unordered_multimap<K, V>> : public std::true_type {
};

// Check if it is a set container
template<typename T>
struct isSetContainer : public std::false_type {
};

template<typename K, typename V>
struct isSetContainer<std::set<K, V>> : public std::true_type {
};

template<typename K, typename V>
struct isSetContainer<std::multiset<K, V>> : public std::true_type {
};

template<typename K, typename V>
struct isSetContainer<std::unordered_set<K, V>> : public std::true_type {
};

template<typename K, typename V>
struct isSetContainer<std::unordered_multiset<K, V>> : public std::true_type {
};

//concept
template<typename T>
concept Iterable = isSequenceContainer<T>::value;

template<typename T>
concept Map = isMapContainer<T>::value;

template<typename T>
concept Set = isSetContainer<T>::value;

template<typename T>
concept Ptr = std::is_pointer<T>::value ||
              std::is_same<T, std::unique_ptr<typename T::element_type>>::value ||
              std::is_same<T, std::shared_ptr<typename T::element_type>>::value;


template<typename T>
void _print(const T &obj, std::ostream &out);

void _print(const bool &obj, std::ostream &out);

template<Iterable T>
void _print(const T &obj, std::ostream &out);

template<Map T>
void _print(const T &obj, std::ostream &out);

template<typename... T>
void _print(const std::tuple<T...> &obj, std::ostream &out);

template<typename T1, typename T2>
void _print(const std::pair<T1, T2> &obj, std::ostream &out);


// fundamental types
template<typename T>
void _print(const T &obj, std::ostream &out) {
    out << obj;
}

// bool
void _print(const bool &obj, std::ostream &out) {
    if (obj)
        out << "True";
    else
        out << "False";
}

// sequence container
template<Iterable T>
void _print(const T &obj, std::ostream &out) {
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

//map container
template<Map T>
void _print(const T &obj, std::ostream &out) {
    bool isFirst = true;
    out << '{';
    for (auto const &entry: obj) {
        if (!isFirst)
            out << ", ";
        isFirst = false;
        _print(entry.first, out);
        out << ": ";
        _print(entry.second, out);
    }
    out << '}';
}

//set container
template<Set T>
void _print(const T &obj, std::ostream &out) {
    bool isFirst = true;
    out << '{';
    for (auto const &entry: obj) {
        if (!isFirst)
            out << ", ";
        isFirst = false;
        _print(entry, out);
    }
    out << '}';
}

// tuple
template<typename... T>
void _print(const std::tuple<T...> &obj, std::ostream &out) {
    bool isFirst = true;
    out << "(";
    std::apply(
            [&isFirst, &out](const T &... entries) {
                ([&isFirst, &out](const T &entry) {
                    if (!isFirst)
                        out << ", ";
                    isFirst = false;
                    _print(entry, out);
                }(entries), ...);
            }, obj);
    out << ")";
}

// pair
template<typename T1, typename T2>
void _print(const std::pair<T1, T2> &obj, std::ostream &out) {
    out << "(";
    out << obj.first;
    out << ", ";
    out << obj.second;
    out << ")";
}

template<Ptr T>
void _print(const T &obj, std::ostream &out) {
    _print(*obj, out);
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
