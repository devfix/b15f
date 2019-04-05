#ifndef VIEW_SELECTION_H
#define VIEW_SELECTION_H

#include <vector>
#include <string>
#include "view.h"

class ViewSelection : public View
{
public:
	virtual void draw(void) override;
	virtual void addChoice(std::string name, std::function<void(int)> call);
	virtual std::function<void(int)> keypress(int& key) override;
	

protected:
	size_t selection = 0;
	std::vector<std::string> choices;
	
	constexpr static int choice_offset_x = 2;
	constexpr static int choice_offset_y = 3;
};

#endif // VIEW_SELECTION_H
