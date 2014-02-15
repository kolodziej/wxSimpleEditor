#ifndef FILE_HPP
#define FILE_HPP
#include "wx/wx.h"
#include "wx/notebook.h"
#include <vector>

using std::vector;

class File {
public:
	File();
	File(const wxString &, const wxString &);

	wxPanel * GetPanel() const;
	wxBoxSizer * GetBoxSizer() const;
	wxTextCtrl * GetTextCtrl() const;
	void SaveFile(const wxString & = wxEmptyString, const wxString & = wxEmptyString);

	size_t GetId() const
	{
		return id;
	}

	const wxString & GetPath() const
	{
		return path;
	}

	const wxString & GetFilename() const
	{
		return fname;
	}

	bool IsSaved() const
	{
		return saved;
	}

	bool IsModified() const
	{
		return textCtrl->IsModified();
	}

	static wxNotebook * notebook;
	static vector<File*> files;

private:
	wxString path;
	wxString fname;
	bool saved;
	size_t id;

	wxPanel * panel;
	wxBoxSizer * sizer;
	wxTextCtrl * textCtrl;

	void InitUI();
};

#endif
