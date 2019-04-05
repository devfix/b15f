#ifndef VIEW_PROMT_H
#define VIEW_PROMT_H

#include <vector>
#include <string>
#include "view.h"

class ViewPromt : public View
{
public:
	virtual void draw(void) override;
	virtual void setMessage(std::string message);
	virtual void setConfirm(std::string name, std::function<void(int)> call);
	virtual void setCancel(std::string name, bool cancelable);
	virtual std::string getInput(void);
	virtual std::function<void(int)> keypress(int& key) override;

protected:
	size_t selection = 1;
	std::string input;
	std::string message = "Input";
	std::string label_confirm = "[ OK ]";
	std::string sep = "   ";
	std::string label_cancel = "[ Cancel ]";
	std::function<void(int)> call_confirm = nullptr;
	bool cancelable = true;
	int button_offset_x = 0, button_offset_y = 0;
	constexpr static int text_offset_x = 2;
	constexpr static int text_offset_y = 3;
};

#endif // VIEW_PROMT_H
