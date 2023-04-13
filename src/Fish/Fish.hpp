#ifndef __FISH__
#define __FISH__
#include <p6/p6.h>
#include <memory>
#include <vector>
#include "Behavior.hpp"
#include "Environment.hpp"
#include "FishData.hpp"
#include "Food/Food.hpp"
#include "glm/fwd.hpp"
#include "internal/generate_range.hpp"

class Fish {
private:
    std::shared_ptr<FishData> _data;
    std::vector<Behavior>     _behaviors;
    int                       _eatingCooldown;

    void addDefaultBehaviors();

public:
    Fish(const glm::vec2& center = p6::random::point(), const p6::Radius& radius = p6::Radius{generate_range(0.01f, 0.02f)}, const p6::Rotation& rotation = p6::Rotation{}, const glm::vec2& movement = {});
    Fish(const Fish&) = delete;
    explicit Fish(std::shared_ptr<FishData> data);

    bool operator==(const Fish& other) const;

    bool isOutOfBounds() const;
    bool isNear(std::shared_ptr<Fish>& other) const;

    const std::shared_ptr<FishData>& getData() const { return _data; }
    void                             showId();

    void eats(std::shared_ptr<Food>& food);
    bool canEat() const;

    void draw(p6::Context& ctx) const;
    void addBehavior(Behavior behavior);
    void applyBehaviors(Environment& env);
    void update();
};

#endif
