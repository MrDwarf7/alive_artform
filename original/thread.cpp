#include <cmath>
#include <vector>

#include "constants.cpp"

struct Particle {
    // float x, y, vx, vy;
    float x, y;
    float vx, vy;
    bool anchored;
};

// Thread class to simulate a string of particles
struct Thread {
    std::vector<Particle> particles;
    float stiffness;

    Thread(const float x, const int numParticles, const float stiffness) : stiffness(stiffness) {
        for (int i = 0; i < numParticles; ++i) {
            const float y = static_cast<float>(i) / static_cast<float>(numParticles - 1) * HEIGHT;
            const bool isAnchored = (i == 0 || i == numParticles - 1);
            particles.push_back({x, y, 0.0f, 0.0f, isAnchored});
        }
    }

    void update(const int clickX, const int clickY, const float forceRadius, const bool &isClicking, Uint32 dt) {
    // Handle mouse input
        if (isClicking) {
            for (auto &particle: particles) {
                if (!particle.anchored) {
                    const float dx = particle.x - static_cast<float>(clickX);
                    const float dy = particle.y - static_cast<float>(clickY);
                    float distance = std::sqrt(dx * dx + dy * dy);
                    if (distance < forceRadius) {
                        const float force = 0.05f * (forceRadius - distance);
                        particle.vx += (force * dx) / (distance + 1.0f) * (dt * 0.5f);
                        particle.vy += (force * dy) / (distance + 1.0f) * (dt * 0.5f);
                    }
                }
            }
        }

        // Apply spring forces between particles
        for (size_t i = 1; i < particles.size(); ++i) {
            Particle &prev = particles[i - 1];
            Particle &curr = particles[i];
            const float dx = curr.x - prev.x;
            const float dy = curr.y - prev.y;
            const float distance = std::sqrt(dx * dx + dy * dy);
            const float targetDistance = static_cast<float>(HEIGHT) / (static_cast<float>(particles.size()) - 1); // 'Resting' distance between particles
            const float springForce = (distance - targetDistance) * stiffness;

            if (distance > 0) {
                const float fx = (dx / distance) * springForce;
                const float fy = (dy / distance) * springForce;
                if (!curr.anchored) {
                    curr.vx -= fx;
                    curr.vy -= fy;
                }

                if (!prev.anchored) {
                    prev.vx += fx;
                    prev.vy += fy;
                }
            }
        }

        for (auto &particle: particles) {
            if (!particle.anchored) {
                // particle.vx *= 0.98f; // Damping -- fades wave efffect (lower value = more damping/slower reset)
                particle.vx *= 0.9999f; // Damping -- fades wave efffect (lower value = more damping/slower reset)
                // particle.vy *= 0.96f;
                particle.vy *= 0.60f;
                particle.x += particle.vx;
                particle.y += particle.vy;
            }
        }
    }

    void draw(SDL_Renderer *renderer) const {
        SDL_SetRenderDrawColor(renderer, WHITE[0], WHITE[1], WHITE[2], WHITE[3]);
        for (size_t i = 0; i < particles.size() - 1; ++i) {
            SDL_RenderDrawLineF(renderer, particles[i].x, particles[i].y, particles[i + 1].x, particles[i + 1].y);
        }
    }
};
