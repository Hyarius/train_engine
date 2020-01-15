#include "engine.h"

static void handle_speed_up(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{
	delta = engine->calc_accelerate_time(index, time_left, rail->speed());
	train->accelerate(delta);
	if (delta <= 0.001f) // On a fini d'accelerer
		train->set_state(e_train_state::normal);
}

static void handle_braking(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{
	delta = engine->calc_stoping_time(index, time_left);
	train->decelerate(delta);
	if (train->speed() <= 0.03f)
		train->set_state(e_train_state::stopped);
}

static void handle_slowing(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{
	delta = engine->calc_decelerate_time(index, time_left, MIN_SPEED);
	train->decelerate(delta);
	if (delta <= 0.001f)
		train->set_state(e_train_state::entering);
}

static void handle_stopping(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{
	delta = time_left;
	engine->move_train(index, engine->calc_distance_left(index));
}

static void handle_stopped(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{
	delta = time_left;
}

static void handle_entering(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{
	delta = engine->calc_distance_left(index) / train->speed();
}

static void handle_normal(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{
	delta = engine->calc_run_time(index, time_left);
	train->run(delta);
}

static void handle_waiting(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{
	delta = engine->calc_waiting_time(index, time_left);
	train->change_waiting_time(-delta);
}

static void handle_start_slowing(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{
	delta = engine->calc_run_time(index, time_left);
	train->run(delta);
	train->set_state(e_train_state::slowing);
}

static void handle_event(size_t index, float &delta, float time_left, c_rail *rail, c_train *train, c_train_engine *engine)
{

}

typedef void (*handler_funct)(size_t, float &, float, c_rail *, c_train *, c_train_engine *);

float c_train_engine::execution(size_t index, float time_left)
{
	static handler_funct funct_tab[13] = {
		nullptr,
		handle_normal,
		handle_speed_up,
		nullptr,
		handle_slowing,
		handle_stopping,
		handle_braking,
		handle_waiting,
		handle_event,
		handle_stopped,
		handle_entering,
		handle_start_slowing
	};
	c_train* train = _journey_list[index]->train();
	c_rail *rail = train->actual_rail();
	float delta = time_left;

	size_t tmp_index = static_cast<int>(train->state());
	if (funct_tab[tmp_index] != nullptr)
		funct_tab[tmp_index](index, delta, time_left, rail, train, this);

	return (delta);
}
