#include "engine.h"

void c_main_window::create_train_panel()
{
	int border = train_box->box().border();
	Vector2 pos = border * 1;
	Vector2 size = Vector2(train_box->box().area().x - border * 2, 30.0f);

	train_box_frame = new c_frame(train_box);
	train_box_frame->set_geometry(0, train_box->area());
	train_box_frame->box().set_border(0);
	//train_box_frame->activate();

	train_box_label = new c_text_label("Train definition", train_box_frame);
	train_box_label->set_geometry(pos, size);
	train_box_label->label().set_align(alignment::centred);
	train_box_label->label().set_style(text_style::underline);
	train_box_label->activate();

	pos.y += size.y + 4;
	Vector2 label_size = Vector2((train_box->box().area().x - border) / 2 - border, 30.0f);
	Vector2 entry_size = Vector2((train_box->box().area().x - border) - label_size.x - border * 5, 30.0f);
	Vector2 label_pos = pos;
	Vector2 entry_pos = pos + Vector2(label_size.x + border, 0.0f);

	string text[3] = {"Train max speed :", "Train acceleration :", "Train deceleration :"};
	float value[3] = {140.0f, 0.75f, 0.75f};

	for (size_t i = 0 ; i < 3; i++)
	{
		train_value_label[i] = new c_text_label(text[i], train_box_frame);
		train_value_label[i]->set_geometry(label_pos, label_size);
		train_value_label[i]->box().set_back(Color(160, 160, 160));
		train_value_label[i]->box().set_front(Color(190, 190, 190));
		train_value_label[i]->activate();

		train_value_entry[i] = new c_value_entry(value[i], train_box_frame);
		train_value_entry[i]->set_geometry(entry_pos, entry_size);
		train_value_entry[i]->box().set_back(Color(160, 160, 160));
		train_value_entry[i]->box().set_front(Color(190, 190, 190));
		train_value_entry[i]->activate();

		label_pos.y += label_size.y + border;
		entry_pos.y += label_size.y + border;
	}

}
