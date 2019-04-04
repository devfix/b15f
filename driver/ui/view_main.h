#ifndef VIEW_MAIN_H
#define VIEW_MAIN_H

#include <vector>
#include <string>
#include "view.h"

class ViewMain : public View
{
public:
	virtual void draw(void) override;
	virtual std::function<void(int)> keypress(int& key) override;

private:
	constexpr static int choice_offset_x = 2;
	constexpr static int choice_offset_y = 3;
	size_t selection = 0;
	const std::vector<std::string> choices = {
		"[ Informationen ]",
		"[ Beenden ]"
	};
};

#endif // VIEW_MAIN_H
