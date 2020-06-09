//
// Created by sv.yarakaev on 09.06.2020.
//

#ifndef WINDOWAPP_MAINWINDOW_H
#define WINDOWAPP_MAINWINDOW_H

#include <gtkmm.h>
#include <gtkmm/comboboxtext.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &refGlade);


    virtual ~MainWindow();
protected:
    void on_button_quit();
    void on_button_Load();
    Glib::RefPtr<Gtk::Builder> m_refGlade;
    Gtk::Button *m_pButton;
    Gtk::ComboBoxText *m_pComboBoxIPAddr;
    Gtk::TextView *m_pViewLog;
    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer1, m_refTextBuffer2;
    Gtk::TextBuffer::iterator iter; //find my seek

    Gtk::Button *m_pbtnLoad;
};


#endif //WINDOWAPP_MAINWINDOW_H
