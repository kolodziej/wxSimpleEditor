#include "../headers/EditorFrame.hpp"
#include "../headers/File.hpp"
#include <vector>

using std::vector;

EditorFrame::EditorFrame() :
	wxFrame(NULL, wxID_ANY, wxString::Format(wxT("SimpleEditor v.%i.%i.%i"),1,2,3), wxPoint(0,0), wxSize(800, 600))
{
	InitMenuBar();
	InitStatusBar();
	InitSizer();
	InitNotebook();
}

void EditorFrame::InitMenuBar()
{
	wxMenuBar * menuBar = new wxMenuBar;

	// menu file
	wxMenu * menuFile = new wxMenu();
	menuFile->Append(wxID_NEW, wxT("Nowy plik\tCtrl+N"));
	menuFile->Append(wxID_OPEN, wxT("Otwórz plik\tCtrl+O"));
	menuFile->Append(wxID_SAVE, wxT("Zapisz plik"));
	menuFile->Append(wxID_SAVEAS, wxT("Zapisz jako"));
	menuFile->Append(SAVEALL, wxT("Zapisz wszystkie pliki\tCtrl+Shift+S"));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_CLOSE, wxT("Zamknij plik"));
	menuFile->Append(wxID_CLOSE_ALL, wxT("Zamknij wszystkie pliki"));
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT, wxT("Zakończ\tCtrl+Q"));
	// menu edit
	wxMenu * menuEdit = new wxMenu();
	menuEdit->Append(wxID_UNDO, wxT("Cofnij\tCtrl+Z"));
	menuEdit->Append(wxID_REDO, wxT("Powtórz\tCtrl+Shift+Z"));
	menuEdit->AppendSeparator();
	menuEdit->Append(wxID_CUT, wxT("Wytnij\tCtrl+X"));
	menuEdit->Append(wxID_COPY, wxT("Kopiuj\tCtrl+C"));
	menuEdit->Append(wxID_PASTE, wxT("Wklej\tCtrl+P"));
	wxMenu * menuView = new wxMenu();
	wxMenu * menuSettings = new wxMenu();

	// menu window
	wxMenu * menuWindow = new wxMenu();
	//menuWindow->Append()

	// menu help
	wxMenu * menuHelp = new wxMenu();
	menuHelp->Append(wxID_HELP, wxT("Pomoc\tF1"));
	menuHelp->Append(wxID_ABOUT, wxT("O programie"));

	menuBar->Append(menuFile, wxT("&Plik"));
	menuBar->Append(menuEdit, wxT("&Edycja"));
	menuBar->Append(menuView, wxT("&Widok"));
	menuBar->Append(menuSettings, wxT("&Ustawienia"));
	menuBar->Append(menuWindow, wxT("&Okno"));
	menuBar->Append(menuHelp, wxT("&Pomoc"));

	SetMenuBar(menuBar);
}

void EditorFrame::InitStatusBar()
{
	return;
}

void EditorFrame::InitSizer()
{
	panel1 = new wxPanel(this);
	sizer1 = new wxBoxSizer(wxVERTICAL);
	panel1->SetSizer(sizer1);
}

void EditorFrame::InitNotebook()
{
	notebook = new wxNotebook(panel1, NOTEBOOK);
	sizer1->Add(notebook, 1, wxEXPAND | wxALL, 5);
	File::notebook = notebook;
}

void EditorFrame::InitEditor(const wxString &path, const wxString &fname)
{
	File * newfile;
	if (path == wxEmptyString || fname == wxEmptyString)
		newfile = new File();
	else
	{
		newfile = new File(path, fname);
		notebook->SetPageText(newfile->GetId(), fname);
	}
}

File * EditorFrame::GetSelectedFile() const
{
	size_t selection = notebook->GetSelection();
	if (selection != wxNOT_FOUND)
		return File::files[selection];

	return NULL;
}

File * EditorFrame::GetFile(size_t id) const
{
	vector<File*>::iterator
		it,
		begin = File::files.begin(),
		end = File::files.end();

	while (begin < end)
	{
		it = begin + File::files.size() / 2;
		if ((*it)->GetId() < id)
			begin = it;
		else
			end = it;
	}

	return *it;
}

// events

void EditorFrame::OnNew(wxCommandEvent &event)
{
	InitEditor();
}

void EditorFrame::OnOpen(wxCommandEvent &event)
{
	wxFileDialog * dialog = new wxFileDialog(this, wxT("Otwórz plik"));
	if (dialog->ShowModal() == wxID_OK)
	{
		InitEditor(dialog->GetPath(), dialog->GetFilename());
	}
}

void EditorFrame::OnSave(wxCommandEvent &event)
{
	size_t selection = notebook->GetSelection();
	if (!File::files[selection]->IsSaved())
	{
		OnSaveAs(event);
	} else
	{
		File::files[selection]->SaveFile();
		notebook->SetPageText(selection, File::files[selection]->GetFilename());
	}
}

void EditorFrame::OnSaveAs(wxCommandEvent &event)
{
	size_t selection = notebook->GetSelection();
	wxFileDialog * dialog = new wxFileDialog(this, wxT("Zapisz jako"), wxEmptyString, wxEmptyString, wxT("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR);
	if (dialog->ShowModal() == wxID_OK)
	{
		File::files[selection]->SaveFile(dialog->GetPath(), dialog->GetFilename());
		notebook->SetPageText(selection, dialog->GetFilename());
	}
}

void EditorFrame::OnSaveAll(wxCommandEvent &event)
{
	for (vector<File*>::iterator it = File::files.begin(); it != File::files.end(); ++it)
	{
		size_t selection = (*it)->GetId();
		notebook->SetSelection(selection);
		OnSave(event);
	}
}

void EditorFrame::OnCloseFile(wxCommandEvent &event)
{
	size_t selection = notebook->GetSelection();

	if (selection == wxNOT_FOUND)
		return;

	if (File::files[selection]->IsModified())
	{
		OnSave(event);
	}
	notebook->DeletePage(selection);
}

void EditorFrame::OnCloseAll(wxCommandEvent &event)
{

}

void EditorFrame::OnUndo(wxCommandEvent &event)
{
	File * file = GetSelectedFile();
	if (file == NULL)
		return;

	file->GetTextCtrl()->Undo();
}

void EditorFrame::OnRedo(wxCommandEvent &event)
{
	File * file = GetSelectedFile();
	if (file == NULL)
		return;

	file->GetTextCtrl()->Redo();
}

void EditorFrame::OnCut(wxCommandEvent &event)
{
	File * file = GetSelectedFile();
	if (file == NULL)
		return;

	file->GetTextCtrl()->Cut();
}

void EditorFrame::OnCopy(wxCommandEvent &event)
{
	File * file = GetSelectedFile();
	if (file == NULL)
		return;

	file->GetTextCtrl()->Copy();
}

void EditorFrame::OnPaste(wxCommandEvent &event)
{
	File * file = GetSelectedFile();
	if (file == NULL)
		return;

	file->GetTextCtrl()->Paste();
}

void EditorFrame::OnExit(wxCommandEvent &event)
{
	Close();
}

void EditorFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageBox(wxT("SimpleEditor"),wxT("O programie"));
}

void EditorFrame::OnSearchFile(wxCommandEvent &event)
{

}

void EditorFrame::OnModify(wxCommandEvent &event)
{
	size_t selection = notebook->GetSelection();
	if (File::files[selection]->IsSaved() && File::files[selection]->GetTextCtrl()->IsModified())
	{
		notebook->SetPageText(selection, wxT("* ") + File::files[selection]->GetFilename());
	}
}

void EditorFrame::OnClose(wxCloseEvent &event)
{
	for (vector<File*>::iterator it = File::files.begin(); it != File::files.end(); ++it)
	{
		if ((*it)->GetTextCtrl()->IsModified())
		{
			wxMessageDialog * dialog = new wxMessageDialog(this, wxT("Nie wszystkie pliki zostały zapisane. Czy na pewno chcesz zakończyć pracę?"), wxT("Zamykanie programu"), wxYES_NO);
			if (dialog->ShowModal() == wxID_NO)
			{
				event.Veto();
				return;
			}

		}
	}
	Destroy();
}

BEGIN_EVENT_TABLE(EditorFrame, wxFrame)
	EVT_MENU(wxID_NEW, EditorFrame::OnNew)
	EVT_MENU(wxID_OPEN, EditorFrame::OnOpen)
	EVT_MENU(wxID_SAVE, EditorFrame::OnSave)
	EVT_MENU(wxID_SAVEAS, EditorFrame::OnSaveAs)
	EVT_MENU(SAVEALL, EditorFrame::OnSaveAll)
	EVT_MENU(wxID_CLOSE, EditorFrame::OnCloseFile)
	EVT_MENU(wxID_CLOSE_ALL, EditorFrame::OnCloseAll)

	EVT_MENU(wxID_UNDO, EditorFrame::OnUndo)
	EVT_MENU(wxID_REDO, EditorFrame::OnRedo)
	EVT_MENU(wxID_CUT, EditorFrame::OnCut)
	EVT_MENU(wxID_COPY, EditorFrame::OnCopy)
	EVT_MENU(wxID_PASTE, EditorFrame::OnPaste)

	EVT_MENU(wxID_ABOUT, EditorFrame::OnAbout)
	EVT_MENU(wxID_EXIT, EditorFrame::OnExit)

	EVT_TEXT(EDITORS, EditorFrame::OnModify)
	EVT_CLOSE(EditorFrame::OnClose)
END_EVENT_TABLE()
