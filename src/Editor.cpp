#include "../headers/Editor.hpp"
#include "../headers/EditorFrame.hpp"

bool Editor::OnInit()
{
	frame = new EditorFrame;
	frame->Show();

	return true;
}
