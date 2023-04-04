#ifndef _CONVEX_COLLIDER_H_
#define _CONVEX_COLLIDER_H_

#include"collider.cpp"
#include"../Math/transform.cpp"
#include"../Debug/logit.cpp"

namespace svg
{
    class ConvexCollider : public Collider
    {
    public:
        CLASS_DECLARATION(ConvexCollider)

        // Форма для рендера
        std::vector<vec2<double>> shape;

        ConvexCollider();

        ConvexCollider(const std::string& name, const std::vector<vec2<double>>& shape, const Transform& transform, bool trigger = false);

        std::array<vec2<double>, 2> GetAABB(Transform final_transform) override;
    };

    CLASS_DEFENITION(Collider, ConvexCollider)

    ConvexCollider::ConvexCollider() : Collider(), shape({{0, 0}, {20, 20}, {20, -20}})
    {}

    ConvexCollider::ConvexCollider(const std::string& name, const std::vector<vec2<double>>& shape, const Transform& transform, bool trigger) : Collider(name, transform, trigger), shape(shape)
    {}

    std::array<vec2<double>, 2> ConvexCollider::GetAABB(Transform final_transform)
    {

        logit("BEEING USED", "ConvexCollider");

        std::array<vec2<double>, 2> AABB;

        AABB[0] = shape[0];
        AABB[1] = shape[1];

        for(auto& point : shape)
        {
            if(point.y > AABB[0].y)
                AABB[0].y = point.y;
            if(point.y < AABB[1].y)
                AABB[1].y = point.y;
            if(point.x < AABB[0].x)
                AABB[0].x = point.x;
            if(point.x > AABB[1].x)
                AABB[1].x = point.x;
        }

        return AABB;
    }
}

#endif