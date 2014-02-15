#include "../headers/File.hpp"
#include "../headers/EditorFrame.hpp"
#include "wx/wx.h"
#include <vector>

using std::vector;

wxNotebook * File::notebook;
vector<File*> File::files;

File::File() : path(wxEmptyString), fname(wxEmptyString), saved(false)
{
	id = files.size();
	InitUI();
	files.push_back(this);
}

File::File(const wxString & _path, const wxString & _fname) : path(_path), fname(_fname), saved(true)
{
	id = files.size();
	InitUI();
	files.push_back(this);
	textCtrl->LoadFile(path);
}

wxPanel * File::GetPanel() const
{
	return panel;
}

wxBoxSizer * File::GetBoxSizer() const
{
	return sizer;
}

wxTextCtrl * File::GetTextCtrl() const
{
	return textCtrl;
}

void File::SaveFile(const wxString &_path, const wxString &_fname)
{
	if (_fname != wxEmptyString)
	{
		fname = _fname;
		path = _path;
	}

	textCtrl->SaveFile(path);
	saved = true;
}

void File::InitUI()
{
	panel = new wxPanel(notebook);
	sizer = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(sizer);
	textCtrl = new wxTextCtrl(panel, EditorFrame::EDITORS, wxEmptyString, wxPoint(0,0), wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER | wxTE_PROCESS_TAB);
	sizer->Add(textCtrl, 1, wxEXPAND | wxALL, 5);

	notebook->AddPage(panel, wxT("[niezapisany plik]"));
}
