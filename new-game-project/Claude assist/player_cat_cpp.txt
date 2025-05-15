#include "player_cat.h"
#include <godot_cpp/classes/input.hpp>

using namespace godot;

// Constructor
PlayerCat::PlayerCat() {
    // Initialize any member variables here
    speed = 300.0f;
}

// Destructor
PlayerCat::~PlayerCat() {
    // Clean up if needed
}

// Called when the node is ready
void PlayerCat::_ready() {
    // Get references to child nodes if needed
    sprite = get_node<Sprite2D>("Sprite2D");
    collision_shape = get_node<CollisionShape2D>("CollisionShape2D");
}

// Called every frame
void PlayerCat::_process(double delta) {
    // Get input direction
    Vector2 direction = Vector2(0, 0);
    
    // Check keyboard input
    Input* input = Input::get_singleton();
    
    if (input->is_action_pressed("ui_right")) {
        direction.x += 1;
    }
    if (input->is_action_pressed("ui_left")) {
        direction.x -= 1;
    }
    if (input->is_action_pressed("ui_down")) {
        direction.y += 1;
    }
    if (input->is_action_pressed("ui_up")) {
        direction.y -= 1;
    }

    // Normalize direction to prevent faster diagonal movement
    if (direction.length() > 0) {
        direction = direction.normalized();
    }

    // Move the player
    Vector2 velocity = direction * speed * delta;
    set_position(get_position() + velocity);
    
    // Optional: Flip sprite based on movement direction
    if (sprite != nullptr) {
        if (direction.x < 0) {
            sprite->set_flip_h(true);
        } else if (direction.x > 0) {
            sprite->set_flip_h(false);
        }
    }
}

// Called for physics processing
void PlayerCat::_physics_process(double delta) {
    // Physics based processing can go here if needed
}

// Register methods and properties
void PlayerCat::_bind_methods() {
    // Register properties
    BIND_PROPERTY(PlayerCat, Variant::FLOAT, speed, set_speed, get_speed);
    
    // Register methods if you need to call them from GDScript
    // ClassDB::bind_method(D_METHOD("method_name"), &PlayerCat::method_name);
}

// Getter for speed
float PlayerCat::get_speed() const {
    return speed;
}

// Setter for speed
void PlayerCat::set_speed(float p_speed) {
    speed = p_speed;
}