#ifndef EDITORFRAME_HPP
#define EDITORFRAME_HPP
#include "wx/wx.h"
#include "wx/notebook.h"

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

	// events
	void OnNew(wxCommandEvent &);
	void OnOpen(wxCommandEvent &);
	void OnSave(wxCommandEvent &);
	void OnSaveAs(wxCommandEvent &);
	void OnSaveAll(wxCommandEvent &);
	void OnCloseFile(wxCommandEvent &);
	void OnCloseAll(wxCommandEvent &);
	void OnExit(wxCommandEvent &);

	void OnAbout(wxCommandEvent &);

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
