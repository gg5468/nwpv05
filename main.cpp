#include <tchar.h>
#include "nwpwin.h"
#include "list"

class main_window : public vsite::nwp::window
{
private:
	std::list<POINT> points;
protected:
	void on_paint(HDC hdc) override  
	{
		if (points.empty())
			return;

		auto it = points.begin();
		MoveToEx(hdc, it->x, it->y, NULL);
		++it;

		for (it; it != points.end(); ++it) {
			LineTo(hdc, it->x, it->y);
		}
	}
	void on_left_button_down(POINT p) override
	{
		points.push_back(p);
		::InvalidateRect(*this, nullptr, TRUE);
	}
	void on_key_down(int vk) override
	{
		switch (vk) {
		case VK_ESCAPE:
			points.clear();
			::InvalidateRect(*this, NULL, TRUE);
			break;

		case VK_BACK:
			if (!points.empty()) {
				points.pop_back();
				::InvalidateRect(*this, NULL, TRUE);
			}
			break;
		}
	}
	void on_destroy() override
	{
		::PostQuitMessage(0);
	}
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	vsite::nwp::application app;
	main_window w;
	w.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP 5");
	return app.run();
}
