#include "engine.h"

void c_train_engine::intelligence(size_t index)
{
	c_train* train = _journey_list[index]->train();
	c_rail *rail = train->actual_rail();

	if (train->state() == e_train_state::starting && train->departure_time() <= _time + 0.05f)
		train->set_state(e_train_state::normal);
	if (train->state() != e_train_state::starting)
	{
		if (train->state() == e_train_state::normal && should_slow(index) == false &&
				train->speed() < train->max_speed() && train->speed() < rail->speed())
			train->set_state(e_train_state::speed_up); // on accelere

		if (should_slow(index) == true && train->state() != e_train_state::stopped && train->state() != e_train_state::slowing)
			train->set_state(e_train_state::braking); // on va s'arreter completement

		if (train->state() != e_train_state::stopped &&
			train->state() != e_train_state::event &&
			train->state() != e_train_state::entering &&
			train->state() != e_train_state::slowing &&
			train->speed() >= MIN_SPEED && train->slow_down_dist() >= calc_distance_left(index) - train->distance_per_tic())
			train->set_state(e_train_state::start_slowing); // on va rouler a 5km/h

		if (calc_distance_left(index) <= 0.005f)
			train->set_state(e_train_state::stopping); // On arrive dans une ville et on doit donc s'arreter

		if (train->state() == e_train_state::stopped && should_slow(index) == false)
			train->set_state(e_train_state::normal); // L'heure du depart est arrive


		if (train->state() == e_train_state::event && train->event_waiting_time() <= 0.0f)
		{
			if (train->index() != 0)
				if (_text_bool == true)
					train->journey()->output_text() += "             -----    Event ended    -----\n";
			train->set_state(e_train_state::waiting);
		}
		if (train->state() == e_train_state::waiting && train->departure_time() <= _time && train->waiting_time() <= 0.0f)
		{
			if (train->index() != 0)
				if (_text_bool == true)
					train->journey()->output_text() += "             -----    The train start again    -----\n";
			train->start();
		}
	}

}
