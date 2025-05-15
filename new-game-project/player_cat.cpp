
/* Jenova C++ Default Script */

// Godot SDK
#include <Godot/godot.hpp>
#include <Godot/classes/character_body2d.hpp>

// Jenova SDK
#include <JenovaSDK.h>

// Namespaces
using namespace godot;
using namespace dsadsajenova::sdk;

// Jenova Script Block Start
JENOVA_SCRIPT_BEGIN

/* Write C++ Script Here */


class Player : public godot::CharacterBody2D {
	GDCLASS(Player, godot::CharacterBody2D)

public:
	void _process(double delta) override;
};

void OnReady(Caller* instance){
	
	
	Output("Hello World");
}

//void OnProcess(Caller* instance, double _delta){
	//
	//godot::Texture2D* thisNode = (Texture2D)instance->self;
	//
	//thisNode->set_position(vector2(00,thisNode->set_position().y+_delta(0,0)));
//}
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class PlayerCat : public Node2D {
	GDCLASS(PlayerCat, Node2D)

private:
	float speed = 200.0f;

public:
	void _physics_process(double delta) override {
		Vector2 direction;

		if (Input::get_singleton()->is_action_pressed("ui_right")) {
			direction.x += 1;
		}
		if (Input::get_singleton()->is_action_pressed("ui_left")) {
			direction.x -= 1;
		}
		if (Input::get_singleton()->is_action_pressed("ui_down")) {
			direction.y += 1;
		}
		if (Input::get_singleton()->is_action_pressed("ui_up")) {
			direction.y -= 1;
		}

		direction = direction.normalized();
		Vector2 new_position = get_position() + direction * speed * delta;
		set_position(new_position);
	}

	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("_physics_process", "delta"), &PlayerCat::_physics_process);
	}
};





// Jenova Script Block End
JENOVA_SCRIPT_END
