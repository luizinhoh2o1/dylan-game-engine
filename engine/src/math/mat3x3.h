#pragma once
#include <SDL3/SDL.h>
#include <cmath>

struct mat3x3 {
    float m[3][3] = {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    };

    static mat3x3 translate(float x, float y) {
        mat3x3 mat;
        mat.m[0][2] = x;
        mat.m[1][2] = y;
        return mat;
    }

    static mat3x3 scale(float sx, float sy) {
        mat3x3 mat;
        mat.m[0][0] = sx;
        mat.m[1][1] = sy;
        return mat;
    }

    static mat3x3 rotate(float angle) {
        mat3x3 mat;
        float c = std::cos(angle);
        float s = std::sin(angle);
        mat.m[0][0] = c;   mat.m[0][1] = -s;
        mat.m[1][0] = s;   mat.m[1][1] = c;
        return mat;
    }

    mat3x3 operator*(const mat3x3& other) const {
        mat3x3 result;
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col)
                result.m[row][col] =
                    m[row][0] * other.m[0][col] +
                    m[row][1] * other.m[1][col] +
                    m[row][2] * other.m[2][col];
        return result;
    }

    SDL_FPoint operator*(const SDL_FPoint& p) const {
        return SDL_FPoint {
            m[0][0] * p.x + m[0][1] * p.y + m[0][2],
            m[1][0] * p.x + m[1][1] * p.y + m[1][2]
        };
    }
};
