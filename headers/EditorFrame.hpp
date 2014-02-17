#ifndef EDITORFRAME_HPP
#define EDITORFRAME_HPP
#include "wx/wx.h"
#include "wx/notebook.h"
#include "File.hpp"

class EditorFrame : public wxFrame
{
public:
	enum {
		PANEL1 = 1000,
		SIZER1,
		SIZER2,
		NOTEBOOK,
		EDITORS,
		SAVEALL,
	};
	EditorFrame();

	File * GetSelectedFile() const;
	File * GetFile(size_t) const;

	// events
	void OnNew(wxCommandEvent &);
	void OnOpen(wxCommandEvent &);
	void OnSave(wxCommandEvent &);
	void OnSaveAs(wxCommandEvent &);
	void OnSaveAll(wxCommandEvent &);
	void OnCloseFile(wxCommandEvent &);
	void OnCloseAll(wxCommandEvent &);
	void OnExit(wxCommandEvent &);

	void OnUndo(wxCommandEvent &);
	void OnRedo(wxCommandEvent &);
	void OnCut(wxCommandEvent &);
	void OnCopy(wxCommandEvent &);
	void OnPaste(wxCommandEvent &);

	void OnAbout(wxCommandEvent &);

	void OnSearchFile(wxCommandEvent &);

	void OnModify(wxCommandEvent &);
	void OnClose(wxCloseEvent &);
private:
	void InitMenuBar();
	void InitStatusBar();
	void InitSizer();
	void InitNotebook();

	void InitEditor(const wxString & = wxEmptyString, const wxString & = wxEmptyString);

	wxPanel * panel1;
	wxBoxSizer * sizer1;
	wxBoxSizer * sizer2;
	wxNotebook * notebook;

	DECLARE_EVENT_TABLE()
};

#endif
