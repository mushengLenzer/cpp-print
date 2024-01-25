//
// Created by Administrator on 2024/1/25.
//

#ifndef PRINT_PRINT_H
#define PRINT_PRINT_H

#include<iostream>

struct Params {
    char sep;
    char end;
    std::ostream *file;
};

void _print(int obj,std::ostream &out) {
    out << obj;
}

//void print(Params Params) {
//    return;
//}


// 变参函数模板，对每个元素进行操作
//template<typename T, typename... Rest>
//void print(const Params params, const T &obj, const Rest &... rest) {
//    print(obj);
//    print(params, rest...); // 递归，操作剩余的元素
//}

//template<typename T, typename... Rest>
//void print(const T& obj, const Rest&... rest) {
//    const Params params={' ', '\n', &std::cout};
//    print(obj);
//    std::cout << params.sep;
//    print(params, rest...); // 递归，操作剩余的元素
//}

//template<typename T, typename... Rest>
//void print(const Params params, const Rest&... rest) {
//    print(params, rest...); // 递归，操作剩余的元素
//}

template<typename... Args>
void print(const Args &... args) {
//    initialization
    Params params = {' ', '\n', &std::cout};

    auto &out = *params.file;
    bool isFirst = true;
    ([&isFirst, &out, &params](auto &&args) {
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


    auto &out = *params.file;
    bool isFirst = true;
    ([&isFirst, &out, &params](auto &&args) {
        if (!isFirst)
            out << params.sep;
        isFirst = false;
        _print(args, out);
    }(args), ...);
    out << params.end;
}


#endif //PRINT_PRINT_H
