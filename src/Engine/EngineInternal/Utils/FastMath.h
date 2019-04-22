

#pragma once

#include <iostream>
#include <vector>

#include <cmath>

class Lookup {
    private:
        static float round(float n) { return std::floor(n + 0.5); }

        std::vector<float> samples;
        float from, to, x;

    public:
        Lookup(float (* func)(float), float from, float to, size_t num_samples) : from(from), to(to), x(double(num_samples - 1) / (to - from)) {
            for (size_t i = 0; i < num_samples; ++i) {
                float num = (to - from) * i / (num_samples - 1);
                float sample = func(num);
                samples.push_back(sample);
            }
        }

        float operator()(float n) const {
            return samples.at(round((n - from) * x));
        }
};