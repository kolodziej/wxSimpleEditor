#ifndef EDITOR_HPP
#define EDITOR_HPP
#include "wx/wx.h"
#include "File.hpp"
#include "EditorFrame.hpp"
#include <vector>

using std::vector;

class Editor : public wxApp
{
public:
	virtual bool OnInit();
	//int FilterEvent(wxEvent &);

private:
	EditorFrame * frame;
};

#endif
