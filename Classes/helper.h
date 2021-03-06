#ifndef __HELPERS_H__
#define __HELPERS_H__
#include <iostream>
#include <random>

class Helpers {
    public:
        static std::string get_uuid() {
            static std::random_device dev;
            static std::mt19937 rng(dev());

            std::uniform_int_distribution<int> dist(0, 15);

            const char *v = "0123456789abcdef";
            const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

            std::string res;
            for (int i = 0; i < 16; i++) {
                if (dash[i]) res += "-";
                res += v[dist(rng)];
                res += v[dist(rng)];
            }
            return res;
        }
};

#endif