#include "string_manipulation.hpp"
#include "constants.hpp"
#include "globals.hpp"
#include "physics.hpp"

void initializeStrings() {
    for (int s = 0; s < NUM_STRINGS; s++) {
        for (int i = 0; i < N_POINTS; i++) {
            strings[s][i] = 0.0f;
            stringsPrev[s][i] = 0.0f;
        }
    }
}

// Helper function to apply displacement to a single point
void displacePoint(const int s, const int j, const float direction, const int randSeed) {
    if (j >= 0 && j < N_POINTS) {
        const float randomFactor = (randSeed - 50) / 50.0f * 0.05f; // -0.05 to 0.05
        strings[s][j] += 0.01f * direction * (1.0f + randomFactor);
    }
}

// Apply displacement to a radius of points around the center
void strumOnRadius(const int mouseY, const int s, const float direction, const int randSeed) {
    const int i_center = static_cast<int>(mouseY / static_cast<float>(HEIGHT) * N_POINTS);
    for (int j = i_center - 1; j <= i_center + 1; j++) {
        displacePoint(s, j, direction, randSeed);
    }
}

// Apply displacement to a single point
void strumBasic(const int mouseY, const int s, const float direction, const int randSeed) {
    const int i = static_cast<int>(mouseY / static_cast<float>(HEIGHT) * N_POINTS);
    displacePoint(s, i, direction, randSeed);
}

// Main function to process all strings
void strumStrings(const int mouseX, const int mouseY, const int deltaX) {
    const float direction = (deltaX > 0) ? 1.0f : (deltaX < 0) ? -1.0f : 0.0f;
    constexpr int speedThreshold = 6; // Pixels per frame

    for (int s = 0; s < NUM_STRINGS; s++) {
        const float xBase = xBaseCalc(s);
        const int i = static_cast<int>(mouseY / static_cast<float>(HEIGHT) * N_POINTS);
        if (i >= 0 && i < N_POINTS) { // bounds check
            const float currentX = xBase + strings[s][i] * MOUSE_STRENGTH_DISPLACEMENT;
            if (abs(mouseX - currentX) < MOUSE_SIZE_THRESHOLD) {
                const int randSeed = randGen(generator);
                if (abs(deltaX) > speedThreshold) {
                    printf("Fast mouse movement\n");
                    strumOnRadius(mouseY, s, direction, randSeed); // Fast mouse movement
                } else {
                    printf("Slow mouse movement\n");
                    strumBasic(mouseY, s, direction, randSeed); // Slow mouse movement
                }
            }
        }
    }
}
