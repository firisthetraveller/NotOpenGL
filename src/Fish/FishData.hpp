#ifndef __FISHDATA__
#define __FISHDATA__

#include <p6/p6.h>
#include "Config.hpp"
#include "Food/Food.hpp"
#include "glm/fwd.hpp"

class FishData {
private:
    const unsigned int _id;

public:
    glm::vec3    _center;
    p6::Radius   _radius;
    p6::Rotation _rotation;
    glm::vec3    _movement;

    FishData(unsigned int id, glm::vec3 center, p6::Radius radius, p6::Rotation rotation, glm::vec3 movement);

    // TODO operator == is expected to compare data fields
    bool operator==(const FishData& other) const { return _id == other._id; }

    bool         isOutOfBounds() const;
    unsigned int getId() const { return _id; };
    bool         isNear(const glm::vec3& position, float otherSize = 0.f, float distance = Config::get().VISUAL_RANGE) const;

    void teleport();
};

#endif
