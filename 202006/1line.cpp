/*
 * author: fuyingjian
 * e-mail: fuyingjian97@163.com
 * date: 2020-7-27 11:00
 * 线性分类器 (line), 题号202006-1 二分类问题
 * 题面：二维平面的上的点分为A和B两类，判断给定直线是否能将训练数据中的A,B类点完美分开.
 * 换而言之,即需要判断所有A类中点与点之间的特征相同，所有B类中点与点之间的特征相同，
 * 任意A类中一个点与B类中一个点特征相异。这里特征指的是点位于直线的哪一侧，在数学上转化为：
 * 位于直线上方θ_0+θ_1*x+θ_2*y > 0; 位于直线下方θ_0+θ_1*x+θ_2*y < 0. 所以简化判断
 * 点通过直线转换后符号的正负即可。
 *
 * 需要注意题目数据：
 * 1. 输入数据保证不存在恰好落在给定直线上的点，即不存在θ_0+θ_1*x_i+θ_2*y_i == 0的情况。
 * 2. A, B两类的点的数量均不为0
 *   这一点需要额外注意，当没有这条件时，代码中需要额外特殊值处理。
*/
#include <iostream>
#include <vector>
#include <set>
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;
// Point类，代表点，三元组(x, y, type)，即点的横坐标，纵坐标和类别
class P {
public:
    int x;
    int y;
    char type;
    P() {}
    P(int x, int y, char t) : x(x), y(y), type(t) {}
    friend istream& operator>> (istream &in, P& obj) {
        in >> obj.x >> obj.y >> obj.type;
        return in;
    }
};

/*
 * 一些封装函数技巧来自，算法竞赛入门:习题与解答
*/
/* 封装读取函数，输入之后直接插入到集合当中 */
// inline P readPoint() {
//     P p;
//     cin >> p;
//     // scanf("%d, %d, %c", &p.x, &p.y, &p.type);
//     return p;
// }

/* 封装两个泛型函数使用c++的IO流对集合进行输出 */
template<typename T>
ostream& operator<< (ostream& os, const vector<T>& V) {
    for (const auto & x : V) {
        os << x << " ";
    }
    return os;
}

// template<typename T>
// ostream& operator<< (ostream& os, const set<T>& S) {
//     for (const auto & x : S) {
//         os << x << " ";
//     }
//     return os;
// }

int main() {
    vector<P> vecA; // A类点
    vector<P> vecB; // B类点
    int n, m;       // 输入数据相关，点和查询的个数
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        P p;
        cin >> p;
        if (p.type == 'A') {
            vecA.push_back(p);
        } else if (p.type == 'B') {
            vecB.push_back(p);
        }
    }
#ifdef DEBUG
    cout << "just for test:" << endl;
    cout << vecA << endl;
    cout << vecB << endl;
#endif
    int a, b, c; // 给定直线的三个参数θ_0, θ_1和θ_2
    int i;       // 循环变量-i
    while (m--) {
        cin >> a >> b >> c;
        // 确保程序健壮性，特殊情况处理
        if (vecA.size() == 0 || vecB.size() == 0) {
            cout << "Yes" << endl;
            continue;
        }
        /*
         * flag为该点是位与直线哪一侧的标记,
         * 当位于直线上方时，即θ_0+θ_1×x+θ_2×y > 0, flag值标记为true(正号的意思)
         * 当位于直线下方时，即θ_0+θ_1×x+θ_2×y < 0, flag值标记为false(负号的意思)
        */
        bool flagA, flagB, flag;
        // 以第一个点为基准判断点进行归类
        flagA = ((a  + b* vecA[0].x + c * vecA[0].y) > 0) ? true : false;
        for (i = 1; i < vecA.size(); ++i) {
            flag = ((a  + b* vecA[i].x + c * vecA[i].y) > 0) ? true : false;
            if (flag ^ flagA) { // 异或运算，异号为true
                break;
            }
        }
        /*
         * 三个continue, 小小的优化，一旦判断不符合分类，即得到结果输出“No”,结束该轮循环
        */
        if (i < vecA.size()) {
            cout << "No" << endl;
            continue;
        }
        flagB = ((a  + b* vecB[0].x + c * vecB[0].y) > 0) ? true : false;
        if (!(flagA ^ flagB)) {
            cout << "No" << endl;
            continue;
        }
        for (i = 1; i < vecB.size(); ++i) {
            flag = ((a  + b* vecB[i].x + c * vecB[i].y) > 0) ? true : false;
             if (flag ^ flagB) {
                break;
            }
        }
        if (i < vecB.size()) {
            cout << "No" << endl;
            continue;
        }
        if (flagA ^ flagB) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}

/*
 * 时间复杂度O(m*n), 空间复杂度O(n)
 * submit: 代码长度 1.659KB, 编程语言 C0X, 评测结果 正确， 时间 15ms, 空间使用556.0KB
*/