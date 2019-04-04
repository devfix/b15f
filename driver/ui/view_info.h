#ifndef VIEW_INFO
#define VIEW_INFO

#include "view.h"

class ViewInfo : public View
{
public:
	ViewInfo(void);
	virtual void draw(void) override;
	virtual std::function<void(int)> keypress(int& key) override;

private:
	constexpr static int text_offset_x = 2;
	constexpr static int text_offset_y = 3;
};

#endif // VIEW_INFO
