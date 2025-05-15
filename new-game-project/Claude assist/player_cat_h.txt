#ifndef PLAYER_CAT_H
#define PLAYER_CAT_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>

namespace godot {

class PlayerCat : public Node2D {
    GDCLASS(PlayerCat, Node2D)

private:
    float speed;
    Sprite2D* sprite = nullptr;
    CollisionShape2D* collision_shape = nullptr;

protected:
    static void _bind_methods();

public:
    PlayerCat();
    ~PlayerCat();

    void _ready() override;
    void _process(double delta) override;
    void _physics_process(double delta) override;

    // Property getters and setters
    float get_speed() const;
    void set_speed(float p_speed);
};

}

#endif // PLAYER_CAT_H