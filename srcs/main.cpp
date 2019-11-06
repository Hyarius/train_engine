#include "engine.h"

using namespace std;

int main(int argc, char**argv)
{
	c_application win("Test", Vector2(0.85f, 0.85f), Color(195, 195, 195));

	c_train_engine *engine;
	c_train *train_1;
	c_train *train_2;
	c_train *train_3;

	engine = new c_train_engine();

	train_1 = new c_train();
	train_1->set_acceleration(0.75f);
	train_1->set_deceleration(-0.75f);

	train_2 = new c_train();
	train_2->set_acceleration(0.75f);
	train_2->set_deceleration(-0.5f);

	train_3 = new c_train();
	train_3->set_acceleration(0.75f);
	train_3->set_deceleration(-0.35f);

	engine->set_time(12, 0);
	engine->set_time_delta(0.16666f);
	engine->add_train(train_1);
	engine->add_train(train_2);
	engine->add_train(train_3);

	engine->run();
	//c_main_window main_window;

	return (win.run());
}
